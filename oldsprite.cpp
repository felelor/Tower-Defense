#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "sprite.h"
#include "Tower.h"
#include "Tile.h"
//#include "Node.h"
#include "Typeset.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int WINDOW_WIDTH = 642;
const int WINDOW_HEIGHT = 560;
const int BUTTON_WIDTH=214;
const int BUTTON_HEIGHT=80;
const int TOWER_WIDTH=40;
const int TOWER_HEIGHT=40;
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;
const char* WINDOW_TITLE = "Tower Sprites";
const int FRAMES_PER_SECOND = 20;
//const int ROW_WIDTH = 12;

sprite::sprite(){
	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING);
	sum=10000;
}

void sprite::play(){
	int x=270;
	int y=0, i=0, j=0;
	//TTF_Font *font = NULL;
	
	SDL_Surface* screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT,0,SDL_HWSURFACE | SDL_DOUBLEBUF);//set screen
	SDL_WM_SetCaption(WINDOW_TITLE, 0);//caption
	SDL_Surface* dot = load_image("dot.bmp");
	//SDL_Surface* background = load_image("background.bmp");//background image
	SDL_Surface* background = SDL_LoadBMP("better_tiles.bmp");
	SDL_Surface* menu = load_image("menu.bmp"); //menu image
	SDL_Surface* sprite_sheet = load_image("sprites_new.bmp");//sprite sheet
	SDL_Surface* flipped_sprite = flip_image(sprite_sheet, FLIP_HORIZONTAL);
	SDL_Surface* title_pic = load_image("Title.bmp"); //title stuff
	//SDL_Surface* brick = SDL_LoadBMP("brick.bmp"); //background filler
	//SDL_SetColorKey( sprite_sheet, SDL_SRCCOLORKEY, SDL_MapRGB(sprite_sheet->format, 255, 0, 255) ); //sets background(magenta) to transperant
	SDL_SetColorKey( dot, SDL_SRCCOLORKEY, SDL_MapRGB(dot->format, 255, 0, 255) );
	//SDL_SetColorKey( background, SDL_SRCCOLORKEY, SDL_MapRGB(background->format, 255, 0, 255) );
	TTF_Font *font = NULL;
	font = TTF_OpenFont( "OptimusPrincepsSemiBold.ttf", 22 );

	Typeset writer(font);

	//draw_sprite(background,screen,0, 0, 0, 0, 640, 480);//draw background
	Tile Tester(0,0,-1,0);
	Tester.set_tiles("field_1.txt",screen,background);
	//cout << "Here" << endl;
	writer.show(1,Tester,screen,background); // write title on buttons
	SDL_Flip(screen);
	//draw_sprite(title_pic,screen,0,0,0,480,640,100);//draw title

	SDL_Event sprites;//event

	bool quit = true;
	int startTicks = SDL_GetTicks(); 
	tower_type = 0;
	int state_anim = 0;
	//int bulba_state = 1;
	int why = 0, ex = 330;
   	while (quit){
		//while(1){
		animate(ex,why,dot,screen,background,Tester);
		if((Tester.get_type((why/40), (ex/40)) !=40 && state_anim==0) || Tester.get_type((why/40), (ex/40)) == 41){
			state_anim = 0;
			if((Tester.get_type((why/40), (ex/40))) ==42){
				state_anim = 1;
				}
			why+=10;
			}
		else{
			ex+=10;
			state_anim=1;
			}
			if(why>=480){
				why=0;
				}
		//}
		//SDL_FreeSurface(dot);
		while (SDL_PollEvent(&sprites)){
         		if (sprites.type == SDL_QUIT){ //if x out is pressed close screen
            			quit = false;
         			}
			else if (sprites.type == SDL_MOUSEBUTTONDOWN){//check to see if mouse button was pressed
				if(sprites.button.button == SDL_BUTTON_LEFT){//left button
					//get mouse coordinates
					int x = sprites.button.x;
					int y = sprites.button.y;
					if(y/40 <= 11){
						i = (y/40); // i and j components for the 2-d game board in Tester tile
						j = (x/40);
						}
					else{
						i = 12; // this is to sginify the larger button row in map grid
						j = (x/40);
						}
					
					//Uint8 r,g,b;
					//Uint32 bg = get_pixel32(background,x,y ); 		//finding colors...not needed now but cool
					//SDL_GetRGB( bg, screen->format, &r, &g, &b );
						//cout << i << " ' " << j<< endl;
						//cout << "outside" << endl;
					if(Tester.get_type(i,j)>=2 && Tester.get_type(i,j)!=10 && Tester.get_type(i,j)!=11 && Tester.get_type(i,j)!=12){ //if click is on pre-determined area
						Tester.draw_sprite(background,screen,120,0,0,480, BUTTON_WIDTH, BUTTON_HEIGHT); //clear buttons
						Tester.draw_sprite(background,screen,120,0,240,480, BUTTON_WIDTH, BUTTON_HEIGHT);
						Tester.draw_sprite(background,screen,120,0,480,480, BUTTON_WIDTH, BUTTON_HEIGHT);
						if( Tester.get_type(i,j)==2){ //starter purchase screen
							writer.show(2,Tester,screen,background);
							state = 0; // states how to handle textual display
							}
						else{ //evlolve/sell
							writer.show(3,Tester,screen,background);
							state = 1;
							}
						//draw_sprite(menu,screen,0,0,0,480,640,100);
						SDL_Flip(screen);
						//cout << "Before this is " << Tester.get_type(i,j) << endl;
						int type = check_key(i,j,state,Tester); //type of tower
						//cout << "OUt" << endl;
						if(type == 4 && state >= 1){ //clear da tower if sold
							Tester.set_type(i,j,2);
							Tester.redraw(2,screen,background);
							}
						else if(type == 1){
							if(Tester.get_type(i,j+2) == 1){ // sees if the image needs to be flipped if on other side of pa
								tower_type = 4; //evolution state
								if(evolution == 3){
									tower_type = 18;
										}
								else if(evolution == 2){
									tower_type = 16;
									state++;
									}
								else if(evolution == 1){
									tower_type = 14;
									//bulba_state++;
									} 
								//cout << "tower is " << tower_type << endl;
								Tester.set_type(i,j,tower_type); // sets game 2d to 4 sig flipped bulbasaur
								Tester.redraw(tower_type,screen,flipped_sprite);
								}

							else{
								tower_type = 3;
								if(evolution == 3){
									tower_type = 17;
										}
								else if(evolution == 2){
									tower_type = 15;
									state++;
									}
								else if(evolution == 1){
									tower_type = 13;
									//bulba_state++;
									}
								//cout << "tower is " << tower_type << endl;
								Tester.set_type(i,j,tower_type); // sets game 2d to 3 sig bulbasaur
								Tester.redraw(tower_type,screen,sprite_sheet);
								}
							sum -=100;
						}
						else if(type == 2){
							if(Tester.get_type(i,j+2) == 1){
								tower_type = 6;
								if(evolution == 3){
									tower_type = 24;
										}
								else if(evolution == 2){
									tower_type = 22;
									state++;
									}
								else if(evolution == 1){
									tower_type = 20;
									//bulba_state++;
									}
								Tester.set_type(i,j,tower_type);
								Tester.redraw(tower_type,screen,flipped_sprite);
								}

							else{
								tower_type = 5;
								if(evolution == 3){
									tower_type = 23;
										}
								else if(evolution == 2){
									tower_type = 21;
									state++;
									}
								else if(evolution == 1){
									tower_type = 19;
									//bulba_state++;
									}
								Tester.set_type(i,j,tower_type);
								Tester.redraw(tower_type,screen,sprite_sheet);
								}
						}
						else if(type == 3){
							if(Tester.get_type(i,j+2) == 1){
								tower_type = 8;
								if(evolution == 3){
									tower_type = 30;
										}
								else if(evolution == 2){
									tower_type = 28;
									state++;
									}
								else if(evolution == 1){
									tower_type = 26;
									//bulba_state++;
									}
								Tester.set_type(i,j,tower_type);
								Tester.redraw(tower_type,screen,flipped_sprite);
								}

							else{
								tower_type = 7;
								if(evolution == 3){
									tower_type = 29;
										}
								else if(evolution == 2){
									tower_type = 27;
									state++;
									}
								else if(evolution == 1){
									tower_type = 25;
									//bulba_state++;
									}
								Tester.set_type(i,j,tower_type);
								Tester.redraw(tower_type,screen,sprite_sheet);
								}
						}
						Tester.draw_sprite(background,screen,120,0,0,480, BUTTON_WIDTH, BUTTON_HEIGHT);
						Tester.draw_sprite(background,screen,120,0,240,480, BUTTON_WIDTH, BUTTON_HEIGHT);
						Tester.draw_sprite(background,screen,120,0,480,480, BUTTON_WIDTH, BUTTON_HEIGHT);
						//draw_sprite(title_pic,screen,0,0,0,480,640,100);
						SDL_Flip(screen);
						cout << "Sum is " << sum << endl;
						}
					}
				}
		}
		
   	}
	SDL_FreeSurface(menu);
	SDL_FreeSurface(title_pic);
	SDL_FreeSurface(background);
   	SDL_FreeSurface(sprite_sheet);
	SDL_FreeSurface(dot);
	TTF_CloseFont( font );
	TTF_Quit();
   	SDL_Quit();
};


