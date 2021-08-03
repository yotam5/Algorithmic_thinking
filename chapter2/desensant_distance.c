#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node 
{
    char *name;
    int num_children;
    struct node **children;
    int score;
} node;

node *find_node(node *nodes[], int num_nodes, char *name);
void *malloc_safe(int size);
node *new_node(char *name);

int main(void)
{

}

//create a new node
node *new_node(char *name)
{
    node *n = malloc_safe(sizeof(node));
    n->name = name;
    n->num_children = 0;
    return n;
}

//safe allocation with indication for errors
void *malloc_safe(int size)
{
    char *mem = malloc(size);
    if(mem == NULL){
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    return mem;
}

//find node with a given name
node *find_node(node *nodes[], int num_nodes, char *name)
{
    int i;
    for( i = 0;i < num_nodes;i++)
    {
        if(strcmp(nodes[i]->name,name) == 0){
            return nodes[i];
        }
    }
    return NULL;
}