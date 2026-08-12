package utility;

public class Dimensions
{
    public enum ButtonDimensions
    {
        LOGIN_BUTTON_WIDTH(200),
        LOGIN_BUTTON_HEIGHT(50),
        REGISTRATION_BUTTON_WIDTH(200),
        REGISTRATION_BUTTON_HEIGHT(50);

        private final int value_;

        ButtonDimensions(int value)
        {
            this.value_ = value;
        }

        public int getValue()
        {
            return this.value_;
        }
    }


    public enum ScreenDimensions
    {
        LOGIN_SCREEN_WIDTH(600),
        LOGIN_SCREEN_HEIGHT(800);

        private final int value_;

        ScreenDimensions(int value)
        {
            this.value_ = value;
        }

        public int getValue()
        {
            return this.value_;
        }
    }
}
