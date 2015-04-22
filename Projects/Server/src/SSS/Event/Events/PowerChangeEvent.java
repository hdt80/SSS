package SSS.Event.Events;

import SSS.Util.Logger;

public class PowerChangeEvent extends Event {
	String stationName;
	int newPower;

	public PowerChangeEvent(String stationName, int newPower) {
		this.stationName = stationName;
		this.newPower = newPower;
	}

	@Override
	public void run() {
		Logger.info("Power change event called: " + stationName + ":" + newPower);
	}
}
