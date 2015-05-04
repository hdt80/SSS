package com.SuperDuperPackage;
import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

import com.Networking.Network;

import Vector.*;

public class CPanel extends JPanel {
		CommandParser parse = new CommandParser(this);

	Color opacities[] = {
		new Color(34f/255,110f/255,35f/255,1f), new Color(34f/255,110f/255,35f/255,0.9f),
		new Color(34f/255,110f/255,35f/255,0.8f), new Color(34f/255,110f/255,35f/255,0.7f), 
		new Color(34f/255,110f/255,35f/255,0.5f),new Color(34f/255,110f/255,35f/255,.4f), 
		new Color(34f/255,110f/255,35f/255,0.3f),new Color(34f/255,110f/255,35f/255,0.2f),
		new Color(34f/255,110f/255,35f/255,0.15f), new Color(34f/255,110f/255,35f/255,0.1f)
	};
	Network net;
	private float shipx = 0, shipy = 0, shipz = 0;
	Font ConsoleFont = new Font(Font.MONOSPACED,Font.BOLD,20);
	int time = 50;
	boolean blink = false;
	String printing = "";
	String error = "";
	String history[] = new String[10];
	ArrayList<Enemy> list = new ArrayList<Enemy>();
	ArrayList<Missle> missleList = new ArrayList<Missle>();
	ArrayList<explosion> boomList = new ArrayList<explosion>();
	Color mygreen = new Color(34f/255,110f/255,35f/255,0.5f);
	Color mygreen2 = new Color(0,255f/255,35f/255,0.5f);
	int circle_diameter = 0;
	Vector3f shipPos = new Vector3f(shipx, shipy, shipz);
	int energy;
	
	

	//end of the public variables	
	public void enterCommand(){
		for (int i = history.length-1; i > 0; i--) {
			history[i] = history[i-1];
		}
		history[0] = printing;
		//register the command
		parse.parseCommand(printing);
		
		printing = "";
	}
	
	public ArrayList<Missle> getMissleList() {
		return missleList;
	}

	public void setMissleList(ArrayList<Missle> missleList) {
		this.missleList = missleList;
	}

	public void upPress(){
		printing = history[0];
	}
	public ArrayList<Enemy> getEnemies(){
		return list;
	}
	public ArrayList<Missle> getMissles(){
		return missleList;
	}
	public void paintComponent(Graphics g)
	{
		ArrayList<Enemy> rlist = new ArrayList<Enemy>();
		ArrayList<Missle> rmissleList = new ArrayList<Missle>();
//		ArrayList<explosion> rboomList = new ArrayList<explosion>();
//		
//		for (int i = 0; i < boomList.size(); i++) {
//			if(boomList.get(i).getLifeSpan() <= 0){
//				rboomList.add(boomList.get(i));
//			}
//			else{
//				boomList.get(i).paint(g, shipx, shipy, this.getWidth(), this.getHeight(), this);
//				boomList.get(i).setLifeSpan(boomList.get(i).getLifeSpan()-20);
//			}
//		}
		for (int i = 0; i < missleList.size(); i++) {
			Missle k = missleList.get(i);
			k.paint(g, shipx, shipy, this.getWidth(), this.getHeight());
			for (int j = 0; j < list.size(); j++) {
				Enemy e = list.get(j);
				if(k.getX() > e.getX()- 5 && k.getX() < e.getX() + 5 &&
						k.getY() > e.getY() - 5 && k.getY() < e.getY() + 5){
					e.hit(25);
					rmissleList.add(k);
					//boomList.add(new explosion(k.getPosition()));
					if(e.health <= 0){
						System.out.println("destroyed: " + e.getName());
						rlist.add(e);
					}
				}
			}
		}
		missleList.removeAll(rmissleList);
		list.removeAll(rlist);
		for (int i = 0; i < list.size(); i++) {
			list.get(i).paint(g, shipx, shipy, this.getWidth(), this.getHeight());
		}
		
		g.setFont(ConsoleFont);
		g.setColor(Color.GREEN);
		if(blink == true)
		g.drawString(printing, 10, this.getHeight()-10);
		
		g.drawString(error, 10, 25);
		
		for (int i = 0; i < history.length; i++) {
			g.setColor(opacities[i]);
			g.drawString(history[i], 10, this.getHeight()-((25*i)+40));
		}
		Blink();
	
	}

	public void Blink(){
		time--;
		if(time == 0 && blink == true){
			blink = !blink;
		time = 25;	
		}else if(time == 0 && blink == false){
			blink = !blink;
			time = 100;
		}
	}
	public CPanel(Color bg, Network ne){
		System.out.println("created");
		this.setBackground(bg);
		for (int i = 0; i < history.length; i++) {
			history[i]= "";
		}
		net = ne;
		
	}
	public void addEnemy(Enemy e){
		list.add(e);
	}
	public void update(){
		ArrayList<Missle> toKill = new ArrayList<Missle>();
		for (int i = 0; i < list.size(); i++) {
			list.get(i).update();
		}
		for(Missle m:missleList){
			if(!(list.contains(m.target))){
				toKill.add(m);
				net.Sendout(m.name);
				//boomList.add(new explosion(m.getPosition()));
			}
			m.update();
		}
		missleList.removeAll(toKill);
	}
	public Network getNet() {
		return net;
	}

	public void setNet(Network net) {
		this.net = net;
	}

	public Vector3f getShipPos() {
		return shipPos;
	}

	public void setShipPos(Vector3f shipPos) {
		this.shipPos = shipPos;
	}

	public void addChar(char c){
		printing = printing + c;
	}
	public void removechar(){
		if(printing.length() > 0)
		 printing = printing.substring(0,printing.length()-1);
	}
	public void setShipX(float x, float y){
		shipx = x; shipy = y;
	}
	public String getError() {
		return error;
	}
	public void setError(String error) {
		this.error = error;
	}
	public String getPrinting() {
		return printing;
	}
	public void setPrinting(String printing) {
		this.printing = printing;
	}
	public String[] getHistory() {
		return history;
	}

	public void setHistory(String[] history) {
		this.history = history;
	}
	public int getEnergy() {
		return energy;
	}

	public void setEnergy(int energy) {
		this.energy = energy;
	}
}
