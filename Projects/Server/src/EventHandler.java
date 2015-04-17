import java.util.ArrayList;


public class EventHandler {
	
	private ArrayList<String> _enemies;
	
	public EventHandler() {
		_enemies = new ArrayList<String>();
		initEnemies();
	}
	
	public void callEvent(int[] vals) {
		if (vals[0] == 0) {
			spawnEnemies(vals[9], vals[3], vals[5], vals[8]);
		} else if (vals[0] == 1) {
			//internal values. will not be called at the moment
		} else if (vals[0] == 2) {
			//events. will not be called at the moment
		}
	}
	
	private void spawnEnemies(int enemyType, int spawnCount, int initialHealth, int isfr) {
		boolean isFriendly = (isfr == 1);
		System.out.println("Enemy   Type   = " + _enemies.get(enemyType));
		System.out.println("Spawn   Count  = " + spawnCount);
		System.out.println("Initial Health = " + initialHealth);
		System.out.println("Enemy Friendly = " + isFriendly);
		//now tell the game to spawn in enemyType for an enemy with the parameters given
	}
	
	private void initEnemies() {
		_enemies.add("Fighter Ship 1");
	}
}