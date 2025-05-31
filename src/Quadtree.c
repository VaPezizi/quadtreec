#include "Quadtree.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>




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
void subdivide(qtree * qtree,qnode * node){

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

qtree * create_tree(int sizeX, int sizeY, int treshold){
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
	qtreeptr->rootnode->size = (Vector2){sizeX, sizeY};

	qtreeptr->rootnode->first = NULL;
	qtreeptr->rootnode->second = NULL;
	qtreeptr->rootnode->third = NULL;
	qtreeptr->rootnode->fourth = NULL;

	puts("Succesfully created tree!");

	return qtreeptr;
}

int add_element_i(qtree * qtree, qnode * currentNode, Vector2 point){

	Vector2 currentHalfSize = (Vector2){ currentNode->size.x / 2.0f, currentNode->size.y / 2.0f};
	Vector2 middlePoint = (Vector2) { currentNode->pos.x + currentHalfSize.x, currentNode->pos.y + currentHalfSize.y };



	//If node is a leaf AND fits more points
	if(is_leaf(currentNode) && currentNode->count < qtree->treshold){
		currentNode->count++;
		currentNode->boxes = (Box*)realloc (currentNode->boxes, sizeof(Box)*(currentNode->count));
		return 1;	

		//If point should go to top left node	
		/*if(point.x < middlePoint.x && point.y < middlePoint.y){
			currentNode->first->count++;				//Note, we first increase count and THEN allocate 	
			currentNode->first->boxes = (Box*)realloc(currentNode->boxes, sizeof(Box)*(currentNode->count));
			return 1;
		}
		//top right
		if(point.x > middlePoint.x && point.y < middlePoint.y){
			currentNode->first->count++;
			
		}*/
		
	}	
	else{	//If point can be added to node	
		subdivide(qtree, currentNode);
	}

	return 1;
}
int add_element(qtree * qtree, Vector2 point){
	add_element_i(qtree ,qtree->rootnode, point);

	return 1;
}
void draw_tree_bounds_i(qnode * node){
	DrawRectangleLines(node->pos.x, node->pos.y, node->size.x, node->size.y, BLACK);

	if(node->first){
		draw_tree_bounds_i(node->first);
		draw_tree_bounds_i(node->second);
		draw_tree_bounds_i(node->third);
		draw_tree_bounds_i(node->fourth);
	}

}
void draw_tree_bounds(qtree * qtree){
	draw_tree_bounds_i(qtree->rootnode);
}
void destroy_tree_i(qnode * node){
	
	//Clearing all the points	
	if(node->count)
		free(node->boxes);
	node->count = 0;

	if(node->first){
		destroy_tree_i(node->first);
		destroy_tree_i(node->second);
		destroy_tree_i(node->third);
		destroy_tree_i(node->fourth);
	}
	free(node);
}
void destroy_tree(qtree * qtree){
	destroy_tree_i(qtree->rootnode);

	free(qtree);
	qtree = NULL;
	fprintf(stdout, "Succesfully freed tree!\n");
}
