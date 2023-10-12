import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    id_user = session["user_id"]

    stocks = db.execute("SELECT symbol, name, SUM(shares) AS shares, price FROM activity WHERE user_id = ? GROUP BY symbol", id_user)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", id_user)[0]

    total = cash['cash']

    for value in stocks:
        total += value['shares'] * value['price']

    return render_template("index.html", stocks=stocks, cash=cash, usd=usd, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("type a integer number of shares")

        if shares <= 0:
            return apology("type a positive number of shares")

        iduser = session["user_id"]

        money = db.execute("SELECT cash FROM users WHERE id = ?", iduser)
        cash = money[0]['cash']

        if not symbol:
            return apology("Missing symbol")
        elif not shares:
            return apology("Missing shares")

        valid_stock = lookup(symbol)

        if not valid_stock:
            return apology("Symbol not valid")

        symbol_stock = valid_stock['symbol']
        name_stock = valid_stock['name']
        price_stock = valid_stock['price']

        total = price_stock * shares

        if total > cash:
            return apology("can't afford")
        else:
            final_cash = cash - total
            db.execute("UPDATE users SET cash = ? WHERE id = ?", final_cash, iduser)
            db.execute("INSERT INTO activity (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                       iduser, name_stock, shares, price_stock, 'buy', symbol_stock)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id_user = session["user_id"]
    
    activities = db.execute("SELECT symbol, type, shares, price, time FROM activity WHERE user_id = ?", id_user)
    
    return render_template("history.html", activities=activities)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Enter a symbol please!")

        info = lookup(symbol)

        if not info:
            return apology("Symbol not valid!")

        return render_template("quoted.html", stock=info)
    else:
        return render_template("quote.html")


@app.route("/addCash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add Cash"""
    if request.method == "POST":
        id_user = session["user_id"]
        added_cash = float(request.form.get("cash"))
        previous_cash = db.execute("SELECT cash FROM users WHERE id = ?", id_user)[0]["cash"]
        print(type(added_cash))
        print(type(previous_cash))
        cash = added_cash + previous_cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, id_user)
        
        return redirect("/")
    else:
        return render_template("cash.html")
        

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Verify the request method
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide username")

        # Ensure both passwords matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords doesn't match")

        # Query database for username
        user_exist = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Verifying if the username is already taken
        if len(user_exist) != 0:
            return apology("username is already taken")

        username = request.form.get("username")
        # Hashing the password
        hash = generate_password_hash(request.form.get("password"))

        # Insert the new user on data base
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

    # GET Method
    else:
        return render_template("register.html")

    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        id_user = session["user_id"]
        
        symbol = request.form.get("symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("type a integer number of shares", 400)

        if not symbol:
            return apology("Missing symbol")
        elif not shares:
            return apology("Missing shares")
            
        stock_price = lookup(symbol)["price"]
        stock_name = lookup(symbol)["name"]
        
        previous_shares = db.execute(
            "SELECT shares FROM activity WHERE user_id = ? AND symbol = ? GROUP BY symbol", id_user, symbol)[0]['shares']
        
        if previous_shares < shares:
            return apology("not enough shares")
            
        previous_cash = db.execute("SELECT cash FROM users WHERE id = ?", id_user)[0]["cash"]
        
        sold = stock_price * shares
        
        db.execute("INSERT INTO activity (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)",
                   id_user, stock_name, -shares, stock_price, "sell", symbol)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", previous_cash + sold, id_user)       
        
        return redirect("/")
            
    else:
        id_user = session["user_id"]
        
        symbols = db.execute("SELECT symbol FROM activity WHERE user_id = ? GROUP BY symbol", id_user)
        
        return render_template("sell.html", symbols=symbols)
        
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
