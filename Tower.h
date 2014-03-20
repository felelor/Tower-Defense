#ifndef TOWER_H
#define TOWER_H


class Tower{

	public:
		Tower();
		int get_build_x(); //x coor of tower
		void set_build_x(int);
		int get_build_y(); //y coor of tower
		void set_build_y(int);
		int get_active(); //set 0 or 1 to proper type
		void set_active(int);
		int get_type(); //whether it be type 1.2.or 3	
		void set_type(int);
		int get_radius(); //whether it be blast radius
		void set_radius(int);
		int get_cost(); //whether it be blast radius
		void set_cost(int);

	private:
		int x;
		int y;
		int active;
		int type;
		int blast_radius;
		int cost;
};

#endif
		
		
		
