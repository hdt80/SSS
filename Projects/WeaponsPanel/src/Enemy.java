import static java.lang.Math.cos;
import static java.lang.Math.sin;
import static org.lwjgl.opengl.GL11.*;
import Vector.*;


public class Enemy {
	public int x , y, z, ID;
	public Vector3f v3;
	public int health;
	public int radius;
	public boolean selected = false;
	public boolean ally;
	private float colorRed, colorBlue, colorGreen, alpha;
	
	Enemy (Vector3f v3, int ID, boolean ally){
		this.v3 = v3;
		this.ID = ID;
		this.ally = ally;
		x = (int) v3.getX();
		y = (int) v3.getY();
		z = (int) v3.getZ();
		health = 30;
		radius = 15;
		setColors();
	}
	
	boolean inBounds(int mousex, int mousey) {
		if (mousex > x - radius && mousex < x + radius && mousey > y - radius && mousey < y + radius){
			return true;
		}
		else{
			return false;
		}
	}
	
	boolean inHitBounds(int mx, int my, int mz) {
		if (mx > x - radius && mx < x + radius && my > y - radius && my < y + radius && mz > z - radius && mz < z + radius){
			return true;
		}
		else{
			return false;
		}
	}
	
	void update(){
		x = (int) v3.getX();
		y = (int) v3.getY();
		z = (int) v3.getZ();
		//System.out.println(x + "," + y + "," + z);
		setColors();
		if (selected == true) {
			//print info
			//draws yellow circle around selected enemy
			DrawCircle(x,y,16,150);
		}
	}
	
	void setColors() {
		colorRed = 255;
		colorGreen = 0;
		colorBlue = 0;
		//the farther away it gets, the darker it gets
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
		glColor4f(colorRed, colorGreen, colorBlue, alpha);
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
	
	void DrawCircle(float cx, float cy, float r, int num_segments) 
	{ 
		glColor3f(1f, 1f, 0f);

		float theta = (float) (2 * 3.1415926 / (float)(num_segments)); 
		float c = (float) cos(theta);//precalculate the sine and cosine
		float s = (float) sin(theta);
		float t;

		float x = r;//we start at angle = 0 
		float y = 0; 
	    
		glBegin(GL_LINE_LOOP); 
		for(int ii = 0; ii < num_segments; ii++) 
		{ 
			glVertex2f(x + cx, y + cy);//output vertex 
	        
			//apply the rotation matrix
			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		} 
		glEnd(); 
	}
}
