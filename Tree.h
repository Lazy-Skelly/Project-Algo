#pragma once

#include <raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>

#define MAKE(x,y) (x*)malloc(y * sizeof(x)) 
#define BRITISH CLITERAL(Color){0,66,37,255}
#define MAX 4
#define RANDOM(x) rand() % (x+1)

typedef struct tree tree;
struct tree {
	int val;
	int Nodes; 
  	tree** child;
        int x; 
        int y;
  	Color color;
};



void Drawnode(int val,int posx,int posy,Color c);

void DrawTree(tree* a,int x,int y,int l,int depth);
 
tree* newnode(int x, int Nodes);
 
tree* insert(tree** t,int x, int Nodes);

int GetDepth(tree* a);
