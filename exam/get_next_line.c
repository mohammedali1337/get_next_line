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
int ft_strchr(char *str, char c)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    if (str[i] == c)
        return (1);
    return (0);
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
    if (!s1 || !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    char *join;
    int i = 0 ;
    int end = 0;
    join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!join)
        return (NULL);
    while (s1[end++])
        join[end] = s1[end];

    while (s2[i])
        join[end++] = s2[i++];

    join[end] = '\0';
    return (join);
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

    while (read_byte && ft_strchr(buff, '\n'))
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
    return (tmp);
}

char *extract_line(char *str)
{
    int i = 0;
    char *line;
    while (str[i] && str[i] != '\n')
        i++;
    if (str[i] == '\n')
        i++;

    line = malloc(ft_strlen(str) - i);
    if (!line)
        return (NULL);

    i = 0;
    while (str[i] && str[i] != '\n')
        line[i] = str[i++];

    if (str[i] == '\n')
        line[i++] = '\n';
    line[i] = '\0';
    return (line);
}   


char *remove_line(char *str)
{
    int i = 0;
    char *new_static;
    while (str[i] && str[i] != '\n')
        i++;
    int new_len = ft_strlen(&str[i]);
    int len = 0;
    new_static = malloc(new_len);
    while (len < new_len)
        new_static[len++] = str[i++];
    new_static[len] = '\0';
    free(str);
    return new_static;
}

char *get_next_line(int fd)
{
    if (fd > INT_MAX|| fd <= 0)
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


int main(void)
{
    int fd = open("get_next_line.h", O_CREAT | O_RDONLY | O_WRONLY, 0777);
    if (fd < 0)
        return (1);
    printf("%s", get_next_line(fd));
    
}