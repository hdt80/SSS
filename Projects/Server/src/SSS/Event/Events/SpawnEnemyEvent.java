package SSS.Event.Events;

import SSS.Util.Logger;

public class SpawnEnemyEvent extends Event {
    private int enemyType;
    private int spawnCount;
    private int enemyHealth;

    public SpawnEnemyEvent(int enemyType, int spawnCount, int enemyHealth) {
        this.enemyType = enemyType;
        this.spawnCount = spawnCount;
        this.enemyHealth = enemyHealth;
    }

    @Override
    public void run() {
        Logger.info("Spawning " + spawnCount + " of type " + enemyType + " with " + enemyHealth + " health");
    }
}
