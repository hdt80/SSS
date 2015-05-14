package com.sss.mastercontroller.lists;

import java.util.ArrayList;

import com.sss.mastercontroller.objects.Collision;

public class Collisions {
	
	private ArrayList<Collision> _collisions;
	
	public Collisions() {
		
		_collisions = new ArrayList<Collision>();

		_collisions.add(new Collision("Collide on top", 0));
		_collisions.add(new Collision("Collide on right", 1));
		_collisions.add(new Collision("Collide on left", 2));
		_collisions.add(new Collision("Collide on bottom", 3));
		_collisions.add(new Collision("Collide on front", 4));
		_collisions.add(new Collision("Collide on back", 5));
	}
	
	public String getCollision(int i) {
		return _collisions.get(i).getName();
	}
	
	public int getSide(int i) {
		return _collisions.get(i).getSide();
	}
	
	public int getCollisions() {
		return _collisions.size();
	}
}