#include "network/EventHandler.h"

void EventHandler::processEvent(std::string event) {
	debug("Event: \'%s\'", event.c_str());
	std::vector<std::string> str = convert::split(event, ';');

	// Max power change event
	if (str[0] == "7") {
		debug("Changing %s's max power relative to %i", str[1].c_str(), convert::toInt(str[2]));
		Reactor::_reactor.setMaxPower(str[1], convert::toInt(str[2]));
	}
}