#include "SDL/SDL.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstdio>
#include <iostream>
#include "Tile.h"
using namespace std;
const int TOWER_WIDTH=40;
const int SCREEN_WIDTH=640;
const int TOWER_HEIGHT=40;
const int TOWER_SPRITES=3;
const int TOTAL_TILES = 192;
const int TILE_SPRITES = 3;

Tile::Tile(int x, int y, int tile_type, int t){
		surface_box[t].x = x;
		surface_box[t].y = y;
		surface_box[t].w = TOWER_WIDTH;
		surface_box[t].h = TOWER_HEIGHT;

		picture_x=0;
		picture_y=0;
		//sprite_sheet = SDL_LoadBMP("sprites.bmp");

		type = tile_type;
		
			
}

bool Tile::set_tiles(string filename,SDL_Surface* screen,SDL_Surface* picture){
	//vector<int> temp;
	//tile offsets
	int x=0, y=0, a, elem_place=0;

	//open map file
	ifstream map (filename.c_str());

	//in case you can't open the map
	if( map == NULL){
		return false;
		}

	while(!map.eof()){ //find size of input file by plugging values into a vector and use get size. Then use a nexted for loop to make board
		map >> a;
		temp.push_back(a);
		//cout << "a is " << a<< endl;
		}

	for(int i=0; i<12; i++){
		vector<int> row; //create a row in the board
			for(int j=0; j<16; j++){
				//x_vector.push_back(x);
				row.push_back(temp[elem_place]);//plugging the file values into a row
				elem_place++;  //determines where in 1d array temp the loop is at 
			}
		game.push_back(row);//ram that filled row into the 2d sudoku vector
		row.clear();
	}
	draw(picture,screen); //draws game 
	//CLOSE FILE
	map.close();
	return true;
}

SDL_Rect Tile::get_surface_box(int t){
	return surface_box[t];
}	
	
SDL_Rect Tile::get_pic_box(int t){
	return pic_box[t];
}	

void Tile::draw_sprite(SDL_Surface* picture,SDL_Surface* screen, int pic_X, int pic_Y, int screen_X, int screen_Y, int width, int height){
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
	//cout<<"After blit"<<endl;
	//SDL_Flip(screen);
	//cout<<"After flip"<<endl;
}

int Tile::get_type(int i,int j){
	return game[i][j];
}

void Tile::set_type(int i,int j,int value){
	game[i][j] = value;
}

void Tile::draw(SDL_Surface* picture,SDL_Surface* screen){
	int x=0,y=0, t=0, choice =0;
	for(int i=0; i<12; i++){
 		//cout <<"Here" << endl;
		y_vector.push_back(y);
		for(int j=0; j<16; j++){
			x_vector.push_back(x);
			if( game[i][j] == 0 ){
				//cout << "brown. Tile number " << t<< endl;
				picture_x=0;
				picture_y=0;
				//choice = 0;
				}
			else if( game[i][j] == 1){
				//cout << "green Tile number " << t<< endl;
				picture_x=40;
				picture_y=0;
				//choice = 0;
				}
			else if( game[i][j] == 2){
				//cout << "ball Tile number " << t<< endl;
				picture_x=80;
				picture_y=0;
				//choice = 0;
				}
			//cout <<"Here" << endl;
			//cout << "x is " << x << endl;
			//cout << "y is " << y << endl;
			draw_sprite(picture,screen,picture_x,picture_y,x,y, TOWER_WIDTH, TOWER_HEIGHT);
			//SDL_Flip(screen);
			x+=TOWER_WIDTH;
			t++;
			//SDL_Flip(screen);
			}
		//t++;
		//SDL_Flip(screen);
		y+=TOWER_HEIGHT;
		x=0;
		//cout << "y is " << y << endl;
		}
	SDL_Flip(screen);
}

void Tile::redraw(int i, int j,int orient,SDL_Surface* screen,SDL_Surface* sprite_sheet){
	if( game[i][j] == 3){
		//cout << "ball Tile number " << t<< endl;
		picture_y=0;
		if(orient==0){ //if the image is not in need of flipping keep same
			picture_x=0;
			//choice = 1;
			}
		else{
			picture_x=440; //if flipped put in flip coordinates
			}
			
		}
	else if( game[i][j] == 4){
		//cout << "ball Tile number " << t<< endl;
		picture_y=0;
		if(orient==0){ //if the image is not in need of flipping keep same
			picture_x=160;
			//choice = 1;
			}
		else{
			picture_x=280; //if flipped put in flip coordinates
			
		}
		//choice = 1;
			}
	else if( game[i][j] == 5){
		//cout << "ball Tile number " << t<< endl;
		picture_y=0;
		if(orient==0){ //if the image is not in need of flipping keep same
			picture_x=320;
			//choice = 1;
			}
		else{
			picture_x=120; //if flipped put in flip coordinates
			
		}
		//choice = 1;
		}
	draw_sprite(sprite_sheet,screen,picture_x,picture_y,x_vector[j],y_vector[i], TOWER_WIDTH, TOWER_HEIGHT);
}
	
