#include "Tree.h"

const int screenWidth = 1080;
const int screenHeight = 700;

int main() {
	
	srand(time(0));
	
	tree* a = NULL;
	tree* p = NULL;

  	bool start=false;
	double t0;

	insert(&a,1,2);
	int l=2;
/*	for(int i =0;i<5;i++){
		insert(&a,RANDOM(1000),2);
	}*/
		insert(&a,51,2);
	Camera2D cd;
	cd.offset.x=540;
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
       
        if(!start){
            DrawText(TextFormat("PRESS SPACE TO INSERT VALUE %d",GetDepth(a)),0,-20,50,GOLD);                    
        }           
           
        if(IsKeyReleased(32)){
          	start=true;    
   			if(p){
   				p->color = BLUE;
   				p = NULL;	
			}
			p = insert(&a,RANDOM(50),2);
			
		  	p->color = RED;  
			 
          	t0=GetTime();
			printf("%d",GetDepth(a));
			l = GetDepth(a);  
			printf("%d",research(a,50));        
        }
      
      	DrawTree(a,screenWidth/2,50,pow(2,l-2)*screenWidth,1);
       
       	if(GetTime()-t0>2 && p){
		   	p->color = BLUE;
		}       
      
        //camera commands
          if(IsMouseButtonDown(0)) cd.zoom+=0.02;
          if(IsMouseButtonDown(1)&& cd.zoom>0.01) cd.zoom-=0.02; 
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

   
   

   

