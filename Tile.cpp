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
const int BUTTON_WIDTH=214;
const int BUTTON_HEIGHT=80; 
const int TOWER_HEIGHT=40;
const int TOWER_SPRITES=3;
const int TOTAL_TILES = 192;
const int TILE_SPRITES = 3;

Tile::Tile(int x, int y, int tile_type, int t){

		clip[0].x = 0;     // grass
		clip[0].y = 0;
		clip[0].w = TOWER_WIDTH;
		clip[0].h = TOWER_HEIGHT;

		clip[1].x = 40;     // path
		clip[1].y = 0;
		clip[1].w = TOWER_WIDTH;
		clip[1].h = TOWER_HEIGHT;
		
		clip[2].x = 80;     // pokeball
		clip[2].y = 0;
		clip[2].w = TOWER_WIDTH;
		clip[2].h = TOWER_HEIGHT;
		
		clip[3].x = 0;     // bulbasaur
		clip[3].y = 0;
		clip[3].w = TOWER_WIDTH;
		clip[3].h = TOWER_HEIGHT;
	
		clip[4].x = 440;     // reverse bulbasaur
		clip[4].y = 0;
		clip[4].w = TOWER_WIDTH;
		clip[4].h = TOWER_HEIGHT;
	
		clip[5].x = 160;     // charmander
		clip[5].y = 0;
		clip[5].w = TOWER_WIDTH;
		clip[5].h = TOWER_HEIGHT;
	
		clip[6].x = 280;     // reverse charmander
		clip[6].y = 0;
		clip[6].w = TOWER_WIDTH;
		clip[6].h = TOWER_HEIGHT;

		clip[7].x = 320;     // squirtle
		clip[7].y = 0;
		clip[7].w = TOWER_WIDTH;
		clip[7].h = TOWER_HEIGHT;

		clip[8].x = 120;     // reverse squirtle
		clip[8].y = 0;
		clip[8].w = TOWER_WIDTH;
		clip[8].h = TOWER_HEIGHT;

		clip[10].x = 120;     // button 1
		clip[10].y = 0;
		clip[10].w = BUTTON_WIDTH;
		clip[10].h = BUTTON_HEIGHT;
	
		clip[11].x = 120;     // button 2
		clip[11].y = 0;
		clip[11].w = BUTTON_WIDTH;
		clip[11].h = BUTTON_HEIGHT;

		clip[12].x = 120;     // button 3
		clip[12].y = 0;
		clip[12].w = BUTTON_WIDTH;
		clip[12].h = BUTTON_HEIGHT;
		
		clip[13].x = 40;     // IvySaur
		clip[13].y = 0;
		clip[13].w = TOWER_WIDTH;
		clip[13].h = TOWER_HEIGHT;

		clip[14].x = 400;     // Reverse IvySaur
		clip[14].y = 0;
		clip[14].w = TOWER_WIDTH;
		clip[14].h = TOWER_HEIGHT;

		clip[15].x = 80;     // VenaSaur
		clip[15].y = 0;
		clip[15].w = TOWER_WIDTH;
		clip[15].h = TOWER_HEIGHT;

		clip[16].x = 360;     // Reverse VenaSaur
		clip[16].y = 0;
		clip[16].w = TOWER_WIDTH;
		clip[16].h = TOWER_HEIGHT;

		clip[17].x = 120;     // Super VenaSaur
		clip[17].y = 0;
		clip[17].w = TOWER_WIDTH;
		clip[17].h = TOWER_HEIGHT;

		clip[18].x = 320;     // Reverse Super venaSaur
		clip[18].y = 0;
		clip[18].w = TOWER_WIDTH;
		clip[18].h = TOWER_HEIGHT;

		clip[19].x = 200;     // Charmeleon
		clip[19].y = 0;
		clip[19].w = TOWER_WIDTH;
		clip[19].h = TOWER_HEIGHT;

		clip[20].x = 240;     // Reverse Charmeleon
		clip[20].y = 0;
		clip[20].w = TOWER_WIDTH;
		clip[20].h = TOWER_HEIGHT;

		clip[21].x = 240;     // Charizard
		clip[21].y = 0;
		clip[21].w = TOWER_WIDTH;
		clip[21].h = TOWER_HEIGHT;

		clip[22].x = 200;     // Reverse Charizard
		clip[22].y = 0;
		clip[22].w = TOWER_WIDTH;
		clip[22].h = TOWER_HEIGHT;

		clip[23].x = 280;     // Super Charizard
		clip[23].y = 0;
		clip[23].w = TOWER_WIDTH;
		clip[23].h = TOWER_HEIGHT;

		clip[24].x = 160;     // Reverse Super Charizard
		clip[24].y = 0;
		clip[24].w = TOWER_WIDTH;
		clip[24].h = TOWER_HEIGHT;

		clip[25].x = 360;     // Warturtle
		clip[25].y = 0;
		clip[25].w = TOWER_WIDTH;
		clip[25].h = TOWER_HEIGHT;

		clip[26].x = 80;     // Reverse Warturtle
		clip[26].y = 0;
		clip[26].w = TOWER_WIDTH;
		clip[26].h = TOWER_HEIGHT;

		clip[27].x = 400;     // Blastoise
		clip[27].y = 0;
		clip[27].w = TOWER_WIDTH;
		clip[27].h = TOWER_HEIGHT;

		clip[28].x = 40;     // Reverse Blastoise
		clip[28].y = 0;
		clip[28].w = TOWER_WIDTH;
		clip[28].h = TOWER_HEIGHT;

		clip[29].x = 440;     // Super Blastoise
		clip[29].y = 0;
		clip[29].w = TOWER_WIDTH;
		clip[29].h = TOWER_HEIGHT;

		clip[30].x = 0;     // Reverse Super Blastoise
		clip[30].y = 0;
		clip[30].w = TOWER_WIDTH;
		clip[30].h = TOWER_HEIGHT;
			
		clip[31].x = 40;     // path
		clip[31].y = 0;
		clip[31].w = TOWER_WIDTH;
		clip[31].h = TOWER_HEIGHT;

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
		cout << "a is " << a<< endl;
		}

	for(int i=0; i<13; i++){
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
	//redraw(10,picture,screen);
	//redraw(11,picture,screen);
	//redraw(12,picture,screen); 
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
	cout << "Get" << endl;
	cout << i << "," << j<<endl;
	return game[i][j];
}

