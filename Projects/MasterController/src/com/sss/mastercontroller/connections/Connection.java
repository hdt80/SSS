package com.sss.mastercontroller.connections;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.ArrayList;
import java.util.concurrent.Executors;

import com.sss.mastercontroller.io.Print;

public class Connection {
	private OutputStream dOut;
    private BufferedReader in;
	private Socket socket;
	private ArrayList<Character> buffer;
	private boolean closed = true;
	
	/**
	 * Default Constructor to initialize the socket
	 * @since 1.0
	 */
	public Connection() {
		buffer = new ArrayList<Character>();
		socket = new Socket();
	}
	
	/**
	 * Constructor that takes in an ip address and a port
	 * @param hostName
	 * @param port
	 */
	public Connection(String hostName, int port) {
		buffer = new ArrayList<Character>();
		socket = new Socket();
		connect(hostName, port);
	}
	
	/**
	 * 
	 * @author Bryce Hahn
	 * @since 1.0
	 */
	public void sendClientIDToServer() {
		try {
			Print.debug("Sending Cliend ID MSC to server.");
			sendBytes(new String("MSC@").getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Takes in a string message to be sent to the server
	 * @param bytes The message in a string format
	 * @author Bryce Hahn
	 * @since 1.0
	 */
	public void sendMessageToServer(String bytes) {
		bytes += "@";
		try {
			sendBytes(bytes.getBytes()); //run the sender method
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Takes in a string as a value to set for a specified 
	 * station to send to the server
	 * @param bytes The value and station in a string format
	 * @author Bryce Hahn
	 * @since 1.0
	 */
	public void setValueOnServer(String bytes) {
		StringBuilder sb = new StringBuilder();
		sb.append("SET#");
		sb.append(bytes);
		sb.append("@");
		try {
			sendBytes(sb.toString().getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Takes in a string of integers to send as values to the server
	 * the server will the parse the values and tell the other clients what to do
	 * @param bytes The string of the values, separated by a semi-colon
	 * @author Bryce Hahn
	 * @since 1.0
	 */
	public void sendEventToServer(String bytes) {
		StringBuilder sb = new StringBuilder();
		sb.append("EVN#");
		sb.append(bytes);
		sb.append('@');
		try {
			sendBytes(sb.toString().getBytes());
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * public method to connect to the server through a specified ip address and port
	 * @param hostname String of the IPv4 Address from the server computer
	 * @param port integer of the port, should remain the same unless connecting to multiple servers
	 * @author Bryce Hahn
	 * @since 1.0
	 */
	public void connect(String hostname, int port) {
		try {
			Print.debug("Trying to connect to ", hostname, " through the ", Integer.toString(port), " port."); //debug text
			socket.connect(new InetSocketAddress(hostname, port)); //connect to the socket using the given parameters
			dOut = socket.getOutputStream();
			in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			closed = false;
			beginRead();
		} catch (IOException e) {
			//connection failed
			Print.error("Failed to connect to ", hostname, " through the ", Integer.toString(port), " port.");
			e.printStackTrace();
		}
	}
	
	/**
	 * public method to disconnect from the server
	 * @author Bryce Hahn
	 * @since 1.0
	 */
	public void disconnect() {
		try {
			Print.debug("Closing the socket.");
			socket.close(); //close the connection
			closed = true;
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Constantly reads from the server on its own thread
	 * to not slow down the main thread. It will only print
	 * when it has a message incoming
	 * @author Mason Cluff
	 * @since 1.0
	 */
	public void beginRead() {
		Executors.newSingleThreadExecutor().execute(new Runnable() {
			@Override
			public void run() {
				try {
					char input;
					while (!closed) {
						input = (char)in.read();
						if (input != '@') {
							buffer.add(input);
						} else {
							Print.debug("Received: ", makeString(buffer));
							buffer.clear();
						}
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	/**
	 * Small private method that will take in an array list
	 * of characters and convert it to a string
	 * @param buffer
	 * @return
	 */
	private String makeString(ArrayList<Character> buffer) {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < buffer.size(); i++) {
			sb.append(buffer.get(i));
		}
		return sb.toString();
	}
	
	/**
	 * private method to send to the server through a byte array
	 * @param myByteArray Byte array that will be sent to the server
	 * @throws IOException
	 * @since 1.0
	 * @author Bryce Hahn, Mason Cluff
	 */
	private void sendBytes(byte[] myByteArray) throws IOException {
	    //write to the server with the length of the array
    	dOut.write(myByteArray);           // write the message to the server
        Print.debug("[Message Send To Server] ", new String(myByteArray)); //debug text
		dOut.flush(); //flush the stream
	}
}