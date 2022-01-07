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
 * @date created: 20200926
 * @date updated: 20220107; from 20211230
 * @website address: http://www.usbong.ph
 *
 * Reference:
 * 1) Astle, D. and Hawkin, K. (2004). "Beginning OpenGL game programming". USA: Thomson Course Technology
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007):
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
 
//added by Mike, 20211217
//note: Maiging may Kasangkapan na magagamit 
//sa paglalagay ng mga Image TILE sa daigdig.
//Babasahin ng computer ang output file nito bilang input 
//upang awtomatiko iguhit ang mga Image TILE.

//INTERACTIVE na Aklat ng Salaysay
//where: INTERACTIVE: May Ugnayang Pagkilos sa nailikhang daigdig
//Sangguninan: Dragon Quest VI; Super Family Computer

//added by Mike, 20211230
//note: max size of actual tile image pixel 64x64
//if enlarged using only SDL Commands, without OpenGL, output incorrect
//reminder: Variations in Computer Monitor/Television, e.g. Portrait, Landscape, Square,
//cause incorrect output tile image positions and total count
//prevously, attempted to set a fixed count for row and column, e.g. 10x10; 10*60 = 600; 600x600px
//however, excess horizontal and vertical margin space for Screens 
//with larger than 600x600, use Landscape view, et cetera
//
//note: Action by SONY U.S.A. to accept only applications that use 3D Technology
//to publish on PS1 in Market caused increase in Developers 
//of Computer Hardware/Software, e.g. Television Screens, Computer Processors, 
//result: variations in screen size, faster processors. increase in Software that sold the Hardware
//
//reminder: There now exist increasing unused Hardware machines 
//whose speed is quickly becoming slower than the newest releases
//action: recycle such unused Hardware machines
//TO-DO: -verify: applications that do NOT auto-resize based on Computer Monitor;
//can use minimum size of Computer Monitor?...

//TO-DO: -update: this

#include <stdio.h>
#include <math.h>

#include "Text.h"
#include "Font.h"

#include <string.h>

//added by Mike, 20201217
//Reference: https://stackoverflow.com/questions/34152424/autodetection-of-os-in-c-c;
//answer by: Jeegar Patel, 20151208T0940
//auto-identify if Windows Machine
#ifdef _WIN32
#include <windows.h> //Windows Machine
#endif

//#include "ModelPool.h"

//added by Mike, 20211217
#define TEXT_TOP_SIDE_TILE 0
#define TEXT_BOTTOM_SIDE_TILE 1
#define TEXT_LEFT_SIDE_TILE 2
#define TEXT_RIGHT_SIDE_TILE 3
#define TEXT_RIGHT_DOWN_CORNER_TILE 4
#define TEXT_DOWN_LEFT_CORNER_TILE 5
#define TEXT_LEFT_UP_CORNER_TILE 6
#define TEXT_UP_RIGHT_CORNER_TILE 7
#define TEXT_CENTER_TILE 8

enum Keys
{
    KEY_W = 0,
    KEY_S,
    KEY_D,
    KEY_A,
    /* //removed by Mike, 20210130
     KEY_UP,
     KEY_DOWN,
     KEY_RIGHT,
     KEY_LEFT,
     KEY_SPACE,
     KEY_ENTER,
     */
    KEY_J,
    KEY_L,
    KEY_I,
    KEY_K,
    KEY_H, 
    KEY_U, 
    
    iNumOfKeyTypes
};


