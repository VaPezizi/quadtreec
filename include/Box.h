#ifndef _BOX
#define _BOX

#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif

//Pos = Left topright of position
typedef struct Box{
	Vector2 pos;	
	Vector2 size;	//pos.y + size.y = bottom
}Box;

float get_bottom(Box * box);
float get_right(Box * box);

int box_contains(Box * fbox, Box * sbox);	//Check if first box contains second box
int box_intersects(Box* fbox, Box * sbox);


#endif
