package com.sss.mastercontroller.lists;

import java.util.ArrayList;

import com.sss.mastercontroller.objects.Enemy;

public class Enemies {
	
	private ArrayList<Enemy> _enemies;
	
	public Enemies() {
		
		_enemies = new ArrayList<Enemy>();
		
		_enemies.add(new Enemy("Fighter Ship 1", "Standard enemy space ship that has simple AI. Easy to manuever around and not too difficult to kill."));
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