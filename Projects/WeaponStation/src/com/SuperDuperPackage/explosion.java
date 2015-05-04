package com.SuperDuperPackage;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

import Vector.Vector3f;

public class explosion {
	private long lifeSpan;
	private double x;
	private double y;
	BufferedImage explosion;
	public explosion(Vector3f v){
		x = v.getX();
		y = v.getY();
		lifeSpan = 1000l;
		try {
			explosion = ImageIO.read(new File("src/explosian.jpg"));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	void paint(Graphics g, float a, float b, int c, int d, CPanel cd){
		//draw the enemies in relation to your ship
		g.drawImage(explosion,(int)(c/2+(getX()-a)),  (int)(d/2+(getY()-b)), cd);
		//g.fillOval((int)(c/2+(getX()-a)), (int)(d/2+(getY()-b)), 10, 10);
		//System.out.println((int)(c/2+(getX()-a)) +", " + (int)(d/2+(getY()-b)));
	}
	
	public long getLifeSpan() {
		return lifeSpan;
	}
	public void setLifeSpan(long lifeSpan) {
		this.lifeSpan = lifeSpan;
	}
	public double getX() {
		return x;
	}
	public void setX(double x) {
		this.x = x;
	}
	public double getY() {
		return y;
	}
	public void setY(double y) {
		this.y = y;
	}
}
