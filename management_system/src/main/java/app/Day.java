package app;

import javafx.scene.control.DatePicker;

import java.time.DayOfWeek;
import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.temporal.TemporalAmount;
import java.util.Date;

public class Day
{
    private final DayOfWeek type_;
    private final LocalDate date_;
    private final Double time_worked_;


    // Control Path for creating initially Day objects.
    Day(LocalDate date, LocalTime started_work, LocalTime ended_work)
    {
        this.date_ = date;
        this.type_ = this.date_.getDayOfWeek();

        Long calculated_minutes = calculateTimeWorked(started_work, ended_work);

        int hours = calculated_minutes.intValue() / 60;
        int minutes = calculated_minutes.intValue() % 60;

        this.time_worked_ = hours + (minutes / 60.0);


    }

    // Control Path for loading Day objects from DB.
    Day(DayOfWeek loaded_type, LocalDate loaded_date, Double time_worked_)
    {
        this.type_ = loaded_type;
        this.date_ = loaded_date;
        this.time_worked_ = time_worked_;
    }

    private Long calculateTimeWorked(LocalTime start, LocalTime end)
    {
        Duration duration = Duration.between(start, end).abs();
        return duration.toMinutes();
    }
}
