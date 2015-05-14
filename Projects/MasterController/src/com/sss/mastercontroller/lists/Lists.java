package com.sss.mastercontroller.lists;

public class Lists {
	private final static int COLISION = 0;
	private final static int SPAWN = 1;
	private final static int PREFERENCES = 2;
	private final static int EXIT = 3;
	
	public static int getEvent(int i) {
		if (i == 0) {
			return COLISION;
		} else if (i == 1) {
			return SPAWN;
		} else if (i == 2) {
			return PREFERENCES;
		} else if (i == 3) {
			return EXIT;
		}
		return 0;
	}
}