//edited by Mike, 20211218
Text::Text(SDL_Renderer* mySDLRendererInput, int xPos, int yPos, int zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,zPos, windowWidth, windowHeight)
{            
/*
    //TO-DO: -add: auto-set width and height based on screen
    myWidth=fMyWindowWidthInput/1.5f;
    myHeight=fMyWindowHeightInput/1.5f;
*/
		iMyWidthAsPixel=64; //64*2; 
  	iMyHeightAsPixel=64; 
  	
  	//edited by Mike, 20211217
  	iInputTileWidth=16*2;
		iInputTileHeight=16*2;
    	
  	iMyXPosAsPixel=xPos;
  	iMyYPosAsPixel=yPos;
  	iMyZPosAsPixel=zPos;

		//TO-DO: -set:fMyWindowWidth to integer	
		//TO-DO: -set:fMyWindowHeight to integer	
		fMyWindowWidth=windowWidth;
		fMyWindowHeight=windowHeight;

printf(">>> fMyWindowWidth: %f\n",fMyWindowWidth);
printf(">>> fMyWindowHeight: %f\n",fMyWindowHeight);

 		//removed by Mike, 20211218; added again by Mike, 20211222		
		//note: shall re-set fGridSquareHeight, fGridSquareWidth
/* //edited by Mike, 20211230
		//added by Mike, 20211215
  	int iRowCountMax=10;
  	int iColumnCountMax=iRowCountMax;//18; 
*/  	
  	iRowCountMax=10;
  	iColumnCountMax=iRowCountMax;//18; 
  	
		//auto-resize width
  	fGridSquareHeight = (windowWidth)/iRowCountMax;
  	fGridSquareWidth = (windowWidth)/iColumnCountMax;
  	  	
		//TO-DO: -add: auto-verify if Portrait, NOT landscape
		//edited by Mike, 20211230
		//iTextBackgroundWidthOffset = (fMyWindowWidth-fMyWindowHeight)/fGridSquareWidth;
		iTextBackgroundWidthOffset = (fMyWindowWidth-fMyWindowHeight)/64; //64 size of each square tile
		
		//removed by Mike, 20220107			    	   
//printf(">>>> iTextBackgroundWidthOffset: %i\n",iTextBackgroundWidthOffset);				    	   
				    	   
  	iCountAnimationFrame=0;
//  	iCurrentKeyInput=2; //start: face RIGHT

		bHasReachedEndOfTextMessage=false;
		idrawPressNextSymbolCount=0;
			
  	mySDLRenderer = mySDLRendererInput;

/*	//removed by Mike, 20211218
		//added by Mike, 20211215
		myFont = new Font(mySDLRenderer,0,0,0,windowWidth,windowHeight);
		myFont->setGridTileWidthHeight(fGridSquareWidth,fGridSquareHeight);	  
  	texture = loadTexture((char*)"textures/text.png");	
*/
		//added by Mike, 20211222
		//use FONT size based on computer/television monitor width and height;
		//output problem NOT noticeable using alpha/transparent borders 
		setFont(); 

    readInputText((char*)"inputHalimbawa.txt");							
}

Text::~Text()
{
}

//added by Mike, 20211218
void Text::setFont() {
	myFont = new Font(mySDLRenderer,0,0,0,fMyWindowWidth,fMyWindowHeight);
	myFont->setGridTileWidthHeightBasedOnMonitorScreen(fGridSquareWidth,fGridSquareHeight);	  
  texture = loadTexture((char*)"textures/text.png");	
}

void Text::drawPressNextSymbolPrev()
{
	  //edited by Mike, 20211222
		int iTileWidth=iInputTileWidth/2; //16;
		int iTileHeight=iInputTileHeight/2; //16;
/*
		int iTileWidth=iInputTileWidth; //16;
		int iTileHeight=iInputTileHeight; //16;
*/
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0;
  	SrcR.y = 0+4*iTileHeight; 
	
  	SrcR.w = iTileWidth; //iMyWidthAsPixel; 
  	SrcR.h = iTileHeight; //iMyHeightAsPixel; 
		
  	DestR.x = 0+fMyWindowWidth/2; //getXPos();
  	DestR.y = fMyWindowHeight-iInputTileHeight*1.5; //4; //1.5; //iTileHeight;//getYPos();

/*
  	DestR.x = 0; 
  	DestR.y = 0;
*/
  	
/* //edited by Mike, 20211209  	
  	DestR.w = iMyWidthAsPixel;
  	DestR.h = iMyHeightAsPixel;
*/
		//edited by Mike, 20211215
//  	DestR.w = fMyWindowWidth-fMyWindowWidth/4/2*2; //fGridSquareWidth;
  	DestR.w = fGridSquareWidth/3;
  	DestR.h = fGridSquareHeight/2;
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white
		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);    	
}

//added by Mike, 20211222
//TO-DO: -reverify: using only 3 rows for text
//TO-DO: -fix: in first set of rows, press next button arrow displayed 
//before computer finishes writing all text in set
//TO-DO: -add: scroll upward after pressing next button arrow
void Text::drawPressNextSymbol()
{
	  //edited by Mike, 20211222
		int iTileWidth=iInputTileWidth/2; //16;
		int iTileHeight=iInputTileHeight/2; //16;
/*
		int iTileWidth=iInputTileWidth; //16;
		int iTileHeight=iInputTileHeight; //16;
*/
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0;
  	SrcR.y = 0+4*iTileHeight; 
	
  	SrcR.w = iTileWidth; //iMyWidthAsPixel; 
  	SrcR.h = iTileHeight; //iMyHeightAsPixel; 
		
		//edited by Mike, 20211222	
//  	DestR.x = 0+fMyWindowWidth/2; //getXPos();
		//edited again by Mike, 20211229
//  	DestR.x = 0+(16+3)*fGridSquareWidth-iTileWidth*2; //getXPos();
  	DestR.x = 0+fMyWindowWidth/2; //getXPos();

  	DestR.y = fMyWindowHeight-iInputTileHeight;//*1.5; //4; //1.5; //iTileHeight;//getYPos();

/*
  	DestR.x = 0; 
  	DestR.y = 0;
*/
  	
/* //edited by Mike, 20211209  	
  	DestR.w = iMyWidthAsPixel;
  	DestR.h = iMyHeightAsPixel;
*/
		//edited by Mike, 20211215
//  	DestR.w = fMyWindowWidth-fMyWindowWidth/4/2*2; //fGridSquareWidth;
  	DestR.w = fGridSquareWidth/3;
  	DestR.h = fGridSquareHeight/2;
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white
		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);    	
}

