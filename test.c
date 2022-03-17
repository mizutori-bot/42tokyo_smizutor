#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *s;

  if (!(s = (char *)malloc(sizeof(char))))
    return (NULL);
}