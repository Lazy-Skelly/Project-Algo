#include "Tree.h"

const int screenWidth = 1080;
const int screenHeight = 700;

int main() {
	
tree* a = newnode(10,3);
int x;

for(int i=0;i<12;i++){
  scanf("%d",&x);
  insert(&a,x, a->Nodes); 
   
}

    InitWindow(screenWidth, screenHeight, "Arbre n-aire ");



    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        
        
        
        BeginDrawing();
        ClearBackground(BLACK);

    
    	DrawTree(a,screenWidth/2,25,screenWidth/3,1);
    
    
     
        EndDrawing();
        
        
    }

     
    CloseWindow();

    return 0;
}