/*
void Text::drawTextBackgroundWithTexturePrev()
{
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0;
  	SrcR.y = 0;
	
  	SrcR.w = iMyWidthAsPixel; 
  	SrcR.h = iMyHeightAsPixel; 
	
		//edited by Mike, 20211215
//  	DestR.x = 0+fMyWindowWidth/4/2; //getXPos();
  	DestR.x = 0+fMyWindowWidth/6/2; //getXPos();

  	DestR.y = fMyWindowHeight-fMyWindowHeight/4;//getYPos();
  	

		//edited by Mike, 20211215
//  	DestR.w = fMyWindowWidth-fMyWindowWidth/4/2*2; //fGridSquareWidth;
  	DestR.w = fMyWindowWidth-fMyWindowWidth/6; //fGridSquareWidth;

  	DestR.h = fMyWindowHeight/4; //fGridSquareHeight;	
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white
		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               	
}
*/

//added by Mike, 20211217
void Text::drawTextBackgroundWithTextureTopLeftCorner()
{
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0;
  	SrcR.y = 0;
	
  	SrcR.w = iInputTileWidth; 
  	SrcR.h = iInputTileHeight; 
	
  	DestR.x = 0+fMyWindowWidth/6/2;
  	DestR.y = fMyWindowHeight-fMyWindowHeight/4;
  	
  	DestR.w = fGridSquareWidth/2; //fMyWindowWidth-fMyWindowWidth/6; //fGridSquareWidth;
  	DestR.h = fGridSquareHeight/2; //fMyWindowHeight/4; //fGridSquareHeight;	
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               	
}

//added by Mike, 20211217
void Text::drawTextBackgroundWithTextureBottomLeftCorner()
{
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0;
  	SrcR.y = 0+iInputTileHeight;
	
  	SrcR.w = iInputTileWidth; 
  	SrcR.h = iInputTileHeight; 
	
  	DestR.x = 0+fMyWindowWidth/6/2;
  	DestR.y = fMyWindowHeight-fGridSquareHeight/2; //-fMyWindowHeight/4;
  	
  	DestR.w = fGridSquareWidth/2; //fMyWindowWidth-fMyWindowWidth/6; //fGridSquareWidth;
  	DestR.h = fGridSquareHeight/2; //fMyWindowHeight/4; //fGridSquareHeight;	
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               	
}

//added by Mike, 20211217
void Text::drawTextBackgroundWithTextureTopRightCorner()
{
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0+iInputTileWidth;
  	SrcR.y = 0;
	
  	SrcR.w = iInputTileWidth; 
  	SrcR.h = iInputTileHeight; 
	
  	DestR.x = 0+fMyWindowWidth-fMyWindowWidth/6;
  	DestR.y = fMyWindowHeight-fMyWindowHeight/4;
  	
  	DestR.w = fGridSquareWidth; ///2; 
  	DestR.h = fGridSquareHeight; ///2; 
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               	
}

//added by Mike, 20211217
void Text::drawTextBackgroundWithTextureBottomRightCorner()
{
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0+iInputTileWidth;
  	SrcR.y = 0+iInputTileHeight;
	
  	SrcR.w = iInputTileWidth; 
  	SrcR.h = iInputTileHeight; 
	
/*	
  	DestR.x = 0+fMyWindowWidth-fMyWindowWidth/6;
  	DestR.y = fMyWindowHeight-fGridSquareHeight/2;
*/
  	DestR.x = 0+fMyWindowWidth-fGridSquareWidth;
  	DestR.y = fMyWindowHeight-fGridSquareHeight;
  	
  	DestR.w = fGridSquareWidth; ///2; 
  	DestR.h = fGridSquareHeight; ///2;

/*
  	DestR.w = fGridSquareWidth/2; TEXT_RIGHT_DOWN_CORNER_TILE
  	DestR.h = fGridSquareHeight/2;
*/
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               	
}

//added by Mike, 20211217
void Text::drawTextBackgroundWithTextureTopSide()
{
   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0+iInputTileWidth*2;// +1; //added +1 due to 1px of left tile included
  	SrcR.y = 0;
	
  	SrcR.w = iInputTileWidth; 
  	SrcR.h = iInputTileHeight; 
	
		//edited by Mike, 20211217
/*	
  	DestR.x = 0+fMyWindowWidth/6/2+fGridSquareWidth/2;
  	DestR.y = fMyWindowHeight-fMyWindowHeight/4;
  	
  	DestR.w = fGridSquareWidth/2;
  	DestR.h = fGridSquareHeight/2;
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               		
*/
	//TOP of text background
	for (int iCount=0; iCount<14; iCount++) {
  	DestR.x = 0+fMyWindowWidth/6/2+(fGridSquareWidth/2*(iCount+1));
  	DestR.y = fMyWindowHeight-fMyWindowHeight/4;
  	
  	DestR.w = fGridSquareWidth/2;
  	DestR.h = fGridSquareHeight/2;
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               		
	}
	
	
}

