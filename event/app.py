from cs50 import SQL
from flask import Flask, render_template, request

app = Flask("__name__")

db = SQL("sqlite:///event.db")

SPORTS = [
    "basketball",
    "soccer",
    "football",
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message=" Missing name")
    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message="Missing sport")
    elif sport not in SPORTS:
        return render_template("error.html", message="Invalid sports")

    db.execute("INSERT INTO event (name, sport) VALUES(?, ?)", name, sport)

    return render_template("success.html")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT name, sport FROM event")
    return render_template("registrants.html", registrants=registrants)

   # if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        # return render_template("failure.html")
