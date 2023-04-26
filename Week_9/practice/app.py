from flask import Flask, render_template, request


app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template('index.html')
    elif request.method == "POST":
        """ request.form for POST requests """
        """ request.args for GET requests """
        name = request.form.get("name","World")
        return render_template('greet.html', name=name)

""" @app.route("/greet", methods=["POST"])
def greet():
    name = request.args.get("name", "World")
    return render_template('greet.html', name=name) """

