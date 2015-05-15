import java.awt.Color;
import java.awt.Font;
import java.util.ArrayList;
import java.util.List;

import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.input.Mouse;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import static java.lang.Math.cos;
import static java.lang.Math.sin;
import static org.lwjgl.opengl.GL11.*;

/*
 * Things to do:
 * Yelloq border when selected
 * select when you click
 * have a toolbar like thing on the bottome of the screen
 * when selected disply information that we know in the bottom of the screen
 * have shoot and scan buttons
 * redraw the screen with movement and stuff
 */

public class Main {

	public static Network net;

	public static void main(String[] arg0) {
		new Main();
	}

	public Main() {
		Thread window = new Thread(new Window());
		net = new Network();
		// create a networking thread and start it
		Thread networkThread = new Thread(new Runnable() {
			@Override
			public void run() {
				String s = null;
				while (true) {
					s = net.Readin();

					System.out.println(s);
				}
			}
		});
		networkThread.start();
		window.start();
	}
}
