package com.SuperDuperPackage;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

import com.Networking.Network;

import Vector.*;

public class Main implements KeyListener, Runnable {

	private int energy = 5;
	private float shipx, shipy, shipz;
	private GraphicsDevice[] GD;
	private GraphicsEnvironment GE;
	private DisplayMode oldDisplayMode;
	private JFrame f;
	private CPanel primary;
	private boolean condition;
	private boolean shift = false;
	private Network net;
	
	public Main() {
		net = new Network();
		GE = GraphicsEnvironment.getLocalGraphicsEnvironment();
		GD = GE.getScreenDevices();
		oldDisplayMode = GD[0].getDisplayMode();
		f = new JFrame(GD[0].getDefaultConfiguration());
		f.setBackground(Color.BLACK);
		
		//f.setLayout(null);
		primary = new CPanel(Color.BLACK, net);
		
		f.add(primary);
	
		f.addKeyListener(this);
		
		changeFrameFullScreenMode(f);
		// end of graphics set up

		// put code here that adds enemies
		Enemy test = new Enemy(new Vector3f(0, 0, 0), new Vector3f(10f, 50f,
				20f), "E1", 100);
		primary.addEnemy(test);
		Enemy test1 = new Enemy(new Vector3f(.06f, .05f, 0), new Vector3f((10f),
				50f, 25f), "E2", 100);
		primary.addEnemy(test1);
		//create a rendering thread and start it
		Thread renderThread = new Thread(this);
		renderThread.start();
		
		//create a networking thread and sttart it
		Thread networkThread = new Thread(new Runnable() {
			@Override
			public void run() {
				String s = null;
				while (true) {
					
					s = net.Readin();
					
					System.out.println(s);
					
					
					//primary.setEnergy(energy);
				}	
				
			}
		});
	    networkThread.start();
	}

	
	void changeFrameFullScreenMode(JFrame app) {
		GraphicsDevice gd = GraphicsEnvironment.getLocalGraphicsEnvironment()
				.getDefaultScreenDevice();
		if (gd.getFullScreenWindow() == null) {
			app.dispose();
			app.setUndecorated(true);
			gd.setFullScreenWindow(app);
			gd.setDisplayMode(oldDisplayMode);
			app.setVisible(true);
		} else { // back to windowed mode
			app.dispose();
			app.setUndecorated(false);
			gd.setFullScreenWindow(null);
			app.setVisible(true);
		}
	}
	private void parseServercomand(String s){
		//format
	}
	public static void main(String[] args) {
		new Main();
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
	}

	@Override
	public void keyPressed(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_SHIFT)
			shift = true;
		if(e.getKeyCode() == KeyEvent.VK_ENTER){
			primary.enterCommand();
		}else if(e.getKeyCode() == KeyEvent.VK_BACK_SPACE){
		primary.removechar();
		}
		else if(Character.isDigit(e.getKeyChar()) || Character.isAlphabetic(e.getKeyChar()) || e.getKeyCode() == KeyEvent.VK_SPACE || e.getKeyCode() == KeyEvent.VK_PERIOD){
		primary.addChar(e.getKeyChar());
		}else if(e.getKeyCode() == KeyEvent.VK_UP){
			primary.upPress();
		}
		
		if(e.getKeyCode() == KeyEvent.VK_Q && shift == true){
			condition = true;
			System.exit(0);
		}
	}

	@Override
	public void keyReleased(KeyEvent e) {
		if(e.getKeyCode() == KeyEvent.VK_SHIFT)
			shift = false;

	}

	@Override
	public void run() {
		boolean t = true;
		boolean f1 = !t;
		 condition = !(!f1);
		while (!condition) {
			primary.update();
			primary.setEnergy(energy);
			f.repaint();
			try {Thread.sleep(2);} catch (InterruptedException e) {e.printStackTrace();}
			
		}
		changeFrameFullScreenMode(f);
	}

}
