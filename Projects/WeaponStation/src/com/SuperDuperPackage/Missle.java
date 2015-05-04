package com.SuperDuperPackage;
import java.awt.Color;
import java.awt.Graphics;

import Vector.Vector3f;


public class Missle {
	Vector3f vector;
	Vector3f position;
	String name;
	Enemy target;
	boolean doKill = false;
	
	public Missle(Vector3f p, String n, Enemy e) {
		System.out.println("new Missle: " + e.getName());
		position = p;
		name = n;
		target = e;
		
//		System.out.println(getPosition().getX() + ", " + getPosition().getY() + ", " + getPosition().getZ());
	}
	void paint(Graphics g, float a, float b, int c, int d){
		//draw the enemies in relation to your ship
		Color myred2 = new Color(255f/255,0,35f/255,1f);
		g.setColor(myred2);
		g.fillOval((int)(c/2+(getX()-a)), (int)(d/2+(getY()-b)), 10, 10);
		//System.out.println((int)(c/2+(getX()-a)) +", " + (int)(d/2+(getY()-b)));
	}
	void update() {
		
		Vector3f velocity = target.getPosition().sub(this.getPosition()).normalized();
		setVector(velocity.mul(0.25f));
		//System.out.println(velocity.getX() + ", " + velocity.getY() + ", " + velocity.getZ());
		setPosition(this.getPosition().add(this.getVector()));
		//System.out.println(getPosition().getX() + ", " + getPosition().getY() + ", " + getPosition().getZ());
	}
	
	
	public Vector3f getVector() {
		return vector;
	}
	public void setVector(Vector3f vector) {
		this.vector = vector;
	}
	public Vector3f getPosition() {
		return position;
	}
	public void setPosition(Vector3f position) {
		this.position = position;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public Enemy getTarget() {
		return target;
	}
	public void setTarget(Enemy target) {
		this.target = target;
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
}
