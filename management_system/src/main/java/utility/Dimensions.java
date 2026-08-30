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
        LOGIN_RETURN_BUTTON_HEIGHT(20),

        REGISTRATION_RETURN_BUTTON_WIDTH(50),
        REGISTRATION_RETURN_BUTTON_HEIGHT(20),
        REGISTRATION_REGISTER_BUTTON_WIDTH(200),
        REGISTRATION_REGISTER_BUTTON_HEIGHT(50),

        HOME_RETURN_BUTTON_WIDTH(50),
        HOME_RETURN_BUTTON_HEIGHT(20),
        HOME_PLUS_BUTTON_WIDTH(200),
        HOME_PLUS_BUTTON_HEIGHT(50),

        WORK_SESSION_RETURN_BUTTON_WIDTH(50),
        WORK_SESSION_RETURN_BUTTON_HEIGHT(200),
        WORK_SESSION_SAVE_BUTTON_WIDTH(200),
        WORK_SESSION_SAVE_BUTTON_HEIGHT(200);

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
        LOGIN_PASSWORD_TXT_HEIGHT(50),

        REGISTER_FIRST_NAME_TXT_WIDTH(200),
        REGISTER_FIRST_NAME_TXT_HEIGHT(50),
        REGISTER_LAST_NAME_TXT_WIDTH(200),
        REGISTER_LAST_NAME_TXT_HEIGHT(50),
        REGISTER_USERNAME_TXT_WIDTH(200),
        REGISTER_USERNAME_TXT_HEIGHT(50),
        REGISTER_PASSWORD_TXT_WIDTH(200),
        REGISTER_PASSWORD_TXT_HEIGHT(50),
        REGISTER_PASSWORD_CONFIRMATION_TXT_WIDTH(200),
        REGISTER_PASSWORD_CONFIRMATION_TXT_HEIGHT(50);

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

    public enum SpinnerDimensions
    {
        WORK_SESSION_SPINNER_WIDTH(200),
        WORK_SESSION_SPINNER_HEIGHT(50);

        private final int value_;

        SpinnerDimensions(int value)
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
        LOGIN_SCREEN_HEIGHT(800),
        REGISTRATION_SCREEN_WIDTH(600),
        REGISTRATION_SCREEN_HEIGHT(800),
        HOME_SCREEN_WIDTH(600),
        HOME_SCREEN_HEIGHT(800),
        WORK_SESSION_WIDTH(600),
        WORK_SESSION_HEIGHT(800);

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
