package com.sss.mastercontroller.lists;

import java.util.ArrayList;
import com.sss.mastercontroller.objects.Event;

public class Events {
	
	private ArrayList<Event> _events;
	
	public Events() {
		
		_events = new ArrayList<Event>();

		_events.add(new Event("Black Hole", "Create a black hole that expands exponentialy and will have an X amount of pull force. The higher the pull force, the more difficult it will be to avoid."));
		_events.add(new Event("Enemy Health Gain", "Give any ship near the teams ship an X amount of health to mess with your team."));
		_events.add(new Event("Meteor Shower", "Spawn a storm of meteors to hurtle towards the team ship, the will probably have to dodge or destroy them."));
		_events.add(new Event("Solar Storm", "Randomly generate a Solar Store to inflict damage apon the team ship."));
		_events.add(new Event("Supernova", "Create a masive solar explosion with an option of either helping the team ship, or hurting them."));
		_events.add(new Event("Worm Hole", "Create a worm hole that expands exponentialy. This worm hole can send the team ship to a random location in the galaxy and will close after exit."));
	}
	
	public String getEventName(int i) {
		return _events.get(i).getName();
	}
	
	public String getEventDefinition(int i) {
		return _events.get(i).getDefinition();
	}
	
	public int getEvents() {
		return _events.size();
	}
}