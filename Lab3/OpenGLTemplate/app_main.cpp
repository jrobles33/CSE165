#include <iostream>
#include <cmath>
#include <vector>
#include <deque>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;


float red = 0.0;
float green  = 0.0;
float blue = 0.0;
float RED = 1.0;
float GREEN = 1.0;
float BLUE = 1.0;
bool drawing;

struct Rect {
    float x;
    float y;
    float w;
    float h;
    
    float r;
    float g;
    float b;
    
    Rect ();
    
    Rect (float x, float y, float w, float h, float r, float g, float b);
    
    bool contains(float mx, float my);
    
    void draw();
};

Rect::Rect (){
    x = -0.8;
    y = 0.8;
    w = 0.8;
    h = 0.8;
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

bool Rect::contains(float mx, float my){
    return mx >= x && mx <= x + w && my <= y && my >= y - h;
}

Rect::Rect (float x, float y, float w, float h, float r, float g, float b){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rect::draw(){
    glLineWidth(3);
    
    glColor3f(r, g , b);
    glBegin(GL_POLYGON);
    
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y - h);
    glVertex2f(x, y - h);
    
    glEnd();
    }


struct Point {
    float x;
    float y;
    float r;
    float g;
    float b;
    
    Point(float x = 0, float y = 0, float r = 0, float g = 0, float b = 0) {
        this->x=x;
        this->y=y;
        this->r=r;
        this->g=g;
        this->b=b;
    }
};

vector<Rect> buttons;
deque<Point> cursor;

// Store the width and height of the window
int width = 640, height = 640;



//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(1.0, 1.0, 1.0, -1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    

    // Draw stuff here
    
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].draw();
    }

    
    for (int i = 0; i < cursor.size(); i++){
        if (drawing == true) {
            
            glPointSize(7);
            glColor3f(cursor[i].r, cursor[i].g, cursor[i].b);
            glBegin(GL_POINTS);
            glVertex2f(cursor[i].x, cursor[i].y);
            glEnd();
        }
    }

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);
    
    if (b == 0){
        if (s == 0){
            //drawing with red
            if(buttons[0].contains(mx, my) == true){
                red = 1.0;
                green = 0.0;
                blue = 0.0;
            }
            //drawing with green
            if(buttons[1].contains(mx, my) == true){
                red = 0.0;
                green = 1.0;
                blue = 0.0;
            }
            //drawing with blue
            if(buttons[2].contains(mx, my) == true){
                red = 0.0;
                green = 0.0;
                blue = 1.0;
            }
            //drawing with black
            if(buttons[3].contains(mx, my) == true){
                red = 0.0;
                green = 0.0;
                blue = 0.0;
            }
            //erasing
            if(buttons[4].contains(mx, my) == true){
                red = 1.0;
                green = 1.0;
                blue = 1.0;
            }
            drawing = true;
            cursor.push_front(Point(mx, my, red, green, blue));
        }
    }

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
    float mx = (float)x;
    float my = (float)y;
    
    windowToScene(mx, my);
    
    if (drawing) {
        cursor.push_front(Point(mx, my, red, green, blue));
    }

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	
    switch (key) {
        case 27:
            exit(0);
            break;
        case 114: // r is pressed 
            red = 1.0;
            green = 0.0;
            blue = 0.0;
            break;
        case 119: // w is pressed
            red = 1.0;
            green = 1.0;
            blue = 1.0;
            break;
        case 103: // g is pressed
            red = 0.0;
            green = 1.0;
            blue = 0.0;
            break;
        case 98: // b is pressed
            red = 0.0;
            green = 0.0;
            blue = 1.0;
            break;
        default:
            break;
    }

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


void idle() {

}


int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("CSE165 OpenGL Demo");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
    
    
    //red button
    buttons.push_back(Rect(-0.9, -0.875, 0.1, 0.1, 1.0, 0.0, 0.0));
    //green button
    buttons.push_back(Rect(-0.7, -0.875, 0.1, 0.1, 0.0, 1.0, 0.0));
    //blue button
    buttons.push_back(Rect(-0.5, -0.875, 0.1, 0.1, 0.0, 0.0, 1.0));
    //black button
    buttons.push_back(Rect(-0.3, -0.875, 0.1, 0.1, 0.0, 0.0, 0.0));
    //erase button
    buttons.push_back(Rect(-0.1, -0.875, 0.1, 0.1, 1.0, 0.75, 0.79));
    //toolbar button
    buttons.push_back(Rect(-1.0, -0.85, 2.0, 2.0, 0.5, 0.5, 0.5));


	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
    glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);
    
    glutIdleFunc(idle);

	// Start the main loop
	glutMainLoop();
}
