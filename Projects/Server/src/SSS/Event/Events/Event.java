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
     * Constructor for a new event with a new ID
     * @param id Internal ID for the event
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
