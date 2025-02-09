/*
 * Copyright 2021 SYSON, MICHAEL B.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @company: USBONG
 * @author: SYSON, MICHAEL B.
 * @date created: 20211117
 * @date updated: 20220108; from 20211209
 * @website address: http://www.usbong.ph
 *
 */

#include <stdio.h>
#include <math.h>

#include "Unit.h"

#include <string>

//Reference: https://stackoverflow.com/questions/34152424/autodetection-of-os-in-c-c;
//answer by: Jeegar Patel, 20151208T0940
//auto-identify if Windows Machine
#ifdef _WIN32
	#include <windows.h> //Windows Machine
#endif
	
Unit::Unit(SDL_Renderer* mySDLRendererInput, int xPos, int yPos, int zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,zPos, windowWidth, windowHeight)
{ 
  currentState=MOVING_STATE;

	iMyWidthAsPixel=64; 
  iMyHeightAsPixel=64; 
    
  iMyXPosAsPixel=xPos;
  iMyYPosAsPixel=yPos;
  iMyZPosAsPixel=zPos;

	iStepXAsPixel=1;
	iStepYAsPixel=1;
	iStepZAsPixel=1;

	fMyWindowWidth=windowWidth;
	fMyWindowHeight=windowHeight;
			
  iMyStartXPos=iMyXPosAsPixel;
	iMyStartYPos=iMyYPosAsPixel;
    
  iMyScoreValue=200;
    
  //added by Mike, 20211117
  iCountAnimationFrame=0;
  iCurrentKeyInput=2; //start: face RIGHT

  mySDLRenderer = mySDLRendererInput;
  
  texture = loadTexture((char*)"textures/unit.png");
	
	//added by Mike, 20211118  
  isCollidable=true;
}

Unit::~Unit()
{
}

void Unit::drawUnit() {	
  	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;
  	
		iCountAnimationFrame=iCountAnimationFrame+1;		               																				

		if (iCountAnimationFrame>=2) { //2 frames of animation only
			iCountAnimationFrame=0;
		}
	    	
  	SrcR.x = 0+iCountAnimationFrame*iMyWidthAsPixel;
  	//edited by Mike, 2021117
//  	SrcR.y = 0;
	//note: based on image file's correct sequence vertically
/*
	KEY_W = 0,
	KEY_S,
	KEY_D,
	KEY_A,
*/
  	SrcR.y = 0+iCurrentKeyInput*iMyHeightAsPixel;

	
  	SrcR.w = iMyWidthAsPixel; 
  	SrcR.h = iMyHeightAsPixel; 
	
  	DestR.x = getXPos();
  	DestR.y = getYPos();
  	
/* //edited by Mike, 20211209  	
  	DestR.w = iMyWidthAsPixel;
  	DestR.h = iMyHeightAsPixel;
*/
  	DestR.w = fGridSquareWidth;
  	DestR.h = fGridSquareHeight;	
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white
		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);
}

void Unit::drawExplosion() {
}

void Unit::draw()
{
    switch (currentState)
    {
        case INITIALIZING_STATE:
        case MOVING_STATE:
          drawUnit();
          break;
      	case DYING_STATE:
					drawExplosion();
        	break;
      	case HIDDEN_STATE:
        	break;        	
	}    
}


void Unit::move(int iKeyInput) 
{
	iCurrentKeyInput = iKeyInput;
//	printf("iCurrentKeyInput: %i\n",iCurrentKeyInput);
}

void Unit::update()
{
    switch (currentState)
    {
        case INITIALIZING_STATE:                
        case MOVING_STATE:      
			  		break;
        case DYING_STATE:
			  		break;
      	case HIDDEN_STATE:
        		break;			  		
        default: //STANDING STATE
          	break;//do nothing    
		}
}

void Unit::changeState(int s)
{
  currentState=s;                  
}

int Unit::getState()
{
    return currentState;
}

void Unit::reset(int iXPosInput, int iYPosInput)
{
    iMyXPosAsPixel=iXPosInput;
    iMyYPosAsPixel=iYPosInput;  

    changeState(INITIALIZING_STATE);
    setCollidable(false);
    iDeathAnimationCounter=0;
}


void Unit::hitBy(MyDynamicObject* mdo)
{
/*	//removed by Mike, 20211118
    setCollidable(false);	
    //TO-DO: -add: score
    changeState(DYING_STATE);
*/    
}

void Unit::destroy()
{
}
