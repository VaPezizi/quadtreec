#ifndef _QTREE
#define _QTREE

#ifndef _RAYLIB
#define _RAYLIB
#include <raylib.h>
#endif
#include "Box.h"

typedef struct qnode{
	int count;	//Number of elements under node
	Vector2 pos;	//Position of segment
	Vector2 size;	//size of segment
	Box ** boxes;	//List of elements
	struct qnode *first;	//Top left Qnode
	struct qnode *second;	//Top right Qnode
	struct qnode *third;	//Bottom left Qnode
	struct qnode *fourth;	//Bottom right Qnode
}qnode;

typedef struct qtree{
	int treshold;	//Amount of values node can contain, before splitting
	qnode* rootnode;
}qtree;

	qnode * qnode_new(Vector2 pos, Vector2 size);
	int is_leaf(qnode* node);
	void subdivide(qtree * tree, qnode * node);
	qtree * create_tree(int size_x, int size_y, int threshold);
	int add_element_i(qtree * qtree, qnode * currentNode, Vector2 point);
	int add_element(qtree * qtree, Vector2 point);
	void draw_tree_bounds_i(qnode * node);
	void draw_tree_bounds(qtree * qtree);
	void destroy_tree_i(qnode * node);
	void destroy_tree(qtree * qtree);

#endif