//added by Mike, 20211119
void Text::drawTextBackgroundWithTextureTile(int iType, int x, int y)
{
/*
	int iTileWidth=fGridSquareWidth;
	int iTileHeight=fGridSquareHeight;
*/
	int iTileWidth=64; //32
	int iTileHeight=64; //32
	
  //Rectangles for drawing which will specify source (inside the texture)
  //and target (on the screen) for rendering our textures.
  SDL_Rect SrcR;
  SDL_Rect DestR;

/*  	    
  SrcR.x = 0; //x;
  SrcR.y = 0; //y;
*/
	
	if (iType==TEXT_TOP_SIDE_TILE) {
  	SrcR.x = 0+iTileWidth*1; 
  	SrcR.y = 0+iTileHeight*2; 
	}
	else if (iType==TEXT_RIGHT_SIDE_TILE) {
  	SrcR.x = 0+iTileWidth*2; 
  	SrcR.y = 0+iTileHeight; 
	}
	else if (iType==TEXT_BOTTOM_SIDE_TILE) {
  	SrcR.x = 0+iTileWidth*2; 
  	SrcR.y = 0+iTileHeight*2;  	
	}	
	else if (iType==TEXT_LEFT_SIDE_TILE) {
  	SrcR.x = 0+iTileWidth;
  	SrcR.y = 0+iTileHeight;  	
	}	
	else if (iType==TEXT_CENTER_TILE) {
  	SrcR.x = 0+iTileWidth*3;
  	SrcR.y = 0+iTileHeight;  	
	}	
	//corner
	else {
		if (iType==TEXT_UP_RIGHT_CORNER_TILE) {
  		SrcR.x = 0;
  		SrcR.y = 0;
		}
		else if (iType==TEXT_RIGHT_DOWN_CORNER_TILE) {
  		SrcR.x = 0+iTileWidth*2;
  		SrcR.y = 0;
		}
		else if (iType==TEXT_DOWN_LEFT_CORNER_TILE) {
  		SrcR.x = 0+iTileWidth*3;
  		SrcR.y = 0;  	
		}
		else if (iType==TEXT_LEFT_UP_CORNER_TILE) {
  		SrcR.x = 0+iTileWidth;
  		SrcR.y = 0;
		}	
	}	

	//edited by Mike, 20211222
  SrcR.w = iTileWidth; //-1;
  SrcR.h = iTileHeight; //-1;

/*
  SrcR.w = iTileWidth-3;
  SrcR.h = iTileHeight-3;
*/  
  
/*
  DestR.x = x; //+iCurrentOffsetWidth;
  DestR.y = y;
*/
  DestR.x = x;
  DestR.y = y;
   
//  printf(">> inside text.cpp fGridSquareWidth: %f\n",fGridSquareWidth);
  
  //edited by Mike, 20211218
  //SDL_RenderCopy(...) accepts only as input whole numbers, instead of floating point numbers
/*Text
  DestR.w = fGridSquareWidth+1;
  DestR.h = fGridSquareHeight+1;
*/

	//note: if input source texture image is square, output should also be square
/*	//edited by Mike, 20211222
  DestR.w = iTileWidth; //fGridSquareWidth;
  DestR.h = iTileHeight; //fGridSquareHeight;
*/
  DestR.w = fGridSquareWidth;
  DestR.h = fGridSquareHeight;

	SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);
}

//added by Mike, 20211217; edited by Mike, 20211230
void Text::drawTextBackgroundWithTexturePrev()
{
 	//edited by Mike, 20211221; edited again by Mike, 20211222
	drawTextBackgroundWithTextureTile(TEXT_UP_RIGHT_CORNER_TILE, 2*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);

	//added by Mike, 20211218
	drawTextBackgroundWithTextureTile(TEXT_LEFT_UP_CORNER_TILE, 2*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	//edited by Mike, 20211222
	//drawTextBackgroundWithTextureTile(TEXT_RIGHT_DOWN_CORNER_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);	

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_DOWN_CORNER_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);	

		//edited by Mike, 20211222
//	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	//edited by Mike, 20211230
//	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	
	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, (15+3-3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	drawTextBackgroundWithTextureTile(TEXT_LEFT_SIDE_TILE, 2*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
		
		//edited by Mike, 20211222
	//note: has margin at right most due to fMyWindowWidth is trimmed
//	drawTextBackgroundWithTextureTile(TEXT_RIGHT_SIDE_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_SIDE_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
		drawTextBackgroundWithTextureTile(TEXT_TOP_SIDE_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);
	}

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
//	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset-3; iCount++) {
		drawTextBackgroundWithTextureTile(TEXT_BOTTOM_SIDE_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);
	}

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
		//edited by Mike, 20211221
//		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount+2)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
	}
}

