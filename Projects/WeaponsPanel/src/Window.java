import java.awt.Font;
import java.util.ArrayList;
import java.util.List;

import org.lwjgl.LWJGLException;
import org.lwjgl.input.Keyboard;
import org.lwjgl.input.Mouse;
import org.lwjgl.opengl.Display;
import org.lwjgl.opengl.DisplayMode;
import org.newdawn.slick.Color;
import org.newdawn.slick.TrueTypeFont;

import static org.lwjgl.opengl.GL11.*;
import Util.Timer;
import Vector.*;

public class Window implements Runnable {
	
	int x, y, z;
	int power = 1;
	int speed;
	public List<Enemy> enemies = new ArrayList<Enemy>(16);
	public List<Missile> missiles = new ArrayList<Missile>(16);
	int midx;
	int midy;
	int height = 800;
	int width = 1200;
	boolean scanning = false;
	boolean pressed = false;
	boolean reload = false;
	Timer timer;
	
	public void run() {
		try {
			Display.setDisplayMode(new DisplayMode(width, height));
			Display.create();
		} catch (LWJGLException e) {
			e.printStackTrace();
			System.exit(0);
		}
		
		timer = new Timer(2000);
		x = 1000; y = 1000; z = 1000;
		midx = width / 2;
		midy = (height - (height / 5)) / 2;
		enemies.add(new Enemy(new Vector3f(midx, midy, 0), enemies.size(), true));
		int ex, ey, ez;
		ex = 1316; ey = 1216; ez = 1100;
		Enemy e = new Enemy(new Vector3f(midx + (ex - x), (midy - (ey - y)), Math.abs(ez - z)), enemies.size(), false);
		enemies.add(e);
		
		TrueTypeFont font;
		TrueTypeFont smallFont;
		Font awtFont = new Font("Times New Roman", Font.BOLD, height/20);
		font = new TrueTypeFont(awtFont, false);
		Font awt2Font = new Font("Times New Roman", Font.BOLD, height/40);
		smallFont = new TrueTypeFont(awt2Font, false);
		
		// init OpenGL
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, width, height, 0, 1, -1);
		glMatrixMode(GL_MODELVIEW);
		
		while (!Display.isCloseRequested()) {
			speed = power;
			// Clear the screen and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//Own ship
			glColor3f(0f, 1f, 0f);
			glBegin(GL_TRIANGLES);
				glVertex2f(midx - 15, midy - 15);
				glVertex2f(midx + 15, midy - 15);
				glVertex2f(midx, midy + 15);
			glEnd();
			//Inteface Panel
			glColor3f(0.5f, 0.5f, 0.5f);
			glBegin(GL_QUADS);
				glVertex2f(0,height);
				glVertex2f(0,height - height/5);
				glVertex2f(width,height - height/5);
				glVertex2f(width,height);
			glEnd();
			//Scanner box
			glColor3f(0f, 1f, 0f);
			glBegin(GL_QUADS);
				glVertex2f(width/40,height - height/30);
				glVertex2f(width/40,height - height/6);
				glVertex2f(width/4,height - height/6);
				glVertex2f(width/4,height - height/30);
			glEnd();
			//Fire box
			glColor3f(1f, 0f, 0f);
			glBegin(GL_QUADS);
				glVertex2f((width/4 + width/40),height - height/30);
				glVertex2f((width/4 + width/40),height - height/6);
				glVertex2f(width/2,height - height/6);
				glVertex2f(width/2,height - height/30);
			glEnd();
			//Info box
			glColor3f(1f, 1f, 1f);
			glBegin(GL_QUADS);
				glVertex2f((width/2 + width/6),height - height/30);
				glVertex2f((width/2 + width/6),height - height/6);
				glVertex2f((width - width/40),height - height/6);
				glVertex2f((width - width/40),height - height/30);
			glEnd();
			//Draw text
			glEnable(GL_TEXTURE_2D);
				//SCAN
				font.drawString(width/30 + width/20,height - height/8,"SCAN", Color.black);
				//FIRE
				font.drawString(width/3 + width/100,height - height/8,"FIRE", Color.black);
			glDisable(GL_TEXTURE_2D);
			//Check mouse + keyboard input
			pollInput();
			for (Enemy enemy : enemies) {
				if (enemy.ID != 0) {
					enemy.update();
					enemy.draw();
				}
				if (scanning == true && enemy.selected == true) {
					glEnable(GL_TEXTURE_2D);
						String distance = "Distance: ";
						String type = "Type: ";
						if (enemy.ally) {
							type += "ALLY";
						}
						else {
							type += "HOSTILE";
						}
						int d = (int)(enemies.get(0).v3.sub(enemy.v3)).length();
						distance += "" + d + " m";
						smallFont.drawString(width/2 + width/5,height - height/7,distance, Color.black);
						smallFont.drawString(width/2 + width/5,height - height/10,type, Color.black);
					glDisable(GL_TEXTURE_2D);
				}
				if (scanning == false) {
					glEnable(GL_TEXTURE_2D);
						String distance = "Distance: N/A";
						String type = "Type: N/A";
						smallFont.drawString(width/2 + width/5,height - height/8,distance, Color.black);
						smallFont.drawString(width/2 + width/5,height - height/10,type, Color.black);
					glDisable(GL_TEXTURE_2D);
				}
			}
			for (Missile missile : missiles) {
				missile.update();
				missile.draw();
			}
			Display.update();
			Display.sync(60);
		}

