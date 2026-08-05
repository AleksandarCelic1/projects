package app;

import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.ServerSocket;
import java.nio.charset.StandardCharsets;

public class P2PChat
{
  private static final int PORT = 9999;

  public static void main(String[] args)
  {
    // System.in is bytes -> InputStreamReader converts them into chars -> BufferedReader is essentially fgets <!>
    try(BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8)))
    {
      System.out.println("===== Welcome to P2P Chat =====");
      System.out.println("Host or Join? (h/j)");
      System.out.print("> ");

      String choice = keyboard.readLine();
      Socket socket = null;

      while(!choice.equals("h") && !choice.equals("j"))
      {
        System.out.println("Invalid choice. Try 'h' or 'j'");
        System.out.print("> ");
        choice = keyboard.readLine();
      }

      if(choice.equals("h"))
      {
        socket = host();
      }
      else
      {
        socket = join(keyboard);
      }

      messanger(socket, keyboard);

    }
    catch (IOException exception)
    {
      System.err.println(exception.getMessage());
    }
  }


  public static Socket host() throws IOException
  {
    try(ServerSocket serverSocket = new ServerSocket(PORT))
    {
      // accept() -> waits here until someone joins this port <!>
      Socket socket = serverSocket.accept();

      System.out.println("Connected to " + socket.getInetAddress().getHostAddress());
      return socket;
    }
  }

  public static Socket join(BufferedReader keyboard) throws IOException
  {
    System.out.println("Enter the host device's LAN IP address: ");
    String host = keyboard.readLine();

    Socket socket = new Socket(host, PORT);

    System.out.println("Connected to " + socket.getInetAddress().getHostAddress());

    return socket;
  }


  public static void messanger(Socket socket, BufferedReader keyboard) throws IOException
  {
    try
    (
      socket;

      // Messages coming from another device <!> -> reading from another stream e.g. NOT stdio
      BufferedReader networkInput = new BufferedReader(new InputStreamReader(socket.getInputStream(), StandardCharsets.UTF_8));

      // Messages being sent to another device <!> -> using C brain this sends strings to a different stream e.g. NOT stdio
      PrintWriter networkOutput = new PrintWriter(socket.getOutputStream(), true, StandardCharsets.UTF_8);
    )
    {
      Thread threadReceiver = new Thread ( () -> receiveMessage(networkInput));
      threadReceiver.setDaemon(true);
      threadReceiver.start();

      System.out.println("Chat is enabled, feel free to chit chat!");
      System.out.print("> ");
      String message;

      while((message = keyboard.readLine()) != null)
      {
        networkOutput.println(message);

        if(message.equals("exit"))
        {
          break;
        }

        System.out.print("> ");
      }
    }


  }

  public static void receiveMessage(BufferedReader networkInput)
  {
    String received_message = "";
    try
    {
      while ((received_message = networkInput.readLine()) != null) {
        System.out.println("Received Message: " + received_message);
        System.out.print("> ");
      }
    }
    catch (IOException exception)
    {
      System.err.println(exception.getMessage());
    }
  }
}
