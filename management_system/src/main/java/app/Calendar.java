package app;

import java.util.ArrayList;
import java.util.List;

public class Calendar
{
    private final int year_;
    private int total_hours_worked_;
    private List<Month> months_;

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
    }

    Calendar(int loaded_year, int loaded_total_hours_worked , List<Month> loaded_months)
    {
        this.year_ = loaded_year;
        this.total_hours_worked_ = loaded_total_hours_worked;
        this.months_ = loaded_months;
    }
}


