package com.sss.mastercontroller.connections;

import java.util.ArrayList;

import com.sss.mastercontroller.objects.IPAddress;

public class Addresses {
	
	private ArrayList<IPAddress> _addresses;
	
	public Addresses() {
		
		_addresses = new ArrayList<IPAddress>();

		_addresses.add(new IPAddress("0.0.0.0", "ip template", 0));
		_addresses.add(new IPAddress("10.65.173.226", "Current Computer I'm using for the server", _addresses.size()));
		_addresses.add(new IPAddress("10.65.175.53", "Mason Cluff's computer in 1-20, when not in c++ spot", _addresses.size()));
		_addresses.add(new IPAddress("10.65.175.117", "Mason Cluff's computer in 1-20, when in c++ spot", _addresses.size()));
		_addresses.add(new IPAddress("127.0.0.1", "Connect through the local host.", _addresses.size()));
		_addresses.add(new IPAddress("172.19.172.90", "Laptop in f-1 with Admin privaledges.", _addresses.size()));
		_addresses.add(new IPAddress("192.168.0.105", "OGPC 2015 server connection.", _addresses.size()));
		_addresses.add(new IPAddress("192.168.1.2", "Bryce Hahn's Personal Desktop.", _addresses.size()));
		_addresses.add(new IPAddress("192.168.1.18", "Bryce Hahn's Personal laptop.", _addresses.size()));
		_addresses.add(new IPAddress("192.168.0.103", "Shitty piece of shit laptop, masons", _addresses.size()));
	}
	
	public String getAddress(int i) {
		return _addresses.get(i).getAddress();
	}
	
	public String getDefinition(int i) {
		return _addresses.get(i).getDefinition();
	}
	
	public int getAddresses() {
		return _addresses.size();
	}
	
	public int getIndex(int i) {
		return _addresses.get(i).getIndex();
	}
}