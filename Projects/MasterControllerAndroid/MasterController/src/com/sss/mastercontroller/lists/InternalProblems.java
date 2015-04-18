package com.sss.mastercontroller.lists;

import java.util.ArrayList;
import com.sss.mastercontroller.objects.InternalProblem;

public class InternalProblems {
	
	private ArrayList<InternalProblem> _internalproblems;
	
	public InternalProblems() {
		
		_internalproblems = new ArrayList<InternalProblem>();
		
		_internalproblems.add(new InternalProblem("Core Meltdown", "Cause a sudden burst in the nuclear core tempurature causing a meltdown. This will lead the enginear to a new mini-game."));
		_internalproblems.add(new InternalProblem("Force reload", "Force the gunner to reload causing a pause in the defense, possibly causing them to receive damage or be hit by an projectile."));
		_internalproblems.add(new InternalProblem("Fuel leak", "Leak fuel, causing team to be more effient on how they use recources, and cause a nesassary repair mini-game for the enginear."));
		_internalproblems.add(new InternalProblem("Hyperjump failure", "The next time the pilot tries to jump in Hyperdrive, give an error on screen and have a 2 minute cooldown time."));
		_internalproblems.add(new InternalProblem("Life Support Failure", "null"));
		_internalproblems.add(new InternalProblem("Non-functioning controls", "Pick one of the 3 control stations and choose a specific control that he/she will no longer be able to use until a mini-game has been succesfully completed."));
		_internalproblems.add(new InternalProblem("Power Shortage", "Cut the power to the whole ship, seting a huge taget to the enemies, also causing another mini-game to be completed to regain power."));
		_internalproblems.add(new InternalProblem("Radiation leak", "Cause a leak in the neclear core, giving team radiation damage, and causing temporary drift through space untill core has been repaired."));
		_internalproblems.add(new InternalProblem("Screen Cracks", "More of a visual Effect, give the spaceship window an X amount of cracks added, so make it more dificult to see."));
		_internalproblems.add(new InternalProblem("Temporary shield removal", "Temporarily remove the team ship sheild, causing damage dealt by enemies, meteors, ex.. to double the damage."));
		_internalproblems.add(new InternalProblem("Weapon Malfunction", "Out of all the weapons the weapon controll station has, choose one to tempoarily be disabled/broken."));
	}
	
	public String getInternalProblem(int i) {
		return _internalproblems.get(i).getName();
	}
	
	public String getDefinition(int i) {
		return _internalproblems.get(i).getDefinition();
	}
	
	public int getInternalProblems() {
		return _internalproblems.size();
	}
}