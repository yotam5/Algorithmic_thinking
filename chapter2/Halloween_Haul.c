

// DMOJ problem dwite12c1p4

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// defined data type
#define SIZE 255
#define TEST_CASES 5

typedef struct node {
  int candy;
  struct node *left, *right;
} node;

typedef struct stack {
  node *values[SIZE];
  int highest_used;
} stack;

// prototypes
node *new_house(int candy);
node *new_nonhouse(node *left, node *right);
int tree_candy(node *tree);
stack *new_stack(void);
void push_stack(stack *s, node *value);
node *pop_stack(stack *s);
bool is_empty_stack(stack *s);
int tree_candy(node *tree);
int tree_nodes(node *tree);
int tree_leaves(node *tree);
int tree_height(node *tree);
int max(int a,int b);
int tree_streets(node *tree);
void tree_solve(node *tree);
node *read_tree(char *line);
node *read_tree_helper(char *line, int *pos);
void testing();
node *read_tree(char *line) {
  int pos = 0;
  return read_tree_helper(line, &pos);
}
int main(void) {
  stack *s;
  s = new_stack();
  node *n, *n1, *n2, *n3;
  n1 = new_house(20);
  n2 = new_house(30);
  n3 = new_house(10);
  push_stack(s, n1);
  push_stack(s, n2);
  push_stack(s, n3);
  while (!is_empty_stack(s)) {
    n = pop_stack(s);
    printf("%d\n", n->candy);
  }
  node *b = new_nonhouse(n1, n2);
  tree_solve(b);
}

void testing()
{
  int i;
  char line[SIZE + 1];
  node *tree;
  for(i = 0; i < TEST_CASES;i++){
    gets(line);
    tree = read_tree(line);
    tree_solve(tree);
  }
}

node *read_tree_helper(char *line, int *pos)
{
  node *tree;
  tree = malloc(sizeof(node));
  if(tree == NULL){
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  if(line[*pos] == '('){
    (*pos)++;
    tree->left = read_tree_helper(line, pos);
    (*pos)++;
    tree->right = read_tree_helper(line, pos);
    (*pos)++;
    return tree;
  }
  else{
    tree->left = NULL;
    tree->right = NULL;
    tree->candy = line[*pos] - '0';
    (*pos)++;
    if(line[*pos] != '\0'){
      tree->candy = tree->candy * 10 + line[*pos] - '0';
      (*pos)++;
    }
    return tree;
  }
}

//calculate how many streets in a tree
int tree_streets(node *tree)
{
  if(!tree->right && !tree->left){
    return 0;
  }
  return tree_streets(tree->left) + tree_streets(tree->right) + 4;
}

void tree_solve(node *tree)
{
  int candy = tree_candy(tree);
  int height = tree_height(tree);
  int num_streets = tree_streets(tree) - height;
  printf("%d %d\n",num_streets,candy);
}

//return the bigger number
int max(int a, int b)
{
  if(a > b){
    return a;
  }
  return b;
}

//calculate the height of a tree
int tree_height(node *tree)
{
  if(!tree->left && !tree->right)
  {
    return 0;
  }
  return 1+ max(tree_height(tree->left), tree_height(tree->right));
}

//calculate how many leaves in a tree
int tree_leaves(node *tree)
{
  if(!tree->left && !tree->right)
  {
    return 1;
  }
  return tree_leaves(tree->left) + tree_leaves(tree->right);  
}

//calculate how many nodes in a tree
int tree_nodes(node *tree)
{
  if(!tree->left && !tree->right){
    return 1;
  }
  return 1 + tree_nodes(tree->left) + tree_nodes(tree->right);
}

// travel the tree and collects candy
int tree_candy(node *tree) {
  int total = 0;
  stack *s = new_stack();
  while (tree != NULL) {
    if (tree->left && tree->right) {
      push_stack(s, tree->left);
      tree = tree->right;
    } else {
      total = total + tree->candy;
    }

    if (is_empty_stack(s)) {
      tree = NULL;
    } else {
      tree = pop_stack(s);
    }
  }
  return total;
}

// check if the stack is empty
bool is_empty_stack(stack *s) { return s->highest_used == -1; }

// push value to the stack
void push_stack(stack *s, node *value) {
  s->highest_used++;
  s->values[s->highest_used] = value;
}

// pop value from the stack
node *pop_stack(stack *s) {
  node *ret = s->values[s->highest_used];
  s->highest_used--;
  return ret;
}

// create a new stack
stack *new_stack(void) {
  stack *s = malloc(sizeof(stack));
  if (s == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  s->highest_used = -1;
  return s;
}

// initialize a house with a candy
node *new_house(int candy) {
  node *house = malloc(sizeof(node));
  if (house == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  house->candy = candy;
  house->left = NULL;
  house->right = NULL;
  return house;
}

// initalize the house with leafs
node *new_nonhouse(node *left, node *right) {
  node *nonhouse = malloc(sizeof(node));
  if (nonhouse == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  nonhouse->left = left;
  nonhouse->right = right;
  return nonhouse;
}
