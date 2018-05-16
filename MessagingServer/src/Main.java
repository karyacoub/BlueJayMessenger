import javax.websocket.DeploymentException;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        org.glassfish.tyrus.server.Server server = new org.glassfish.tyrus.server.Server("localhost", 8025, "/", Server.class);

        try
        {
            server.start();

            System.out.println("Press 'Enter' to stop the server..");
            Scanner sc = new Scanner(System.in);
            sc.nextLine();
        }
        catch (DeploymentException e)
        {
            throw new RuntimeException(e);
        }
        finally
        {
            server.stop();
        }
    }
}