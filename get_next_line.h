#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

size_t  ft_strlen(const char *s);
char    *ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
size_t  ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *b, int c, size_t len);
int		ft_memdel(char **ptr);
void    n_split(char **save, char **line, char **tmp, int ret);
int     read_join(char **save, char **tmp, int fd);
char    *get_next_line(int fd);

#endif