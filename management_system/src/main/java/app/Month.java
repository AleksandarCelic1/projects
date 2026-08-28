package app;

import lombok.Data;

import java.util.ArrayList;
import java.util.List;

@Data
public class Month
{
    public enum MonthType
    {
        JANUARY(31),
        FEBRUARY(28),
        FEBRUARY_LEAP(29),
        MARCH(31),
        APRIL(30),
        MAY(31),
        JUNE(30),
        JULY(31),
        AUGUST(31),
        SEPTEMBER(30),
        OCTOBER(31),
        NOVEMBER(30),
        DECEMBER(31);

        private final int amount_of_days_;

        MonthType(int new_amount_of_days)
        {
            this.amount_of_days_ = new_amount_of_days;
        }

        int getAmountOfDays()
        {
            return this.amount_of_days_;
        }
    }

    private final MonthType type_;
    private final List<Day> days_;
    private final Integer total_hours_this_month_;

    Month(MonthType type)
    {
        this.type_ = type;
        this.total_hours_this_month_ = 0;

        this.days_ = new ArrayList<>();
        for(int index = 0; index < this.type_.getAmountOfDays(); index++)
        {
            // This Day CTOR is tmp
            this.days_.add(index, new Day());
        }
    }

    // Need one CTOR for loading from DB
}
