# Spotify Songs Analysis

This project contains SQL queries to analyze a dataset of the 100 most-streamed songs on Spotify in 2018. The database (`songs.db`) contains information about songs and artists, including attributes like danceability, energy, tempo, valence, and duration.

## Database Structure

- **Artists Table:** Each artist has an `id` and a `name`.
- **Songs Table:** Each song has a `name`, `artist_id` (linking to the artist), and attributes including:
  - `danceability`
  - `energy`
  - `key`
  - `loudness`
  - `speechiness`
  - `valence`
  - `tempo`
  - `duration` (in milliseconds)

## SQL Queries

The repository includes the following SQL queries:

1. `1.sql` – Lists all song names.
2. `2.sql` – Lists all song names in increasing order of tempo.
3. `3.sql` – Lists the top 5 longest songs in descending order of duration.
4. `4.sql` – Lists songs with danceability, energy, and valence all greater than 0.75.
5. `5.sql` – Returns the average energy of all songs.
6. `6.sql` – Lists the names of songs by Post Malone.
7. `7.sql` – Returns the average energy of songs by Drake.
8. `8.sql` – Lists songs that feature other artists (contain "feat." in the song name).

