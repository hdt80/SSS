package com.sss.mastercontroller.io;

public class Print {
	
	/**
	 * Debug method will take in an infinite amount of string parameters and print
	 * it out in an organized fashion.
	 * @param messages A String of strings separated by a comma
	 */
	public static void debug(String... messages) {
		String finalmessage = "";
		for (String message : messages) {
			finalmessage += message;
		}
		System.out.println("[DEBUG] " + finalmessage);
	}
	
	/**
	 * Warning method will take in an infinite amount of string parameters and print
	 * it out in an organized fashion.
	 * @param messages A String of strings separated by a comma
	 */
	public static void warning(String... messages) {
		String finalmessage = "";
		for (String message : messages) {
			finalmessage += message;
		}
		System.out.println("[WARNING] " + finalmessage);
	}
	
	/**
	 * Error method will take in an infinite amount of string parameters and print
	 * it out in an organized fashion.
	 * @param messages A String of strings separated by a comma
	 */
	public static void error(String... messages) {
		String finalmessage = "";
		for (String message : messages) {
			finalmessage += message;
		}
		System.out.println("[ERROR] " + finalmessage);
	}
	
	/**
	 * Message received from the server, will print with a nice looking
	 * server style for debugging what the server is saying
	 * @param messages A String of strings separated by a comma
	 */
	public static void server(String... messages) {
		String finalmessage = "";
		for (String message : messages) {
			finalmessage += message;
		}
		System.out.println("[SERVER] " + finalmessage);
	}
}