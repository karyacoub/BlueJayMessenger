import javax.websocket.OnClose;
import javax.websocket.OnOpen;
import javax.websocket.server.ServerEndpoint;
import javax.websocket.Session;
import java.io.IOException;
import java.util.Collections;
import java.util.Set;
import java.util.HashSet;

@ServerEndpoint("/chat")
public class Server
{
    private Set<Session> clients = Collections.synchronizedSet(new HashSet<Session>());

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
}