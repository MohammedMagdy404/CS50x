-- Keep a log of any SQL queries you execute as you solve the mystery.

-- tables in the database
SELECT name 
  FROM sqlite_master
 where type = 'table';
 
-- crime_scene_report table
SELECT sql 
  FROM sqlite_master
 where name = 'crime_scene_reports';
-- interviews table
SELECT sql 
  FROM sqlite_master
 where name = 'interviews';
-- atm_transactions table
SELECT sql 
  FROM sqlite_master
 where name = 'atm_transactions';
-- bank_accounts table
SELECT sql 
  FROM sqlite_master
 where name = 'bank_accounts';
-- airports table
SELECT sql 
  FROM sqlite_master
 where name = 'airports';
-- flights table
SELECT sql 
  FROM sqlite_master
 where name = 'flights';
-- passengers table
SELECT sql 
  FROM sqlite_master
 where name = 'passengers';
-- phone_calls table
SELECT sql 
  FROM sqlite_master
 where name = 'phone_calls';
-- people table
SELECT sql 
  FROM sqlite_master
 where name = 'people';
-- bakery_security_logs table
SELECT sql 
  FROM sqlite_master
 where name = 'bakery_security_logs';


-- select the crime data from crime_scene_report table
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street' AND description LIKE "%duck%";

-- select the crime data from interviews table
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND (transcript LIKE "%Humphrey%" OR transcript LIKE "%bakery%");

-- the data from every interviewer
-- first: within ten minutes of the theft, a car in the bakery parking lot and drive away.
SELECT bakery_security_logs.activity, bakery_security_logs.license_plate, people.name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25;

-- second: I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money
SELECT atm_transactions.transaction_type, people.name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.transaction_type = "withdraw";

-- third: called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on 
-- the other end of the phone to purchase the flight ticket.


/* ALTER TABLE phone_calls
ADD COLUMN caller_name text;

ALTER TABLE phone_calls
ADD COLUMN receiver_name text; */


UPDATE phone_calls
SET caller_name = people.name
FROM people
WHERE phone_calls.caller = people.phone_number;

UPDATE phone_calls
SET receiver_name = people.name
FROM people
WHERE phone_calls.receiver = people.phone_number;

SELECT caller, caller_name, receiver, receiver_name FROM phone_calls
WHERE month = 7 
AND day = 28
AND duration <= 60; 


UPDATE flights
SET origin_airport_id = airports.city
FROM airports
WHERE flights.origin_airport_id = airports.id;

UPDATE flights
SET destination_airport_id = airports.city
FROM airports
WHERE flights.destination_airport_id = airports.id;

SELECT id, hour, minute, origin_airport_id, destination_airport_id FROM flights
WHERE month = 7 AND day = 29
ORDER BY hour ASC
LIMIT 1;


/* SELECT flights.destination_airport_id, name, phone_number,
license_plate FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE flights.id = 36
ORDER BY flights.hour ASC; */

-- select exactly the name of the criminal from the ubove data
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON flights.id = passengers.flight_id
WHERE month = 7 
AND day = 29
AND flights.id = 36
AND name IN (SELECT phone_calls.caller_name FROM phone_calls
WHERE month = 7 
AND day = 28
AND duration <= 60)
AND name IN (SELECT people.name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2021
AND atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.atm_location = "Leggett Street"
AND atm_transactions.transaction_type = "withdraw")
AND name IN (SELECT people.name FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021
AND bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute >= 15
AND bakery_security_logs.minute <= 25)