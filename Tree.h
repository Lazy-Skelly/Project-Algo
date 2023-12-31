#pragma once


#include <raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <time.h>
#include <assert.h>


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

bool research(tree* t,int x,tree** out);

int PopMaximum(tree** t);

int PopMinimum(tree** t);

tree* GetMaximum(tree* t);

tree* GetMinimum(tree* t);

int lastNode(tree* t);

void Delete(tree** t,int x);

void DeleteRec(tree** t,int x);

int GetDepth(tree* a);

void FreeTree(tree** a);

int GuiFloatBox(Rectangle bounds, const char* text, int* value, int minValue, int maxValue, bool editMode);


