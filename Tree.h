#pragma once

#include <raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAKE(x,y) (x*)malloc(y * sizeof(x)) 


typedef struct tree tree;
struct tree {
	int val;
	int Nodes; 
  	tree** child;
  	 
};



void Drawnode(int val,int posx,int posy);

void DrawTree(tree* a,int x,int y,int l,int depth);
 
tree* newnode(int x, int Nodes);
 
void insert(tree** t,int x, int Nodes);
