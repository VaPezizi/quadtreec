#include <raylib.h>
#include <memory.h>
#include "Box.h"
#include "Quadtree.h"

const int ballSize = 5;
const int screenWidth = 800;
const int screenHeight = 600;
const int maxCount = 4;


int main(int argc, char**argv){
	InitWindow(screenWidth, screenHeight, "Quadtree test");
	
	//qtree * quadtree = createTree(screenWidth, screenHeight, 4);
	Box box = (Box){(Vector2){200.0f, 200.0f}, (Vector2){50, 51}};
	Box sbox = (Box){(Vector2){220.0f, 220.0f}, (Vector2){20, 20}};
	
	int dir = 0; //Is box turning big or small

	qtree * tree = create_tree(screenWidth, screenHeight, 4);
	add_element(tree, (Vector2){100.0f, 100.0f});	

	SetTargetFPS(60);

	while(!WindowShouldClose()){


		if(dir){
			box.size.y += 0.5f;
			if(box.size.y >= 50.0f)
				dir = 0;
		}else{
			box.size.y -= 0.5f;
			if(box.size.y <= 10.0f)
				dir = 1;
		}	

		BeginDrawing();
		
		ClearBackground(WHITE);
		DrawText("Hello world!", screenWidth / 2, screenHeight / 2, 16, BLACK);
		//drawTreeBounds(quadtree);
		DrawRectangleLines(box.pos.x, box.pos.y, box.size.x, box.size.y, RED);
		DrawRectangleLines(sbox.pos.x, sbox.pos.y, sbox.size.x, sbox.size.y, GREEN);
		
		if(box_contains(&box, &sbox))
			DrawRectangle(20, 20, 20, 20, GREEN);
		if(box_intersects(&box, &sbox))
			DrawRectangle(50, 20, 20, 20, ORANGE);

		draw_tree_bounds(tree);
		EndDrawing();
	}

	destroy_tree(tree);

	CloseWindow();
}
