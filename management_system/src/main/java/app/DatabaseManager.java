package app;

import java.io.File;
import java.io.FileNotFoundException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.*;


public class DatabaseManager
{
    private Connection conn;

    private enum Credentials
    {
        HOST,
        PORT,
        DBNAME,
        USER,
        PASSWORD
    };


    /* In Java Enums can directly hold strings so there is no need for enum to string dictionary <!> */
    /* In Java's PostgreSQL API, we use ? for values in query strings and not $1 like in libpq C++ */
    private enum SQLQueries
    {
        LOGIN_QUERY("SELECT * FROM Employee WHERE Employee.employee_id_ = ?; "),
        REGISTRATION_QUERY(" NOT FINISHED ");

        private final String value_;

        SQLQueries(String value)
        {
            this.value_ = value;
        }

        public String getValue()
        {
            return this.value_;
        }
    };

    public DatabaseManager()
    {
        File env = new File("../../env_/db-credentials.env");

        Dictionary<Credentials, String> credentials = new Hashtable<>();

        try(Scanner scanner = new Scanner(env))
        {
            for(Credentials iterator : Credentials.values())
            {
                credentials.put(iterator, scanner.nextLine());
            }
        }
        catch (FileNotFoundException e)
        {
            System.out.println("[DatabaseManager::DatabaseManager()] -> [ERROR] -> File error");
            // Should I terminate the process?
        }

        System.out.println("[DatabaseManager::DatabaseManager()] -> [SUCCESS] -> File opened and parsed <!> ");

        String url = "jdbc:postgresql://";
        url += credentials.get(Credentials.HOST) + ":";
        url += credentials.get(Credentials.PORT) + "/";
        url += credentials.get(Credentials.DBNAME);

        String user = credentials.get(Credentials.USER);
        String password = credentials.get(Credentials.PASSWORD);


        try
        {
            this.conn = DriverManager.getConnection(url, user, password);
        }
        catch (SQLException e)
        {
            System.out.println("[DatabaseManager::DatabaseManager()] -> [ERROR] -> Connection error");
            // Should I terminate the process?
        }

        System.out.println("[DatabaseManager::DatabaseManager()] -> [SUCCESS] -> Connected to PostgreSQL Database <!> ");
    };
}


