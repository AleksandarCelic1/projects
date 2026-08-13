package app;


// Import javafx.* -> imports all subclasses, but it doesn't do it recursively
// meaning in the example below Application wouldn't been added

// An issue regarding the imports was updating the classpaths <!>
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.util.HashMap;
import java.util.Map;

import utility.Utility;
import utility.Dimensions;


public class MainEventHandler extends Application
{
    public enum Screens
    {
        AUTHENTICATION_SCREEN,
        LOGIN_SCREEN,
        REGISTRATION_SCREEN,
        HOME_SCREEN
    }

    /*
        Names are composed of Screen + Button Name,
        so LOGIN LOGIN Button stands for LOGIN screen
        and it represents LOGIN button
    */
    public enum Buttons
    {
        AUTH_LOGIN_BUTTON,
        AUTH_REGISTRATION_BUTTON,
        LOGIN_LOGIN_BUTTON,
        LOGIN_RETURN_BUTTON

    }

    public enum TextFields
    {
        LOGIN_USERNAME_TXT_PLACEHOLDER,
        LOGIN_PASSWORD_TXT_PLACEHOLDER,
    }

    private DatabaseManager db;
    private Map<Screens, Scene> scenes_;
    private Map<Buttons, Button> buttons_;
    private Map<TextFields, TextField> text_placeholders_;

    /* There is no need for another map that maps Pane's because we can retrieve it from Scenes <!> */

    public static void main()
    {
        launch(); // -> starts JavaFX, then jumps to "start" function <!>
    }

    @Override
    public void init()
    {
        db = new DatabaseManager();
        scenes_ = new HashMap<>();
        buttons_ = new HashMap<>();
        text_placeholders_ = new HashMap<>();

        // Initial Authentication Screen <!>
        initAuthScene();
        initLoginScene();

    }

    @Override
    public void start(Stage stage)
    {
        Scene auth = this.scenes_.get(Screens.AUTHENTICATION_SCREEN);
        stage.setTitle("Employee-Management-System");
        stage.setScene(auth);


        handleClickAuthScreen(stage);
        handleClickLoginScreen(stage);

        stage.show();

    }


    private void initAuthScene()
    {
        // Auth <!>
        int auth_screen_w = Dimensions.ScreenDimensions.AUTH_SCREEN_WIDTH.getValue();
        int auth_screen_h = Dimensions.ScreenDimensions.AUTH_SCREEN_HEIGHT.getValue();

        Pane auth_root = new Pane();
        Scene auth = new Scene(auth_root,
                Dimensions.ScreenDimensions.AUTH_SCREEN_WIDTH.getValue(),
                Dimensions.ScreenDimensions.AUTH_SCREEN_HEIGHT.getValue());

        Button login_button = new Button("Log In");
        Button registration_button = new Button("Register");

        // Dimensions
        login_button.setPrefWidth(Dimensions.ButtonDimensions.AUTH_LOGIN_BUTTON_WIDTH.getValue());
        login_button.setPrefHeight(Dimensions.ButtonDimensions.AUTH_LOGIN_BUTTON_HEIGHT.getValue());
        registration_button.setPrefWidth(Dimensions.ButtonDimensions.AUTH_REGISTRATION_BUTTON_WIDTH.getValue());
        registration_button.setPrefHeight(Dimensions.ButtonDimensions.AUTH_REGISTRATION_BUTTON_HEIGHT.getValue());

        // Coords
        login_button.setLayoutX(Utility.centerX(0, auth_screen_w, (int)login_button.getPrefWidth()));
        login_button.setLayoutY(200);

        registration_button.setLayoutX(Utility.centerX(0, auth_screen_w, (int)registration_button.getPrefWidth()));
        registration_button.setLayoutY(300);

        // Add elements to canvas <!>
        auth_root.getChildren().addAll(login_button, registration_button);

        this.scenes_.put(Screens.AUTHENTICATION_SCREEN, auth);
        this.buttons_.put(Buttons.AUTH_LOGIN_BUTTON, login_button);
        this.buttons_.put(Buttons.AUTH_REGISTRATION_BUTTON, registration_button);

    }

