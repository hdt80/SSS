package com.SuperDuperPackage;
import java.awt.Color;
import java.awt.Graphics;

import Vector.*;

public class Enemy {


	Vector3f vector;
	Vector3f position;
	String name;
	int health;
	
	public int hit(int energy){
		health = health-energy;
		return health;
	}
	public Enemy(Vector3f v, Vector3f p, String n, int h) {
		vector = v;
		position = p;
		name = n;
		health = h;
	}
	void paint(Graphics g, float a, float b, int c, int d){
		//draw the enemies in relation to your ship
		Color mygreen2 = new Color(0,255f/255,35f/255,0.5f);
		g.setColor(mygreen2);
		g.fillOval((int)(c/2+(getX()-a)), (int)(d/2+(getY()-b)), 10, 10);
		g.drawString(name, (int)(c/2+(getX()-a+5)), (int)(d/2+(getY()-b-5)));
		
	}
	void update() {
		setPosition(this.getPosition().add(this.getVector()));
	}
	public Vector3f getVector() {
		return vector;
	}
	public Vector3f getPosition() {
		return position;
	}

	public void setPosition(Vector3f position) {
		this.position = position;
	}

	public void setVector(Vector3f vector) {
		this.vector = vector;
	}
	float getX(){
		return this.getPosition().getX();
	}
	float getY(){
		return this.getPosition().getY();
	}
	float getZ(){
		return this.getPosition().getZ();
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}


}
