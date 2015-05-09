package SSS.Event.Events;

import SSS.Server;
import SSS.Util.Logger;

import java.io.IOException;

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
    public void run() throws IOException {
        Logger.info("Spawning " + spawnCount + " of type " + enemyType + " with " + enemyHealth + " health");
        try {
            Server.get().clientHandler.send("NAV", "EVN#0;" + spawnCount + ';' + enemyType + ';' + enemyHealth + ';');
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
