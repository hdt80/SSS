package com.sss.mastercontroller.lists;

public class Lists {
	public final static int COLLISION = 0;
	public final static int SPAWN = 1;
	public final static int DESPAWN = 2;
	public final static int PREFERENCES = -1;
	public final static int EXIT = 3;
	
	public static int getEvent(int i) {
		if (i == 0) {
			return COLLISION;
		} else if (i == 1) {
			return SPAWN;
		} else if (i == 2) {
			return DESPAWN;
		} //else if (i == 3) {
			//return PREFERENCES;
		 else if (i == 3) {
			return EXIT;
		}
		return 0;
	}
}