package utility;

public class Utility
{
    public static int centerX(int background_x, int background_w, int object_width)
    {
        return background_x + (background_w / 2) - (object_width / 2);
    }

    public static int centerY(int background_y, int background_h, int object_height)
    {
        return background_y + (background_h / 2) - (object_height / 2);
    }
}
