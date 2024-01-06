#include "Tree.h"
#define RAYGUI_IMPLEMENTATION

#include "raygui.h"



void Drawnode(int val,int posx,int posy,Color c){
        DrawCircle(posx,posy,20,c);
        DrawText(TextFormat("%d",val),posx-6,posy-6,15,WHITE);
}

void DrawTree(tree* a,int x,int y,int l,int depth){ 

    
    if(a!=NULL){
           
        a->x=x;
        a->y=y;
        
         int k = pow(a->Nodes,depth)-1;
      	if(k == 0){
      		k = 1;
		  }
         int h;
         
         if(a->Nodes>0)h=a->Nodes-1;
         else h=0;
        
        for(int i=0;i<a->Nodes;i++){
               
         if (a->child[i]!=NULL) {
             
         DrawLine( x , y-9 , x+(2*i-h)*(l/k)/2 , y+300-9 , BLUE );
         DrawTree( a->child[i] , x+(2*i-h)*(l/k)/2 , y+300 , l , depth+1);
            
          }    
        }
        Drawnode(a->val,x,y,a->color);
    } 
}




tree* newnode(int x, int Nodes){
    tree* t;
    t=MAKE(tree,1);
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
				break;
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

bool research(tree* t,int x, tree** out){
	if(t){
    bool found = false;
    if(t->val==x){
    	insert(out,(int)t,1);
    	for(int i=0;i<t->Nodes;i++){
        	found = research(t->child[i], x, out);
        }
        return true;
    }else if(t->val!=x){
        for(int i=0;i<t->Nodes;i++){
        	found = found || research(t->child[i], x, out);
        }
        return found;
    }
	}
	return false;
}

int PopMaximum(tree** t){
	if(*t){
		int last = lastNode(*t);
		int val;
		if(last == -1){
			val = (*t)->val;
			FreeTree(t);
			return val;
		}else{
			if((*t)->child[last]->val < (*t)->val){
				val = (*t)->val;
				(*t)->val = PopMaximum(&((*t)->child[last]));
				return val;	
			}
			return PopMaximum(&((*t)->child[last]));
		}	
	}
}

int PopMinimum(tree** t){
	if(*t){
		int last = lastNode(*t);
		int val;
		if(last == -1){
			val = (*t)->val;
			FreeTree(t);
			return val;
		}else{
			if((*t)->child[0]->val > (*t)->val){
				val = (*t)->val;
				(*t)->val = PopMinimum(&((*t)->child[0]));
				return val;	
			}
			return PopMinimum(&((*t)->child[0]));
		}
	}
}

tree* GetMaximum(tree* t){
	if(t){
		int last = lastNode(t);
		int val;
		val = t->val;
		if(last != -1){
			if(t->child[last]->val > t->val){
				return GetMaximum(t->child[last]);
			}
		}	
		return t;	
	}
	return NULL;
}

tree* GetMinimum(tree* t){
	if(t){
		int last = lastNode(t);
		int val;
		val = t->val;
		if(last != -1){
			if(t->child[0]->val < t->val){
				return GetMinimum(t->child[0]);
			}
		}
		return t;
	}
	return NULL;
}

 int lastNode(tree* t){
 	if(t){
   int i=0;
   if(t->child[i]==NULL){
   return -1;
   }
    
  while(t->child[i+1]!=NULL && i+1<t->Nodes){
      i++;
  }
  return i;
	}
  }
 
 
void Delete(tree** t, int x){
	tree* p =*t;
	if(p){
		if(p->val == x){
			int last = lastNode(*t);
			if(last == -1){
				FreeTree(t);
			}else{
				p->val = PopMaximum(&(p->child[last]));
			}
		}else{
			DeleteRec(t,x);	
		}
	}	
}  

void DeleteRec(tree** t,int x){
	tree* p =*t;
	if(p){
		int last = lastNode(*t);
		int found=-1;
		if(last != -1){
			for(int i=0; i<=last;i++){
				if(p->child[i]->val == x){
					found = i;
					break;
				}
			}
			if(found != -1){
				if(found < last){
					if(lastNode(p->child[found]) == -1){
						int end=found;
						for(int i =found+1;i<=last;i++){
							if(lastNode(p->child[i]) == -1){
								end =i;
							}else{
								break;
							}
						}
						for(int i = found; i < end;i++){
							p->child[i]->val = p->child[i+1]->val;
						}
						if(end == last){
							FreeTree(&(p->child[end]));
						}else{
							p->child[end]->val = PopMinimum(&(p->child[end+1]));							
						}				

					}else{
						p->child[found]->val = PopMaximum(&(p->child[found]->child[lastNode(p->child[found])]));
					}					
				}else{
					if(lastNode(p->child[found]) == -1){
						FreeTree(&(p->child[found]));						
					}else{
						p->child[found]->val = PopMaximum(&(p->child[found]->child[lastNode(p->child[found])]));
					}					
				}
			}else{
				for(int i=0; i<=last;i++){
					DeleteRec(&(p->child[i]),x);
				}	
			}
		}		
	}
}  

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

void KillChild(tree** a){
	if(*a != NULL){
		bool done = true;
		for(int i=0;i<(*a)->Nodes;i++){
			done = done && (*a)->child[i] != NULL;
		}
		if(!done){
			for(int i=0;i<(*a)->Nodes;i++){
				FreeTree(&((*a)->child[i]));
				free((*a)->child[i]);
			}
		}
		free((*a)->child);
		(*a)->child = NULL;
	}
}

void FreeTree(tree** a){
	if(*a){
		KillChild(a);
		free(*a);
		*a = NULL;
	}	
}

int TextToFloat(const char* text)
{
	int value = 0.0f;
	float floatingPoint = 0.0f;
	int sign = 1;

    // deal with the sign
	if ((text[0] == '+') || (text[0] == '-'))
	{
		if (text[0] == '-') sign = -1;
		text++;
	}

    // convert text to float
	for (int i = 0; (((text[i] >= '0') && (text[i] <= '9')) || text[i] == '.'); i++)
	{
		/*if (text[i] == '.')
		{
			if (floatingPoint > 0.0f) break;

			floatingPoint = 10.0f;
			continue;
		}
		if (floatingPoint > 0.0f) // after encountering decimal separator
		{
			value += (float)(text[i] - '0') / floatingPoint;
			floatingPoint *= 10.0f;
		}
		else */                  // before decimal separator
			value = value * 10.0f + (float)(text[i] - '0');
	}

	return value * sign;
}

int GuiFloatBox(Rectangle bounds, const char* text, int* value, int minValue, int maxValue, bool editMode)
{
#if !defined(RAYGUI_VALUEBOX_MAX_CHARS)
#define RAYGUI_VALUEBOX_MAX_CHARS  32
#endif

    int result = 0;
    GuiState state = guiState;

    char textValue[RAYGUI_VALUEBOX_MAX_CHARS + 1] = "\0";

    Rectangle textBounds = { 0 };
    if (text != NULL)
    {
        textBounds.width = (float)GetTextWidth(text) + 2;
        textBounds.height = (float)GuiGetStyle(DEFAULT, TEXT_SIZE);
        textBounds.x = bounds.x + bounds.width + GuiGetStyle(VALUEBOX, TEXT_PADDING);
        textBounds.y = bounds.y + bounds.height / 2 - GuiGetStyle(DEFAULT, TEXT_SIZE) / 2;
        if (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == TEXT_ALIGN_LEFT) textBounds.x = bounds.x - textBounds.width - GuiGetStyle(VALUEBOX, TEXT_PADDING);
    }

    // Update control
    //--------------------------------------------------------------------
    if ((state != STATE_DISABLED) && !guiLocked && !guiSliderDragging)
    {
        Vector2 mousePoint = GetMousePosition();

        if (*value >= 0) sprintf(textValue, "%d", *value);
        else sprintf(textValue, "%d", *value);

        bool valueHasChanged = false;

        int keyCount = (int)strlen(textValue); //- guiFloatingPointIndex;

        if (editMode)
        {
            state = STATE_PRESSED;

            // Only allow keys in range [48..57]
            if (keyCount < RAYGUI_VALUEBOX_MAX_CHARS)
            {
                if (GetTextWidth(textValue) < bounds.width)
                {
                    int key = GetCharPressed();
                    if ((key >= 48) && (key <= 57))
                    {
                        textValue[keyCount] = (char)key;
                        textValue[++keyCount] = '\0';
                        valueHasChanged = true;
                    }
                }
            }

            // Delete text
            if (keyCount > 0)
            {
                if (IsKeyPressed(KEY_BACKSPACE))
                {

                    keyCount--;
                    textValue[keyCount] = '\0';
                    valueHasChanged = true;
                }
            }

            // Change sign
            if (IsKeyPressed(KEY_MINUS))
            {
                if (textValue[0] == '+') textValue[0] = '-';
                else if (textValue[0] == '-') textValue[0] = '+';
                valueHasChanged = true;
            }

            // Add decimal separator
      /*      if ((IsKeyPressed(KEY_COMMA) || IsKeyPressed(KEY_PERIOD)) && guiFloatingPointIndex == 4)
            {
                guiFloatingPointIndex--;
                valueHasChanged = true;
            }*/

            if (valueHasChanged)
            {
                *value = TextToFloat(textValue);
            }

            if (IsKeyPressed(KEY_ENTER) || (!CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
            {
                
                result = 1;
            }
        }
        else
        {
            if (*value > maxValue) *value = maxValue;
            else if (*value < minValue) *value = minValue;

            if (CheckCollisionPointRec(mousePoint, bounds))
            {
                state = STATE_FOCUSED;
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) result = 1;
            }
        }
    }
    //--------------------------------------------------------------------

    // Draw control
    //--------------------------------------------------------------------
    Color baseColor = BLANK;
    sprintf(textValue, "%d", *value);

    if (state == STATE_PRESSED)
    {
        baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_PRESSED));
        textValue[(int)strlen(textValue)] = '\0';
    }
    else if (state == STATE_DISABLED) baseColor = GetColor(GuiGetStyle(VALUEBOX, BASE_COLOR_DISABLED));

    // WARNING: BLANK color does not work properly with Fade()
    GuiDrawRectangle(bounds, GuiGetStyle(VALUEBOX, BORDER_WIDTH), Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER + (state * 3))), guiAlpha), baseColor);
    GuiDrawText(textValue, GetTextBounds(VALUEBOX, bounds), TEXT_ALIGN_CENTER, Fade(GetColor(GuiGetStyle(VALUEBOX, TEXT + (state * 3))), guiAlpha));

    // Draw cursor
    if (editMode)
    {
        // NOTE: ValueBox internal text is always centered
        Rectangle cursor = { bounds.x + GetTextWidth(textValue) / 2 + bounds.width / 2 + 1, bounds.y + 2 * GuiGetStyle(VALUEBOX, BORDER_WIDTH), 4, bounds.height - 4 * GuiGetStyle(VALUEBOX, BORDER_WIDTH) };
        GuiDrawRectangle(cursor, 0, BLANK, Fade(GetColor(GuiGetStyle(VALUEBOX, BORDER_COLOR_PRESSED)), guiAlpha));
    }

    // Draw text label if provided
    GuiDrawText(text, textBounds, (GuiGetStyle(VALUEBOX, TEXT_ALIGNMENT) == TEXT_ALIGN_RIGHT) ? TEXT_ALIGN_LEFT : TEXT_ALIGN_RIGHT, Fade(GetColor(GuiGetStyle(LABEL, TEXT + (state * 3))), guiAlpha));
    //--------------------------------------------------------------------

    return result;
}

