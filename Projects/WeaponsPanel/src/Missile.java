import static org.lwjgl.opengl.GL11.GL_BLEND;
import static org.lwjgl.opengl.GL11.GL_ONE_MINUS_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.GL_SRC_ALPHA;
import static org.lwjgl.opengl.GL11.GL_TRIANGLE_FAN;
import static org.lwjgl.opengl.GL11.glBegin;
import static org.lwjgl.opengl.GL11.glBlendFunc;
import static org.lwjgl.opengl.GL11.glColor4f;
import static org.lwjgl.opengl.GL11.glEnable;
import static org.lwjgl.opengl.GL11.glEnd;
import static org.lwjgl.opengl.GL11.glPopMatrix;
import static org.lwjgl.opengl.GL11.glPushMatrix;
import static org.lwjgl.opengl.GL11.glScalef;
import static org.lwjgl.opengl.GL11.glTranslatef;
import static org.lwjgl.opengl.GL11.glVertex2f;
import Vector.*;

public class Missile {
    
	public int x, y, z, speed;
	public Vector3f v3;
	public Vector3f targetV;
	public Vector3f trajectory;
	public int radius = 5;
	float alpha;
	public boolean ally;
	
	Missile(Vector3f v3, Vector3f targetV, int speed, boolean ally) {
		this.v3 = v3;
		this.speed = speed;
		this.ally = ally;
		this.targetV = targetV;
		setTrajectory(targetV);
		update();
	}
	
	void update(){
		x = (int) v3.getX();
		y = (int) v3.getY();
		z = (int) v3.getZ();
		System.out.println(x+","+y+","+z);
		setColors();
		this.v3.add(trajectory);
		this.v3 = this.v3.add(trajectory);
	}
	
	public void setTrajectory(Vector3f v3) {
		trajectory = (v3.sub(this.v3).normalized().mul(speed));
	}

	void setColors() {
		if (z < 400 && z != 0) {
			alpha = 1f - (float)(z)/400;
		}
		else if (z == 0) {
			alpha = 1;
		}
		else {
			alpha = 0;
		}
	}
	
	void draw() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1f, 1f, 1f, alpha);
		glPushMatrix();
		glTranslatef(x, y, 0);
		glScalef(radius, radius, 1);

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0, 0);
		for(int i = 0; i <= 150; i++){ //NUM_PIZZA_SLICES decides how round the circle looks.
		    double angle = Math.PI * 2 * i / 150;
		    glVertex2f((float)Math.cos(angle), (float)Math.sin(angle));
		}
		glEnd();

		glPopMatrix();
	}
	
}
