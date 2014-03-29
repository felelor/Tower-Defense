//#include "SDL.h"
#include "Node.h"
#include <string>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<vector>

Node::Node( int setx, int sety, int path)
{
	x=setx;
	y=sety;
	pathNum = path;
	if(path == 34)
	{
	cout<<"set "<<x<<", "<<y<<" to b"<<endl;
	type = 'b';
	}
	else if(path == 35)
	{
		cout<<"set "<<x<<", "<<y<<" to e"<<endl;
		type = 'e';
	}
	else if(path == 31)
		type ='p';
	else
		type = 'n';
}

int Node::getY() {return x;}

Node *Node::getNext() {return next;}

void Node::cascadeNext(vector<vector<Node> > &board)
{
//cout<<getY()<<" compared to "<<board.size()<<endl;
//if(getY()==board.size()-1)
	if(type ==  'e')
	{
		dir = '0';
		pathNum = (*prev).getPathNum();
		return;
	}
//cout<<board[x+1][y].getPathNum() <<endl;

	else if(type == 'b')
	{
		cout<<"Made it"<<endl;
		if(x < board.size()-1 && board[x+1][y].getPathNum()>0)
		{
			dir = 'd';
			pathNum = board[x+1][y].getPathNum();
			next = &board[x+1][y];
			board[x+1][y].setPrev(this);
			board[x+1][y].cascadeNext(board);
		}
		else if(x > 0 && board[x-1][y].getPathNum()>0)
		{
			dir = 'u';
			pathNum = board[x-1][y].getPathNum();
			next = &board[x-1][y];
			board[x-1][y].setPrev(this);
			board[x-1][y].cascadeNext(board);
		}
		else if(y < board.size()-1 && board[x][y+1].getPathNum()>0)
		{
			dir = 'r';
			pathNum = board[x][y+1].getPathNum();
			next = &board[x][y+1];
			board[x][y+1].setPrev(this);
			board[x][y+1].cascadeNext(board);
		}
		else if(y > 0 && board[x][y-1].getPathNum()>0)
		{
			dir = 'l';
			pathNum = board[x][y-1].getPathNum();
			next = &board[x][y-1];
			board[x][y-1].setPrev(this);
			board[x][y-1].cascadeNext(board);
		}
		return;
	}
	else if(type == 'p')
	{
		if(x < board.size()-1 && board[x+1][y].getPathNum() > 30 && this != board[x+1][y].getNext())
		{
			dir = 'd';
			next = &board[x+1][y];
			board[x+1][y].setPrev(this);
			//	 cout<<"found next at "<<x+1<<", "<<y<<endl;
			//	 board[x+1][y].setPathNum(getPathNum()+1);
			board[x+1][y].cascadeNext(board);
			return;
		}
		if(y > 0 && board[x][y-1].getPathNum() > 30 && this != board[x][y-1].getNext())
		{
			dir = 'l';
			next = &board[x][y-1];
			board[x][y-1].setPrev(this);
			//	 cout<<"found next at "<<x<<", "<<y-1<<endl;
			board[x][y-1].cascadeNext(board);
			return;
		}
		if(y < board.size()-1&& board[x][y+1].getPathNum() > 30 && this != board[x][y+1].getNext())
		{
			dir = 'r';
			next = &board[x][y+1];
			board[x][y-1].setPrev(this);
			//	 cout<<"found next at "<<x<<", "<<y+1<<endl;
			board[x][y+1].cascadeNext(board);
			return;
		}
		if(x > 0 && board[x-1][y].getPathNum() > 30 && this != board[x-1][y].getNext())
		{
			dir = 'u';
			next = &board[x-1][y];
			board[x-1][y].setPrev(this);
			//	 cout<<"found next at "<<x<<", "<<y+1<<endl;
			board[x-1][y].cascadeNext(board);
			return;
		}
	}
cout<<"Error, could not find next node for node type: "<< type<< " at "<<x<<", "<<y<<endl;
return;
}

void Node::setPathNum(int num) {pathNum = num;}

int Node::getPathNum()	{return pathNum;}

void Node::setPrev(Node *in) {prev = in;}

char Node::getDir() {return dir;}