		Display.destroy();
		System.exit(0);
	}

	public void pollInput() {

		for (int a = 0; a < enemies.size(); a++) {
			Enemy enemy = enemies.get(a);
			//checks to see if missile hit enemy
			for (int i = 0; i < missiles.size(); i++) {
				if (enemy.inHitBounds(missiles.get(i).x, missiles.get(i).y, missiles.get(i).z)) {
					missiles.remove(i);
					//enemy.health -= 10;
				}
			}
			//destroys enemy if health gets to 0
			if (enemy.health <= 0) {
				enemies.remove(a);
			}
		}
		
		while (Mouse.next()) {
			if (Mouse.getEventButtonState() && Mouse.isButtonDown(0)) {
				if (timer.isOver()) {
					reload = false;
					timer.reset();
				}
				if (pressed == false) {
					pressed = true;
					for (int a = 0; a < enemies.size(); a++) {
						Enemy enemy = enemies.get(a);
						//checks to see if selected enemy
						if (enemy.inBounds(Mouse.getX(), height - Mouse.getY())) {
							scanning = false;
							enemy.selected = true;
						}
						//checks to see if firing at enemy
						else if (inAttack() && enemy.selected == true && reload == false) {
							reload = true;
							System.out.println("New Missile!");
							Main.net.Sendout("EVN#2;Missile;" + enemy.ID);
							missiles.add(new Missile(new Vector3f(midx,midy,0),new Vector3f(enemy.x,enemy.y,enemy.z),speed,true));
						}
						else if (inScan() && enemy.selected == true) {
							scanning = true;
							System.out.println("Scan scan scan scan scan scan...");
						}
						//deselects enemy
						else {
							enemy.selected = false;
						}
					}
				}
			}else {
		        if (Mouse.getEventButton() == 0) {
		            pressed = false;
		        }
		    }
		}
	}
	
	public boolean inAttack() {
		if (Mouse.getX() > (width/4 + width/40) && Mouse.getY() > height/30 && Mouse.getX() < width/2 && Mouse.getY() < height/6) {
			return true;
		}
		else {
			return false;
		}
	}
	
	public boolean inScan() {
		if (Mouse.getX() > (width/40) && Mouse.getY() > height/30 && Mouse.getX() < width/4 && Mouse.getY() < height/6) {
			return true;
		}
		else {
			return false;
		}
	}
}
