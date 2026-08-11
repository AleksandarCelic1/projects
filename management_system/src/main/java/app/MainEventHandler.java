package app;


// Import javafx.* -> imports all subclasses, but it doesn't do it recursively
// meaning in the example below Application wouldnt been added

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class MainEventHandler extends Application
{
    private DatabaseManager db;

    public static void main(String[] args)
    {

    }

    @Override
    public void init()
    {
       db = new DatabaseManager();
    }

    @Override
    public void start(Stage stage)
    {

    }
}