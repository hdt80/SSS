package SSS.Event;

import SSS.Event.Events.*;
import SSS.Util.Logger;

import java.util.ArrayList;


public class EventHandler {

	// ==================================================
	// enum declaration of the different event types
	// ==================================================
	public enum EventType {
		SPAWNENEMY    (0), // Occurs when the Master Controller spawns enemies
		COLLISION     (1), // Occurs when when the ship collides with another object, such as an enemy, meteror, or a giant fat oaf Bryce
		SHIPFIRES     (2), // Occurs when we fire any weapon
		MINIGAMEDONE  (3), // Occurs when a minigame is completed
		POWERCHANGE   (4), // Occurs when the engineer changes the power level in a cell
		ENEMYDESPAWN  (5), // Occurs when an enemy is despawned
		ENEMYFIRES    (6), // Occurs when an enemy fires it's weapon
		MAXPOWERCHANGE(7); // Occurs when the eng panel should update a cell's max power

		final int id; // Internal ID of the event

		EventType(int id) {
			this.id = id;
		}

		int getId() {
			return id;
		}
	};
	// ==================================================


	private ArrayList<String> enemies;
	private EventQueue        eventQueue;

	/**
	 * Default constructor for an EventHandler
	 */
	public EventHandler() {
		enemies    = new ArrayList<String>();
		eventQueue = new EventQueue();
		initEnemies();
		eventQueue.run();
	}

	/**
	 * Initialize the enemy types into internal values
	 */
	private void initEnemies() {
		enemies.add("Fighter Ship 1");
	}

	/**
	 * When an event message is read from a client
	 * @param args Event arguments to be passed on event's creation
	 */
	public void callEvent(ArrayList<String> args) {
		EventType eventType = EventType.values()[Integer.parseInt(args.get(0))];
		switch (eventType) {
			case COLLISION:
				eventQueue.enqueue(new CollisionEvent(Integer.parseInt(args.get(1))));
				break;
			case SPAWNENEMY:
				eventQueue.enqueue(new SpawnEnemyEvent(Integer.parseInt(args.get(1)), Integer.parseInt(args.get(2)), Integer.parseInt(args.get(3))));
				break;
			case POWERCHANGE:
				eventQueue.enqueue(new PowerChangeEvent(args.get(1), Integer.parseInt(args.get(2))));
				break;
            case MINIGAMEDONE:
                eventQueue.enqueue(new MinigameDoneEvent(args.get(1), args.get(2)));
                break;
			case SHIPFIRES:
				eventQueue.enqueue(new ShipFiresEvent(args.get(1), Integer.parseInt(args.get(2))));
				break;
			default:
				Logger.error("Unknown event type " + args.get(0));
				break;
		}
	}
}