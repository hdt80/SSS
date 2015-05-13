package SSS.Event.Events;

import SSS.Server;
import SSS.Util.Logger;

import java.io.IOException;

public class CollisionEvent extends Event {
    final static private String[] sides = {"top", "right", "left", "bottom", "front", "back"};
    final static private String[] powerCell = {"Engines", "Weapons", "Shield", "Engines", "Radar", "Engines"};

    /**
     * 0 - top
     * 1 - right
     * 2 - left
     * 3 - bottom
     * 4 - front
     * 5 - back
     */
    private int collisionSide;
    private String side;

    public CollisionEvent(int collisionSide) {
        this.collisionSide = collisionSide;

        if (collisionSide >= 0 && collisionSide < 6) {
            side = sides[collisionSide];
        } else {
            Logger.warn("Tried to set collision side to " + collisionSide);
        }
    }

    @Override
    public void run() throws IOException {
        Logger.info("Collision: Collided on side " + side + " (" + collisionSide + ")");
        Server.get().clientHandler.send("ENG", "EVN#7;" + powerCell[collisionSide] + ";-1");
    }
}
