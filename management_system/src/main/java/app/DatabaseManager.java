package app;

import java.io.File;
import java.io.FileNotFoundException;
import java.nio.charset.StandardCharsets;
import java.sql.*;
import java.time.DayOfWeek;
import java.time.LocalDate;
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
        LOGIN_QUERY(            "SELECT * FROM Employee WHERE username_ = ? AND password_ = ?;", 2),
        REGISTRATION_QUERY(     "INSERT INTO Employee (total_hours_worked_, first_name_, last_name_, username_, password_) " +
                                         "VALUES (?, ?, ?, ?, ?) RETURNING employee_id_;", 5),

        GETTER_CALENDAR_QUERY(  "SELECT * FROM Calendar WHERE employee_id_ = ?;", 1),
        GETTER_MONTHS_QUERY(    "SELECT * FROM Months WHERE calendar_id_ = ?;", 1),
        GETTER_DAYS_QUERY(      "SELECT * FROM Day WHERE month_id_ = ?;", 1);

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
        File env = new File("src/main/env_/db-credentials.env");

        Dictionary<Credentials, String> credentials = new Hashtable<>();

        try(Scanner scanner = new Scanner(env))
        {
            for(Credentials iterator : Credentials.values())
            {
                String tmp = scanner.nextLine();
                StringBuilder cred = new StringBuilder();

                boolean start_taking = false;

                for(int index = 0; index < tmp.length(); index++)
                {
                    char placeholder = tmp.charAt(index);

                    if(start_taking)
                    {
                        cred.append(placeholder);
                    }

                    if(placeholder == '=')
                    {
                        start_taking = true;
                    }
                }
                credentials.put(iterator, cred.toString());

            }
        }
        catch (FileNotFoundException e)
        {
            System.out.println("[DatabaseManager::DatabaseManager()] -> [ERROR] -> File error");
            // Should I terminate the process?
        }

        System.out.println("[DatabaseManager::DatabaseManager()] -> [SUCCESS] -> File opened and parsed <!> ");

        StringBuilder url = new StringBuilder();
        url.append("jdbc:postgresql://");
        url.append(credentials.get(Credentials.HOST) + ":");
        url.append(credentials.get(Credentials.PORT) + "/");
        url.append(credentials.get(Credentials.DBNAME));

        System.out.println(url);

        String user = credentials.get(Credentials.USER);
        String password = credentials.get(Credentials.PASSWORD);

        try
        {
            this.conn = DriverManager.getConnection(url.toString(), user, password);
        }
        catch (SQLException e)
        {
            System.out.println("[DatabaseManager::DatabaseManager()] -> [ERROR] -> Connection error");
            e.printStackTrace();
        }

        System.out.println("[DatabaseManager::DatabaseManager()] -> [SUCCESS] -> Connected to PostgreSQL Database <!> ");
    };

    public ResultSet execute(SQLQueries query, List<Object> args)
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

            for(int index = 0; index < argc; index++)
            {
                statement.setObject(index + 1, args.get(index));
            }

            ResultSet result = statement.executeQuery();
            return result;


        }
        catch(SQLException exception)
        {
            System.out.println("[DatabaseManager::execute] -> [ERROR] -> conn.prepareStatement failed <!> ");
            exception.printStackTrace();
            return null;
        }
    }

    public Employee executeLogin(SQLQueries query, List<Object> args)
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


                List<Calendar> loaded_calendars = executeCalendarGetter(SQLQueries.GETTER_CALENDAR_QUERY, List.of(loaded_employee_id));
                if(loaded_calendars == null)
                {
                    System.out.println("[DatabaseManager::executeLogin] -> [ERROR] -> Getter Calendar failed, stoping Login Request");
                    return null;
                }

                return new Employee(loaded_first_name, loaded_last_name, loaded_employee_id, loaded_calendars);
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

    public Employee executeRegistration(SQLQueries query, List<Object> args)
    {
      // Args come in this order -> FirstName -> LastName -> Username -> Password <!>
      // Args are essentially always in the SQL variable order

        Integer total_hours = (Integer) args.get(0);
        String first_name = (String) args.get(1);
        String last_name = (String) args.get(2);
        String username = (String) args.get(3);
        String password = (String) args.get(4);

        List<Object> login_args = new ArrayList<>();
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

    private List<Calendar> executeCalendarGetter(SQLQueries query, List<Object> args)
    {
        ResultSet placeholder = execute(query, args);

        if(placeholder == null)
        {
            /* Execute already explains why did the query fail <!> */
            return null;
        }


        List<Calendar> loaded_calendars = new ArrayList<>();

        try
        {
            while(placeholder.next())
            {
                Integer loaded_calendar_id        =     placeholder.getInt("calendar_id_");
                Integer loaded_year               =     placeholder.getInt("year_");
                Integer loaded_total_hours_worked =     placeholder.getInt("total_hours_worked_");

                // Need to Call executeMonthGetter <!>

                List<Month> loaded_months = executeMonthGetter(SQLQueries.GETTER_MONTHS_QUERY, List.of(loaded_calendar_id));
                if(loaded_months == null)
                {
                    System.out.println("[DatabaseManager::executeCalendarGetter] -> [ERROR] -> Month Getter failed, Calendar Getter is stopped <!> ");
                    return null;
                }

                Calendar tmp = new Calendar(loaded_year, loaded_total_hours_worked, loaded_months);
                loaded_calendars.add(tmp);

            }

        }
        catch (SQLException e)
        {
            System.out.println("[DatabaseManager::executeCalendarGetter] -> [ERROR] -> Exception Caught <!> ");
            e.printStackTrace();
            return null;
        }


        return loaded_calendars;
    }

    private List<Month> executeMonthGetter(SQLQueries query, List<Object> args)
    {
        ResultSet placeholder = execute(query, args);

        if(placeholder == null)
        {
            /* Execute already explains why did the query fail <!> */
            return null;
        }

        // here you need to get a list of months for each calendar call <!>
        // then for each month you take you need to take the DAY, becasue each month is constructed of list of days <!>

        List<Month> loaded_months = new ArrayList<>();

        try
        {
            while(placeholder.next())
            {
                Integer loaded_month_id         =       placeholder.getInt("month_id_");
                Integer loaded_hours_worked     =       placeholder.getInt("hours_worked_");
                String  loaded_month_type       =       placeholder.getString("month_type_");


                // This can get converted later in Month CTOR <!>

                List<Day> loaded_days = executeDaysGetter(SQLQueries.GETTER_DAYS_QUERY, List.of(loaded_month_id));
                if(loaded_days == null)
                {
                    System.out.println("[DatabaseManager::executeCalendarGetter] -> [ERROR] -> Day Getter failed, Month Getter is stopped <!> ");
                    return null;
                }

                Month tmp = new Month(loaded_month_type, loaded_days, loaded_hours_worked);
                loaded_months.add(tmp);
            }
        }
        catch (SQLException e)
        {
            System.out.println("[DatabaseManager::executeMonthGetter] -> [ERROR] -> Exception Caught <!> ");
            e.printStackTrace();
            return null;
        }


        return loaded_months;
    }


    private List<Day> executeDaysGetter(SQLQueries query, List<Object> args)
    {
        ResultSet placeholder = execute(query, args);

        if(placeholder == null)
        {
            /* Execute already explains why did the query fail <!> */
            return null;
        }


        List<Day> loaded_days = new ArrayList<>();

        try
        {
            while(placeholder.next())
            {
                Integer   loaded_time_worked = placeholder.getInt("time_worked_");
                LocalDate loaded_date = placeholder.getObject("date_", LocalDate.class);
                DayOfWeek loaded_day_type = DayOfWeek.valueOf(placeholder.getString("type_"));

                Day tmp = new Day(loaded_day_type, loaded_date, loaded_time_worked);
                if(tmp == null)
                {
                    System.out.println("[DatabaseManager::executeDaysGetter] -> [ERROR] -> Day Creation failed, Day Getter is stopped <!> ");
                    return null;
                }

                loaded_days.add(tmp);

            }
        }
        catch (SQLException e)
        {
            System.out.println("[DatabaseManager::executeDaysGetter] -> [ERROR] -> Exception Caught <!> ");
            e.printStackTrace();
        }

        return loaded_days;
    }
}


