#include "get_next_line.h"

int ft_strlen(char *s)
{
    if (!s)
        return (0);
    int i = 0;
    while (s[i])
        i++;
    return (i);
}
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char *ft_strdup(char *s)
{
    if (!s)
        return (NULL);
    char *dup;
    int len;

    len = ft_strlen(s);
    dup = malloc(len + 1);
    int i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}


char *ft_strjoin(char *s1, char *s2)
{
    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));

    int len1 = ft_strlen(s1);
    int len2 = ft_strlen(s2);

    char *join = malloc(len1 + len2 + 1);
    if (!join)
        return (NULL);

    int i = 0;
    for (; i < len1; i++)
        join[i] = s1[i];

    for (int j = 0; j < len2; j++)
        join[i + j] = s2[j];

    join[i + len2] = '\0';

    return join;
}
   //------------------------------------------------------------------------------------------------ 
char *read_fd(int fd, char *static_str)
{
    int read_byte;
    char *buff;
    char *tmp;

    buff = malloc((size_t)BUFFER_SIZE + 1);
    if (!buff)
        return (NULL);
    read_byte = 1;
    while (read_byte && !ft_strchr(buff, '\n'))
    {
        read_byte = read(fd, buff, BUFFER_SIZE);
        if (read_byte < 0)
        {
            free(buff);
            free(static_str);
            return (NULL);
        }
        buff[read_byte] = '\0';
        tmp = ft_strjoin(static_str, buff);
        if (!tmp)
        {
            free(buff);
            free(static_str);
            return (NULL);
        }
        free(static_str);
        static_str = tmp;
    }
    free(buff);
    return (static_str);
}

char *extract_line(char *str)
{
    int i = 0;
    char *line;

    if (!*str)
        return (NULL);
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        i++;

    line = malloc( i + 1);
    if (!line)
        return (NULL);

    i = 0;
    while (str[i] && str[i] != '\n'){
        line[i] = str[i];
        i++;
    }

    if (str[i] == '\n')
        line[i++] = '\n';
    
    line[i] = '\0';
    return (line);
}   


char *remove_line(char *str)
{
    int i = 0;
    int j = 0;
    int *new_str;
    
    while (str[i] && str[i] != '\n')
        i++;
    if (!str[i])
        return (free(str), NULL);
    new_str = malloc(ft_strlen(str) - i);
    if (!new_str)
        return (NULL);
    i++;
    while (str[i])
        new_str[j++] = str[i++];
    new_str[j] = '\0';
    free(str);
    return (new_str);
}

char *get_next_line(int fd)
{
    if (fd > INT_MAX|| BUFFER_SIZE <= 0)
        return (NULL);

    static char *static_str;
    char *line ;

    static_str = read_fd(fd, static_str);
    if (!static_str)
        return (NULL);
    line = extract_line(static_str);
    static_str = remove_line(static_str);
    return (line);
}

void f(){system("leaks a.out");}

int main(void)
{
    atexit(f);
    int fd = open("get_next_line.h", O_RDWR);
    if (fd < 0)
        return (1);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
}