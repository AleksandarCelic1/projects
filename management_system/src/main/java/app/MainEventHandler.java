package app;


// Import javafx.* -> imports all subclasses, but it doesn't do it recursively
// meaning in the example below Application wouldn't been added

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Separator;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
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
        LOGIN_RETURN_BUTTON,
        REGISTRATION_REGISTER_BUTTON,
        REGISTRATION_RETURN_BUTTON,
        HOME_RETURN_BUTTON,
        HOME_PLUS_BUTTON
    }

    public enum TextFields
    {
        LOGIN_USERNAME_TXT_PLACEHOLDER,
        LOGIN_PASSWORD_TXT_PLACEHOLDER,
        REGISTER_FIRST_NAME_TXT_PLACEHOLDER,
        REGISTER_LAST_NAME_TXT_PLACEHOLDER,
        REGISTRATION_USERNAME_TXT_PLACEHOLDER,
        REGISTRATION_PASSWORD_TXT_PLACEHOLDER,
        REGISTRATION_PASSWORD_CONFIRMATION_TXT_PLACEHOLDER
    }

    public enum Texts
    {
        HOME_SCREEN_INTRODUCTION_TEXT,
        HOME_SCREEN_STATS
    }

    private DatabaseManager db;
    private Employee account_;
    private Map<Screens, Scene> scenes_;
    private Map<Buttons, Button> buttons_;
    private Map<TextFields, TextField> text_placeholders_;
    private Map<Texts, Text> texts_;


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
        texts_ = new HashMap<>();
        account_ = new Employee("John", "Doe", -1);

        // Initial Authentication Screen <!>
        initAuthScene();
        initLoginScene();
        initRegistrationScene();
        initHomeScene();

    }

    @Override
    public void start(Stage stage)
    {
        Scene auth = this.scenes_.get(Screens.AUTHENTICATION_SCREEN);
        stage.setTitle("Employee-Management-System");
        stage.setScene(auth);


        handleClickAuthScreen(stage);
        handleClickLoginScreen(stage);
        handleClickRegistrationScreen(stage);
        handleClickHomeScreen(stage);
        // Handle also click for closure
        // So we can execute a save
        // and then let the user exit <!>

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

    private void initLoginScene()
    {
        // Login Screen

        int login_screen_w = Dimensions.ScreenDimensions.LOGIN_SCREEN_WIDTH.getValue();
        int login_screen_h = Dimensions.ScreenDimensions.LOGIN_SCREEN_HEIGHT.getValue();

        Pane root = new Pane();
        Scene login_screen = new Scene(root, login_screen_w, login_screen_h);

        TextField username = new TextField("Enter Username: ");
        TextField password = new TextField("Enter Password: ");

        Button login_button = new Button("Log In");
        Button return_button = new Button("←");

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

    private void initRegistrationScene()
    {
        Pane registration_root = new Pane();
        int reg_screen_w = Dimensions.ScreenDimensions.REGISTRATION_SCREEN_WIDTH.getValue();
        int reg_screen_h = Dimensions.ScreenDimensions.REGISTRATION_SCREEN_HEIGHT.getValue();

        Scene registration_screen = new Scene(registration_root, reg_screen_w, reg_screen_h);

        // Creation

        Button return_button = new Button("←");
        Button register_button = new Button("Register");

        TextField first_name = new TextField("First Name: ");
        TextField last_name = new TextField("Last Name: ");

        TextField username = new TextField("New Username: ");
        TextField password = new TextField("New Password: ");
        TextField password_confirmation = new TextField("Confirm Password: ");

        // PasswordField password = new PasswordField();
        // with this we'd have to change UI
        // lets make it functional and the make it prettier <!>

        // Dimensions
        return_button.setPrefWidth(Dimensions.ButtonDimensions.REGISTRATION_RETURN_BUTTON_WIDTH.getValue());
        return_button.setPrefHeight(Dimensions.ButtonDimensions.REGISTRATION_RETURN_BUTTON_HEIGHT.getValue());

        register_button.setPrefWidth(Dimensions.ButtonDimensions.REGISTRATION_REGISTER_BUTTON_WIDTH.getValue());
        register_button.setPrefHeight(Dimensions.ButtonDimensions.REGISTRATION_REGISTER_BUTTON_HEIGHT.getValue());

        first_name.setPrefWidth(Dimensions.TextFieldDimensions.REGISTER_FIRST_NAME_TXT_WIDTH.getValue());
        first_name.setPrefHeight(Dimensions.TextFieldDimensions.REGISTER_FIRST_NAME_TXT_HEIGHT.getValue());

        last_name.setPrefWidth(Dimensions.TextFieldDimensions.REGISTER_LAST_NAME_TXT_WIDTH.getValue());
        last_name.setPrefHeight(Dimensions.TextFieldDimensions.REGISTER_LAST_NAME_TXT_HEIGHT.getValue());

        username.setPrefWidth(Dimensions.TextFieldDimensions.REGISTER_USERNAME_TXT_WIDTH.getValue());
        username.setPrefHeight(Dimensions.TextFieldDimensions.REGISTER_USERNAME_TXT_HEIGHT.getValue());

        password.setPrefWidth(Dimensions.TextFieldDimensions.REGISTER_PASSWORD_TXT_WIDTH.getValue());
        password.setPrefHeight(Dimensions.TextFieldDimensions.REGISTER_PASSWORD_TXT_HEIGHT.getValue());

        password_confirmation.setPrefWidth(Dimensions.TextFieldDimensions.REGISTER_PASSWORD_CONFIRMATION_TXT_WIDTH.getValue());
        password_confirmation.setPrefHeight(Dimensions.TextFieldDimensions.REGISTER_PASSWORD_CONFIRMATION_TXT_HEIGHT.getValue());

        // Coords -> Make an enum for this <!>
        return_button.setLayoutX(20);
        return_button.setLayoutY(20);

        register_button.setLayoutX(Utility.centerX(0, reg_screen_w, (int)register_button.getPrefWidth()));
        register_button.setLayoutY(475);

        password_confirmation.setLayoutX(Utility.centerX(0, reg_screen_w, (int)password_confirmation.getPrefWidth()));
        password_confirmation.setLayoutY(400);

        password.setLayoutX(Utility.centerX(0, reg_screen_w, (int)password.getPrefWidth()));
        password.setLayoutY(325);

        username.setLayoutX(Utility.centerX(0, reg_screen_w, (int)username.getPrefWidth()));
        username.setLayoutY(250);

        last_name.setLayoutX(Utility.centerX(0, reg_screen_w, (int)last_name.getPrefWidth()));
        last_name.setLayoutY(175);

        first_name.setLayoutX(Utility.centerX(0, reg_screen_w, (int)first_name.getPrefWidth()));
        first_name.setLayoutY(100);

        // Adding Elements <!>

        registration_root.getChildren().addAll(return_button, register_button, username, password, password_confirmation, first_name, last_name);

        this.scenes_.put(Screens.REGISTRATION_SCREEN, registration_screen);
        this.buttons_.put(Buttons.REGISTRATION_RETURN_BUTTON, return_button);
        this.buttons_.put(Buttons.REGISTRATION_REGISTER_BUTTON, register_button);
        this.text_placeholders_.put(TextFields.REGISTER_FIRST_NAME_TXT_PLACEHOLDER, first_name);
        this.text_placeholders_.put(TextFields.REGISTER_LAST_NAME_TXT_PLACEHOLDER, last_name);
        this.text_placeholders_.put(TextFields.REGISTRATION_USERNAME_TXT_PLACEHOLDER, username);
        this.text_placeholders_.put(TextFields.REGISTRATION_PASSWORD_TXT_PLACEHOLDER, password);
        this.text_placeholders_.put(TextFields.REGISTRATION_PASSWORD_CONFIRMATION_TXT_PLACEHOLDER, password_confirmation);

    }

    private void initHomeScene()
    {

        // Found some inspiration for home design <>

        Pane root = new Pane();

        int home_screen_w = Dimensions.ScreenDimensions.HOME_SCREEN_WIDTH.getValue();
        int home_screen_h = Dimensions.ScreenDimensions.HOME_SCREEN_HEIGHT.getValue();
        Scene home_screen = new Scene(root, home_screen_w, home_screen_h);


        // Creation

        Button return_button = new Button("←");
        Button plus_button = new Button("+");
        Text introduction_text = new Text("Hello, " + account_.getFirst_name_() + "!");
        Text stats_text = new Text("Stats:");
        Text actual_stats = new Text(
                "• Total Hours Worked: " + account_.getTotal_hours_ever_().toString() + "\n" +
                "• Total Hours worked this year: " + account_.getCalendar_in_use_().getTotal_hours_worked_().toString() + "\n" +
                "• Total Hours worked this month: " + account_.getCalendar_in_use_().getCurrent_month_().getTotal_hours_this_month_().toString() + "\n"
        );


        // Dimensions

        return_button.setPrefWidth(Dimensions.ButtonDimensions.HOME_RETURN_BUTTON_WIDTH.getValue());
        return_button.setPrefHeight(Dimensions.ButtonDimensions.HOME_RETURN_BUTTON_HEIGHT.getValue());

        plus_button.setPrefWidth(Dimensions.ButtonDimensions.HOME_PLUS_BUTTON_WIDTH.getValue());
        plus_button.setPrefHeight(Dimensions.ButtonDimensions.HOME_PLUS_BUTTON_HEIGHT.getValue());

        introduction_text.setFont(Font.font("Arial", FontWeight.BOLD, 42));
        stats_text.setFont(Font.font("Arial", FontWeight.NORMAL, 22));
        actual_stats.setFont(Font.font("Arial", FontWeight.NORMAL, 18));

        // Coords

        return_button.setLayoutX(20);
        return_button.setLayoutY(20);

        plus_button.setLayoutX(Utility.centerX(0, home_screen_w, (int)plus_button.getPrefWidth()));
        plus_button.setLayoutY(350);

        introduction_text.setLayoutX(Utility.centerX(0, home_screen_w, (int)introduction_text.getLayoutBounds().getWidth()));
        introduction_text.setLayoutY(150);
        introduction_text.setTextAlignment(TextAlignment.CENTER);

        stats_text.setLayoutX(20);
        stats_text.setLayoutY(200);
        stats_text.setTextAlignment(TextAlignment.LEFT);

        actual_stats.setLayoutX(20);
        actual_stats.setLayoutY(250);
        actual_stats.setTextAlignment(TextAlignment.LEFT);


        // Adding elements

        root.getChildren().addAll(return_button, plus_button, introduction_text, stats_text, actual_stats);

        this.scenes_.put(Screens.HOME_SCREEN, home_screen);
        this.buttons_.put(Buttons.HOME_RETURN_BUTTON, return_button);
        this.buttons_.put(Buttons.HOME_PLUS_BUTTON, plus_button);
        this.texts_.put(Texts.HOME_SCREEN_INTRODUCTION_TEXT, introduction_text);
        this.texts_.put(Texts.HOME_SCREEN_STATS, actual_stats);

    }

    private void handleClickAuthScreen(Stage stage)
    {
        Button login_button = this.buttons_.get(Buttons.AUTH_LOGIN_BUTTON);
        Button registration_button = this.buttons_.get(Buttons.AUTH_REGISTRATION_BUTTON);

        login_button.setOnAction( event -> {
            stage.setScene(this.scenes_.get(Screens.LOGIN_SCREEN));
        });

        registration_button.setOnAction( event -> {
            stage.setScene(this.scenes_.get(Screens.REGISTRATION_SCREEN));
        });
    }

    private void handleClickLoginScreen(Stage stage)
    {
        Button login_button = this.buttons_.get(Buttons.LOGIN_LOGIN_BUTTON);
        Button return_button = this.buttons_.get(Buttons.LOGIN_RETURN_BUTTON);
        TextField username_placeholder = this.text_placeholders_.get(TextFields.LOGIN_USERNAME_TXT_PLACEHOLDER);
        TextField password_placeholder = this.text_placeholders_.get(TextFields.LOGIN_PASSWORD_TXT_PLACEHOLDER);

        login_button.setOnAction( event ->
        {
            String username = username_placeholder.getText();
            String password = password_placeholder.getText();

            List<Object> args = new ArrayList<>();
            args.add(username);
            args.add(password);


            System.out.println("[INFORMATION] -> Username: " + username + ", Password: " + password);

            Employee employee = db.executeLogin(DatabaseManager.SQLQueries.LOGIN_QUERY, args);
            if(employee != null)
            {
                this.account_ = employee;
                updateHomeScreen();
                stage.setScene(this.scenes_.get(Screens.HOME_SCREEN));

            }
        });

        return_button.setOnAction( event ->
        {
            stage.setScene(this.scenes_.get(Screens.AUTHENTICATION_SCREEN));
        });
    }

    private void handleClickRegistrationScreen(Stage stage)
    {
        Button return_button = this.buttons_.get(Buttons.REGISTRATION_RETURN_BUTTON);
        Button register_button = this.buttons_.get(Buttons.REGISTRATION_REGISTER_BUTTON);

        TextField first_name_placeholder = this.text_placeholders_.get(TextFields.REGISTER_FIRST_NAME_TXT_PLACEHOLDER);
        TextField last_name_placeholder = this.text_placeholders_.get(TextFields.REGISTER_LAST_NAME_TXT_PLACEHOLDER);
        TextField username_placeholder = this.text_placeholders_.get(TextFields.REGISTRATION_USERNAME_TXT_PLACEHOLDER);
        TextField password_placeholder = this.text_placeholders_.get(TextFields.REGISTRATION_PASSWORD_TXT_PLACEHOLDER);
        TextField password_confirmation_placeholder = this.text_placeholders_.get(TextFields.REGISTRATION_PASSWORD_CONFIRMATION_TXT_PLACEHOLDER);

        return_button.setOnAction(event ->
        {
            stage.setScene(this.scenes_.get(Screens.AUTHENTICATION_SCREEN));
        });

        register_button.setOnAction(event ->
        {

            /* Think about if it's needed to introduce some constraints regarding input <!>  */
            Integer hours = 0;
            String first_name = first_name_placeholder.getText();
            String last_name = last_name_placeholder.getText();
            String username = username_placeholder.getText();
            String password = password_placeholder.getText();
            String password_confirmation = password_confirmation_placeholder.getText();

            if(password.equals(password_confirmation))
            {
                List<Object> args = new ArrayList<>();
                args.add(hours);
                args.add(first_name);
                args.add(last_name);
                args.add(username);
                args.add(password);

                Employee new_employee = db.executeRegistration(DatabaseManager.SQLQueries.REGISTRATION_QUERY, args);
                if(new_employee != null)
                {
                  this.account_ = new_employee;
                  this.updateHomeScreen();
                  stage.setScene(this.scenes_.get(Screens.HOME_SCREEN));

                  System.out.println("[INFORMATION] -> Registration attempt successful <!> ");
                  return;
                }

                System.out.println("[MainEventHandler::handleClickRegistrationScreen] -> [INFORMATION] -> Registration failed <!> ");
                return;
            }
        });
    }

    private void handleClickHomeScreen(Stage stage)
    {
        Button return_button = this.buttons_.get(Buttons.HOME_RETURN_BUTTON);
        Button plus_button = this.buttons_.get(Buttons.HOME_PLUS_BUTTON);

        return_button.setOnAction(event ->
        {
            stage.setScene(this.scenes_.get(Screens.AUTHENTICATION_SCREEN));
        });

        plus_button.setOnAction(event ->
        {
            // Not yet implemented <!>
        });
    }


    private void updateHomeScreen()
    {
        Text introduction = this.texts_.get(Texts.HOME_SCREEN_INTRODUCTION_TEXT);
        Text stats = this.texts_.get(Texts.HOME_SCREEN_STATS);

        introduction.setText(
                "Hello, " + account_.getFirst_name_() + "!"
        );

        stats.setText(
                "• Total Hours Worked: " + account_.getTotal_hours_ever_().toString() + "\n" +
                "• Total Hours worked this year: " + account_.getCalendar_in_use_().getTotal_hours_worked_().toString() + "\n" +
                "• Total Hours worked this month: " + account_.getCalendar_in_use_().getCurrent_month_().getTotal_hours_this_month_().toString() + "\n"
        );
    }



}