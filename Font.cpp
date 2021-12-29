/*
 * Copyright 2020~2021 SYSON, MICHAEL B.
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
 * @date created: 20201010
 * @date updated: 20211229
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
/*
 * This program demonstrates how to render
 * a simple heads-up display.  It uses a
 * font texture to display the text.
 *
 * Eric Vidal
 */

//#include <SDL.h>

//TO-DO: -update: this

//added by Mike, 20201010
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#endif

//added by Mike, 20210903
//note: reverifying: use of SDL Image + OpenGL, without GLUT
#ifdef _WIN32 //Windows machine
	#include <SDL.h>
	#include <SDL_image.h>
#elif defined(__APPLE__)
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif

#include <stdio.h>
#include <stdlib.h>

//edited by Mike, 20201011
//#include <string.h>
#include <string>

//added by Mike, 20201011
#include <iostream>

//added by Mike, 20211005
#include "Font.h"
//#include "UsbongUtils.h"


Font::Font(SDL_Renderer* mySDLRendererInput, int xPos, int yPos, int zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,zPos, windowWidth, windowHeight)
{            
/*
    //TO-DO: -add: auto-set width and height based on screen
    myWidth=fMyWindowWidthInput/1.5f;
    myHeight=fMyWindowHeightInput/1.5f;
*/
		iMyWidthAsPixel=20; 
  	iMyHeightAsPixel=32; 
    	
  	iMyXPosAsPixel=xPos;
  	iMyYPosAsPixel=yPos;
  	iMyZPosAsPixel=zPos;
	
		fMyWindowWidth=windowWidth;
		fMyWindowHeight=windowHeight;
				    	   
  	iCountAnimationFrame=0;
//  	iCurrentKeyInput=2; //start: face RIGHT
	
  	mySDLRenderer = mySDLRendererInput;
  
  	texture = loadTexture((char*)"textures/font.png");	
}

void Font::draw_string(int x, int y, int z, char *string)
{
    //    printf(">>string: %s\n",string);
    //    printf(">>string's c: %c\n",string[0]);
    
    int iStringCharCount=0;
    
    while (string[0] != 0)
    {
//        printf(">>string's c: %c\n",string[0]);
        
        draw_char(x, y, z, string[0]);
  			
  			//edited by Mike, 20211215              
//        x += fGridSquareWidth/3; //iMyWidthAsPixel; //0.035f;
        x += fGridSquareWidth/3/1.5;

        //go to the next character in the string
        string++;
    }
}

void Font::draw_char(int xInput, int yInput, int zInput, char c) {
//		c='A';

  	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;
  	
  	// check if the character is valid
    if (c < ' ' || c > '~')
        return;

//    printf(">>start c: %i\n",c); 
    
    //subtract 32, since the first character in the font texture
    //is the space (ascii value 32)
    c = c - 32;
    
    //each character in the font texture image file
    //has a width-height ratio of 10:16
    int tx = (c % 12 * iMyWidthAsPixel); //0.078125f;   
    int ty = (c / 12 * iMyHeightAsPixel); //0.125f);

/*
       	printf(">>c: %i\n",c); 
        printf(">>tx: %i\n",tx);    
        printf(">>ty: %i\n",ty);
*/
  		    	
  	SrcR.x = 0+tx;
  	SrcR.y = 0+ty;
	
  	SrcR.w = iMyWidthAsPixel; 
  	SrcR.h = iMyHeightAsPixel; 

	 //edited by Mike, 20211215	
  	DestR.x = xInput; //getXPos();
  	DestR.y = yInput; //getYPos();  	
  	DestR.w = fGridSquareWidth/3/1.5;
  	DestR.h = fGridSquareHeight/2/1.5;	
	
  	//note: SDL color max 255; GIMP color max 100
		//SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);


		//-----
		//increase font thickness
/* //edited by Mike, 20211229
  	DestR.x = xInput-2;
  	DestR.y = yInput-2;
  	DestR.w = fGridSquareWidth/3/1.5+1; //2;
  	DestR.h = fGridSquareHeight/2/1.5+1; //2;	
*/
/*
  	DestR.x = xInput - 2/3/1.5;
  	DestR.y = yInput - 2/3/1.5;

  	DestR.w = fGridSquareWidth/3/1.5 + 2/3/1.5;
  	DestR.h = fGridSquareHeight/2/1.5 + 2/3/1.5;	
*/
  	DestR.x = xInput - 2/3;
  	DestR.y = yInput - 2/3;

  	DestR.w = fGridSquareWidth/3/1.5 + 2/3;
  	DestR.h = fGridSquareHeight/2/1.5 + 2/3;	
	
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);
		//-----

}
