import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

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

    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    username = username[0]["username"]
    total_stocks = 0

    if len(db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name= 'purchases'")) == 0:
        info = [{"symbol": "N/A", "shares": 0, "price": 0, "value": 0}]

    else:
        info = db.execute(
            "SELECT DISTINCT symbol FROM purchases WHERE user_id = ?", session["user_id"])
        if not info:
            info = [{"symbol": "N/A", "shares": 0, "price": 0, "value": 0}]
        else:
            for dict in info:
                dict["price"] = lookup(dict["symbol"])["price"]
                dict["shares"] = db.execute(
                    "SELECT SUM(shares) FROM purchases WHERE user_id = ? AND symbol = ?", session["user_id"], dict["symbol"])[0]["SUM(shares)"]

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    for dict in info:
        dict["value"] = dict["price"]*dict["shares"]
        total_stocks = total_stocks + dict["value"]

    new_info = [dict for dict in info if dict["shares"] != 0]

    grand_total = cash+total_stocks
    return render_template("index.html", username=username, info=new_info, cash=cash, total_stocks=total_stocks, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not shares:
            return apology("Symbol/Shares Required")
        else:
            try:
                shares = int(shares)
            except:
                return apology("Number of Shares not Valid")

        if shares <= 0:
            return apology("Number of Shares not Valid")
        else:
            search = lookup(symbol)
            if search == None:
                return apology("Symbol not Found")

            total_price = search["price"]*shares
            user_cash = db.execute("SELECT * FROM users WHERE id = ?",
                                   session["user_id"])[0]["cash"]
            if total_price > user_cash:
                return apology("Not Enough Cash")
            else:
                db.execute("UPDATE users SET cash = ? WHERE id = ?",
                           user_cash - total_price, session["user_id"])
                if not db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name= 'purchases'"):
                    db.execute("""
                        CREATE TABLE purchases (
                        id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL UNIQUE,
                        user_id INTEGER NOT NULL,
                        symbol TEXT NOT NULL,
                        price REAL NOT NULL,
                        shares REAL NOT NULL,
                        date DATETIME NOT NULL,
                        FOREIGN KEY(user_id) REFERENCES users(id) )
                    """)
                    db.execute("CREATE INDEX user_id_index ON purchases(user_id)")
                db.execute("INSERT INTO purchases (user_id, symbol, price, shares, date) VALUES (?, ?, ?, ?, datetime('now'))",
                           session["user_id"], symbol, search["price"], shares)
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])
    username = username[0]["username"]

    if len(db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name= 'purchases'")) == 0:
        info = [{"symbol": "N/A", "shares": 0, "price": 0, "type": "N/A", "date": "N/A"}]

    else:
        info = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
        for dict in info:
            if dict["shares"] < 0:
                dict["type"] = "Sold"
                dict["shares"] = -dict["shares"]
            else:
                dict["type"] = "Purchased"

    return render_template("history.html", username=username, info=info)


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

    if request.method == "GET":
        return render_template("quote.html")

    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Symbol Required")
        else:
            search = lookup(symbol)
            if search == None:
                return apology("Symbol not Found")
            else:
                return render_template("quoted.html", price=search["price"], symbol=search["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        Username = request.form.get("username")
        if not Username:
            return apology("Username Required")
        user = db.execute("SELECT username FROM users WHERE username = (?)", Username)
        if user:
            return apology("Username Already in Use")

        Password = request.form.get('password')
        Confirmation = request.form.get('confirmation')
        if not Password or not Confirmation:
            return apology("Password and Confirmation Required")
        if Password != Confirmation:
            return apology("Password and Confirmation do not match")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   Username, generate_password_hash(Password))
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        if len(db.execute("SELECT name FROM sqlite_master WHERE type='table' AND name= 'purchases'")) == 0:
            info = []
        else:
            info = db.execute(
                "SELECT DISTINCT symbol FROM purchases WHERE user_id = ?", session["user_id"])

        return render_template("sell.html", info=info)

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol or not shares:
            return apology("Symbol/Shares Required")

        try:
            shares = int(shares)
        except:
            return apology("Number of Shares not Valid")

        if shares <= 0:
            return apology("Number of Shares not Valid")

        info = db.execute(
            "SELECT DISTINCT symbol FROM purchases WHERE user_id = ?", session["user_id"])
        for dict in info:
            dict["shares"] = db.execute("SELECT SUM(shares) FROM purchases WHERE user_id = ? AND symbol = ?",
                                        session["user_id"], dict["symbol"])[0]["SUM(shares)"]

        number = [dict for dict in info if dict.get("symbol") == symbol][0]["shares"]
        if shares > number:
            return apology("Not Enough Shares")

        db.execute("INSERT INTO purchases (user_id, symbol, price, shares, date) VALUES (?, ?, ?, ?, datetime('now'))",
                   session["user_id"], symbol, lookup(symbol)["price"], -shares)

        earning = lookup(symbol)["price"]*shares
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", earning, session["user_id"])
        return redirect("/")


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change user's password"""

    if request.method == "GET":
        return render_template("password.html")

    else:
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        if not old_password or not new_password or not confirmation:
            return apology("Password Missing")

        if new_password != confirmation:
            return apology("Confirmation Not Matching")

        hash = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        if not check_password_hash(hash[0]["hash"], old_password):
            return apology("Invalid Old Password")

        db.execute("UPDATE users SET hash = ? WHERE id = ?",
                   generate_password_hash(new_password), session["user_id"])
        return redirect("/")
