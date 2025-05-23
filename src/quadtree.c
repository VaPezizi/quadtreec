#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <memory.h>
#include "Box.h"

const int ballSize = 5;
const int screenWidth = 800;
const int screenHeight = 600;
const int maxCount = 4;

typedef struct Box{
	Vector2 pos;	
	Vector2 size;
}Box;

typedef struct qnode{
	int count;	//Number of elements under node
	Vector2 pos;	//Position of segment
	Vector2 size;	//size of segment
	Box ** points;	//List of elements
	struct qnode *first;	//Top left Qnode
	struct qnode *second;	//Top right Qnode
	struct qnode *third;	//Bottom left Qnode
	struct qnode *fourth;	//Bottom right Qnode
}qnode;

typedef struct qtree{
	int treshold;	//Amount of values node can contain, before splitting
	qnode* rootnode;
}qtree;

//Makes a  new qnode and returns pointer
qnode * qnode_new(Vector2 pos, Vector2 size){
	qnode * node = (qnode*)malloc(sizeof(qnode));
	memset(node, 0, sizeof(qnode));
	node->pos = pos;
	node->size = size;

	return node;
}
//Returns 1 if node is a leaf node
int is_leaf(qnode * node){
	return (node->first == NULL);
}

//Subdivides the node into 4 seqments (Turns leaf node into internal node)
void subdivide(qnode * node){
	Vector2 newSize = {node->size.x / 2.0f, node->size.y / 2.0f};

	Vector2 firstPos = node->pos;
	Vector2 secondPos = (Vector2){node->pos.x + newSize.x, node->pos.y};
	Vector2 thirdPos = (Vector2){node->pos.x, node->pos.y + newSize.y};	
	Vector2 fourthPos = (Vector2){node->pos.x + newSize.x, node->pos.y + newSize.y};

	node->first = qnode_new(firstPos, newSize);
	node->second = qnode_new(secondPos, newSize); 
	node->third = qnode_new(thirdPos, newSize);
	node->fourth = qnode_new(fourthPos, newSize);
}

qtree * createTree(int sizeX, int sizeY, int treshold){
	qtree * qtreeptr = (qtree *) malloc(sizeof(qtree));
	if(!qtreeptr){
		fprintf(stderr, "ERROR in allocation of Qtree!\n");
		exit(1);
	}
	qtreeptr->rootnode = (qnode*) malloc(sizeof(qnode));
	if(!qtreeptr->rootnode){
		fprintf(stderr, "ERROR in allocation of QNode!\n");
		exit(1);
	}	
	
	qtreeptr->rootnode->count = 0;
	qtreeptr->rootnode->pos = (Vector2){0.0f, 0.0f};
	qtreeptr->rootnode->size = (Vector2){screenWidth, screenHeight};

	qtreeptr->rootnode->first = NULL;
	qtreeptr->rootnode->second = NULL;
	qtreeptr->rootnode->third = NULL;
	qtreeptr->rootnode->fourth = NULL;

	puts("Succesfully created tree!");

	return qtreeptr;
}

int addElement_i(qtree * qtree, qnode * currentNode, Vector2 point){

	Vector2 currentHalfSize = (Vector2){ currentNode->size.x / 2.0f, currentNode->size.y / 2.0f};
	Vector2 middlePoint = (Vector2) { currentNode->pos.x + currentHalfSize.x, currentNode->pos.y + currentHalfSize.y };



	//If node is full	
	if(currentNode->count <= qtree->treshold){
		//If current node already holds a point (Is a leaf node)
		subdivide(currentNode);
		//If point should go to top left node	
		if(point.x < middlePoint.x && point.y < middlePoint.y){
			currentNode->first->count++;	
			currentNode->first->points = realloc(currentNode->points, sizeof(struct point*)*(currentNode->count+1));
			return 1;
		}
		
	}	
	else{
		
	}

	return 1;
}
int addElement(qtree * quadtree, Vector2 point){
	addElement_i(quadtree ,quadtree->rootnode, point);

	return 1;
}
void drawTreeBounds_i(qnode * node){
	DrawRectangleLines(node->pos.x, node->pos.y, node->size.x, node->size.y, BLACK);

	if(node->first){
		drawTreeBounds_i(node->first);
		drawTreeBounds_i(node->second);
		drawTreeBounds_i(node->third);
		drawTreeBounds_i(node->fourth);
	}

}
void drawTreeBounds(qtree * quadtree){
	drawTreeBounds_i(quadtree->rootnode);
}
void destroyTree_i(qnode * node){
	
	//Clearing all the points	
	if(node->count)
		free(node->points);
	node->count = 0;

	if(node->first){
		destroyTree_i(node->first);
		destroyTree_i(node->second);
		destroyTree_i(node->third);
		destroyTree_i(node->fourth);
	}
	free(node);
}
void destroyTree(qtree * quadtree){
	destroyTree_i(quadtree->rootnode);

	free(quadtree);
	quadtree = NULL;
}
int main(int argc, char**argv){
	InitWindow(screenWidth, screenHeight, "Quadtree test");
	
	qtree * quadtree = createTree(screenWidth, screenHeight, 4);


	SetTargetFPS(60);

	while(!WindowShouldClose()){
		BeginDrawing();
		
		ClearBackground(WHITE);
		DrawText("Hello world!", screenWidth / 2, screenHeight / 2, 16, BLACK);
		drawTreeBounds(quadtree);

		EndDrawing();
	}

	destroyTree(quadtree);

	CloseWindow();
}
