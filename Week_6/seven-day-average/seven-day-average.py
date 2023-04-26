import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)
    # print(reader.line_num)
    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)
    # print(new_cases)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        for i in new_cases:
            if state == i["state"]:
                states.append(state)
                break
        if len(state) == 0:
            break

    # print(states)
    # print(new_cases)

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new = []
    # print(new)
    c = 14
    for row in reader:
        if c < 0:
            break

        prevCases = row["cases"]
        for j in new:
            if (row["state"] == j["state"]):
                prevCases = int(prevCases) - int(j["cases"])
                # j["cases"] = row['cases']

        new.append(dict(state=row['state'], cases=prevCases))
        # print(dict(state= row['state'], cases = row['cases']))
        # print(c)
        c -= 1

    return new


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    # print(states)
    global dec_inc
    for state in states:
        # print(state)
        sumb = 0
        suma = 0
        for i in new_cases[0:7]:
            if state == i["state"]:
                sumb += int(i["cases"])
        for i in new_cases[7:14]:
            if state == i["state"]:
                suma += int(i["cases"])

        try:
            dec_inc = (suma - sumb)/suma
        except ZeroDivisionError:
            ...
        dec_inc = 0
        momo = "increase"
        if (dec_inc < 0):
            momo = "decrease"
        elif (dec_inc == 0):
            momo = "stable"
        print(f"{state} had a 7-day average of {sumb/7} and a {momo} of {dec_inc}%.")


main()
