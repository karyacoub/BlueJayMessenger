import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.util.Collections;
import java.util.Set;
import java.util.HashSet;

@ServerEndpoint("/chat")
public class Server
{
    private static Set<Session> clients = Collections.synchronizedSet(new HashSet<>());

    @OnOpen
    public void onOpen(Session session)
    {
        clients.add(session);
        System.out.println(String.format("%s has joined the chatroom!", session.getId()));
    }

    @OnClose
    public void onClose(Session session) throws IOException
    {
        clients.remove(session);
        System.out.println(String.format("%s has left the chatroom.", session.getId()));

        // notify peers that client has left the chatroom
        for(Session s : clients)
        {
            s.getBasicRemote().sendText(String.format("%s has left the chatroom.", session.getId()));
        }
    }

    @OnMessage
    public void onMessage(String message, Session session) throws IOException
    {
        System.out.println(session.getId() + ": " + message);
        for(Session client : clients)
        {
            if(!session.getId().equals(client.getId()))
            {
                client.getBasicRemote().sendText(message);
            }
        }
    }
}