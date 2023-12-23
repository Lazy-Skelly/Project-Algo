#include "Tree.h"
#define MAX 4


void Drawnode(int val,int posx,int posy){
        DrawCircle(posx,posy,18,BLUE);
        DrawText(TextFormat("%d",val),posx-2,posy-6,15,WHITE);
}

void DrawTree(tree* a,int x,int y,int l,int depth){
        if(a!=NULL){
           
        Drawnode(a->val,x,y);
        
         int k = pow(4,depth)-1;
        
        
         if (a->child[0]!= NULL) {
       
         DrawTree( a->child[0] ,x-3*(l/k)/2,y+300,l,depth+1);
         DrawLine( x-9 , y-9 , x-3*(l/k)/2-9 , y+300-9 , BLUE );
         }
        
         if (a->child[1] != NULL) {
        
         DrawTree(a->child[1],x-(l/k)/2,y+300,l,depth+1);
         DrawLine(x+9,y-9,x-(l/k)/2+9,y+300-9,BLUE);
         }
        
         
         if (a->child[2] != NULL) {
        
        DrawTree(a->child[2],x+(l/k)/2,y+300,l,depth+1);
        DrawLine(x+9,y-9,x+(l/k)/2+9,y+300-9,BLUE);
         }
         
         if (a->child[3] != NULL) {
        
        DrawTree(a->child[3],x+3*(l/k)/2,y+300,l,depth+1);
        DrawLine(x+9,y-9,x+3*(l/k)/2+9,y+300-9,BLUE);
         }
        
         
         
        } 
 }
/*
 void DrawTree(tree* a,int x,int y,int l,int depth){
        if(a!=NULL){
           
        Drawnode(a->val,x,y);
        
        DrawTree(a->left,x-(l/pow(2,depth)),y+150,l/2,depth);
        
        DrawTree(a->right,x+(l/pow(2,depth)),y+150,l/2,depth);
        
        } 
 }
*/
tree* newnode(int x, int Nodes){
    tree* t;
    t=MAKE(tree,1);//malloc(sizeof(tree));
    t->val=x;
    t->Nodes = Nodes;

    t->Child = MAKE(tree*,Nodes);
    
    for(int i = 0; i<t->Nodes;i++){
    	t->Child[i] = NULL;
	}
    
    return t;
}


tree* newnode2(int x){
    tree* t;
    t=malloc(sizeof(tree));
    t->val=x;
    t->child=malloc(sizeof(tree)*MAX);
    
    for(int i=0;i<MAX;i++){
    t->child[i]=NULL;
    }
    
    return t;
}


void insert(tree** t,int x, int Nodes){
    if(*t==NULL){
        *t=newnode(x,Nodes);
    }else{
      
		for(int i = 0; i<(*t)->Nodes;i++){
    		if((*t)->Child[i] == NULL){
   	 			(*t)->Child[i] = newnode(x, (*t)->Nodes);
   	 			break;
			}else if((*t)->Child[i]->val >= x){
				insert(&((*t)->Child[i]), x, (*t)->Nodes);
				break;
			}else if(i == (*t)->Nodes -1){
				insert(&((*t)->Child[i]), x,  (*t)->Nodes);
			}
		}
	}
      
         
} 







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
