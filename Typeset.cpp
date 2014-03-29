#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <iostream>
#include <vector>
#include "Tile.h"
#include "Typeset.h"
using namespace std;

const int BUTTON_WIDTH=160;
const int BUTTON_HEIGHT=40;

Typeset::Typeset(TTF_Font *font){
	menu.x = 0;
	menu.y = 480;
	menu.w = 640;
	menu.h = 80;

	string a = "100";

	button1_x = 20;
	button2_x = 240;
	button3_x = 510;

	SDL_Color textColor = { 0, 0, 0 };

	message1 = TTF_RenderText_Solid( font, "Pokemon", textColor );
	message2 = TTF_RenderText_Solid( font, "Tower", textColor );
	message3 = TTF_RenderText_Solid( font, "Defense", textColor );

	message4 = TTF_RenderText_Solid( font, "Bulbasaur", textColor );
	message5 = TTF_RenderText_Solid( font, "100", textColor);
	message6 = TTF_RenderText_Solid( font, "Charmander", textColor );
	message7 = TTF_RenderText_Solid( font, "125", textColor);
	message8 = TTF_RenderText_Solid( font, "Squirtle", textColor );
	message9 = TTF_RenderText_Solid( font, "150", textColor);

	message10 = TTF_RenderText_Solid( font, "Evolve", textColor );
	message11 = TTF_RenderText_Solid( font, "Sell", textColor );
	message12 = TTF_RenderText_Solid( font, "Wa", textColor );
	  
}
	
void Typeset::show(int mess,Tile test, SDL_Surface* screen,SDL_Surface* picture){

	
	if(mess ==1){
		test.draw_sprite(message1,screen,NULL,NULL,button1_x,500, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message2,screen,NULL,NULL,button2_x,500, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message3,screen,NULL,NULL,button3_x,500, BUTTON_WIDTH, BUTTON_HEIGHT);
	}

	else if(mess == 2) {
		test.draw_sprite(message4,screen,NULL,NULL,button1_x,490, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message6,screen,NULL,NULL,button2_x,490, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message8,screen,NULL,NULL,button3_x,490, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message5,screen,NULL,NULL,button1_x+50,510, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message7,screen,NULL,NULL,button2_x+70,510, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message9,screen,NULL,NULL,button3_x+30,510, BUTTON_WIDTH, BUTTON_HEIGHT);
		}

	else if(mess == 3) {
		test.draw_sprite(message10,screen,NULL,NULL,button1_x,500, BUTTON_WIDTH, BUTTON_HEIGHT);
		test.draw_sprite(message11,screen,NULL,NULL,button2_x,500, BUTTON_WIDTH, BUTTON_HEIGHT);
		//test.draw_sprite(message12,screen,NULL,NULL,button3_x,500, BUTTON_WIDTH, BUTTON_HEIGHT);
		}	
}
	

	
	
