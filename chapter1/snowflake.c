#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 100000

// program to find identical snowflakes
// This is DMOJ problem cco07p2 .

//page 16

// simple node definiton
typedef struct snowflake_node {
  int snowflake[6];
  struct snowflake_node *next;
} snowflake_node;

// function prototypes
void identify_identical(snowflake_node *snowflakes[]);
bool identical_right(int snow1[], int snow2[], int start);
bool identical_left(int snow1[], int snow2[], int start);
bool are_identical(int snow1[], int snow2[]);
int code(int snowflakes[]);

int main(void) {
  static snowflake_node *snowflakes[SIZE] = {NULL};
  snowflake_node *snow;
  int n, i, j, snowflake_code;
  puts("enter how many snowflakes:");
  scanf("%d",&n);
  for(int i = 0; i < n;i++){
      snow = malloc(sizeof(snowflake_node));
      if(snow == NULL){
          fprintf(stderr, "malloc error\n");
          exit(1);
      }
      puts("snowflake:");
      for(j=0;j< 6;j++){
          scanf("%d",&snow->snowflake[j]);
      }
      snowflake_code = code(snow->snowflake);
      snow->next = snowflakes[snowflake_code];
      snowflakes[snowflake_code] = snow;
  }
  identify_identical(snowflakes);
  //decalocate all malloc'd memory
  return 0;
}

bool are_identical(int snow1[], int snow2[]) {
  int start;
  for (start = 0; start < 6; start++) {
    if (identical_right(snow1, snow2, start)) {
      return true;
    }
    if (identical_left(snow1, snow2, start)) {
      return true;
    }
  }
  return false;
}

void identify_identical(snowflake_node *snowflakes[]) {
  int i;
  snowflake_node *node1, *node2;
  for(i=0;i < SIZE;i++){
      node1 = snowflakes[i];
      while(node1 != NULL){
          node2 = node1->next;
          while(node2!=NULL){
              if(are_identical(node1->snowflake, node2->snowflake)){
                  puts("twin snowflakes found");
                  return;;
              }
              node2 = node2->next;
          }
          node1 = node1->next;
      }
  }
  puts("no twin snowflakes found");
}

bool identical_right(int snow1[], int snow2[], int start) {
  int offset;
  for (offset = 0; offset < 6; offset++) {
    if (snow1[offset] != snow2[(start + offset) % 6])
      return false;
  }
  return true;
}

bool identical_left(int snow1[], int snow2[], int start) {
  int offset, snow2_index;
  for (offset = 0; offset < 6; offset++) {
    snow2_index = start - offset;
    if (snow2_index < 0) {
      snow2_index = snow2_index + 6;
    }
    if (snow1[offset] != snow2[snow2_index])
      return false;
  }
  return true;
}

int code(int snowflakes[]) {
  int sum = 0;
  for (int i = 0; i < 6; i++) {
    sum += snowflakes[i];
  }
  return sum % SIZE;
}
