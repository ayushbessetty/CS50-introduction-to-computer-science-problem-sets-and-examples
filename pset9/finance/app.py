import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import pytz
from datetime import datetime

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
    stocks = db.execute("SELECT * FROM stocks WHERE id = ?", session["user_id"])
    user = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
    t = float(user[0]["cash"])
    for i in stocks:
        stock = lookup(i["symbol"])
        t += int(i["shares"]) * float(stock["price"])
        i["prices"] = usd(stock["price"])
        i["total"] = usd(int(i["shares"]) * float(stock["price"]))

    return render_template("index.html", stocks=stocks, user=usd(user[0]["cash"]), total=usd(t))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # check for stock symbol
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("Enter the correct symbol", 400)

        # check for amount of shares
        shares = request.form.get("shares")
        if not shares or not shares.isdigit() or (float(shares) <= 0):
            return apology("Enter number of shares", 400)

        # price of shares
        price = float(symbol["price"])
        cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
        cashs = float(cash[0]["cash"])
        prices = price*float(shares)
        if prices > cashs:
            return apology("Not Enough cash", 400)

        # cash left
        db.execute("UPDATE users SET cash=? WHERE id=?", (cashs - prices), int(session["user_id"]))

        # add data to buy table;
        db.execute("INSERT INTO history(id, symbol, shares, price, transcated, type) VALUES(?, ?, ?, ?, ?,'BUY')",
                   session["user_id"], symbol["symbol"], float(shares), price, datetime.now(pytz.timezone('Asia/Kolkata')))
        try:
            db.execute("INSERT INTO stocks(id, symbol, shares, price, type) VALUES(?, ?, ?, ?, 'BUY')",
                       session["user_id"], symbol["symbol"], float(shares), price)
        except ValueError:
            s = db.execute("SELECT shares FROM stocks WHERE symbol=? AND id =?",
                           symbol["symbol"], session["user_id"])
            s[0]["shares"] = float(shares) + float(s[0]["shares"])
            db.execute("UPDATE stocks SET shares=? WHERE symbol=? AND id =?",
                       symbol["symbol"], session["user_id"])

        flash("Bought!", "success")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return render_template("history.html", stocks=db.execute("SELECT * FROM history"))


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

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
    if request.method == "POST":
        symbol = lookup(request.form.get("symbol"))
        if not symbol:
            return apology("enter correct symbol")
        symbol["price"] = usd(symbol["price"])
        return render_template("quoted.html", symbol=symbol)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # username
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)
        # password
        password = request.form.get("password")
        confirm = request.form.get("confirmation")
        if not password:
            return apology("please enter correct password", 400)
        if not confirm or (password != confirm):
            return apology("please enter correct confirmation password", 400)

        hash = generate_password_hash(password)
        try:
            db.execute("INSERT INTO users(username,hash) VALUES(?,?)", username, hash)
        except ValueError:
            return apology("username already taken", 400)

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("select a symbol", 403)
        shares = request.form.get("shares")
        if not shares:
            return apology("enter amount of shares", 403)
        # present value of stock
        present_stock = lookup(symbol)
        present_price = present_stock["price"] * int(shares)

        # saved stock
        stock = db.execute("SELECT * FROM stocks WHERE symbol = ? AND id = ?",
                           symbol, session["user_id"])

        # present balance of user
        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        db.execute("INSERT INTO history(id, symbol, shares, price, transcated, type) VALUES(?, ?, ?, ?, ?, 'SELL')",
                   session["user_id"], symbol, int(shares), present_stock["price"], datetime.now(pytz.timezone('Asia/Kolkata')))

        diff = int(stock[0]["shares"]) - int(shares)
        if diff < 0:
            return apology("too much shares", 403)
        elif diff == 0:
            db.execute("DELETE FROM stocks WHERE symbol = ? AND id=?", symbol, session["user_id"])
        else:
            db.execute("UPDATE stocks SET shares = ? WHERE symbol = ? AND id=?",
                       diff, symbol, session["user_id"])

        # updating cash of user
        db.execute("UPDATE users SET cash = ? WHERE id = ?",
                   (int(balance[0]["cash"]) + present_price), session["user_id"])

        flash("sold!", "success")
        return redirect("/")

    else:
        return render_template("sell.html", symbols=db.execute("SELECT symbol,shares FROM stocks WHERE id = ?", session["user_id"]))


@app.route("/change", methods=["GET", "POST"])
@login_required
def change():
    """Register user"""
    if request.method == "POST":
        # username
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 403)
        # password
        opassword = request.form.get("old_password")
        npassword = request.form.get("new_password")
        confirm = request.form.get("confirmation")
        if not opassword:
            return apology("please enter correct present password", 403)
        if not npassword:
            return apology("please enter correct new password", 403)
        if not confirm or (npassword != confirm):
            return apology("please enter correct confirmation of new password", 403)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
                rows[0]["hash"], opassword):
            return apology("invalid username and/or password", 403)

        hash = generate_password_hash(npassword)
        db.execute("UPDATE users SET hash = ? WHERE username = ? AND id=?",
                   hash, username, session["user_id"])
        return redirect("/login")

    else:
        return render_template("change.html")


@app.route("/cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """add cash to account"""
    if request.method == "POST":
        add = float(request.form.get("add"))
        if not add:
            return apology("must provide amount", 403)
        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        db.execute("UPDATE users SET cash = ? WHERE id =?",
                   (add + float(balance[0]["cash"])), session["user_id"])

        flash("Amount Added", "success")
        return redirect("/")

    else:
        return render_template("cash.html")
