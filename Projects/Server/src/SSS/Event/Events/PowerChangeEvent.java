package SSS.Event.Events;

import SSS.Util.EventTester;
import SSS.Util.Logger;

import java.io.IOException;

public class PowerChangeEvent extends Event {
	String stationName;
	int newPower;

	public PowerChangeEvent(String stationName, int newPower) {
		this.stationName = stationName;
		this.newPower = newPower;
	}

	@Override
	public void run() throws IOException {
		Logger.info("Power change event called: " + stationName + ":" + newPower);
        EventTester.testMaxPower();
	}
}
