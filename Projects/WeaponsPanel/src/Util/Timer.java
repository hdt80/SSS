package Util;

public class Timer {
	private long startTime;
	private long duration;
	
	public Timer(long duration) {
		this.duration = duration;
		this.startTime = System.currentTimeMillis();
	}
	
	public boolean isOver() {
		return startTime + duration < System.currentTimeMillis();
	}
	
	public void reset() {
		startTime = System.currentTimeMillis();
	}
}
