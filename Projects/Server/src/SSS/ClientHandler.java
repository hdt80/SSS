package SSS;

import SSS.Util.Logger;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.Executors;

/**
 * Class that manages all the client connect to the server
 */
public class ClientHandler {
    private ServerSocket serverSocket;
    private ArrayList<Client> clients;

    private boolean close;

    /**
     * Default constructor for a ClientHandler
     */
    public ClientHandler(ServerSocket server) {
        this.serverSocket = server;
        clients = new ArrayList<>();
        close = false;
    }

    /**
     * Add a Client to the list of clients we manage
     * @param client Client to add to the list
     */
    public void addClient(Client client) {
        clients.add(client);
    }

    /**
     * Remove a Client from the clients we handle
     * @param name Name of the Client to remove
     * @return true  - The Client was removed
     *         false - The Client is not in the list, and cannot be removed
     */
    public boolean removeClient(String name) {
        int index = getIndex(name);
        if (index != -1) {
            clients.remove(index);
            return true;
        }
        return false;
    }

    /**
     * Send the msg to client
     * @param clientID 3-letter name of the client to send the message to
     * @param msg Message to be send to the client
     * @throws IOException
     */
    public void send(String clientID, String msg) throws IOException {
        Client client = getClient(clientID);
        if (client != null) {
            client.send(msg);
        } else {
            Logger.warn("No client with name \'" + clientID + '\'');
        }
    }

    /**
     * Iterate through our clients to find the first Client that matches the name
     * @param clientName ClientID of the Client to return
     * @return The first Client that matches clientName, or null if no Client matches that name
     */
    public Client getClient(String clientName) {
        for (Client client : clients) {
            if (client.getClientID().equals(clientName)) {
                return client;
            }
        }
        return null;
    }

    /**
     * Return the index a Client's name is stored
     * @param clientName Client's name to be found
     * @return The index of the Client, -1 if a Client with that name doesn't exist
     */
    public int getIndex(String clientName) {
        for (int i = 0; i < clients.size(); ++i) {
            if (clients.get(i).getClientID().equals(clientName)) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Tell the ClientHandler to close all connections with clients and properly
     * clean up the remaining resources
     */
    public void close() {
        close = true;
    }

    /**
     * Begin accepting new connections on a new Thread
     */
    public void acceptConnections() {
        Executors.newSingleThreadExecutor().execute(new Runnable() {
            @Override
            public void run() {
                try {
                    Logger.debug("Listening for new connections");
                    while (!close) {
                        Socket clientSocket = serverSocket.accept();
                        Client client = new Client(clientSocket);

                        addClient(client);
                        client.start();
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
