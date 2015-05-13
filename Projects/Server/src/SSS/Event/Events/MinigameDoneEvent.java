package SSS.Event.Events;

import SSS.Server;
import SSS.Util.Logger;

import java.io.IOException;

public class MinigameDoneEvent extends Event {
    String station; // What station completed a minigame
    String reward;  // What will happen when the minigame is complete

    public MinigameDoneEvent(String station, String reward) {
        this.station = station;
        this.reward = reward;
    }

    @Override
    public void run() throws IOException{
        Logger.info("Minigame done: Station (" + station + ") done | Reward: " + reward);
        Server.get().clientHandler.send("ENG", "EVN#7;" + reward + ";1");
    }
}
