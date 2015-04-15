package com.sss.mastercontroller.lists;

import java.util.ArrayList;

import com.sss.mastercontroller.objects.Enemy;

public class Enemies {
	
	private ArrayList<Enemy> _enemies;
	
	public Enemies() {
		
		_enemies = new ArrayList<Enemy>();
		
		_enemies.add(new Enemy("Assault Ship", ""));
		_enemies.add(new Enemy("Battle Cruiser", ""));
		_enemies.add(new Enemy("Battle Ship", ""));
		_enemies.add(new Enemy("Bomber", "ddddd"));
		_enemies.add(new Enemy("Command Ship", ""));
		_enemies.add(new Enemy("Cruiser", ""));
		_enemies.add(new Enemy("Destroyer", ""));
		_enemies.add(new Enemy("Dreadnaught", ""));
		_enemies.add(new Enemy("Frigate", ""));
		_enemies.add(new Enemy("Heavy Assault Ship", ""));
		_enemies.add(new Enemy("Hostile Space Station", ""));
		_enemies.add(new Enemy("Intercepter", ""));
		_enemies.add(new Enemy("Recon Ship", ""));
		_enemies.add(new Enemy("Shuttle", ""));
		_enemies.add(new Enemy("Stealth Ship", ""));
		_enemies.add(new Enemy("The Mothership", ""));
		_enemies.add(new Enemy("Transporter Ship", ""));
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