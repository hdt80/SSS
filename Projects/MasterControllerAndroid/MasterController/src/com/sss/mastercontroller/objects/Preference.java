package com.sss.mastercontroller.objects;

public class Preference {
	
	private String name;
	private String definition;

	public Preference(String name, String def) {
		this.name = name;
		this.definition = def;
	}
	
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDefinition() {
		return definition;
	}

	public void setDefinition(String definition) {
		this.definition = definition;
	}
}