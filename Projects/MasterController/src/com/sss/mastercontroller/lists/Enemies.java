package com.sss.mastercontroller.lists;

import java.util.ArrayList;

import com.sss.mastercontroller.objects.Enemy;

public class Enemies {
	
	private ArrayList<Enemy> _enemies;
	
	public Enemies() {
		
		_enemies = new ArrayList<Enemy>();
		
		_enemies.add(new Enemy("Fighter Ship 1", "Standard Enemy ship. Basic health, basic attack power. Limited AI."));
	}
	
	public String getEnemy(int i) {
		return _enemies.get(i).getName();
	}
	
	public String getDefinition(int i) {
		return _enemies.get(i).getDefinition();
	}
	
	public int getEnemies() {
		return _enemies.size();
	}
}