package app;


// Import javafx.* -> imports all subclasses, but it doesn't do it recursively
// meaning in the example below Application wouldnt been added

// An issue regarding the imports was updating the classpaths <!>
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import utility.Utility;
import utility.Dimensions;

public class MainEventHandler extends Application
{
    private DatabaseManager db;

    public static void main()
    {
        launch(); // -> starts JavaFX, then jumps to "start" function <!>
    }

    @Override
    public void init()
    {
       db = new DatabaseManager();
    }

    @Override
    public void start(Stage stage)
    {
        int screen_w = Dimensions.ScreenDimensions.LOGIN_SCREEN_WIDTH.getValue();
        int screen_h = Dimensions.ScreenDimensions.LOGIN_SCREEN_HEIGHT.getValue();

        Pane root = new Pane();
        Scene login_screen = new Scene(root, screen_w, screen_h);

        Button login_button = new Button("Log In");
        Button registartion_button = new Button("Register");

        // Dimensions
        login_button.setPrefWidth(Dimensions.ButtonDimensions.LOGIN_BUTTON_WIDTH.getValue());
        login_button.setPrefHeight(Dimensions.ButtonDimensions.LOGIN_BUTTON_HEIGHT.getValue());
        registartion_button.setPrefWidth(Dimensions.ButtonDimensions.REGISTRATION_BUTTON_WIDTH.getValue());
        registartion_button.setPrefHeight(Dimensions.ButtonDimensions.REGISTRATION_BUTTON_HEIGHT.getValue());

        // Coords
        login_button.setLayoutX(Utility.centerX(0, screen_w, (int)login_button.getPrefWidth()));
        login_button.setLayoutY(200);

        registartion_button.setLayoutX(Utility.centerX(0, screen_w, (int)registartion_button.getPrefWidth()));
        registartion_button.setLayoutY(300);

        root.getChildren().addAll(login_button, registartion_button);

        stage.setTitle("Employee-Management-System");
        stage.setScene(login_screen);
        stage.show();

    }
}