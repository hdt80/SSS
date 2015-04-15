import java.io.IOException;
import java.util.HashMap;

public class InternalValues {
    private HashMap<String, String> values;

    public InternalValues() {
        values = new HashMap<>();
    }

    /**
     * Process the String supplied and update the value on the server
     * @param msg String to be processed
     */
    public void processString(String msg) {
        // Messages are in [1-3] Client name, [4-7] SET/GET, [8-n] Key, :, [n-n] Value
        if (msg.substring(4, 7).equals("SET")) {
            setValue(msg);
        } else if (msg.substring(4, 7).equals("GET")) {
            requestValue(msg);
        } else {
            Logger.warn("Unknown request: \'" + msg + "\'");
        }
    }

    /**
     * Set an internal value for the server based on the unprocessed String
     * @param msg The key and value seperated by an ':'
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
     * Returns a value on the server that matches the String
     * @param msg Value to be gotten
     * @return The value on the server, or null if that value hasn't been set
     */
    public String requestValue(String msg) {
        Logger.debug('\'' + msg.substring(8, msg.length()) + "\'=\'" + values.get(msg.substring(8, msg.length())) + "\'");
        try {
            Client toSend = Server.getClientByName(msg.substring(0, 3));
            if (toSend != null) {
                if (values.containsKey(msg.substring(8, msg.length()))) {
                    toSend.send(values.get(msg.substring(8, msg.length())));
                } else {
                    Logger.warn("Key \'" + msg.substring(8, msg.length()) + "\' does not have a value");
                }
            } else {
                Logger.error("Unknown client ID \'" + msg.substring(0, 3) + "\'");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return values.get(msg.substring(4, msg.length()));
    }

    public void print() {
        Logger.debug(values.toString());
    }
}
