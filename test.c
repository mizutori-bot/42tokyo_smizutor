#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * foo() {
  char a[200];
  strcpy(a, "hello world cup\n");
  return a;
}

int main() {
  char * a = foo();
  char c = a[0];
  printf("a[0] = %c\n", c);
  printf("a = %s\n", a);
  return 0;
}