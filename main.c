#include "Tree.h"
#include "raygui.h"

const int screenWidth = 1080;
const int screenHeight = 700;

int main(){
//variables init used in program	
	srand(time(0));
	
	tree* a = NULL;
	tree* FoundTree = NULL;
	tree* Inserted = NULL;
	tree* DeleteTree = NULL;	
 	
	bool ToChange,ToDelete, ToSearch, ToRandomize, HaveSearch, Settings, HaveInserted, HaveDeleted; 
	ToChange = ToDelete = ToSearch = ToRandomize = HaveSearch = Settings = HaveInserted = HaveDeleted = false;
	
	int Changed, Deleted, Searched, LastDeleted, Randomized;
	Changed = Deleted = Searched = Randomized = 0;
	
	double SearchTime, InsertedTime, DeletedTime; 
	
	int l, Nodes;
	Nodes = 4;
	
//generating random tree with quad children	
	for(int i =0;i<6;i++){
		insert(&a,RANDOM(i*20),Nodes);
	}

//camera init	
	Camera2D Camera;
	Camera.offset.x=540;
    Camera.offset.y=350;
    
    Camera.target.x=540;
    Camera.target.y=350;
    
    Camera.rotation=0;
    Camera.zoom=1; 
    
	Camera2D UICamera = Camera;
 
	
    InitWindow(screenWidth, screenHeight, "Arbre n-aire ");
    SetTargetFPS(60);
	


//sound init
	InitAudioDevice();        

    Sound ClickSound = LoadSound("click-button.mp3");
    Sound NotFoundSound = LoadSound("playerno.mp3");	
	Sound CorrectSound = LoadSound("correct-choice.mp3");
	Sound DestroySound = LoadSound("destroy.mp3");
	
    while (!WindowShouldClose()) {


	    
        BeginDrawing();
        BeginMode2D(Camera);
        
        ClearBackground(BRITISH);
        
		
        // l=5:  2^(5-2)= 8*screenWidth space needed
        // l=4:  2^(4-2)= 4*screenWidth space needed
        // l=3:  2^(3-2)= 2*screenWidth space needed
        // etc...
    
	//drawing the tree on its own layer       
        l=GetDepth(a)-1;
        DrawTree(a,screenWidth/2,50,pow(2,l-2)*screenWidth,1);

    //strating ui layer
		BeginMode2D(UICamera);
	
	if(Settings){
		if(GuiWindowBox((Rectangle){0, 0, screenWidth/5, screenHeight }, "#142# SETTINGS")){
			Settings = false;
			PlaySound(ClickSound);
		}
		
		//clearinf tree
		DrawText("Clear Tree",70,40,20,BLACK);                    
		if(GuiButton((Rectangle){10,30,40,40},"#143#")){
			FreeTree(&a);
			PlaySound(ClickSound);
		}
		
		//adding element ui with sounds and colors
		DrawText("Add Element",10,80,20,BLACK);
		if(GuiFloatBox((Rectangle){ 10, 100, 200, 30 }, NULL, &Changed, -1000000.0, 1000000.0, ToChange)){
			ToChange = !ToChange;
			if(ToChange){
				Changed =0;
			}
			if(IsKeyDown(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !ToChange)){
				if(Inserted){
					Inserted->color = BLUE;
				}
				HaveInserted = true;
				InsertedTime = GetTime();				
				Inserted = insert(&a,Changed,Nodes);
				Inserted->color = GOLD;
				PlaySound(ClickSound);
			}
		}
		if(HaveInserted){
			if(GetTime()-InsertedTime >2){
				HaveInserted = false;
				Inserted->color = BLUE;
				Inserted = NULL;
			}
		}
			
		//deleting element ui with sounds and colors
		DrawText("Delete Element",10,140,20,BLACK);
		if(GuiFloatBox((Rectangle){ 10, 160, 200, 30 }, NULL, &Deleted, -1000000.0, 1000000.0, ToDelete)){
			ToDelete = !ToDelete;
			if(ToDelete){
				Deleted =0;
			}
			if(IsKeyDown(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !ToDelete)){
				if(DeleteTree){
					((tree*)DeleteTree->val)->color = BLUE;
					Delete(&a,LastDeleted);
					FreeTree(&DeleteTree);	
					PlaySound(DestroySound);
				}
				if(research(a,Deleted,&DeleteTree)){
					((tree*)DeleteTree->val)->color = RED;
					HaveDeleted = true;
					LastDeleted = Deleted;
					DeletedTime = GetTime();
				}								
			}
		}
		if(HaveDeleted){
			if(GetTime()-DeletedTime > 2){
				HaveDeleted = false;
				((tree*)DeleteTree->val)->color = BLUE;
				Delete(&a,LastDeleted);				
				FreeTree(&DeleteTree);
				PlaySound(DestroySound);
			}	
		}
		
		//TO DO OR DISCUSS
		//ADD MULTI-DELETE
/*		DrawText("Delete multi-Element",10,140,20,BLACK);
		if(GuiFloatBox((Rectangle){ 10, 160, 200, 30 }, NULL, &Deleted, -1000000.0, 1000000.0, ToDelete)){
			ToDelete = !ToDelete;
			if(ToDelete){
				Deleted =0;
			}
			if(IsKeyDown(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !ToDelete)){				
				Delete(&a,Deleted);
			}
		}*/
		
		//searching element ui with sounds and colors
		DrawText("Search Element",10,200,20,BLACK);
		if(GuiFloatBox((Rectangle){ 10, 220, 200, 30 }, NULL, &Searched, -1000000.0, 1000000.0, ToSearch)){
			ToSearch = !ToSearch;
			if(ToSearch){
				Searched = 0;	
			}
			if(IsKeyDown(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !ToSearch)){
				HaveSearch = true;
				SearchTime = GetTime();
				tree* temp = FoundTree;
				while(temp){
					((tree*)temp->val)->color = BLUE;
					temp = temp->child[0];  
				}
				FreeTree(&FoundTree);				
				if(research(a,Searched,&FoundTree)){
					PlaySound(CorrectSound);
					temp = FoundTree;
					while(temp){
						((tree*)temp->val)->color = GREEN;
						temp = temp->child[0];  
					}
				}else{
					PlaySound(NotFoundSound);
				}
				
			}
		}
		if(HaveSearch){
			tree* temp = FoundTree;
			if(GetTime() - SearchTime< 2){
				if(FoundTree){
					int times =0;
					while(temp){
						times++;
						temp = temp->child[0];  
					}			
					DrawText(TextFormat("Found: %d time",times),10,250,20,RED);
				}else{
					DrawText(TextFormat("Value Not Found!"),10,250,20,RED);
				}
			}else{
				HaveSearch = false;
				while(temp){
					((tree*)temp->val)->color = BLUE;
					temp = temp->child[0];  
				}
				FreeTree(&FoundTree);
			}
		}
		
		//number of random element made into a new tree
		DrawText("Randomize Tree",10,280,20,BLACK);
		if(GuiFloatBox((Rectangle){ 10, 300, 200, 30 }, NULL, &Randomized, -1000000.0, 1000000.0, ToRandomize)){
			ToRandomize = !ToRandomize;
			if(ToRandomize){
				Randomized = 0;	
			}
			if(IsKeyDown(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !ToRandomize)){
				FreeTree(&a);
				for(int i = 0; i < Randomized;i++){
					insert(&a,RANDOM(i*20),Nodes);
				}				
			}
		}
		
		//number of child regulator
		DrawText("Number of Nodes",20,530,20,BLACK);
		DrawText(TextFormat("%d",Nodes),97,550,30,BLACK);
		if(GuiButton((Rectangle){20,550,30,30},"#130#") && Nodes > 2){
			Nodes--;
			PlaySound(ClickSound);
		}		
		if(GuiButton((Rectangle){160,550,30,30},"#131#") && Nodes < 4){
			Nodes++;
			PlaySound(ClickSound);
		}		
		
		//camera commands
		if(GuiButton((Rectangle){90,590,30,30},"#117#") || IsKeyDown(KEY_UP)){
			Camera.target.y-=15;
			PlaySound(ClickSound);
		}
		if(GuiButton((Rectangle){60,620,30,30},"#114#") || IsKeyDown(KEY_LEFT)){
			Camera.target.x-=15;
			PlaySound(ClickSound);
		}
		if(GuiButton((Rectangle){120,620,30,30},"#115#") || IsKeyDown(KEY_RIGHT)){
			Camera.target.x+=15;
			PlaySound(ClickSound);
		}
		if(GuiButton((Rectangle){90,650,30,30},"#116#") || IsKeyDown(KEY_DOWN)){
			Camera.target.y+=15;
			PlaySound(ClickSound);
		}
		if(GuiButton((Rectangle){90,620,30,30},"#57#")){
			Camera = UICamera;
			PlaySound(ClickSound);
		}
		//zoom
		if(GuiButton((Rectangle){160,620,30,30},"#42#") || IsKeyDown(KEY_LEFT_CONTROL)){
			Camera.zoom-=0.02; 
			PlaySound(ClickSound);	
		}
		if(GuiButton((Rectangle){20,620,30,30},"#43#") || IsKeyDown(KEY_LEFT_SHIFT)&& Camera.zoom>0.01){
			Camera.zoom+=0.02;
			PlaySound(ClickSound);
		}
		
    }else{
    	//camera commands if settings are collapsed
    	if(GuiButton((Rectangle){10,10,30,30},"#142#")){
			Settings = true;
			PlaySound(ClickSound);
		}		
		if(IsKeyDown(KEY_UP)){
			Camera.target.y-=15;
		}
		if(IsKeyDown(KEY_LEFT)){
			Camera.target.x-=15;
		}
		if(IsKeyDown(KEY_RIGHT)){
			Camera.target.x+=15;
		}
		if(IsKeyDown(KEY_DOWN)){
			Camera.target.y+=15;
		}		
		if(IsKeyDown(KEY_LEFT_CONTROL)){
			Camera.zoom-=0.02; 	
		}
		if(IsKeyDown(KEY_LEFT_SHIFT)&& Camera.zoom>0.01){
			Camera.zoom+=0.02;
		}	
	}
       	EndMode2D();
		EndDrawing();		
	}
	
    CloseWindow();
    
	
    return 0;
}

   
   

   

