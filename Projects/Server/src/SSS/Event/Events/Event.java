package SSS.Event.Events;

public abstract class Event {
    private int id;

    /**
     * Default constructor for an Event
     */
    public Event() {
        id = -1;
    }

    /**
     *
     * @param id
     */
    public Event(int id) {
        this.id = id;
    }

    /**
     * Method overridden by events
     */
    public void run() {
        // To be overran by child Events
    }
}
