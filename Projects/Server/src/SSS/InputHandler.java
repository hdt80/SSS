package SSS;

import SSS.Util.Logger;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.concurrent.Executors;

/**
 * InputHandler is a class to handle and parse all the input from Clients
 */
public class InputHandler {
    private ArrayList<String> queue;
    private boolean closed;

    public InputHandler() {
        queue = new ArrayList<>();
        closed = false;
    }

    /**
     * Add an input String to be processed to the queue
     * @param input String to be proccessed
     */
    public void processInput(String input) {
        queue.add(input);
    }

    /**
     * Returns if there are any queued events
     * @return True  - The queue is not empty and is processing requests
     *         False - The queue is empty
     */
    public boolean isEmpty() {
        // If we don't yield the Thread here, the anonymous runnable inside run() never properly
        // calls queue.isEmpty(), so by yielding the Thread, we guarantee the isEmpty to be called
        Thread.yield();
        return queue.isEmpty();
    }

    /**
     * Return if the event handler is closed and done handling events
     * @return The value of closed
     */
    public boolean getClosed() {
        return closed;
    }

    /**
     * Set closed to the new closed
     * @param closed The new value of closed
     */
    public void setClosed(boolean closed) {
        this.closed = closed;
    }

    /**
     * Begin processing all the queued events
     */
    public void run() {
        Executors.newSingleThreadExecutor().execute(new Runnable() {
            @Override
            public void run() {
                while (!closed) {
                    if (!isEmpty()) {
                        processString(queue.get(0));
                        queue.remove(0);
                    }
                }
            }
        });
    }

    /**
     * Process the String
     * @param input Input to be processed
     */
    private void processString(String input) {
        //Logger.debug("I'm proccessing: \'" + input + '\'');
        if (input.substring(4, 7).equals("EVN")) {
            Logger.debug("Event");
            Server.get().eventHandler.callEvent(new ArrayList<>(Arrays.asList(input.substring(8).split(";"))));
        }
    }
}
