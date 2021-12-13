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
 * @date updated: 20211213
 *
 * Acknowledgments:
 * 1) "Bulalakaw Wars" Team (2007): 
 * Syson, M., Camacho, R., Gonzales, D., Del Rosario, R., Vidal, E., et al.
 *
 */
#include <stdlib.h> 

//edited by Mike, 20201011
//#include <string.h>
#include <string>

//added by Mike, 20211008
#include "MyDynamicObject.h"

//class UsbongUtils;

class Font: public MyDynamicObject
{	
public:
    Font(SDL_Renderer* mySDLRenderer, int xPos, int yPos, int zPos,int windowWidth,int windowHeight);
		~Font();
    
//    UsbongUtils *myUsbongUtils;

		void draw_string(int x, int y, int z, char *string);
    //void draw_stringCharOutputOK(GLuint glIFontTexture, GLfloat x, GLfloat y, GLfloat z, char *string);
    
    void draw_char(int x, int y, int z, char c);    
};
	
