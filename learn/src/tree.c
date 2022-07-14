#include "tree.h"
#include <stdint.h>

struct node_s* 
malloc_node(char data) {
  struct node_s *new_node =
    (struct node_s*)malloc(sizeof(struct node_s));
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->data = data;

  return new_node;
}

void 
free_node(struct node_s *node) {
  if(node != NULL) {
    free_node(node->left);
    free_node(node->right);
    free(node);
  }
}

static void 
tree_normal_print(struct node_s *node) {
  if ( node != NULL ) {
    printf("%c ", node->data);
    tree_normal_print(node->left);
    tree_normal_print(node->right);
  }
}

static void
tree_symmetric_print(struct node_s *node) {
  if ( node != NULL ) {
    tree_symmetric_print(node->left);
    printf("%c ", node->data);
    tree_symmetric_print(node->right);
  }
}

static void
tree_reverse_print(struct node_s *node) {
  if ( node != NULL) {
    tree_reverse_print(node->left);
    tree_reverse_print(node->right);
    printf("%c ", node->data);
  }
}

static struct node_s*
add_node(struct node_s *node, char data) {
  if ( node == NULL ) {
    node = malloc_node(data);
  }
  else if ( node->data < data ) {
    node->right = add_node(node->right, data); 
  }
  else if ( node->data > data ) {
    node->left = add_node(node->left, data);
  }
  return node;
}

static void
read_data(struct node_s *node)
{
  char data_buff;
  printf("Enter new data: ");
  data_buff = getchar();
  getchar();
  add_node(node, data_buff);
}

void 
run_tree(void) {
  char buff[128];
  struct node_s *root = malloc_node('A');
  
  __loop__ {
    printf("I - input data, N - output normal,\nR - output recurse, S - output symmetric, Q - exit: ");
    fgets(buff, 128, stdin);
    switch (toupper(*buff)) {
      case 'I':   read_data(root); break;
      case 'N': {
                  tree_normal_print(root);
                  puts("");
                  break;
                }
      case 'R': {
                  tree_reverse_print(root);
                  puts("");
                  break;
                }
      case 'S': {
                  tree_symmetric_print(root); 
                  puts("");
                  break;
                }
      case 'Q': return;
    }

  }
}
