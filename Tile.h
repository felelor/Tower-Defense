#ifndef TILE_H
#define TILE_H
#include <string>
#include <vector>
#include "SDL/SDL.h"
using namespace std;

class Tile {
	
	public:
		Tile(int x, int y, int tile_type, int t);
		//void show();			// try and display in oldsprite...for loop and call apply surface
		bool set_tiles(string filename, SDL_Surface*, SDL_Surface*);
		//int get_type();
		SDL_Rect get_surface_box(int);
		SDL_Rect get_pic_box(int);
		void draw_sprite(SDL_Surface* picture,SDL_Surface* screen, int pic_X, int pic_Y, int screen_X, int screen_Y, int width, int height);
		int get_type(int,int);
		void set_type(int,int,int);
		void draw(SDL_Surface*,SDL_Surface*);
		void redraw(int, int,int,SDL_Surface*,SDL_Surface*);
		
	private:
		SDL_Rect surface_box[192];
		SDL_Rect pic_box[192];
		int type,picture_x,picture_y;
		vector<int> temp;
		vector<int> x_vector;
		vector<int> y_vector;
		vector<vector<int> > game;
		SDL_Surface* sprite_sheet;
};

#endif
