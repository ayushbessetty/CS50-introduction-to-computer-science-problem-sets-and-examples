from flask import Flask, render_template, request       # request gives parameter from user input, render_template open html page and send from server to browser

app = Flask(__name__)                    # variable app, the Flask function converts to web application referred by app


@app.route("/", methods=["GET", "POST"])                  # decorator when the  user choses the path(route)  / --> (TLD), EXECUTE THE BELOW FUNCTION
def index():
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name"))
    else:
        return render_template("index.html")                                        # file in same page
                                                     #request.args (dictionaries) store key value pairs
# check jinja.palletsprojects.com/templates/
                                                    # FOR GET = request.args
                                                    # FOR POST = request.form