int sprite::check_key(int eye, int jay, int state, Tile Tester){
	// q will quit the menu
	int i=0,j=0;
	SDL_Event key_test;
	//cout << "In this is " << Tester.get_type(eye,jay) << endl;
	bool end = true;
	while(end){
		while(SDL_PollEvent(&key_test)){
			if(key_test.type == SDL_KEYDOWN){
				switch(key_test.key.keysym.sym){
					case SDLK_q:	//quit
						return 0;
						end = false;   ///////////////////have a start button to start enemy wave
						break;
					}
				}
			else if(key_test.type == SDL_MOUSEBUTTONDOWN){
				if(key_test.button.button == SDL_BUTTON_LEFT){
					cout << "Here in button" << endl;
					int x = key_test.button.x;
					//cout << "Herin x button " << x << endl;
					int y = key_test.button.y;
					i = 12; // i and j components for the 2-d game board in Tester tile
					//cout << "Here in i button " << i << endl;
					j = (x/40);
					//cout << "Here in j button " << j << endl;
					//cout << "get da tye " << Tester.get_type(i,j) << endl;
					//cout << "This thing is " << Tester.get_type(eye,jay) << endl;
					if(Tester.get_type(i,j)==10){
						if(Tester.get_type(eye,jay)==3 || Tester.get_type(eye,jay)==4){ // evolu to Ivysaur
							evolution = 1;
							return 1;
							}
						else if(Tester.get_type(eye,jay)==5 || Tester.get_type(eye,jay)==6){ //evolu to Charmeleon
							evolution = 1;
							return 2;
							}
						else if(Tester.get_type(eye,jay)==7 || Tester.get_type(eye,jay)==8){
							evolution = 1;
							return 3;
							}
						else if(Tester.get_type(eye,jay)==13 || Tester.get_type(eye,jay)==14){ //evolu to Venasaur
							evolution = 2;
							return 1;
							}
						else if(Tester.get_type(eye,jay)==19 || Tester.get_type(eye,jay)==20){ //evolu to charizard
							evolution = 2;
							return 2;
							}
						else if(Tester.get_type(eye,jay)==25 || Tester.get_type(eye,jay)==26){ //evolu to blastoise
							evolution = 2;
							return 3;
							}
						else if(Tester.get_type(eye,jay)==15 || Tester.get_type(eye,jay)==16){ //Super venasaur
							evolution = 3;
							return 1;
							}
						else if(Tester.get_type(eye,jay)==21 || Tester.get_type(eye,jay)==22){ // Super Charizard
							evolution = 3;
							return 2;
							}
						else if(Tester.get_type(eye,jay)==27 || Tester.get_type(eye,jay)==28){ //evolu to super blastoise
							evolution = 3;
							return 3;
							}
						else if(Tester.get_type(eye,jay)==17 || Tester.get_type(eye,jay)==18){ // Super vena maxed exit
							//evolution = 3;
							return 0;
							}
						else if(Tester.get_type(eye,jay)==23 || Tester.get_type(eye,jay)==24){ // Super Charizard maxed exit
							//evolution = 3;
							return 0;
							}
						else if(Tester.get_type(eye,jay)==29 || Tester.get_type(eye,jay)==30){ //Super blas maxed exit
							//evolution = 2;
							return 0;
							}
						evolution = 0;
						return 1;
						}
					else if(Tester.get_type(i,j)==11){
						if (state >=1 ){
							return 4;
							}
						evolution = 0;
						return 2;
						}
					else if(Tester.get_type(i,j)==12 && state==0){
						evolution = 0;
						return 3;
						}
					}
				}
					
		}
	}
}