//added by Mike, 20211217; edited by Mike, 20211230
void Text::drawTextBackgroundWithTextureBuggy()
{
 	//edited by Mike, 20211221; edited again by Mike, 20211222
//	drawTextBackgroundWithTextureTile(TEXT_UP_RIGHT_CORNER_TILE, 2*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);
	drawTextBackgroundWithTextureTile(TEXT_UP_RIGHT_CORNER_TILE, 1*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);

	//added by Mike, 20211218; edited by Mike, 20211230
//	drawTextBackgroundWithTextureTile(TEXT_LEFT_UP_CORNER_TILE, 2*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	
	drawTextBackgroundWithTextureTile(TEXT_LEFT_UP_CORNER_TILE, 1*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	//edited by Mike, 20211222
	//drawTextBackgroundWithTextureTile(TEXT_RIGHT_DOWN_CORNER_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);	

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_DOWN_CORNER_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);	

		//edited by Mike, 20211222
//	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	//edited by Mike, 20211230
//	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	
	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, (15+3-4)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	//edited by Mike, 20211230
//	drawTextBackgroundWithTextureTile(TEXT_LEFT_SIDE_TILE, 2*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
	drawTextBackgroundWithTextureTile(TEXT_LEFT_SIDE_TILE, 1*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
		
		//edited by Mike, 20211222
	//note: has margin at right most due to fMyWindowWidth is trimmed
//	drawTextBackgroundWithTextureTile(TEXT_RIGHT_SIDE_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_SIDE_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
	//edited by Mike, 20211230
//		drawTextBackgroundWithTextureTile(TEXT_TOP_SIDE_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);
		drawTextBackgroundWithTextureTile(TEXT_TOP_SIDE_TILE, (iCount+2)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);

	}

/* //edited by Mike, 20211230
	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
//	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset-1; iCount++) {
		//edited by Mike, 20211230
//		drawTextBackgroundWithTextureTile(TEXT_BOTTOM_SIDE_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);
		drawTextBackgroundWithTextureTile(TEXT_BOTTOM_SIDE_TILE, (iCount+2)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);
	}
*/	

	//removed by Mike, 20220107
//printf(">>>iTextBackgroundWidthOffset: %i\n",iTextBackgroundWidthOffset);

	for (int iCount=iColumnCountMax+iTextBackgroundWidthOffset+1; iCount>1; iCount--) {
		//edited by Mike, 20211230
//		drawTextBackgroundWithTextureTile(TEXT_BOTTOM_SIDE_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);
		drawTextBackgroundWithTextureTile(TEXT_BOTTOM_SIDE_TILE, fGridSquareWidth*iCount,fMyWindowHeight-1*fGridSquareHeight);
	}

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
		//edited by Mike, 20211221
//		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount+2)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
		//edited by Mike, 20211230
//		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount+2)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
	}
}


