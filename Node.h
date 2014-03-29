//#include "SDL.h"
#include<vector>
#include <iostream>
using namespace std;
#ifndef NODE_H
#define NODE_H
class Node
{
public:
Node(int, int, int);
int getPathNum();
void setPathNum(int);
int getY();
void cascadeNext(vector<vector<Node> > &);
Node *getNext();
void setPrev(Node *);
char getDir();
private:
int x;
int y;
int pathNum;
Node *next;
Node *prev;
char type;
char dir;
};

#endif
