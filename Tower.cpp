#include "Tower.h"

Tower::Tower(){
	x=0;
	y=0;
	active=0;
	blast_radius=0;
	type=0;
}

int Tower::get_build_x(){
	return x;
}

void Tower::set_build_x(int value){
	x=value;
}

int Tower::get_build_y(){
	return y;
}

void Tower::set_build_y(int value){
	y=value;
}

int Tower::get_active(){
	return active;
}

void Tower::set_active(int value){
	active=value;
}

int Tower::get_type(){
	return type;
}

void Tower::set_type(int value){
	type=value;
}

int Tower::get_radius(){
	return blast_radius;
}

void Tower::set_radius(int value){
	blast_radius=value;
}
	
int Tower::get_cost(){
	return cost;
}

void Tower::set_cost(int value){
	if(value == 1){
		cost = 100;
		}
	else if(value == 2){
		cost = 125;
		}
	else if(value ==3){
		cost = 150;
	}
}	


	
