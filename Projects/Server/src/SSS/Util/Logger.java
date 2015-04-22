package SSS.Util;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * A class with methods to provide structured output
 */
public class Logger {
	public static boolean debug = false;

	private static final SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");

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

	public static void error(String message) {
		StringBuilder sb = new StringBuilder();
		Date date = new Date();
		sb.append(format.format(date)).append(" [");
		sb.append(Color.RED).append("ERROR").append(Color.RESET).append("]: ");
		sb.append(message);
		System.out.println(sb.toString());
	}

	public static void debug(String message) {
		if (debug) {
			StringBuilder sb = new StringBuilder();
			Date date = new Date();
			sb.append(format.format(date)).append(" [");
			sb.append(Color.PURPLE).append("DEBUG").append(Color.RESET).append("]: ");
			sb.append(message);
			System.out.println(sb.toString());
		}
	}
}
