#include "Tree.h"

const int screenWidth = 1080;
const int screenHeight = 700;

int main() {
 
tree* a;
a=newnode2(1);

a->child[0]=newnode2(2);
a->child[1]=newnode2(3);
a->child[2]=newnode2(4);
a->child[3]=newnode2(5);

a->child[0]->child[0]=newnode2(6);
a->child[0]->child[1]=newnode2(7);
a->child[0]->child[2]=newnode2(8);
a->child[0]->child[3]=newnode2(9);

a->child[1]->child[0]=newnode2(10);
a->child[1]->child[1]=newnode2(11);
a->child[1]->child[2]=newnode2(12);
a->child[1]->child[3]=newnode2(13);

a->child[0]->child[0]->child[0]=newnode2(6);
a->child[0]->child[0]->child[1]=newnode2(6);
a->child[0]->child[0]->child[2]=newnode2(6);
a->child[0]->child[0]->child[3]=newnode2(6);

a->child[0]->child[1]->child[0]=newnode2(6);
a->child[0]->child[1]->child[1]=newnode2(6);
a->child[0]->child[1]->child[2]=newnode2(6);
a->child[0]->child[1]->child[3]=newnode2(6);

a->child[0]->child[2]->child[0]=newnode2(6);
a->child[0]->child[2]->child[1]=newnode2(6);
a->child[0]->child[2]->child[2]=newnode2(6);
a->child[0]->child[2]->child[3]=newnode2(6);

a->child[0]->child[3]->child[0]=newnode2(6);
a->child[0]->child[3]->child[1]=newnode2(6);
a->child[0]->child[3]->child[2]=newnode2(6);
a->child[0]->child[3]->child[3]=newnode2(6);




//scanf l 
int l=4;
//l is the number of lines 

 Camera2D cd;
    (cd.offset).x=540;
    cd.offset.y=350;
    
    cd.target.x=540;
    cd.target.y=350;
    cd.rotation=0;
    cd.zoom=1;
    
    InitWindow(screenWidth, screenHeight, "Arbre n-aire ");



    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        
        
        
        BeginDrawing();
        BeginMode2D(cd);
        
        ClearBackground(BRITISH);


        // l=5:  2^(5-2)= 8*screenWidth space needed
        // l=4:  2^(4-2)= 4*screenWidth space needed
        // l=3:  2^(3-2)= 2*screenWidth space needed
        // etc...
        
        
        
        DrawTree(a,screenWidth/2,50,pow(2,l-2)*screenWidth,1);
   
        //camera commands
         if(IsMouseButtonDown(0)) cd.zoom+=0.02;
          if(IsMouseButtonDown(1)) cd.zoom-=0.02; 
          if(cd.zoom<0){
          	cd.zoom =0;
		  }
          if(IsKeyDown(262)) cd.target.x+=15;
          if(IsKeyDown(263)) cd.target.x-=15;
          if(IsKeyDown(264)) cd.target.y+=15;
          if(IsKeyDown(265)) cd.target.y-=15;    
    
        EndMode2D();
        EndDrawing();
        
        
    }

   
   

   
    CloseWindow();

    return 0;
}
