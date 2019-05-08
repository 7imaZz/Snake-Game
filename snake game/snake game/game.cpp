#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <gl\glut.h>
#include "game.h" 
#pragma comment(lib, "Winmm.lib") 

#define COLUMNS 40
#define ROWS 40


int FPS = 10; 
extern short sDirection; 
bool gameOver = false;  
int score = 0; 
void displayCallback(); 
void reshapeCallback(int ,int);
void timerCallback(int); 
void keyboardCallback(int, int, int); 


void init(){
	glClearColor(0.0, 0.0, 0.0, 1.0); 
	initGrid(COLUMNS, ROWS); 
}

int main(int argc, char **argv){

	mciSendString("open \"music.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3 repeat", NULL, 0, NULL);
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); 
	glutInitWindowSize(500, 500); 
	glutCreateWindow("Snake"); 
	glutPositionWindow(400, 150);
	glutDisplayFunc(displayCallback); 
	glutReshapeFunc(reshapeCallback); 
	glutTimerFunc(0, timerCallback, 0);
	glutSpecialFunc(keyboardCallback); 
	init(); 
	glutMainLoop(); 
	
	return 0; 
}

void displayCallback(){
	

	glClear(GL_COLOR_BUFFER_BIT); 
	drawGrid();
	drawSnake(); 
	drawFruit(); 
	glutSwapBuffers(); 
	if(gameOver){
		mciSendString("stop mp3", NULL, 0, NULL);
		PlaySound(TEXT("death.wav"), NULL, SND_SYNC);
		char _score [10]; 
		itoa(score, _score, 10); 
		char text[50] = "Your Score: "; 
		strcat(text, _score); 
		MessageBox(NULL, text, "GAME OVER", 0); 
		gameOver=false; 
		mciSendString("play mp3 from 0", NULL, 0, NULL);
		mciSendString("play mp3 repeat", NULL, 0, NULL);
		score=0; 
	}
}

void reshapeCallback(int w, int h){
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0); 
	glMatrixMode(GL_MODELVIEW);
}

void timerCallback(int){
	
	glutPostRedisplay(); 
	glutTimerFunc(1000/FPS, timerCallback, 0); 

}

void keyboardCallback(int key, int, int){
	switch (key){
	case GLUT_KEY_UP:
		if(sDirection != DOWN)
			sDirection = UP;
		break;
	case GLUT_KEY_DOWN:
		if(sDirection != UP)
			sDirection = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		if(sDirection != LEFT)
			sDirection = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		if(sDirection != RIGHT)
			sDirection = LEFT;
		break;
	}
}