//added by Mike, 20211217; edited by Mike, 20211230
void Text::drawTextBackgroundWithTexture()
{
 	//edited by Mike, 20211221; edited again by Mike, 20211222
	drawTextBackgroundWithTextureTile(TEXT_UP_RIGHT_CORNER_TILE, 1*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);

	//added by Mike, 20211218
	drawTextBackgroundWithTextureTile(TEXT_LEFT_UP_CORNER_TILE, 1*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	int iMaxColumnCountBasedOnWidth = fMyWindowWidth/fGridSquareWidth;

//removed by Mike, 20220107
//printf(">>>iTextBackgroundWidthOffset: %i\n",iTextBackgroundWidthOffset);

	//edited by Mike, 20211230
//	for (int iCount=3; iCount<iMaxColumnCountBasedOnWidth-3; iCount++) {
	for (int iCount=2; iCount<iMaxColumnCountBasedOnWidth-2; iCount++) {
		drawTextBackgroundWithTextureTile(TEXT_BOTTOM_SIDE_TILE, (iCount)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);
	}
	
	//added by Mike, 20211230
	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, (iMaxColumnCountBasedOnWidth-2)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_DOWN_CORNER_TILE, (iMaxColumnCountBasedOnWidth-2)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);	

	for (int iCount=2; iCount<iMaxColumnCountBasedOnWidth-2; iCount++) {
		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
	}
	
	drawTextBackgroundWithTextureTile(TEXT_LEFT_SIDE_TILE, 1*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_SIDE_TILE, (iMaxColumnCountBasedOnWidth-2)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	for (int iCount=2; iCount<iMaxColumnCountBasedOnWidth-2; iCount++) {
		drawTextBackgroundWithTextureTile(TEXT_TOP_SIDE_TILE, (iCount)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);
	}

/*
	//edited by Mike, 20211222
	//drawTextBackgroundWithTextureTile(TEXT_RIGHT_DOWN_CORNER_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);	

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_DOWN_CORNER_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);	

		//edited by Mike, 20211222
//	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	//edited by Mike, 20211230
//	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	
	drawTextBackgroundWithTextureTile(TEXT_DOWN_LEFT_CORNER_TILE, (15+3-3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);	

	drawTextBackgroundWithTextureTile(TEXT_LEFT_SIDE_TILE, 2*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
		
		//edited by Mike, 20211222
	//note: has margin at right most due to fMyWindowWidth is trimmed
//	drawTextBackgroundWithTextureTile(TEXT_RIGHT_SIDE_TILE, fMyWindowWidth-3*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	drawTextBackgroundWithTextureTile(TEXT_RIGHT_SIDE_TILE, (15+3)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
		drawTextBackgroundWithTextureTile(TEXT_TOP_SIDE_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-3*fGridSquareHeight);
	}

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
//	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset-3; iCount++) {
		drawTextBackgroundWithTextureTile(TEXT_BOTTOM_SIDE_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-1*fGridSquareHeight);
	}

	//edited by Mike, 20211223
//	for (int iCount=0; iCount<15; iCount++) {
	for (int iCount=0; iCount<11+iTextBackgroundWidthOffset; iCount++) {
		//edited by Mike, 20211221
//		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount+2)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
		drawTextBackgroundWithTextureTile(TEXT_CENTER_TILE, (iCount+3)*fGridSquareWidth,fMyWindowHeight-2*fGridSquareHeight);
	}
*/
	
}


void Text::drawText()
{
    if (bHasReachedEndOfTextMessage) {
        if(bHasPressedKeyToCloseEndOfTextMessage) {
            return;
        }
    }		

		drawTextBackgroundWithTexture();

   	drawTextWithFontTexture(0, 0);

		if (isAtMaxTextCharRow) {		
/*  
        if ((idrawPressNextSymbolCount)%2==0) {
            drawPressNextSymbol();
        }
        idrawPressNextSymbolCount=idrawPressNextSymbolCount+1;
*/        
        if (idrawPressNextSymbolCount<10) {
            drawPressNextSymbol();
        }
        else {
        	if (idrawPressNextSymbolCount>20) {
        		idrawPressNextSymbolCount=0;
        	}
        }
        idrawPressNextSymbolCount=idrawPressNextSymbolCount+1;
    }              	
}
    
void Text::drawTextWithFontTexture(int x, int y)
{
		char tempText[MAX_TEXT_CHAR_ROW_RAM][MAX_TEXT_CHAR_COLUMN];        
    int iRowCount;    
          
for (iRowCount=0; iRowCount<iTextCurrentMaxRowCount;) {

  for (int iRowCountToSetDefault=0; iRowCountToSetDefault<MAX_TEXT_CHAR_ROW_RAM; iRowCountToSetDefault++) {
    for (int iColumnCount=0; iColumnCount<MAX_TEXT_CHAR_COLUMN; iColumnCount++) {
        tempText[iRowCountToSetDefault][iColumnCount]='\0'; //verified: in macOS, with Japanese keyboard ro-maji input, "¥0", backspace is "¥"
    }
	}
        
  for (int iColumnCount=0; iColumnCount<iCurrentMaxColumnCountPerRowContainer[iRowCount]; iColumnCount++) {
            tempText[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW][iColumnCount]=cCurrentTextContainer[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW][iColumnCount];
  }
  
  	//edited by Mike, 20211215
//    myFont->draw_string(x+fGridSquareWidth,y+fGridSquareHeight/2*iRowCount,0,tempText[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW]);

		//edited by Mike, 20211217
//    myFont->draw_string(x+fGridSquareWidth,fMyWindowHeight-fMyWindowHeight/4 +fGridSquareHeight/2*iRowCount +fGridSquareHeight*0.2,0,tempText[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW]);
		
		//edited by Mike, 20211222
//    myFont->draw_string(x+fGridSquareWidth+fGridSquareWidth*0.2,fMyWindowHeight-fMyWindowHeight/3.5 +fGridSquareHeight/2*iRowCount +fGridSquareHeight*0.2,0,tempText[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW]);
	//edited by Mike, 20211230
	
//    myFont->draw_string(x+fGridSquareWidth+fGridSquareWidth*1.4,fMyWindowHeight-fMyWindowHeight/4.0 +fGridSquareHeight/1.5*iRowCount +fGridSquareHeight*0.2,0,tempText[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW]);
    
    myFont->draw_string(x+fGridSquareWidth*2,fMyWindowHeight-fMyWindowHeight/4.0 +fGridSquareHeight/1.5*iRowCount +fGridSquareHeight*0.2,0,tempText[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW]);
    
  iTextAnimationCountDelay=0;
  
  if ((iRowCount)==(iTextCurrentMaxRowCount-1)) {
      iCurrentMaxColumnCountPerRowContainer[iRowCount]++;
      
      //added by Mike, 20210617
      if (iCurrentMaxColumnCountPerRowContainer[iRowCount]>=MAX_TEXT_CHAR_COLUMN) {
          iCurrentMaxColumnCountPerRowContainer[iRowCount]=MAX_TEXT_CHAR_COLUMN;
      }
  }
        
        
  //'\n'){ //new line; "\0" empty character
  if (cCurrentTextContainer[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW][iCurrentMaxColumnCountPerRowContainer[iRowCount]-1]=='\n') {
      
  //TO-DO: -add: instructions to auto-identify end row by removing empty rows after reading input file
  //if next row is already empty
  //row, column
  if (cCurrentTextContainer[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW][iCurrentMaxColumnCountPerRowContainer[iTextCurrentMaxRowCount]]=='\0') {
      //removed by Mike, 20210905
//      iTextCurrentMaxRowCount=iTextCurrentMaxRowCount;
  }
  else {
      
      if ((iRowCount)==(iTextCurrentMaxRowCount-1)) {
          iTextCurrentMaxRowCount++;
      }
      
      //added by Mike, 20210618
      //if has reached end of rows, no need to execute this
      //TO-DO: -add: auto-identify if at MAX row
      if (cCurrentTextContainer[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW+1][0]=='\0') {
          printf(">>>>>>>>>>>>>>> WAKAS!\n");
          
          bHasReachedEndOfTextMessage=true;
          
          break;
      }
      else {
/*
          printf(">>> iRowCount: %i\n",iRowCount);
          printf(">>> iTextCurrentMaxRowCount: %i\n",iTextCurrentMaxRowCount);
*/          
          
          if (iRowCount>=MAX_TEXT_CHAR_ROW) {
              iRowCountPageNumber++;
              iTextCurrentMaxRowCount=1;
              iRowCount=-1; //note: we add 1 near the closing of the for loop
          }
      }
    }
  
      //edited by Mike, 20210618
      //re-set isAtMaxTextCharRow to FALSE after button press
      //edited by Mike, 20210905
      if ((iRowCount+1)>=MAX_TEXT_CHAR_ROW) {
      		iRowCount=3;
      		//edited by Mike, 20211229
//          iTextCurrentMaxRowCount=4;
          iTextCurrentMaxRowCount=3;

          isAtMaxTextCharRow=true;
      }
            
            //printf("iTextCurrentMaxRowCount: %i\n",iTextCurrentMaxRowCount);
            
            //added by Mike, 20210617
            //TO-DO: fix: next row only iTextCurrentMaxColumnCount=1       
  		}
  		else {
      		break;
  		}
              
      iTextAnimationCountDelay+=1;
      
        //added by Mike, 20210618
        iRowCount=iRowCount+1;       
    }
    
}

void Text::update(float dt)
{
/* //removed by Mike, 20211214
    switch (currentState)
    {
        case INITIALIZING_STATE:
        case MOVING_STATE:
            switch(currentMovingState) {
                case WALKING_MOVING_STATE:
                    break;
                case ATTACKING_MOVING_STATE:                    
                    break;                    
                default: //STANDING STATE
                    break;//do nothing
            }            
            break;
        case IN_TITLE_STATE:
            break;
        default: //STANDING STATE
            break;//do nothing
    }
*/    
}

//added by Mike, 20201226
void Text::keyDown(int keyCode) {
    myKeysDown[keyCode] = TRUE;
    
//    printf(">>keyDown: %i",keyCode);
    //added by Mike, 20210619
    //TO-DO: -reverify: output of over 6 rows in input file
    if (myKeysDown[KEY_K]==TRUE) {
        if (bHasReachedEndOfTextMessage) {
            bHasPressedKeyToCloseEndOfTextMessage=true;
        }
        else {
            if (isAtMaxTextCharRow) {
                isAtMaxTextCharRow=false;
                
                iRowCountPageNumber++;
                iTextCurrentMaxRowCount=1;
                
                //next row; reminder: MAX_TEXT_CHAR_ROW=4
                for(int iCount=0; iCount<MAX_TEXT_CHAR_ROW; iCount++) {
                    iCurrentMaxColumnCountPerRowContainer[iCount]=1;
                }
            }
        }
    }
}

void Text::keyUp(int keyCode) {
    myKeysDown[keyCode] = FALSE;
}

void Text::destroy()
{
    /*
     for(int i = 0; i < MAX_EXPLOSION_PARTICLES; ++i) {
	    delete [] explosionParticle[i];
     }
     delete [] explosionParticle;
     */
}


//added by Mike, 20210614
//note: error occurs if excess rows > 1
//TO-DO: -fix: this
void Text::readInputText(char *inputFilename) {
    int c;
    FILE *file;
    
    //TO-DO: update: this
    //	char** iCurrentLevelMapContainer = new char[100][100];
    int iRowCount=0;
    int iColumnCount=0;
    
    //TO-DO: -update: this
    /*	int MAX_TEXT_CHAR_ROW=2;
     int MAX_TEXT_CHAR_COLUMN=8;
     */
    
    for (iRowCount=0; iRowCount<MAX_TEXT_CHAR_ROW; iRowCount++) {
        for (iColumnCount=0; iColumnCount<MAX_TEXT_CHAR_COLUMN; iColumnCount++) {
            iCurrentMaxColumnCountPerRowContainer[iRowCount]=1;
        }
    }
    
    //added by Mike, 20210618
    for (iRowCount=0; iRowCount<MAX_TEXT_CHAR_ROW_RAM; iRowCount++) {
        for (iColumnCount=0; iColumnCount<MAX_TEXT_CHAR_COLUMN; iColumnCount++) {
            cCurrentTextContainer[iRowCount][iColumnCount]='\0';
        }
    }
    
    iRowCount=0;
    iColumnCount=0;
    
    //added by Mike, 20210617
    iTextCurrentMaxRowCount=1;
    
    //added by Mike, 20210618
    iRowCountPageNumber=0; //start at zero
    
				
    //noted by Mike, 20201210
    //note: if concatenated string exceeds size, "stack smashing detected"; terminated; Aborted (core dumped)
    //I prefer to set a size, instead of dynamically allocate due to increasing likelihood of memory leaks
    //where memory leaks = not deallocated storage in memory, albeit not used by software application
    //identifying not deallocated storage in memory becomes more difficult with increasing use
    //edited by Mike, 20210615
    //	char input[MAX_TEXT_CHAR_COLUMN]; //max size
    //TO-DO: -update: this; if total size of the input filename > total size of container, in macOS abort trap 6 error
    char input[100]; //max size in Char of input filename
    
    char inputTextLine[MAX_TEXT_CHAR_COLUMN]; //max size
    char tempInputTextLine[MAX_TEXT_CHAR_COLUMN]; //max size
    
    //added by Mike, 20210618
    //TO-DO: -add: auto-notify Unit member if input over max
    
    strcpy(input, "input/");
    strcat(input, inputFilename); //already includes .txt
    //	strcat(input,".txt");
    
    //	printf("dito: %s",input);
    
    //	file = fopen("input/"+inputFilename, "r"); //.txt file
    //	file = fopen("input/inputHalimbawa.txt", "r"); //.txt file
    file = fopen(input, "r"); //.txt file
    
    //TO-DO: -reverify: tile positions
    int iCount=0;
    
    strcpy(tempInputTextLine,""); //added by Mike, 20210615
    
    if (file) {
        while (fgets (inputTextLine, MAX_TEXT_CHAR_COLUMN, file)) { /* read each line of input */
            
            iCount=iCount+1;
            
            //added by Mike, 20210208
            iColumnCount=0;
            
            //edited by Mike, 20210616
            //TO-DO: -verify: add tool for computer to notify Unit member if max characters per row already exceeded
            //at present, 19 characters including space
            //TO-DO: -add: auto-put excess characters in next row
            //TO-DO: -fix: text background image texture file after scale up
            //TO-DO: -add: remaining Font characters
            //TO-DO: -update: Font characters to use handwritting
            //TO-DO: -reverify: max rows due to text length long in Filipino language
            //TO-DO: -add: auto-write text per character
            //TO-DO: -add: auto-pause for text with several rows
            strcpy(tempInputTextLine,inputTextLine);
            
/* //removed by Mike, 20211004            
            printf(">>> inputTextLine: %s\n",inputTextLine);
*/            
            
            //added by Mike, 20210617
            //TO-DO: -add: trim to input text line
            
            int iCharCount;
            for (iCharCount=0; iCharCount<strlen(tempInputTextLine); iCharCount++) {
                cCurrentTextContainer[iRowCount][iCharCount]=tempInputTextLine[iCharCount];
                
                printf("cCurrentTextContainer[%i][%i]: %c\n",iRowCount, iCharCount, tempInputTextLine[iCharCount]);
            }
            //added by Mike, 20210617
            cCurrentTextContainer[iRowCount][iCharCount]='\n';
            
            iColumnCount=iColumnCount+1;
            
            if (iRowCount<MAX_TEXT_CHAR_ROW_RAM) {
                iRowCount=iRowCount+1;
                
                //TO-DO: -notify: Unit member if over MAX_TEXT_CHAR_ROW_RAM
            }
            else {
                iRowCount=0;
            }
            
            printf("\n");
        }
        fclose(file);
        
        //added by Mike, 20210615
        //        free(tempInputTextLine);
    }
}
