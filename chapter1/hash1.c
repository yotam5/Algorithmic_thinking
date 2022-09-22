// simple hash function

#include "stdio.h"

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

unsigned long oaat(char *key, unsigned long len, unsigned long bits);

int main(void) {
  long snowflake[] = {1, 2, 3, 4, 5, 6};
  unsigned long code = oaat((char *)snowflake, sizeof(snowflake), 17);
  printf("%lu\n", code);
  printf("%ld\n", code % 100000);
  return 0;
}

unsigned long oaat(char *key, unsigned long len, unsigned long bits) {
  unsigned long hash, i;
  for (hash = 0,i = 0; i < len; i++) {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash & hashmask(bits);
}