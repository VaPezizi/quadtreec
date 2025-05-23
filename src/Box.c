#include "Box.h"

//If first box contains second box
int box_contains(Box * fbox, Box * sbox){
	return fbox->pos.x <= sbox->pos.x && get_right(fbox) >= get_right(sbox)
		&& fbox->pos.y <= sbox->pos.y && get_bottom(fbox) >= get_bottom(sbox); 
}
//If second box intersects first box
int box_intersects(Box * fbox, Box * sbox){
	
	return !(fbox->pos.x >= get_right(sbox) ||
		get_right(sbox) < sbox->pos.x || 
		fbox->pos.y > get_bottom(sbox) ||
		get_bottom(fbox) < sbox->pos.y
		);
}
float get_bottom(Box * box){
	return box->pos.y + box->size.y;
}	
float get_right(Box * box){
	return box->pos.x + box->size.y;
}

