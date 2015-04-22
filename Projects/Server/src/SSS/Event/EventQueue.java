package SSS.Event;

import SSS.Event.Events.Event;

import java.util.ArrayList;
import java.util.concurrent.Executors;

public class EventQueue {
    private ArrayList<Event> queue;
    private boolean          closed;

    public EventQueue() {
        queue = new ArrayList<>();
    }

    /**
     * Add a new Event to the queue
     * @param event
     */
    public void enqueue(Event event) {
        queue.add(event);
    }

    /**
     * Returns if there are any queued events
     * @return If there are queued events
     */
    public boolean isEmpty() {
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
     * Begin running through all the queued events until we close
     */
    public void run() {
        Executors.newSingleThreadExecutor().execute(new Runnable() {
            @Override
            public void run() {
                while (!closed) {
                    if (!isEmpty()) {
                        queue.get(0).run();
                        queue.remove(0);
                    }
                }
            }
        });
    }
}