void sprite::animate(int x,int y,SDL_Surface* dot,SDL_Surface* screen,SDL_Surface* background,Tile Tester){ //Not used as of now
		Tester.redraw(1,screen,background);//draw background
		Tester.redraw(31,screen,background);
		//SDL_Delay(1000);
		Tester.draw_sprite(dot, screen,0,0,x, y, 20, 20 );
		SDL_Flip(screen);
	}

SDL_Surface* sprite::load_image( std::string filename ){
	//Temporary storage for the image that's loaded
    	SDL_Surface* loadedImage = NULL;
    
    	//The optimized image that will be used
    	SDL_Surface* optimizedImage = NULL;

	loadedImage = SDL_LoadBMP(filename.c_str());

	if(loadedImage !=NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
		}

	if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }

	return optimizedImage;
}
					

Uint32 sprite::get_pixel32( SDL_Surface *surface, int x, int y )
{
    	//Convert the pixels to 32 bit
    	Uint32 *pixels = (Uint32 *)surface->pixels;
    
   	//Get the requested pixel
    	return pixels[ ( y * surface->w ) + x ];
}


void sprite::put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    	//Convert the pixels to 32 bit
    	Uint32 *pixels = (Uint32 *)surface->pixels;

    	//Set the pixel
    	pixels[ ( y * surface->w ) + x ] = pixel;
}


