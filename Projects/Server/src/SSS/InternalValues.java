package SSS;

import SSS.Event.EventHandler;
import SSS.Util.Logger;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * InternalValues is a class that holds all the server values
 * All parsing of String will be done here, and not in message handlers
 */
public class InternalValues {
    private HashMap<String, String> values;

    public InternalValues() {
        values = new HashMap<>();
    }

    /**
     * Parse an unparsed message from a Client and update the key and value that are seperated by a colon
     * @param msg Unparsed message from a Client
     */
    public void setValue(String msg) {
        int keyStop = msg.indexOf(":");
        Logger.debug("keyStop at " + keyStop);
    }

    public void print() {
        Logger.debug(values.toString());
    }
}
