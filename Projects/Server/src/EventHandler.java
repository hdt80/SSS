
public class EventHandler {
	
	public static void callEvent(int[] vals) {
		if (vals[0] == 0) {
			spawnEnemies(vals[9], vals[3], vals[5], vals[8]);
		} else if (vals[0] == 1) {
			//internal values. will not be called at the moment
		} else if (vals[0] == 2) {
			//events. will not be called at the moment
		}
	}
	
	public static void spawnEnemies(int enemyType, int spawnCount, int initialHealth, int isFriendly) {
		System.out.println("Enemy Type = " + enemyType);
		System.out.println("Spawn Count= " + spawnCount);
		System.out.println("Init Health= " + initialHealth);
		System.out.println("Is Friendly= " + isFriendly);
	}
}