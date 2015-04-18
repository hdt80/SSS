package com.sss.mastercontroller.lists;

import java.util.ArrayList;

import com.sss.mastercontroller.objects.Collision;

public class Collisions {
	
	private ArrayList<Collision> _collisions;
	
	public Collisions() {
		
		_collisions = new ArrayList<Collision>();
		
		_collisions.add(new Collision("Collide with meteor", 20));
		_collisions.add(new Collision("Collide with enemy", 200));
		_collisions.add(new Collision("Collide with bulles", 2000));
	}
	
	public String getCollision(int i) {
		return _collisions.get(i).getName();
	}
	
	public int getDamage(int i) {
		return _collisions.get(i).getDamage();
	}
	
	public int getCollisions() {
		return _collisions.size();
	}
}