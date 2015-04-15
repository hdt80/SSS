package com.sss.mastercontroller.objects;

public class InternalProblem {
	
	private String name;
	private String definition;

	public InternalProblem(String name, String def) {
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