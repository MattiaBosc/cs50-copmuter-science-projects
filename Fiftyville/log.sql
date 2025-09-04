-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Select relevant crime scene reports
SELECT * FROM crime_scene_reports WHERE year =  2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Select relevant interviews
SELECT * FROM interviews WHERE year =  2023 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Select relevant bakery security logs
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;

-- Select relevant atm transactions
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Select relevant phone calls
SELECT * FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;

-- Select passengers on relevant flight out of Fiftyville
SELECT * FROM passengers WHERE flight_id IN
(SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2023 AND month = 7 AND day = 29 AND city = 'Fiftyville' ORDER BY hour LIMIT 1);

-- Select people that carried out the above relevant transctions and phone calls,
-- whose license plate was seen leaving the bakery, and is a passenger on
-- relevant flight out of Fiftyville AKA the thief!
SELECT * FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))
INTERSECT
SELECT * FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25)
INTERSECT
SELECT * FROM people WHERE phone_number IN
(SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60)
INTERSECT
SELECT * FROM people WHERE passport_number IN
(SELECT passport_number FROM passengers WHERE flight_id IN
(SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2023 AND month = 7 AND day = 29 AND city = 'Fiftyville' ORDER BY hour LIMIT 1));

-- Select city the thief escaped to
SELECT * FROM airports WHERE id IN
(SELECT destination_airport_id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE year = 2023 AND month = 7 AND day = 29 AND city = 'Fiftyville' ORDER BY hour LIMIT 1);

-- Accomplice
SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE caller IN
(SELECT phone_number FROM people WHERE name = 'Bruce')
AND year = 2023 AND month = 7 AND day = 28 AND duration < 60);
