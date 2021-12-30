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
 * @date created: 20210613
 * @date updated: 20211230
 * @website address: http://www.usbong.ph
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007):
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */

#include "MyDynamicObject.h"

#include <string>

//added by Mike, 20201226
#define TRUE 1
#define FALSE 0

//added by Mike, 20210614; edited by Mike, 20210616
//#define MAX_TEXT_CHAR_ROW 2idrawPressNextSymbolCount
//edited by Mike, 20210618
//#define MAX_TEXT_CHAR_ROW 3
//edited by Mike, 20210618
//per textbox
//edited by Mike, 20211229
//#define MAX_TEXT_CHAR_ROW 4 //TO-DO: -auto-identify if over MAX; execute pause write action
#define MAX_TEXT_CHAR_ROW 3 

//note: MAX rows in Random Access Memory (RAM) storage
//reminder: "Random" need not be so, due to existing pattern; albeit "RAM" is still used
#define MAX_TEXT_CHAR_ROW_RAM 100 //TO-DO: -auto-identify if over MAX; execute pause write action

//edited by Mike, 20210615
//#define MAX_TEXT_CHAR_COLUMN 8 //note: 8 with comma to be end of line
//#define MAX_TEXT_CHAR_COLUMN 16 //note: 8 with comma to be end of line
#define MAX_TEXT_CHAR_COLUMN 42 //note: 8 with comma to be end of line

#define MAX_WAIT_COUNT 5


//class UsbongUtils;

class Font;

//TO-DO: -update: this
class Text: public MyDynamicObject
{
private:    
		int iInputTileWidth;
		int iInputTileHeight;
		
		char cCurrentTextContainer[MAX_TEXT_CHAR_ROW_RAM][MAX_TEXT_CHAR_COLUMN];
    
    int iTextAnimationCountDelay;
    
    int iTextCurrentMaxRowCount;
    int iCurrentMaxColumnCountPerRowContainer[MAX_TEXT_CHAR_ROW];
    
    int iRowCountPageNumber; //start at zero
    bool isAtMaxTextCharRow;
    int idrawPressNextSymbolCount;
    
    //added by Mike, 20211223
    int iTextBackgroundWidthOffset;
    
    //added by Mike, 20210723
    bool bHasReachedEndOfTextMessage,
    		 bHasPressedKeyToCloseEndOfTextMessage;
    
    //edited by Mike, 20211222
    void drawPressNextSymbolPrev();
    void drawPressNextSymbol();
    
public:    
    Text(SDL_Renderer* mySDLRenderer, int xPos, int yPos, int zPos,int windowWidth,int windowHeight);
		~Text();
    
//    UsbongUtils *myUsbongUtils;
    
    Font *myFont;
    
    int myKeysDown[10]; //note: includes KEY_J, KEY_L, KEY_I, KEY_K,
        
    void readInputText(char *inputFilename);
    
    virtual void draw() {
        drawText();      
    }

		//added by Mike, 20211218
		void setFont();

    void drawText();    
    void drawTextBackgroundWithTexture();  
    //added by Mike, 20211217     
		void drawTextBackgroundWithTextureTile(int iType, int x, int y);    
    
    void drawTextBackgroundWithTexturePrev(); 
    void drawTextBackgroundWithTextureBuggy(); //added by Mike, 20211230

    void drawTextBackgroundWithTextureTopLeftCorner(); 
    void drawTextBackgroundWithTextureBottomLeftCorner();
    void drawTextBackgroundWithTextureTopRightCorner();
    void drawTextBackgroundWithTextureBottomRightCorner();
    void drawTextBackgroundWithTextureTopSide();
    
    void drawTextWithFontTexture(int x, int y);
    void update(float dt);
    
    //added by Mike, 20201226
    void keyDown(int keyCode);	
    void keyUp(int keyCode);
    
    virtual void destroy();
};
