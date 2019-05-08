#include <stdlib.h>
#include <Windows.h>
#include <MMSystem.h>
#include <gl\glut.h>
#include <random>
#include <ctime>
#include "game.h"


extern int FPS;
extern int score; 
int gridX, gridY;
int snakeLength = 5; 
bool food = true;
int foodX, foodY; 
int posX[60] = {20, 20, 20, 20, 20}, posY[60] = {20, 19, 18, 17, 16}; 
short sDirection = RIGHT; 
extern bool gameOver; 

void initGrid(int x, int y){
	gridX = x;
	gridY = y; 
}

void drawGrid(){
	for(int x=0; x<gridX; x++){
		for(int y=0; y<gridY; y++){
			unit(x, y); 
		}
	}
}

void unit(int x, int y){

	if( x==0 || y==0 || x==gridX-1 || y==gridY-1){
		glColor3f(1.0, 0.0, 0.0); 
		glLineWidth(3.0); 
	}else{
		glLineWidth(1.0); 
		glColor3f(0.0, 0.0, 0.0);	
	}
	
	glBegin(GL_LINE_LOOP); 
		glVertex2f(x, y); 
		glVertex2f(x+1, y);
		glVertex2f(x+1, y+1);
		glVertex2f(x, y+1);
	glEnd(); 
}

void drawSnake(){

	for(int i=snakeLength-1; i>0; i--){
		posX[i] = posX[i-1]; 
		posY[i] = posY[i-1];
	}

	if(sDirection == UP)
		posY[0]++; 
	else if(sDirection == DOWN)
		posY[0]--; 
	else if(sDirection == RIGHT)
		posX[0]++; 
	else if(sDirection == LEFT)
		posX[0]--; 

	for(int i=0; i<snakeLength; i++){
		if (i==0)
			glColor3f(1.0, 1.0, 0.0);  
		else
			glColor3f(0.0, 1.0, 0.0); 
		glRectd(posX[i], posY[i], posX[i]+1, posY[i]+1);  
	}

	if (posX[0]==0 || posX[0]==gridX-1 || posY[0]==0 || posY[0]==gridY-1){

		gameOver = true; 
		snakeLength = 5;
		sDirection = RIGHT;
		FPS = 10;
		posX[0]=20;
		posX[1]=20;
		posX[2]=20;
		posX[3]=20;
		posX[4]=20;

		posY[0]=20;
		posX[1]=19;
		posY[2]=18;
		posY[3]=17;
		posY[4]=16;
	}
	if (posX[0] == foodX && posY[0] == foodY){

		score+=5; 
		FPS++;
		snakeLength++; 
		PlaySound(TEXT("bite.wav"), NULL, SND_ASYNC);
		food = true;  
	}

	for(int j=1;j<snakeLength;j++)
	{
        if(posX[j]==posX[0] && posY[j]==posY[0]){
			
            gameOver=true;
			snakeLength = 5;
			FPS = 10;
			sDirection = RIGHT;
			posX[0]=20;
			posX[1]=20;
			posX[2]=20;
			posX[3]=20;
			posX[4]=20;

			posY[0]=20;
			posX[1]=19;
			posY[2]=18;
			posY[3]=17;
			posY[4]=16;
		}
	}
}

void drawFruit(){
	glColor3f(0.0, 0.0, 1.0); 
	if (food)
		random(foodX, foodY);
	food = false; 
	glRectf(foodX, foodY, foodX+1, foodY+1); 
}

void random(int &x, int &y){
	
	int _maxX = gridX-2; 
	int _maxY = gridY-2; 
	int _min = 1;
	srand(time(NULL)); 
	x = _min + rand()%(_maxX-_min); 
	y = _min + rand()%(_maxY-_min); 
}