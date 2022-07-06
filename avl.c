#include "avl.h"

avl_node_t *create_new_node(image_t *img) {
  avl_node_t *new_node = (avl_node_t*) malloc(sizeof(avl_node_t));
  new_node->height 	= 0;
  new_node->left   	= NULL;
  new_node->right  	= NULL;
	new_node->img 		= img;
	return new_node;
}

int height(avl_node_t *node) {
	if (node == NULL) return -1;
  else return node->height;
}

int get_balance_factor(avl_node_t *node) {
  if (node == NULL) return 0;
  return height(node->left) - height(node->right);
}

avl_node_t *rotate_right(avl_node_t *node) {
  avl_node_t *left_child = node->left;
  avl_node_t *left_child_right = left_child->right;

  left_child->right = node;
  node->left = left_child_right;

  node->height = max(height(node->left), height(node->right)) + 1;
  left_child->height = max(height(left_child->left), height(left_child->right)) + 1;

  return left_child;
}

avl_node_t *rotate_left(avl_node_t *node) {
  avl_node_t *right_child = node->right;
  avl_node_t *right_child_left = right_child->left;

  right_child->left = node;
  node->right = right_child_left;

  node->height = max(height(node->left), height(node->right)) + 1;
  right_child->height = max(height(right_child->left), height(right_child->right)) + 1;
  return right_child;
}

avl_node_t *rebalance(avl_node_t *node) {
  node->height = max(height(node->left), height(node->right)) + 1;

  int balance_factor = get_balance_factor(node);
  if (balance_factor > 1) {
    if (get_balance_factor(node->left) > 0) {           /* LL */
      return rotate_right(node);
    } else {                                            /* LR */
      node->left = rotate_left(node->left);
      return rotate_right(node);
    }
  } else if (balance_factor < -1) {
    if (get_balance_factor(node->right) < 0) {          /* RR */
      return rotate_left(node);
    } else {                                            /* RL */
      node->right = rotate_right(node->right);      
      return rotate_left(node);
    }
  } 

  return node;
}

avl_node_t *avl_insert(avl_node_t *node, image_t *img) {
  if (node == NULL) return node = create_new_node(img);
  else if (img->contrast < node->img->contrast) node->left = avl_insert(node->left, img);
  else node->right = avl_insert(node->right, img);
  return rebalance(node);
}

avl_node_t *avl_init() {
	return NULL;
}

void avl_display(avl_node_t* node) {
	if (node == NULL) return;
	avl_display(node->left);
  printf("RMS CONTRAST VAL: %lf %s\n", node->img->contrast, node->img->path);
	avl_display(node->right);
}

