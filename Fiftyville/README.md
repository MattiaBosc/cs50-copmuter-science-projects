# Fiftyville: The Stolen CS50 Duck

This project involves solving the mystery of the stolen CS50 Duck using SQL queries on a SQLite database (`fiftyville.db`) containing town records.

## Objective

Using the database, determine:

1. Who the thief is.
2. Which city the thief escaped to.
3. Who the thief’s accomplice is.

The theft occurred on **July 28, 2024** on **Humphrey Street**.

## Database Structure

The database contains multiple tables capturing town records around the time of the theft. Key tables include:

- **crime_scene_reports** – Records of crimes, including date and location.
- **citizens** – Details about individuals in Fiftyville.
- **flights** – Records of flights taken by citizens.
- **accomplices** – Relationships between citizens who may have helped in crimes.

> Use `.tables` in `sqlite3` to list all tables and `.schema TABLE_NAME` to inspect columns.

## Solving the Mystery

1. Start by examining the `crime_scene_reports` table for reports on July 28, 2024, on Humphrey Street.
2. Identify suspects and check any associated flights around the date of the crime.
3. Cross-reference possible accomplices using relationships stored in the database.
4. Record all SQL queries in `log.sql`. Use comments (`--`) to describe your thought process and reasoning for each query.
5. Once the thief, escape city, and accomplice are identified, complete `answers.txt` with the findings.


Follow good SQL style guidelines for readability: [sqlstyle.guide](https://sqlstyle.guide).
