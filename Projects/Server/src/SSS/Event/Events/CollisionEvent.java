package SSS.Event.Events;

import SSS.Util.Logger;

public class CollisionEvent extends Event {
    private int damageDone;

    public CollisionEvent(int damageDone) {
        this.damageDone = damageDone;
    }

    @Override
    public void run() {
        Logger.info("Collision: " + damageDone + " damage done");
    }
}
