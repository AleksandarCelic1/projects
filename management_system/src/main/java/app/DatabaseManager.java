package app;

import java.io.File;
import java.io.FileNotFoundException;
import java.sql.*;
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
    public enum SQLQueries
    {
        LOGIN_QUERY("SELECT * FROM Employee WHERE Employee.username_ = ? AND Employee.password_ = ?; ", 2),
        REGISTRATION_QUERY("INSERT INTO Employee (first_name_, last_name_, username_, password_) " +
                                    "VALUES (?, ?, ?, ?) RETURNING Employee.employee_id_; ", 4),

        GETTER_CALENDAR_QUERY("SELECT * From Calendar WHERE Calendar.employee_id = ?; ", 1);

        private final String sql_string_;
        private final Integer argc_;

        SQLQueries(String sql_string, Integer argc)
        {
            this.sql_string_ = sql_string;
            this.argc_ = argc;
        }

        public String getSQLString()
        {
            return this.sql_string_;
        }

        public Integer getArgc()
        {
            return this.argc_;
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

    public ResultSet execute(SQLQueries query, List<String> args)
    {
        String sql_string = query.getSQLString();
        Integer argc = query.getArgc();

        if(argc != args.size())
        {
            System.out.println("[DatabaseManager::execute] -> [ERROR] -> SQLQuery argc and args size dont match <!> ");
            return null;
        }

        try
        {
            PreparedStatement statement = conn.prepareStatement(sql_string);

            for(int index = 1; index <= argc; index++)
            {
                statement.setString(index, args.get(index));
            }

            ResultSet result = statement.executeQuery();
            return result;


        }
        catch(SQLException exception)
        {
            System.out.println("[DatabaseManager::execute] -> [ERROR] -> conn.prepareStatement failed <!> ");
            return null;
        }
    }

    public Employee executeLogin(SQLQueries query, List<String> args)
    {
        ResultSet placeholder = execute(query, args);

        if(placeholder == null)
        {
            /* The error occurred is already explained in "execute" function <!> */
            return null;
        }

        try
        {
            if(placeholder.next())
            {
                // Query success <!> you are logged in <!>
                // We should create the Employee object here <!>


                String loaded_first_name = placeholder.getString("first_name_");
                String loaded_last_name = placeholder.getString("last_name_");
                int loaded_employee_id = placeholder.getInt("employee_id_");

                return new Employee(loaded_first_name, loaded_last_name, loaded_employee_id);
            }
            else
            {
                return null;
            }
        }
        catch(SQLException exception)
        {
            System.out.println("[DatabaseManager::executeLogin] -> [CAUGHT] -> Exception caught <!> ");
            return null;
        }
    }

    public Employee executeRegistration(SQLQueries query, List<String> args)
    {
      // Args come in this order -> FirstName -> LastName -> Username -> Password <!>
      // Args are essentially always in the SQL variable order

        String first_name = args.get(0);
        String last_name = args.get(1);
        String username = args.get(2);
        String password = args.get(3);

        List<String> login_args = new ArrayList<>();
        login_args.add(username);
        login_args.add(password);

        Employee employee = executeLogin(SQLQueries.LOGIN_QUERY, login_args);
        if(employee != null)
        {
          System.out.println("[DatabaseManager::executeRegistration] -> [ERROR] -> Can not make an account that already exists <!> ");
          return null;
        }


        ResultSet result = execute(query, args);
        if(result == null)
        {
          /* Failed in execute already <!> */
          return null;
        }

        try
        {
          if(result.next())
          {
            // Query success <!> you are logged in <!>
            // We should create the Employee object here <!>

            int loaded_employee_id = result.getInt("employee_id_");
            return new Employee(first_name, last_name, loaded_employee_id);
          }
          else
          {
            return null;
          }
        }
        catch(SQLException exception)
        {
          System.out.println("[DatabaseManager::executeLogin] -> [CAUGHT] -> Exception caught <!> ");
          return null;
        }
    }
}


