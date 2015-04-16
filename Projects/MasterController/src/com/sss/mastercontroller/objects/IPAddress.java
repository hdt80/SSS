package com.sss.mastercontroller.objects;

public class IPAddress {
	String adress = "0.0.0.0";
	String definition = "default def";
	int index = 0;
	public IPAddress(String adress, String def, int index) {
		this.adress = adress;
		this.definition = def;
		this.index = index;
	}
	
	public String getAddress() {
		return adress;
	}
	
	public String getDefinition() {
		return definition;
	}
	
	public void setAdress(String adress) {
		this.adress = adress;
	}
	
	public int getIndex() {
		return index;
	}
}