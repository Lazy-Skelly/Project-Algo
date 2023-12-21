#include "Ligma.h"


void Drawnode(int val,int posx,int posy){
        DrawCircle(posx,posy,18,BLUE);
        DrawText(TextFormat("%d",val),posx-2,posy-6,15,WHITE);
}

 void DrawTree(tree* a,int x,int y,int l,int depth){
        if(a!=NULL){
//         	printf("\n-----------\nthe node is val is : %d", a->val);
        	Drawnode(a->val,x,y);
/*        	printf("\nits children are:");
        	for(int i =0; i < a->Nodes ;i++){
        		if(a->Child[i] == NULL){
        			break;
				}
				printf("%d,",a->Child[i]->val);
			}*/
       		for(int i =0; i < a->Nodes ;i++){
        		DrawTree(a->Child[i], x+(i -1)* (l/pow(2,depth)) ,y+50,l/2,depth);
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
/*
tree* newnode(int x, int Nodes){
    tree* t;
    t=MAKE(tree,1);//malloc(sizeof(tree));
    t->Nodes = Nodes;
    t->val=x;
    t->left=NULL;
    t->right=NULL;
    for(int i = 0; i<t->Nodes;i++){
    	
	}
    
    return t;
}
*/
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
