package SSS.Util;

import SSS.Server;

import java.io.IOException;

public class EventTester {
    public static void testMaxPower() {
        try {
            Server.get().clientHandler.send("ENG", "EVN#7;Weapons;-1");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
