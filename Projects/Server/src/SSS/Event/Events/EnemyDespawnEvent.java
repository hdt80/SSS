package SSS.Event.Events;

import SSS.Util.Logger;

public class EnemyDespawnEvent extends Event {
    int id; // ID of the ship despawning

    public EnemyDespawnEvent(int id) {
        Logger.info("Despawning enemy with id " + id);
    }
}
