import os
from cs50 import SQL
from flask import Flask, jsonify, redirect, render_template, request, session

# configure application
app = Flask(__name__)

# ensure templates are auto-reloaded
# app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 library to use sqlite db
db = SQL("sqlite:///birthdays.db")

#@app.after_request
#def after_request(response):
  #  """ensure responses aren't cached"""
   # response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    #response.headers["Expires"] = 0
    #response.headers["Pragma"] = "no-cache"
    #return response

@app.route("/", methods = ["GET", "POST"])
def index():
    if request.method == "POST":
        # add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if not month or not day or not name:
            return redirect("/")

        db.execute("INSERT INTO birthdays(name, month, day) VALUES(?, ?, ?)", name, month, day)

        return redirect("/")
    else:
        # display the entries in db
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)
