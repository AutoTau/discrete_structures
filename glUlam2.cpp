#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


// consts
const int ARESX = 761;
const int ARESY = 761;
const int WRESX = 2*ARESX;
const int WRESY = 2*ARESY;


// functions
void display();
void fill(unsigned char arr[ARESY][ARESX][3], unsigned int spiral[ARESY][ARESX]);
void fill(unsigned int arr[ARESY][ARESX]);
void print(unsigned char arr[ARESY][ARESX][3]);
int isPrime(int n);
long int factorial(long int n);

int main(int argc, char** argv) {
    // set up displays and mode (we won't change this!)
	glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    
	// set window size
	glutInitWindowSize (WRESX, WRESY); 
    
	// set window position on screen
	glutInitWindowPosition (0, 0);

	// set window title
    glutCreateWindow ("test");
    
    // set the display function to the one we made below
	glutDisplayFunc(display);

	// set up the display function to loop and make an animation
	// glutIdleFunc(glutPostRedisplay);
	
	// required to make the thing go 
    glutMainLoop();

	// exit
    return 0;
}


void display() {
	//  clear all pixels
    glClear (GL_COLOR_BUFFER_BIT);

	// make and fill in array
	static unsigned char arr[ARESY][ARESX][3] = {0};
	static unsigned int spiral[ARESY][ARESX] = {0};
	fill(spiral);
	fill(arr, spiral);

	// resize the array to the size of the window RES
	glPixelZoom((float)WRESX/ARESX, (float)WRESY/ARESY);
	
	// unpack wrong??
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

	// draw the array to the screen
	glDrawPixels(ARESX, ARESY, GL_RGB, GL_UNSIGNED_BYTE, arr);

	// start processing buffered OpenGL routines 
    glFlush ();
}


void fill(unsigned int arr[ARESY][ARESX]) {
	// start in middle
	int legLength = 1;
	int num = 1;
	int r = (ARESY/2);
	int c = (ARESX/2);

	// check that we don't go out of bounds on any edge
	while(true) {
		// do each of the four directions on each loop
		for(int i = 0; i < legLength; i++) { // right
			arr[r][c] = num;
			num += 2;
			c++;
			if(c > ARESX-1) {
				return;
			}
		}
		for(int i = 0; i < legLength; i++) { // down
			arr[r][c] = num;
			num += 2;
			r--;
			if(r < 0) {
				return;
			}
		}	
		legLength++;
		for(int i = 0; i < legLength; i++) { // left
			arr[r][c] = num;
			num += 2;
			c--;
			if(c < 0) {
				return;
			}
		}	
		for(int i = 0; i < legLength; i++) { // up
			arr[r][c] = num;
			num += 2;
			r++;
			if(r > ARESY-1) {
				return;
			}
		}
		legLength++;
	}
}


int isPrime(int n) {

	int divCount = 0;
	for(int i = 2; i*i <= n; i++) {
		if(n%i == 0) {
			divCount++;
		}
	}
	return divCount++;

	/*int i;
	for(i = 2; i < n; i++)
	{
		if(n % i == 0)
		{
			return 1;
		}
	}
	return i;
	*/
/*
int i;

	for(i=2; i<n; i++)
	{
		if(n % i == 0)
		{	
			return 1;
		}
	}
return 0;
*/
}


void fill(unsigned char arr[ARESY][ARESX][3], unsigned int spiral[ARESY][ARESX]) {
	for(int r = 0; r < ARESY; r++) {
		for(int c = 0; c < ARESX; c++) {
				arr[r][c][0] = 5*factorial(spiral[r][c] % 255) % 255; 





				 //1*isPrime(spiral[r][c]) % 255; // red
				arr[r][c][1] = 23*isPrime(spiral[r][c]) % 255; // green
				arr[r][c][2] = 53*isPrime(spiral[r][c]) % 255; // bluei
				
		}
	}
	//print(arr);    // error check
}

long int factorial(long int n)
{
	return (n==1 || n==0) ? 1 : factorial(n-1) * n;
}


void print(unsigned char arr[ARESY][ARESX][3]) {
	for(int r = 0; r < ARESY; r++) {
		for(int c = 0; c < ARESX; c++) {
			cout << (int)arr[r][c][0] << " "
				<< (int)arr[r][c][0] << " "
				<< (int)arr[r][c][0] << "   ";
		}
		cout << endl;
	}
}


