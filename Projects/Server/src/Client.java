import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.Executors;

public class Client extends Thread {

	private Socket clientSocket;
	private OutputStream out;
	private BufferedReader in;

	private String clientID;
	private ArrayList<Character> buffer;
	private boolean closed;

	public Client(Socket s) {
		buffer = new ArrayList<>();
		clientSocket = s;
		closed = false;
		try {
			out = clientSocket.getOutputStream();
			in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
		} catch (IOException e) {
			e.printStackTrace();
		}
		Logger.debug("Created a new connection");
	}

	public void start() {
		try {
			send("Connection to main server successful");
			getClientName();
			Logger.info("Connection made to " + clientID + " (" + clientSocket.getLocalAddress().getHostName() + ":" + clientSocket.getPort() + ")");

			Server.clients.add(this);

			Executors.newSingleThreadExecutor().execute(new Runnable() {
				@Override
				public void run() {
					while (!closed) {
						try {
							Thread.sleep(1000);
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				}
			});
			read();

		} catch (IOException e) {
			System.out.println("Exception caught when trying to listen on port or listening for a connection");
			e.printStackTrace();
		}
	}

	/**
	 * Disconnect from the socket
	 */
	public void disconnect() {
		try {
			Logger.debug("Disconnecting to " + clientID);
			closed = true;
			getSocket().close();
			Server.clients.remove(this);
			Logger.info("Disconnected from " + clientID);
		} catch (IOException e) {
			Logger.error("Failed to disconnect from " + clientID);
			e.printStackTrace();
			closed = true;
		}
	}

	/**
	 * The first thing recieved from the socket is the display name of the socket
	 */
	public void getClientName() throws IOException {
		Logger.debug("Getting client name");
		StringBuilder name = new StringBuilder();
		name.append((char) in.read());
		while (name.toString().charAt(name.length() - 1) != '@') {
			name.append((char) in.read());
		}
		// Remove the last char from the String, as it'll be an @
		clientID = name.toString().substring(0, name.length() - 1);
	}

	/**
	 * Send a message to the other socket
	 * @param msg Message to be sent
	 * @throws IOException
	 */
	public void send(final String msg) throws IOException {
		if (closed) {
			return;
		}
		Executors.newSingleThreadExecutor().execute(new Runnable() {
			@Override
			public void run() {
				try {
					out.write(msg.getBytes());
				} catch (Exception e) {
					e.printStackTrace();
					disconnect();
				}
			}
		});
	}

	/**
	 * Send a request to the client to set the key to the value
	 * @param key   Variable to be set
	 * @param value Value var should be set to
	 */
	public void setValue(String key, String value) throws IOException {
		StringBuilder msg = new StringBuilder();
		msg.append("SET#");
		msg.append(key);
		msg.append(':');
		msg.append(value);
		send(msg.toString());
	}

	/**
	 * Read the bytes from the socket to create a String of data read
	 */
	public void read() {
		if (closed) {
			return;
		}
		Executors.newSingleThreadExecutor().execute(new Runnable() {
			@Override
			public void run() {
				try {
					char input;
					while (!closed) {
						input = (char) in.read();
						if (input != '@') {
							buffer.add(input);
						} else {
							Logger.debug("RECV: \'" + makeString(buffer) + '\'');
							Server.values.processString(makeString(buffer));
							buffer.clear();
						}
					}
				} catch (Exception e) {
					if (e.getMessage().equals("Connection reset")) {
						disconnect();
					} else {
						e.printStackTrace();
						disconnect();
					}
				}
			}
		});
	}

	/**
	 * Make a String from an ArrayList of chars
	 * @param buffer ArrayList to stringify
	 * @return A String of the the chars in the ArrayList
	 */
	public String makeString(ArrayList<Character> buffer) {
		StringBuilder sb = new StringBuilder();
		sb.append(clientID);
		sb.append("#");

		for (int i = 0; i < buffer.size(); ++i) {
			sb.append(buffer.get(i));
		}
		return sb.toString();
	}

	/**
	 * Return the socket associated with the client
	 * @return Socket associated with the client
	 */
	public Socket getSocket() {
		return clientSocket;
	}

	/**
	 * Return the Client's name
	 * @return Client's name
	 */
	public String getClientID() {
		return clientID;
	}

}
