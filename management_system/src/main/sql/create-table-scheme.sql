DROP TABLE IF EXISTS Employee;
DROP TABLE IF EXISTS CalendarYear;
DROP TABLE IF EXISTS OneMonth;

CREATE TABLE Employee
(
    employee_id_                SERIAL              PRIMARY KEY,
    total_hours_worked_         INTEGER             NOT NULL,
    first_name_                 VARCHAR(32)         NOT NULL,
    last_name_                  VARCHAR(32)         NOT NULL,
    username_                   VARCHAR(32)         NOT NULL,
    password_                   VARCHAR(32)         NOT NULL

);

CREATE TABLE Calendar
(
    calendar_id_                SERIAL              PRIMARY KEY,
    employee_id_                INTEGER             NOT NULL REFERENCES  Employee(employee_id_),
    year_                       INTEGER             NOT NULL,
    total_hours_worked_         INTEGER             NOT NULL,
);

CREATE TABLE Month
(
    month_id_                   SERIAL              PRIMARY KEY,
    calendar_id_                INTEGER             NOT NULL REFERENCES  Calendar(calendar_id_),
    hours_worked_               INTEGER             NOT NULL,
    month_type_                 VARCHAR(32)         NOT NULL,
);