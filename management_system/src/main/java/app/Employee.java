package app;

import java.util.List;

public class Employee
{
    private final String first_name_;
    private final String last_name_;
    private final int id_;

    private List<Calendar> current_decade_;
    private Calendar calendar_in_use_;

    Employee(String loaded_first_name, String loaded_last_name, int loaded_employee_id)
    {
        this.first_name_ = loaded_first_name;
        this.last_name_ = loaded_last_name;
        this.id_ = loaded_employee_id;

    }

    // Now I have to represent somehow a full calendar year and each month within it should
    // have certain amount of days




}