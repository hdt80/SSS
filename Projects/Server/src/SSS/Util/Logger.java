package SSS.Util;

import SSS.Server;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.logging.Level;

public class Logger {
	private static final SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");

	public static void log(Level level, String message) {
		Date date = new Date();
		StringBuilder sb = new StringBuilder();
		sb.append(format.format(date)).append(" [");
		sb.append(Color.RED).append(level.toString()).append(Color.RESET).append("]: ");
		sb.append(message);
		System.out.println(sb.toString());
	}

	public static void info(String message) {
		StringBuilder sb = new StringBuilder();
		Date date = new Date();
		sb.append(format.format(date)).append(" [");
		sb.append(Color.GREEN).append("INFO").append(Color.RESET).append("]: ");
		sb.append(message);
		System.out.println(sb.toString());
	}

	public static void warn(String message) {
		StringBuilder sb = new StringBuilder();
		Date date = new Date();
		sb.append(format.format(date)).append(" [");
		sb.append(Color.YELLOW).append("WARN").append(Color.RESET).append("]: ");
		sb.append(message);
		System.out.println(sb.toString());
	}

	public static void severe(String message) {
		log(Level.SEVERE, message);
	}

	public static void error(String message) {
		StringBuilder sb = new StringBuilder();
		Date date = new Date();
		sb.append(format.format(date)).append(" [");
		sb.append(Color.RED).append("ERROR").append(Color.RESET).append("]: ");
		sb.append(message);
		System.out.println(sb.toString());
	}

	public static void debug(String message) {
		if (Server.isDebug() == true) {
			StringBuilder sb = new StringBuilder();
			Date date = new Date();
			sb.append(format.format(date)).append(" [");
			sb.append(Color.PURPLE).append("DEBUG").append(Color.RESET).append("]: ");
			sb.append(message);
			System.out.println(sb.toString());
		}
	}
}
