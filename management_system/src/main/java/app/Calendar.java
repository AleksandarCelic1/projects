package app;

import java.util.ArrayList;
import java.util.List;
import lombok.Data;

@Data
public class Calendar
{
    private final Integer year_;
    private final Integer id_;
    private Integer total_hours_worked_;
    private List<Month> months_;
    private Month current_month_;

    Calendar(int year)
    {
        this.year_ = year;
        this.total_hours_worked_ = 0;
        this.months_ = new ArrayList<>();

        for(Month.MonthType iterator : Month.MonthType.values())
        {
            if((iterator == Month.MonthType.FEBRUARY) && (this.year_ % 4 == 0))
            {
                months_.add(new Month(Month.MonthType.FEBRUARY_LEAP));
                continue;
            }

            months_.add(new Month(iterator));
        }

        this.current_month_ = months_.get(0);
    }

    Calendar(int loaded_calendar_id, int loaded_year, int loaded_total_hours_worked , List<Month> loaded_months)
    {
        this.id_ = loaded_calendar_id;
        this.year_ = loaded_year;
        this.total_hours_worked_ = loaded_total_hours_worked;
        this.months_ = loaded_months;
        this.current_month_ = this.months_.get(0);
    }
}


