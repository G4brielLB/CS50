-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Descriptions
SELECT description FROM crime_scene_reports
WHERE day == 28 AND month == 7 and street == "Chamberlin Street";

-- Interviews
SELECT name, transcript FROM interviews
WHERE month == 7 AND day == 28 AND year == 2020;

-- Flights 
SELECT * FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE city LIKE "%Fiftyville%"
AND day == 29 AND month == 7 AND year == 2020 ORDER BY hour;

SELECT city FROM airports WHERE id == "4";

-- License Plate
SELECT name FROM people WHERE license_plate
IN (SELECT license_plate FROM courthouse_security_logs
WHERE month == 7 AND day == 28 AND hour == 10
AND minute > 15 AND minute < 30 AND activity = "exit");

-- Passport Number
SELECT name FROM people WHERE passport_number
IN (SELECT passport_number FROM passengers WHERE flight_id == 36);

-- Bank Accounts
SELECT name FROM people JOIN bank_accounts
ON people.id = bank_accounts.person_id WHERE account_number
IN (SELECT account_number FROM atm_transactions
WHERE day == 28 AND month == 7 AND atm_location = "Fifer Street"
AND transaction_type = "withdraw");

-- Phone Calls
SELECT name FROM people WHERE phone_number
IN (SELECT caller FROM phone_calls
WHERE day == 28 AND month == 7 AND year == 2020 AND duration < 60);

SELECT phone_number FROM people WHERE name == "Ernest";

SELECT name FROM people WHERE phone_number
IN (SELECT receiver FROM phone_calls
WHERE caller = "(367) 555-5533" AND day == 28 AND month = 7 AND duration < 60);