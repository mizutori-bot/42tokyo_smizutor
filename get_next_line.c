/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sho <sho@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 20:34:00 by sho               #+#    #+#             */
/*   Updated: 2022/03/09 17:52:43 by sho              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 4
/* #define LEAK_DETECT
#ifdef LEAK_DETECT
#include "leakdetect.h"
#define init leak_detect_init
#define malloc(s) leak_detelc_malloc(s, __FILE__, __LINE__) 
#define free leak_detect_free
#define check leak_detect_check
#else
#define init() 
#define check()
#endif  */

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

char	*ft_strdup(const char *s1)
{
	size_t	count_s;
	char	*s2;
	size_t	i;

	count_s = ft_strlen(s1);
	s2 = (char *)malloc(sizeof(char) * count_s + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < count_s)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	if (!s || !c)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (str[i] != c)
	{
		if (str[i] == '\0')
		{
			return (NULL);
		}
		i++;
	}
	return ((char *)&s[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s2 = (char *)malloc(sizeof(char) * len + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		s2[i] = s[i + start];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned	char	*ub;

	ub = (unsigned char *)b;
	while (len > 0)
	{
		*ub = c;
		len--;
		ub++;
	}
	return (b);
}

int		ft_memdel(void **ptr)
{
	if (*ptr)
	{
		ft_memset(*ptr, 0, ft_strlen(*ptr));
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

void n_split(char *save, char **line, char **tmp, int ret)
{
	if (ret == 0)
		*line = ft_strdup(save);
	else if (ret > 0)
	{
		*line = ft_substr(save, 0, (ft_strchr(save, '\n') - save));
		*tmp = ft_strdup(save + ft_strlen(*line) + 1);
	}
}

int read_join(char **save, char **tmp, int fd)
{
	char buf[BUFFER_SIZE + 1];
	int ret;

	ret = 1;
	while (!(ft_strchr(*save, '\n')) && ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == 0 && *save[0] == '\0')
			return (-1);
		buf[ret] = '\0';
		*tmp = ft_strjoin(*save, buf);
		/* printf(" before free save ptr = %p\n", *save);
		printf(" before free save = %s\n", *save);

		printf("before free  tmp ptr = %p\n", *tmp);
		printf("before free  tmp = %s\n", *tmp); */
		ft_memdel((void *)save);
		/* printf("save ptr = %p\n", *save);
		printf("save = %s\n", *save);

		printf("tmp ptr = %p\n", *tmp);
		printf("tmp ptr = %s\n", *tmp); */
		*save = *tmp;
	}
	return (ret);
}

char *get_next_line(int fd)
{
	char *line;
	static char *save;
	char *tmp;
	int ret;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (!save)
	{
		save = (char *)malloc(sizeof(char));
		save[0] = '\0';
	}
	ret = read_join(&save, &tmp, fd);
	if (ret < 0)
		return (NULL);
	n_split(save, &line, &tmp, ret);
	save = tmp;

	if(ret == 0)
		ft_memdel((void *)&save);
	return (line);
}

int main(void)
{
	int fd;
	char *line = NULL;

	//init();
    
 	if ((fd = open("shobobo.text", O_RDONLY)) == -1)
	{
		perror("open");
		return (0);
	}
	
	while (1)
	{
		free(line);
		line = get_next_line(fd);
		printf("%s\n", line);

		if (!line)
		{
			free(line);
			break;
		}
	}
	
	if (close(fd) == -1)
	{
		perror("close");
		return (0);
	}
	//check();

	return (0);
}

//標準入力に対応できていない