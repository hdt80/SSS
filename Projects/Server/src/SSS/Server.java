package SSS;

import SSS.Util.Logger;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.Executors;

public class Server {
	public static boolean debug;

	private int port = 5003;
	private ServerSocket serverSocket;

	public ArrayList<Client> clients = new ArrayList<>();
	public InternalValues values = new InternalValues();

	private static Server instance;

	public static void main(String[] args) {
		for (int i = 0; i < args.length; ++i) {
			if (args[i].equals("-v")) {
				debug = true;
				Logger.debug("Debug true");
			}
		}
		new Server();
	}

	public Server() {
		try {
			instance = this;
			serverSocket = new ServerSocket(port);
			Logger.info("Awaiting connections");

			// Accept any new clients on a new thread
			Executors.newSingleThreadExecutor().execute(new Runnable() {
				@Override
				public void run() {
					try {
						while (true) {
							Socket clientSocket = serverSocket.accept();
							Client client = new Client(clientSocket);
							client.start();
						}
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static Server get() {
		return instance;
	}

	public Client getClientByName(String name) {
		for (int i = 0; i < clients.size(); ++i) {
			if (clients.get(i).getClientID().equals(name)) {
				return clients.get(i);
			}
		}
		return null;
	}

	public void addClient(Client client) {
		clients.add(client);
	}

	public void removeClient(Client client) {
		clients.remove(client);
	}

	public static boolean isDebug() {
		return debug;
	}
}
