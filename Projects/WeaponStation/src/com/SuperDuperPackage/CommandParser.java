package com.SuperDuperPackage;
import java.util.ArrayList;

import com.Networking.Network;

import Vector.Vector3f;


public class CommandParser {

			private String[] array;
			private ArrayList<Enemy> list;
			private String[] history;
			private Vector3f shipPos; 
			private CPanel panel;
			private Network net;
			private ArrayList<Missle> list1;
			
		public void parseCommand(String s/*, ArrayList<Enemy> list, ArrayList<Missle> list1,  String[] history, Vector3f shipPos, CPanel panel, Network net*/){
			//check for the command token
			this.panel = panel;
			this.list = panel.getEnemies();
			this.history = panel.getHistory();
			this.shipPos = panel.getShipPos();
			this.net = panel.getNet();
			this.list1 = panel.getMissleList();
			array = s.split(" ");
			
			
			String firstWord = array[0].toLowerCase();
			if(firstWord.equals("create")){
				panel.addEnemy(new Enemy(new Vector3f(0,0,0), new Vector3f(Float.parseFloat(array[2]),Float.parseFloat(array[3]),Float.parseFloat(array[4])), array[1], 100));
			}else if(firstWord.equals("attack")){
				boolean test = false;
				System.out.println("attack");
				for (int i = 0; i < list.size(); i++) {
					if(list.get(i).getName().toLowerCase().equals(array[1].toLowerCase())){
						list1.add(new Missle(shipPos,"Missle" + list.get(i).getName(), list.get(i)));
						test = true;
						//System.out.println(shipPos.getX() + ", " + shipPos.getY() + ", " + shipPos.getZ());
					}
				}
				if(test == false){panel.setError("Enemy(" + array[1] + ") does not exist...");}
			}else if(firstWord.toLowerCase().equals("quit")){
				System.exit(0);
			}else if(firstWord.toLowerCase().equals("info")){
				System.out.println("info");
				for (int i = 0; i < list.size(); i++) {
					for (int j = history.length-1; j > 0; j--) {
						history[j] = history[j-1];
					}
					history[0] = list.get(i).getName() + " Z:" + list.get(i).getZ() + " X:" + list.get(i).getX() + " Y:" + list.get(i).getY();
				}
			}else if(firstWord.toLowerCase().equals("write")){
				String output = "";
				for (int i = 1; i < array.length; i++) {
					output = output + " " + array[i];
				}
				net.Sendout(output);
			}else if(firstWord.toLowerCase().equals("help")){
				panel.setError("Your commands are as follows: info, help, attack{target name}, system.info");
			}else if(firstWord.toLowerCase().equals("system.info")){
				panel.setError("Current reactor energy: " + panel.getEnergy());
			}else if(firstWord.toLowerCase().equals("force.quit")){
				System.exit(0);
			}
			else{
				panel.setError("Command \"" + array[0] + "\" does not exist");
			}
			
		}
		public CommandParser(CPanel panel){
			this.panel = panel;
			this.list = panel.getEnemies();
			this.history = panel.getHistory();
			this.shipPos = panel.getShipPos();
			this.net = panel.getNet();
			this.list1 = panel.getMissleList();
		}
}
