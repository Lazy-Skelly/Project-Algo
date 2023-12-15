#include <raylib.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct tree tree;
struct tree {
  int val;
  tree* left;
  tree* right;  
    
};
   const int screenWidth = 1080;
    const int screenHeight = 700;

void Drawnode(int val,int posx,int posy){
        DrawCircle(posx,posy,18,BLUE);
        DrawText(TextFormat("%d",val),posx-2,posy-6,15,WHITE);
}


/*
 void DrawTree(tree* a,int x,int y,int l,int depth){
        if(a!=NULL){
           
        Drawnode(a->val,x,y);
        
        DrawTree(a->left,x-(l/pow(2,depth)),y+150,l/2,depth+1);
        
        DrawTree(a->right,x+(l/pow(2,depth)),y+150,l/2,depth+1);
        
        }   
}*/
//testing....
 void DrawTree(tree* a,int x,int y,int l,int depth){
        if(a!=NULL){
           
        Drawnode(a->val,x,y);
        
        DrawTree(a->left,x-(l/pow(2,depth)),y+150,l/2,depth);
        
        DrawTree(a->right,x+(l/pow(2,depth)),y+150,l/2,depth);
        
        } 
 }







tree* newnode(int x){
    tree* t;
    t=malloc(sizeof(tree));
    t->val=x;
    t->left=NULL;
    t->right=NULL;
    return t;
}


void insert(tree** t,int x){
    if(*t==NULL){
        *t=newnode(x);
    }
      else if((*t)->val>=x) insert(&(*t)->left,x);
      else     insert(&(*t)->right,x); 
}   
    







int main() {
 
tree* a=malloc(sizeof(tree));
int x;

a->val=5;
a->left=NULL;
a->right=NULL;

for(int i=0;i<6;i++){
  scanf("%d",&x);
  insert(&a,x);
   
}



    
    InitWindow(screenWidth, screenHeight, "Arbre n-aire ");



    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        
        
        
        BeginDrawing();
        ClearBackground(BRITISH);

    
    DrawTree(a,screenWidth/2,25,screenWidth/2,1);
    
    
    
        EndDrawing();
        
        
    }

   
   

   
    CloseWindow();

    return 0;
}