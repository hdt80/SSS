import java.util.ArrayList;


public class EventHandler {
	
	private final int Colision = 0;
	private final int SpawnEnemy = 1;
	private final int InternalProblem = 2;
	private final int ExteriorEvent = 3;
	
	/*
	public enum EventType {
		0 = Colision,
		1 = SpawnEnemy,
		2 = InternalProblem,
		3 = ExteriorEvent;
	}*/
	
	private ArrayList<String> _enemies;
	
	public EventHandler() {
		_enemies = new ArrayList<String>();
		initEnemies();
	}
	
	public void callEvent(ArrayList<Integer> args) {
		switch (args.get(0)) {
			case Colision:
				//occurs when, get this, you collide with an enemy, meteor, bullet, ect...
				collide(args.get(1));
			case SpawnEnemy:
				//occurs when, get this, you want to spawn an enemy! :O
				spawnEnemy(args.get(1), args.get(2), args.get(3), args.get(4));
			case InternalProblem:
				//nothing yet
			case ExteriorEvent:
				//nothing yet
		}
	}
	
	private void spawnEnemy(int enemyType, int spawnCount, int initialHealth, int isfr) {
		boolean isFriendly = (isfr == 1);
		System.out.println("Enemy   Type   = " + _enemies.get(enemyType));
		System.out.println("Spawn   Count  = " + spawnCount);
		System.out.println("Initial Health = " + initialHealth);
		System.out.println("Enemy Friendly = " + isFriendly);
		//send the spawn command to the game
	}
	
	private void collide(int damage) {
		Logger.info("We just took " + damage + " damage.");
		//send damage to the game
	}
	
	private void initEnemies() {
		_enemies.add("Fighter Ship 1");
	}
}