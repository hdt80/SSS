package com.sss.mastercontroller.objects;

public class Collision {
	
	private String name;
	private int side;
	
	public Collision(String name, int side) {
		this.name = name;
		this.side = side;
	}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getSide() {
		return side;
	}
}