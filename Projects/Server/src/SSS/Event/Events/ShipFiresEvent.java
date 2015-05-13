package SSS.Event.Events;

import SSS.Util.EventTester;
import SSS.Util.Logger;

public class ShipFiresEvent extends Event {
    String shotType; // The various types of projectiles we can shoot
    int targetID;    // What ship we've targeted to shoot at

    public ShipFiresEvent(String shotType, int targetID) {
        this.shotType = shotType;
        this.targetID = targetID;
    }

    @Override
    public void run() {
        Logger.info("Firing a " + shotType + " at ship id " + targetID);
        EventTester.testWepPanel();
    }
}