void Tile::set_type(int i,int j,int value){
	game[i][j] = value;
	for(int i=0; i<13; i++){
			for(int j=0; j<16; j++){
				//rray temp the loop is at
				cout << game[i][j] << " "; 
			}
		cout << "\n" << endl;
	}
}

void Tile::draw(SDL_Surface* picture,SDL_Surface* screen){
	int x=0,y=0, t=0, choice =0;
	for(int i=0; i<13; i++){
 		//cout <<"Here" << endl;
		y_vector.push_back(y);
		for(int j=0; j<16; j++){
			x_vector.push_back(x);
			if( game[i][j] == 0){
				//cout << "brown. Tile number " << t<< endl;
				picture_x=0;
				//cout << "y is " << y << endl;
				draw_sprite(picture,screen,picture_x,0,x,y, TOWER_WIDTH, TOWER_HEIGHT);
				}
			else if( game[i][j] == 1 || game[i][j] == 31){
				//cout << "green Tile number " << t<< endl;
				picture_x=40;
				draw_sprite(picture,screen,picture_x,0,x,y, TOWER_WIDTH, TOWER_HEIGHT);
				//choice = 0;
				}
			else if( game[i][j] == 2){
				//cout << "ball Tile number " << t<< endl;
				picture_x=80;
				draw_sprite(picture,screen,picture_x,0,x,y, TOWER_WIDTH, TOWER_HEIGHT);
				}
			else if( game[i][j] == 10){
				//cout << "button. Tile number " << t<< endl;
				draw_sprite(picture,screen,120,0,0,480, BUTTON_WIDTH, BUTTON_HEIGHT);
			}
			
			else if( game[i][j] == 11){
				//cout << "button. Tile number " << t<< endl;
				draw_sprite(picture,screen,120,0,240,480, BUTTON_WIDTH, BUTTON_HEIGHT);
			}
		
			else if( game[i][j] == 12){
				//cout << "button. Tile number " << t<< endl;
				draw_sprite(picture,screen,120,0,480,480, BUTTON_WIDTH, BUTTON_HEIGHT);
			}  //MAKE A DRAW BUTTONS FUNCTION TO OVER WRITE BUTTONS
				
			//cout <<"Here" << endl;
			//cout << "x is " << x << endl;
			//cout << "y is " << y << endl;
			//draw_sprite(picture,screen,picture_x,0,x,y, TOWER_WIDTH, TOWER_HEIGHT);
			//SDL_Flip(screen);
			x+=TOWER_WIDTH;
			t++;
			//SDL_Flip(screen);
			}
		//t++;
		//SDL_Flip(screen);
		y+=TOWER_HEIGHT;
		x=0;
		cout << "y is " << y << endl;
		}
	SDL_Flip(screen);
}

void Tile::redraw(int type,SDL_Surface* screen,SDL_Surface* picture){
	int x=0,y=0, t=0, choice =0;
	for(int i=0; i<13; i++){
		//cout << i << " ' " << j<< endl;
 		cout <<"Here" << endl;
		y_vector.push_back(y);
		for(int j=0; j<16; j++){
			x_vector.push_back(x);
			if( game[i][j] == type ){
				cout << i << " ' " << j<< endl;
				draw_sprite(picture,screen,(clip[type].x),(clip[type].y),x,y, TOWER_WIDTH, TOWER_HEIGHT);
				//choice = 0;
				}
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
		//cout << game[12][0] << endl;
}
	
