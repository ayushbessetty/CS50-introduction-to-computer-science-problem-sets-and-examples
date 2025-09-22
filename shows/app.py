from cs50 import SQL
from flask import Flask, render_template, request, jsonify, session, redirect
from flask_session import Session

app = Flask(__name__)

db = SQL("sqlite:///store.db")

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():
    query = request.args.get("q")
    if query:
        books = db.execute("SELECT * FROM books WHERE title LIKE ?", "%" + query + "%")
    else:
        books=[]
    return jsonify(books)

@app.route("/book")
def book():
    book = request.args.get("book")
    if not book:
        books = db.execute("SELECT * FROM books")
    else:
        books = db.execute("SELECT * FROM books WHERE title LIKE ?", "%"+book+"%")
    return render_template("books.html", books=books)

@app.route("/cart", methods=["GET","POST"])
def cart():

    if "cart" not in session:
        session["cart"] = []

    if request.method == "POST":
        book_id = request.form.get("id")
        if book_id:
            session["cart"].append(book_id)
        return redirect("/cart")

    books = db.execute("SELECT * FROM books WHERE id IN (?)", session["cart"])
    return render_template("cart.html", books=books)