    public void initLoginScene()
    {
        // Login Screen

        int login_screen_w = Dimensions.ScreenDimensions.LOGIN_SCREEN_WIDTH.getValue();
        int login_screen_h = Dimensions.ScreenDimensions.LOGIN_SCREEN_HEIGHT.getValue();

        Pane root = new Pane();
        Scene login_screen = new Scene(root, login_screen_w, login_screen_h);

        TextField username = new TextField("Enter Username: ");
        TextField password = new TextField("Enter Password: ");

        Button login_button = new Button("Log In");
        Button return_button = new Button("<");

        // Dimensions
        username.setPrefWidth(Dimensions.TextFieldDimensions.LOGIN_USERNAME_TXT_WIDTH.getValue());
        username.setPrefHeight(Dimensions.TextFieldDimensions.LOGIN_USERNAME_TXT_HEIGHT.getValue());

        password.setPrefWidth(Dimensions.TextFieldDimensions.LOGIN_PASSWORD_TXT_WIDTH.getValue());
        password.setPrefHeight(Dimensions.TextFieldDimensions.LOGIN_PASSWORD_TXT_HEIGHT.getValue());

        login_button.setPrefWidth(Dimensions.ButtonDimensions.AUTH_LOGIN_BUTTON_WIDTH.getValue());
        login_button.setPrefHeight(Dimensions.ButtonDimensions.AUTH_LOGIN_BUTTON_HEIGHT.getValue());

        return_button.setPrefWidth(Dimensions.ButtonDimensions.LOGIN_RETURN_BUTTON_WIDTH.getValue());
        return_button.setPrefHeight(Dimensions.ButtonDimensions.LOGIN_RETURN_BUTTON_HEIGHT.getValue());


        // Coords
        username.setLayoutX(Utility.centerX(0, login_screen_w, (int)username.getPrefWidth()));
        username.setLayoutY(200);

        password.setLayoutX(Utility.centerX(0, login_screen_w, (int)password.getPrefWidth()));
        password.setLayoutY(300);

        login_button.setLayoutX(Utility.centerX(0, login_screen_w, (int)login_button.getPrefWidth()));
        login_button.setLayoutY(400);

        return_button.setLayoutX(20);
        return_button.setLayoutY(20);


        // Add elements to canvas <!>
        root.getChildren().addAll(username, password, login_button, return_button);

        this.scenes_.put(Screens.LOGIN_SCREEN, login_screen);
        this.text_placeholders_.put(TextFields.LOGIN_USERNAME_TXT_PLACEHOLDER, username);
        this.text_placeholders_.put(TextFields.LOGIN_PASSWORD_TXT_PLACEHOLDER, password);
        this.buttons_.put(Buttons.LOGIN_LOGIN_BUTTON, login_button);
        this.buttons_.put(Buttons.LOGIN_RETURN_BUTTON, return_button);


    }

    public void handleClickAuthScreen(Stage stage)
    {
        Button login_button = this.buttons_.get(Buttons.AUTH_LOGIN_BUTTON);
        Button registration_button = this.buttons_.get(Buttons.AUTH_REGISTRATION_BUTTON);

        login_button.setOnAction( event -> {
            stage.setScene(this.scenes_.get(Screens.LOGIN_SCREEN));
        });

        registration_button.setOnAction( event -> {
            // Make a registration Screen than you can access it <!>
        });
    }

    public void  handleClickLoginScreen(Stage stage)
    {
        Button login_button = this.buttons_.get(Buttons.LOGIN_LOGIN_BUTTON);
        Button return_button = this.buttons_.get(Buttons.LOGIN_RETURN_BUTTON);
        TextField username_placeholder = this.text_placeholders_.get(TextFields.LOGIN_USERNAME_TXT_PLACEHOLDER);
        TextField password_placeholder = this.text_placeholders_.get(TextFields.LOGIN_PASSWORD_TXT_PLACEHOLDER);

        login_button.setOnAction( event ->
        {
            String username = username_placeholder.getText();
            String password = password_placeholder.getText();

            System.out.println("[INFORMATION] -> Username: " + username + ", Password: " + password);

        });

        return_button.setOnAction( event ->
        {
            stage.setScene(this.scenes_.get(Screens.AUTHENTICATION_SCREEN));
        });
    }
}