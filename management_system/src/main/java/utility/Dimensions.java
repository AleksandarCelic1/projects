package utility;

public class Dimensions
{
    public enum ButtonDimensions
    {
        AUTH_LOGIN_BUTTON_WIDTH(200),
        AUTH_LOGIN_BUTTON_HEIGHT(50),
        AUTH_REGISTRATION_BUTTON_WIDTH(200),
        AUTH_REGISTRATION_BUTTON_HEIGHT(50),
        LOGIN_RETURN_BUTTON_WIDTH(50),
        LOGIN_RETURN_BUTTON_HEIGHT(50);

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

    public enum TextFieldDimensions
    {
        LOGIN_USERNAME_TXT_WIDTH(200),
        LOGIN_USERNAME_TXT_HEIGHT(50),
        LOGIN_PASSWORD_TXT_WIDTH(200),
        LOGIN_PASSWORD_TXT_HEIGHT(50);

        private final int value_;

        TextFieldDimensions(int value)
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
        AUTH_SCREEN_WIDTH(600),
        AUTH_SCREEN_HEIGHT(800),
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