SDL_Surface* sprite::flip_image(SDL_Surface* sprite, int flags){

	//Pointer to the soon to be flipped surface
    	SDL_Surface *flipped = NULL;

    	//If the image is color keyed
    	if( sprite->flags & SDL_SRCCOLORKEY ){

 	       flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, sprite->w, sprite->h, sprite->format->BitsPerPixel, sprite->format->Rmask, sprite->format->Gmask, sprite->format->Bmask, 0 );
    		}
    	//Otherwise
    	else{

        	flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, sprite->w, sprite->h, sprite->format->BitsPerPixel, sprite->format->Rmask, sprite->format->Gmask, sprite->format->Bmask, sprite->format->Amask );
    		}

    	//If the surface must be locked
    	if( SDL_MUSTLOCK( sprite ) ){
        	//Lock the surface
        	SDL_LockSurface( sprite );
    	}

    //Go through columns
    	for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- ){
        	//Go through rows
        	for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- ){
            		//Get pixel
            		Uint32 pixel = get_pixel32( sprite, x, y );

            		//Copy pixel
            		if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) ){
                		put_pixel32( flipped, rx, ry, pixel );
            			}
            		else if( flags & FLIP_HORIZONTAL ){
                		put_pixel32( flipped, rx, y, pixel );
            			}
            		else if( flags & FLIP_VERTICAL ){
                		put_pixel32( flipped, x, ry, pixel );
            			}
        		}
    		}

    	//Unlock surface
    	if( SDL_MUSTLOCK( sprite ) ) {
        	SDL_UnlockSurface( sprite );
    		}

    	//Copy color key
    	if( sprite->flags & SDL_SRCCOLORKEY ){
        	SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, sprite->format->colorkey );
    		}

    	//Return flipped surface
    	return flipped;
}
















