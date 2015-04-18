package com.sss.mastercontroller.lists;

import java.util.ArrayList;

import com.sss.mastercontroller.objects.Preference;

public class Preferences {
	
	private ArrayList<Preference> _preferences;
	
	public Preferences() {
		
		_preferences = new ArrayList<Preference>();
		
		_preferences.add(new Preference("Master Controller", "Edit preferences about the layout and colors of the Master Controller program. "
				+ "This of course is extremely limited to what I decide should be editable, but hey! At least you have a couple gismoes you can toy"
				+ " with while you mess with your friends in game. Have fun!"));
		_preferences.add(new Preference("Sunset Space Simulation", "Edit options of in game directly from the Master Controller. You can edit options such as"
				+ " how often to autosave, some basic graphical options, and some controls."));
	}
	
	public String getPreferenceName(int i) {
		return _preferences.get(i).getName();
	}
	
	public String getPreferenceDefinition(int i) {
		return _preferences.get(i).getDefinition();
	}
	
	public int getPreferences() {
		return _preferences.size();
	}
}