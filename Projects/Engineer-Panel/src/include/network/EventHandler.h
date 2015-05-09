#ifndef NETWORK_EVENTHANDER_H
#define NETWORK_EVENTHANDER_H

#include <string>
#include <string.h>
#include <util/Logger.h>
#include <util/Convert.h>
#include <power_comps/Reactor.h>

class EventHandler {
	public:
		static void processEvent(std::string event);
};

#endif