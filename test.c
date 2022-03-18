#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFD 1024

size_t	ft_strlen(const char *s)
{	
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total;
	char	*s3;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(sizeof(char) * total + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (i < total)
	{
		s3[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char *add_a(int num)
{
  static char *s[MAXFD];
  char *tmp;

  if (!s[num])
  {
    s[num] = (char *)malloc(sizeof(char));
    if (!s[num])
      return (NULL);
    s[num][0] = '\0';
  }
  tmp = ft_strjoin(s[num], "a");
  free(s[num]);
  s[num] = tmp;
  return (s[num]);
}

int main(void)
{
  printf("num0 = %s\n", add_a(0));
  printf("num0 = %s\n", add_a(0));
  printf("num0 = %s\n", add_a(0));

  printf("num1 = %s\n", add_a(1));
  printf("num1 = %s\n", add_a(1));
  return (0);
}