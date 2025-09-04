# Birthdays Web Application

This project is a web application that allows users to keep track of friends’ birthdays using Python, Flask, and SQLite.

## Objective

- Build a web application that displays and stores birthdays.
- Allow users to add new birthdays via a web form.
- Display all stored birthdays in a table format on the main page.

## Implementation

### Backend

- Built using Python and Flask.
- The application has one main route (`/`) that handles both GET and POST requests:
  - **GET requests**: Queries the database for all birthdays and renders them in `index.html`.
  - **POST requests**: Inserts a new birthday into the database and redirects back to the main page.

### Database

- `birthdays.db` is a SQLite database.
- Contains a single table, `birthdays`, with columns: `id`, `name`, `month`, `day`.
- Supports inserting new rows with user-submitted birthdays.

### Frontend

- `index.html` template renders the birthdays in a table.
- Includes an HTML form that lets users submit a name, month, and day for a birthday.
- Submitted data is sent to the server via POST request to add to the database.

### CSS

- Styles are handled in `static/styles.css` to make the table and form visually appealing.

