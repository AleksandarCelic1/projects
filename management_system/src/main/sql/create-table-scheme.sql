DROP TABLE IF EXISTS Employer;
DROP TABLE IF EXISTS Employee;
DROP TABLE IF EXISTS CalendarYear;
DROP TABLE IF EXISTS OneMonth;


CREATE TABLE Employer
(
    employer_id_                SERIAL              PRIMARY KEY,
    first_name_                 VARCHAR(32)         NOT NULL,
    last_name_                  VARCHAR(32)         NOT NULL
);


CREATE TABLE Employee
(
    employee_id_                SERIAL              PRIMARY KEY,
    employer_id_                INTEGER             NOT NULL REFERENCES Employer(employer_id_),
    first_name_                 VARCHAR(32)         NOT NULL,
    last_name_                  VARCHAR(32)         NOT NULL,

);

CREATE TABLE CalendarYear
(
    calendar_id_ SERIAL PRIMARY KEY,
);

CREATE TABLE OneMonth
(
    month_id_       SERIAL            PRIMARY KEY,
    calendar_id_    SERIAL            NOT NULL REFERENCES  CalendarYear(calendar_id_),
    name_           VARCHAR(16)       NOT NULL,
);