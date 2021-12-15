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
 * @date updated: 20211215
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


Text::Text(SDL_Renderer* mySDLRendererInput, int xPos, int yPos, int zPos, int windowWidth, int windowHeight): MyDynamicObject(xPos,yPos,zPos, windowWidth, windowHeight)
{            
/*
    //TO-DO: -add: auto-set width and height based on screen
    myWidth=fMyWindowWidthInput/1.5f;
    myHeight=fMyWindowHeightInput/1.5f;
*/
		iMyWidthAsPixel=64*2; 
  	iMyHeightAsPixel=64; 
    	
  	iMyXPosAsPixel=xPos;
  	iMyYPosAsPixel=yPos;
  	iMyZPosAsPixel=zPos;
	
		fMyWindowWidth=windowWidth;
		fMyWindowHeight=windowHeight;

		//added by Mike, 20211215
  	int iRowCountMax=10;
  	int iColumnCountMax=iRowCountMax;//18; 
		//auto-resize width
  	fGridSquareHeight = (windowWidth)/iRowCountMax;
  	fGridSquareWidth = (windowWidth)/iColumnCountMax;
				    	   
  	iCountAnimationFrame=0;
//  	iCurrentKeyInput=2; //start: face RIGHT

		bHasReachedEndOfTextMessage=false;
		idrawPressNextSymbolCount=0;
			
  	mySDLRenderer = mySDLRendererInput;

		//added by Mike, 20211215
		myFont = new Font(mySDLRenderer,0,0,0,windowWidth,windowHeight);
		myFont->setGridTileWidthHeight(fGridSquareWidth,fGridSquareHeight);	
  
  	texture = loadTexture((char*)"textures/text.png");	

    readInputText((char*)"inputHalimbawa.txt");							
}

Text::~Text()
{
}

void Text::drawPressNextSymbol()
{
		int iTileWidth=16;
		int iTileHeight=16;

   	//Rectangles for drawing which will specify source (inside the texture)
  	//and target (on the screen) for rendering our textures.
  	SDL_Rect SrcR;
  	SDL_Rect DestR;

  	SrcR.x = 0;
  	SrcR.y = 0+4*iTileHeight;
	
  	SrcR.w = iTileWidth; //iMyWidthAsPixel; 
  	SrcR.h = iTileHeight; //iMyHeightAsPixel; 
		
  	DestR.x = 0+fMyWindowWidth/2; //getXPos();
  	DestR.y = fMyWindowHeight-iTileHeight*2;//getYPos();

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

void Text::drawTextBackgroundWithTexture()
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
  	
/* //edited by Mike, 20211209  	
  	DestR.w = iMyWidthAsPixel;
  	DestR.h = iMyHeightAsPixel;
*/
		//edited by Mike, 20211215
//  	DestR.w = fMyWindowWidth-fMyWindowWidth/4/2*2; //fGridSquareWidth;
  	DestR.w = fMyWindowWidth-fMyWindowWidth/6; //fGridSquareWidth;

  	DestR.h = fMyWindowHeight/4; //fGridSquareHeight;	
	
  	//note: SDL color max 255; GIMP color max 100
//		SDL_SetRenderDrawColor(mySDLRenderer, 255*1, 255*1, 255*1, 255); //white
		
		SDL_RenderCopy(mySDLRenderer, texture, &SrcR, &DestR);               	
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

    myFont->draw_string(x+fGridSquareWidth,fMyWindowHeight-fMyWindowHeight/4 +fGridSquareHeight/2*iRowCount +fGridSquareHeight*0.2,0,tempText[iRowCount+iRowCountPageNumber*MAX_TEXT_CHAR_ROW]);

    
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
          iTextCurrentMaxRowCount=4;
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
