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
     * Set an internal value for the server based on the unprocessed String
     * @param msg The key and value separated by an ':'
     */
    public void setValue(String msg) {
        int keyStop = 0;

        for (int i = 0; i < msg.length(); ++i) {
            if (msg.charAt(i) == ':') {
                keyStop = i;
                break;
            }
        }
        Logger.debug("Setting:\'" + msg.substring(8, keyStop) + "\' to \'" + msg.substring(keyStop + 1, msg.length()) + '\'');
        values.put(msg.substring(8, keyStop), msg.substring(keyStop + 1, msg.length()));
    }

    /**
     * Get the value of the key stored in the HashMap
     * @param key Key in the HashMap
     * @return The value of the key, or null if they key hasn't been set
     */
    public String getValue(String key) {
        Logger.debug('\'' + key.substring(8, key.length()) + "\'=\'" + values.get(key.substring(8, key.length())) + "\'");
        try {
            Client toSend = Server.get().getClientByName(key.substring(0, 3));
            if (toSend != null) {
                if (values.containsKey(key.substring(8, key.length()))) {
                    toSend.send(values.get(key.substring(8, key.length())));
                } else {
                    Logger.warn("Key \'" + key.substring(8, key.length()) + "\' does not have a value");
                }
            } else {
                Logger.error("Unknown client ID \'" + key.substring(0, 3) + "\'");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return values.get(key.substring(4, key.length()));
    }

    public void print() {
        Logger.debug(values.toString());
    }
}
