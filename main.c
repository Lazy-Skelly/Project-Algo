#include "Tree.h"
#include "raygui.h"

const int screenWidth = 1080;
const int screenHeight = 700;

int main() {
	
	srand(time(0));
	
	tree* a = NULL;
	tree* p = NULL;
	float smth = 0;
  	bool start=false;
	double t0;

	insert(&a,1,4);
	int l=GetDepth(a);
	for(int i =0;i<5;i++){
		insert(&a,RANDOM(1000),4);
	}
	insert(&a,51,4);
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
           
        if(IsKeyReleased(32) || true){
          	start=true;    
   			if(p){
   				p->color = BLUE;	
			}
		
//			p = insert(&a,RANDOM(1000),2);
//		 	p->color = RED; 
			 
          	t0=GetTime();
//			l = GetDepth(a);         
        }
      
       	DrawTree(a,screenWidth/2,50,pow(2,l-2)*screenWidth,1);
       
/*     	if(GetTime()-t0>2 && p){
		   	p->color = BLUE;
		   	p = NULL;
		} */      
      
        GuiWindowBox((Rectangle){ 0, 0, screenWidth/5, screenHeight }, "#198# PORTABLE WINDOW");
        GuiFloatBox((Rectangle){ 10, 100, 200, 50 }, NULL, &smth, -1000000.0, 1000000.0, true);
 //       GuiButton((Rectangle){20,50,100,100},"hallo");
		DrawText("hallo",1000,40,10,GRAY);    
        //camera commands
          if(IsKeyDown(KEY_LEFT_CONTROL)) cd.zoom+=0.02;
          if(IsKeyDown(KEY_LEFT_SHIFT)&& cd.zoom>0.01) cd.zoom-=0.02; 
          if(IsKeyDown(262)) cd.target.x+=15;
          if(IsKeyDown(263)) cd.target.x-=15;
          if(IsKeyDown(264)) cd.target.y+=15;
          if(IsKeyDown(265)) cd.target.y-=15;
		  
		  if(IsKeyReleased(32)){
			FreeTree(&(a->child[0]));		  
		  } 
		     
    
       	EndMode2D();
        EndDrawing();    
    }
	  
    CloseWindow();

    return 0;
}

   
   

   

