#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "sprite.h"
#include "Tower.h"
#include "Tile.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 580;
const int TOWER_WIDTH=40;
const int TOWER_HEIGHT=40;
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;
const char* WINDOW_TITLE = "Tower Sprites";
const int FRAMES_PER_SECOND = 20;
//const int ROW_WIDTH = 12;

sprite::sprite(){

	SDL_Init(SDL_INIT_EVERYTHING);
	sum=300;
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
	//SDL_SetColorKey( dot, SDL_SRCCOLORKEY, SDL_MapRGB(dot->format, 255, 0, 255) );
	//SDL_SetColorKey( background, SDL_SRCCOLORKEY, SDL_MapRGB(background->format, 255, 0, 255) );

	//draw_sprite(background,screen,0, 0, 0, 0, 640, 480);//draw background
	Tile Tester(0,0,-1,0);
	Tester.set_tiles("field_1.txt",screen,background);
	SDL_Flip(screen);
	draw_sprite(title_pic,screen,0,0,0,480,640,100);//draw title

	SDL_Event sprites;//event

	//area where tower can be built
	Tower build1; //tower class
	build1.set_build_x(320);
	build1.set_build_y(80); 

	Tower build2; //tower class
	build2.set_build_x(213);
	build2.set_build_y(186);

	Tower build3; //tower class
	build3.set_build_x(320);
	build3.set_build_y(345);  
	//draw_sprite(dot,screen,270,0,x,y,20,20);

	bool quit = true;
	int startTicks = SDL_GetTicks(); 
   	while (quit){
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
					i = (y/40); // i and j components for the 2-d game board in Tester tile
					j = (x/40);
					
					//Uint8 r,g,b;
					//Uint32 bg = get_pixel32(background,x,y ); 		//finding colors...not needed now but cool
					//SDL_GetRGB( bg, screen->format, &r, &g, &b );

					if(Tester.get_type(i,j)==2){ //if click is on pre-determined area
						draw_sprite(menu,screen,0,0,0,480,640,100);
						SDL_Flip(screen);
						int type = check_key(sprite_sheet,screen); //type of tower
						
						if(type == 1){
							Tester.set_type(i,j,3); // sets game 2d to 3 sig bulbasaur
							if(Tester.get_type(i,j+2) == 1){ // sees if the image needs to be flipped if on other side of path for display
								Tester.redraw(i,j,1,screen,flipped_sprite);
								}

							else{
								Tester.redraw(i,j,0,screen,sprite_sheet);
								}
						}
						else if(type == 2){
							Tester.set_type(i,j,4);
							if(Tester.get_type(i,j+2) == 1){
								Tester.redraw(i,j,1,screen,flipped_sprite);
								}

							else{
								Tester.redraw(i,j,0,screen,sprite_sheet);
								}
						}
						else if(type == 3){
							Tester.set_type(i,j,5);
							if(Tester.get_type(i,j+2) == 1){ // checks to see if path is to right
								Tester.redraw(i,j,1,screen,flipped_sprite);
								}

							else{
								Tester.redraw(i,j,0,screen,sprite_sheet);
								}
						}
						draw_sprite(title_pic,screen,0,0,0,480,640,100);
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
   	SDL_Quit();
};

//Rudimetary draw function...i think i'll be updating or removing it
void sprite::draw_sprite(SDL_Surface* picture,SDL_Surface* screen, int pic_X, int pic_Y, int screen_X, int screen_Y, int width, int height){
	//cout <<"In draw" << endl;
	SDL_Rect pic_Rect;
	pic_Rect.x = pic_X;
   	pic_Rect.y = pic_Y;
   	pic_Rect.w = width;
   	pic_Rect.h = height;

   	SDL_Rect screen_Rect;
   	screen_Rect.x = screen_X;
   	screen_Rect.y = screen_Y;
   	screen_Rect.w = width;
   	screen_Rect.h = height;
	//cout<<"Before blit"<<endl;
   	SDL_BlitSurface(picture, &pic_Rect, screen, &screen_Rect);
	
}

int sprite::check_key(SDL_Surface* sprite_sheet,SDL_Surface* screen){
	// q will quit the menu
	SDL_Event key_test;
	bool end = true;
	while(end){
		while(SDL_PollEvent(&key_test)){
			if(key_test.type == SDL_KEYDOWN){
				switch(key_test.key.keysym.sym){
					case SDLK_1: 
						//sprite_x=0; //bulbasaur
						return 1;
						end = false;
						break;
					case SDLK_2:
						//sprite_x=132;
						return 2;	//charmander
						end = false;
						break;
					case SDLK_3:
						//sprite_x=255;
						return 3;	//squirtle
						end = false;
						break;
					case SDLK_q:	//quit
						return 0;
						end = false;
						break;
					}
				}
		}
	}
}

void sprite::animate(int x,int y,SDL_Surface* dot,SDL_Surface* screen,SDL_Surface* background){ //Not used as of now
		draw_sprite(background,screen,0, 0, 0, 0, 640, 480);//draw background
		draw_sprite(dot, screen,0,0,x, y, 20, 20 );
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
















