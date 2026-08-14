package app;

public class Day
{
    public enum DayType
    {
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    }

    private final DayType type_;

    Day() { this.type_ = DayType.MONDAY; }

    Day(DayType type)
    {
        this.type_ = type;
    }


}
