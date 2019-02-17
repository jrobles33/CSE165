#include <iostream>
#include <cmath>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


using namespace std;

// Store the width and height of the window
int width = 640, height = 640;

float mxpos, mypos;
bool quad1 = false, quad2 = false, quad3 = false, quad4 = false, quad5 = false, quad6 = false, quad7 = false, quad8 = false, quad9 = false;

int quadarr[9];


bool onClick = false;

int valuearr[2];


    float theta = 0;
    
    float thetaInc = M_PI/100;
    
    float radius = 0.25;
    
    float funcxOffset;
    
    float funcyOffset;

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
    
    //void windowToScene(float& x, float& y) {
	funcxOffset = (2.0f*(funcxOffset / float(width))) - 1.0f;
	funcyOffset = 1.0f - (2.0f*(funcyOffset / float(height)));
//}
    
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    

    // Draw stuff here
    
    
     glBegin(GL_LINE_LOOP);
    if (onClick == true){
    //Draw a Circle Here
    
    glColor3f(0.0, 1.0, 0.0);
    
    cout<<"our x funcxOffset is " << funcxOffset<<endl<<endl<<"our y funcyOffset is "<<funcyOffset<<endl<<endl;
    
    
   
    
    for (theta; theta < 2*M_PI; theta+=thetaInc) {
        glVertex2f(radius * cos(theta) + funcxOffset, radius * sin(theta) + funcyOffset);
    }
    
    
    
    }
    
    glEnd();
    
    
    
    
    
    
    //GRID DREW HERE
    
    glColor3f(1.0, 0.0, 0.0);
    
    glLineWidth(5);
    
    glBegin(GL_LINES);
    
    //bottom horizontal
    glVertex2f(-1.0, -0.33);
    glVertex2f(1.0, -0.33);
    
    //left vertical
    glVertex2f(-0.33, 1.0);
    glVertex2f(-0.33, -1.0);
    
    //middle horizontal
    //glVertex2f(-1.0, 0.0);
    //glVertex2f(1.0, 0.0);
    
    //middle vertical
    //glVertex2f(0.0, 1.0);
    //glVertex2f(0.0, -1.0);
    
    //top horizontal
    glVertex2f(-1.0, 0.33);
    glVertex2f(1.0, 0.33);
    
    //right vertical
    glVertex2f(0.33, 1.0);
    glVertex2f(0.33, -1.0);
    
    glEnd();
    
    //GRID ENDING HERE
    
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


int * QuadrantCheck(float x, float y){
    //a lot of if statements that are tedious because I'm too dumb to figure out how to do it iteravily
    //quad check so we know where we are and what gets full
    int curQuad;
    if (x >= 0 && x < 214 && y>=0 && y < 214){
        quad1 = true;
        quadarr[1] = 1;
        curQuad = 1;
        funcxOffset = 107;
        funcyOffset = 107;
    }
    else if (x > 214 && x < 428 && y >= 0 && y < 214){
        quad2 = true;
        quadarr[2] = 1;
        curQuad = 2;
        funcxOffset = 321;
        funcyOffset = 107;
    }
    else if (x > 428 && x < 640 && y>=0 && y < 214){
        quad3 = true;
        quadarr[3] = 1;
        curQuad = 3;
        funcxOffset = 535;
        funcyOffset = 107;
    }
    else if (x >= 0 && x < 214 && y> 214 && y < 428){
        quad4 = true;
        quadarr[4] = 1;
        curQuad = 4;
        funcxOffset = 107;
        funcyOffset = 321;
    }
    else if (x > 214 && x < 428 && y> 214 && y < 428){
        quad5 = true;
        quadarr[5] = 1;
        curQuad = 5;
        funcxOffset = 321;
        funcyOffset = 321;
    }
    else if (x > 428 && x < 640 && y> 214 && y < 428){
        quad6 = true;
        quadarr[6] = 1;
        curQuad = 6;
        funcxOffset = 535;
        funcyOffset = 321;
    }
    else if (x >= 0 && x < 214 && y> 428 && y < 640){
        quad7 = true;
        quadarr[7] = 1;
        curQuad = 7;
        funcxOffset = 107;
        funcyOffset = 535;
    }
    else if (x > 214 && x < 428 && y> 428 && y < 640){
        quad8 = true;
        quadarr[8] = 1;
        curQuad = 8;
        funcxOffset = 321;
        funcyOffset = 535;
    }
    else if (x > 428 && x < 640 && y> 428 && y < 640){
        quad9 = true;
        quadarr[9] = 1;
        curQuad = 9;
        funcxOffset = 535;
        funcyOffset = 535;
    }
    
    
    
    valuearr[0] = curQuad;
    valuearr[1] = funcxOffset;
    valuearr[2] = funcyOffset;

    return valuearr;
}
    
    
    

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

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
    
    if( s == 0) {
        onClick = true;
        
        QuadrantCheck(x,y);
        
       cout<<"We clicked at ( " <<x << " , " << y<< " ) and we are in quadrant "<< valuearr[0]<<endl;
        
    }
	glutPostRedisplay();
     
}
   
//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {

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
