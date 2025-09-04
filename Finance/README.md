# C$50 Finance Web Application

C$50 Finance is a web application that allows users to “buy” and “sell” stocks, as well as manage a virtual portfolio similarly to a stock broker.

## Purpose

- Allow users to register and manage an account.
- Look up the current price of stocks by their symbol.
- Buy and sell stocks using virtual money.
- View a complete history of all transactions.
- Display a portfolio summary showing cash balance and total value of owned stocks.

## Implementation

### Backend

- Built with Python and Flask.
- Uses a SQLite database (`finance.db`) with `users` and stock transaction tables.
- Main functions:
  - **register**: Create an account securely with username and password.
  - **login/logout**: Handle user authentication.
  - **quote**: Look up a stock’s current price using the `lookup` function.
  - **buy/sell**: Allows buying or selling stocks, checking available cash and share quantities.
  - **index**: Displays the user's portfolio summary.
  - **history**: Displays a full history of purchases and sales for the user.
- Security:
  - Passwords stored as hashes.
  - Server-side data validation to prevent errors or SQL injection.

### Frontend

- Jinja templates render dynamic HTML.
- `layout.html` includes a responsive navbar using Bootstrap.
- Forms allow user interaction (registration, login, buying/selling stocks, checking quotes).
- Custom CSS styles in `static/styles.css`.

### Database

- The `users` table contains `id`, `username`, `hash` (password), and `cash`.
- Stock transactions store `user_id`, `symbol`, `shares`, `price`, and `timestamp`.
- Supports aggregated queries and summaries using `GROUP BY`, `SUM`, and `WHERE` filters.


