#ifndef TYPESET_H
#define TYPESET_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "Tile.h"
#include <string>

class Typeset{

	public:
		Typeset(TTF_Font*);
		void show(int,Tile,SDL_Surface*,SDL_Surface*);

	private:
		SDL_Rect menu;
		int button1_x, button2_x, button3_x;
		SDL_Surface* message1;
		SDL_Surface* message2;
		SDL_Surface* message3;
		SDL_Surface* message4;
		SDL_Surface* message5;
		SDL_Surface* message6;
		SDL_Surface* message7;
		SDL_Surface* message8;
		SDL_Surface* message9;
		SDL_Surface* message10;
		SDL_Surface* message11;
		SDL_Surface* message12;

};

#endif
		
