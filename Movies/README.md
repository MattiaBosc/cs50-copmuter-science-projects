# IMDb Movies Analysis

This project contains SQL queries to analyze a database of movies and people associated with them, including actors, directors, and ratings. The database (`movies.db`) includes tables for movies, people, and their roles in films.

## Database Structure

- **Movies Table:** Contains information about each movie, including:
  - `title`
  - `release_year`
  - `rating` (IMDb score)
- **People Table:** Contains information about actors and directors, including:
  - `name`
  - `birth_year`
- **Roles Table:** Contains relationships between movies and people, including:
  - `movie_id`
  - `person_id`
  - `role` (actor or director)

## SQL Queries

The repository includes the following SQL queries:

1. `1.sql` – List all movies released in 2008.
2. `2.sql` – Find the birth year of Emma Stone.
3. `3.sql` – List all movies released on or after 2018 in alphabetical order.
4. `4.sql` – Count the number of movies with a 10.0 rating.
5. `5.sql` – List titles and release years of all Harry Potter movies in chronological order.
6. `6.sql` – Find the average rating of movies released in 2012.
7. `7.sql` – List all movies released in 2010 with ratings, sorted by rating and title.
8. `8.sql` – List names of all people who starred in Toy Story.
9. `9.sql` – List names of people who starred in movies released in 2004, ordered by birth year.
10. `10.sql` – List names of all people who directed movies rated at least 9.0.
11. `11.sql` – List the titles of the five highest rated movies starring Chadwick Boseman.
12. `12.sql` – List titles of all movies featuring both Bradley Cooper and Jennifer Lawrence.
13. `13.sql` – List names of all people who starred in movies with Kevin Bacon (born 1958), excluding Kevin Bacon himself.

