import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    transactions_db = db.execute(
        "SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING SUM(shares) > 0", user_id=user_id)
    cash_db = db.execute(
        "SELECT cash FROM users WHERE id = :user_id", user_id=user_id)
    cash = cash_db[0]["cash"]

    return render_template("index.html", transactions=transactions_db, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")
        if not shares:
            return apology("must provide shares")

        quote = lookup(symbol.upper())

        if not quote:
            return apology("invalid symbol")
        if not shares.isdigit():
            return apology("invalid shares")
        shares = int(shares)
        if shares <= 0:
            return apology("invalid shares")

        rows = db.execute(
            "SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        cash = rows[0]["cash"]
        price = quote["price"]
        total = price * shares
        if cash < total:
            return apology("not enough cash")

        date = datetime.datetime.now()
        db.execute("UPDATE users SET cash = cash - :total WHERE id = :id",
                   total=total, id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (:user_id, :symbol, :shares, :price, :date)",
                   user_id=session["user_id"], symbol=symbol.upper(), shares=shares, price=price, date=date)
        # return jsonify(rows)
        # flash() function view sign on the top of the page
        flash("Bought!")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions_db = db.execute(
        "SELECT symbol, shares, price, date FROM transactions WHERE user_id = :user_id", user_id=user_id)
    return render_template("history.html", transactions=transactions_db)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol")
        quote = lookup(symbol.upper())
        if not quote:
            return apology("invalid symbol")
        return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=quote["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("Username required")
        if not password:
            return apology("password required")
        if not confirmation:
            return apology("Conconfirmation required")

        if username == "" or username in db.execute("SELECT username FROM users"):
            return apology("Username already exist")
        if password == "" or password != confirmation:
            return apology("Password not match")
        try:

            name = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                              username=username, hash=generate_password_hash(password))
            # to enter the acount once the user is registered not need to login
        except:
            return apology("Username already exist")
        session["user_id"] = name
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbols_db = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=user_id)
        return render_template("sell.html", symbols=[row["symbol"] for row in symbols_db])
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")
        if not shares:
            return apology("must provide shares")

        quote = lookup(symbol.upper())

        if quote == None:
            return apology("invalid symbol")
        if shares.isdigit() <= 0:
            return apology("invalid shares")

        shares = int(shares)
        if shares < 0:
            return apology("invalid shares")

        user_id = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)

        cash = rows[0]["cash"]
        price = quote["price"]
        total = price * shares

        user_shares = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id = :user_id AND symbol = :symbol GROUP BY symbol",
                                 user_id=session["user_id"], symbol=symbol.upper())
        user_shares_real = user_shares[0]["SUM(shares)"]
        if shares > user_shares_real:
            return apology("not enough shares")

        uptd_cash = cash + total

        db.execute("UPDATE users SET cash = :total WHERE id = :id",
                   total=uptd_cash, id=session["user_id"])

        date = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (:user_id, :symbol, :shares, :price, :date)",
                   user_id=session["user_id"], symbol=symbol.upper(), shares=(-1)*shares, price=price, date=date)

        flash("Sold!")
        return redirect("/")


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Add cash to account"""
    if request.method == "GET":
        return render_template("addcash.html")
    else:
        cash = request.form.get("cash")
        if not cash:
            return apology("must provide cash")
        if not cash.isdigit():
            return apology("invalid cash")
        cash = int(cash)
        if cash <= 0:
            return apology("invalid cash")
        db.execute("UPDATE users SET cash = cash + :cash WHERE id = :id",
                   cash=cash, id=session["user_id"])
        flash("Cash added!")
        return redirect("/")
