#include "Tree.h"



void Drawnode(int val,int posx,int posy,Color c){
        DrawCircle(posx,posy,20,c);
        DrawText(TextFormat("%d",val),posx-6,posy-6,15,WHITE);
}

void DrawTree(tree* a,int x,int y,int l,int depth){ 

        if(a!=NULL){
           
        Drawnode(a->val,x,y,a->color);
        a->x=x;
        a->y=y;
        
         int k = pow(4,depth)-1;
        
        
         if (a->child[0]!= NULL && a->Nodes >= 1) {
       
         DrawTree( a->child[0] ,x-3*(l/k)/2,y+300,l,depth+1);
         DrawLine( x-9 , y-9 , x-3*(l/k)/2 , y+300-9 , BLUE );
         }
        
         if (a->child[1] != NULL && a->Nodes >= 2) {
        
         DrawTree(a->child[1],x-(l/k)/2,y+300,l,depth+1);
         DrawLine(x-9,y-9,x-(l/k)/2,y+300-9,BLUE);
         }
        
         
         if (a->child[2] != NULL && a->Nodes >= 3) {
        
        DrawTree(a->child[2],x+(l/k)/2,y+300,l,depth+1);
        DrawLine(x+9,y-9,x+(l/k)/2,y+300-9,BLUE);
         }
         
         if (a->child[3] != NULL && a->Nodes >= 4) {
        
        DrawTree(a->child[3],x+3*(l/k)/2,y+300,l,depth+1);
        DrawLine(x+9,y-9,x+3*(l/k)/2,y+300-9,BLUE);
         }
        
         
         
        } 
 }


tree* newnode(int x, int Nodes){
    tree* t;
    t=MAKE(tree,1);//malloc(sizeof(tree));
    t->val=x;
    t->Nodes = Nodes;

    t->child = MAKE(tree*,Nodes);
    t->color = BLUE;
    for(int i = 0; i<t->Nodes;i++){
    	t->child[i] = NULL;
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


tree* insert(tree** t,int x, int Nodes){
    if(*t==NULL){
        *t=newnode(x,Nodes);
        return *t;
    }else{
      
		for(int i = 0; i<(*t)->Nodes;i++){
    		if((*t)->child[i] == NULL){
   	 			(*t)->child[i] = newnode(x, (*t)->Nodes);
   	 			return (*t)->child[i];
   	 			break;
			}else if((*t)->child[i]->val >= x){
				insert(&((*t)->child[i]), x, (*t)->Nodes);
				break;
			}else if(i == (*t)->Nodes -1){
				insert(&((*t)->child[i]), x,  (*t)->Nodes);
			}
		}
	}       
} 


void insert2pos(tree** t,int val,tree** q){
    int p;
    scanf("%d",&p);
    if((*t)->child[p]==NULL){
        (*t)->child[p]=newnode(val,4);
        *q=(*t)->child[p];
    }
    else insert2pos(&((*t)->child[p]),val,&*q);
}

bool research(tree* t,int x){
	if(t){
    if(t->val==x){
        return true;
    }else if(t->val!=x){
        for(int i=0;i<t->Nodes;i++){
        	return research(t->child[i], x);
        }
    }
	}
	return false;
}


void delete(tree** t,int x){
    tree* p=*t;
    tree* q;
   if(p->val==x){
       if(p->Nodes>0){
       do{
       p->val=p->child[Nodes]->val;
       p=p->child[Nodes];
       }while(p->Nodes!=0);
        p->val=p->child[Nodes]->val;
        p->child[Nodes]=NULL;
        p->Nodes--;
       }else{
       int j=0;
       while(q->child[j]!=p){
           j++
           
       }
       do{
           q->child[j]->val= q->child[j+1]->val;
           j++;
       }while(j<(Nodes-1));
       q->child[Nodes]=NULL;
       q->Nodes--;
        else{
              q=p;
            for(int i=0;i<(*t)->Nodes){
                delete((*t)->child[i],int x);
            }
        }
    }
/*
 void delete(tree** t,int x){
    if (research(*t,x)){
        if((*t)->Nodes==0){
            *t=NULL;
        }else{
            (*t)->val=(*t)->child[Nodes]->val;
            (*t)->child[Nodes]=NULL;
            Nodes--;
        }
    }
    */
int GetDepth(tree* a){
	int Depth =0;
	if(a != NULL){
		for(int i =0; i<a->Nodes;i++){
			int temp = 1 + GetDepth(a->child[i]);
			if(temp>Depth){
				Depth = temp;
			}
		}
	}
	return Depth;	
}



