package app;

import java.util.ArrayList;
import java.util.List;

import lombok.*;

@Data
public class Employee
{
    private final String first_name_;
    private final String last_name_;
    private final int id_;

    private List<Calendar> calendars_;
    private Calendar calendar_in_use_;
    private Integer total_hours_ever_;

    private Boolean currently_employed_;

    // Login Path
    Employee(String loaded_first_name, String loaded_last_name, int loaded_employee_id, List<Calendar> calendars)
    {
        this.first_name_ = loaded_first_name;
        this.last_name_ = loaded_last_name;
        this.id_ = loaded_employee_id;

        this.calendars_ = calendars;
        // this.calendar_in_use_ = this.calendars_.get(0);

    }

    // Registration Path
    Employee(String first_name, String last_name, Integer id)
    {
        this.first_name_ = first_name;
        this.last_name_ = last_name;
        this.id_ = id;
        this.total_hours_ever_ = 0;

        Calendar year_one = new Calendar(2026);
        Calendar year_two = new Calendar(2027);
        Calendar year_three = new Calendar(2028);


        this.calendars_ = new ArrayList<>();
        this.calendars_.addAll(List.of(year_one, year_two, year_three));
        this.calendar_in_use_ = this.calendars_.get(0);
    }


    // Now I have to represent somehow a full calendar year and each month within it should
    // have certain amount of days




}