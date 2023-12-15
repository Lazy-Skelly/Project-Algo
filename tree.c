#include <raylib.h>
#include<stdio.h>
#include<stdlib.h>
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


/*void DrawTree(tree* a,int x,int y){
    if(a!=NULL){
        DrawTree(a->left,x-40,y+50);
         Drawnode(a->val,x,y);
        
         
         DrawTree(a->right,x+20,y+50);
         
    }*/
 void DrawTree(tree* a,int x,int y,int l){
        if(a!=NULL){
           
        Drawnode(a->val,x,y);
        l+=2;
        DrawTree(a->left,screenWidth/l,y+50,l);
        
        DrawTree(a->right,2*x-screenWidth/l,y+50,l);
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

    
    DrawTree(a,screenWidth/2,25,2);
    
    
    
        EndDrawing();
        
        
    }

   
   

   
    CloseWindow();

    return 0;
}