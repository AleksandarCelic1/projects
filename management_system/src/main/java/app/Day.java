package app;

import javafx.scene.control.DatePicker;

import java.time.DayOfWeek;
import java.time.LocalDate;
import java.util.Date;

public class Day
{
    private final DayOfWeek type_;
    private final LocalDate date_;
    private final Integer time_worked_;


    // Control Path for creating initially Day objects.
    Day(DatePicker picker, Integer started_work, Integer ended_work)
    {
        this.date_ = picker.getValue();
        this.type_ = this.date_.getDayOfWeek();
        this.time_worked_ = calculateTimeWorked(started_work, ended_work);
    }

    // Control Path for loading Day objects from DB.
    Day(DayOfWeek loaded_type, LocalDate loaded_date, Integer time_worked_)
    {
        this.type_ = loaded_type;
        this.date_ = loaded_date;
        this.time_worked_ = time_worked_;
    }

    private Integer calculateTimeWorked(Integer start, Integer end)
    {
        /* Yet to be implemented <!> */
        return 0;
    }



}
