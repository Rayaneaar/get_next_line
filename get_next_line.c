/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 08:45:49 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/13 08:56:02 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>

char    *read_and_save(int fd, char *cache)
{
    ssize_t bytes_read;
    char    *buffer;
    char    *temp;

    bytes_read = 1;
    while (!ft_strchr(cache, '\n')
        && bytes_read  > 0)
    {
        buffer = malloc((size_t) BUFFER_SIZE);
        if (!buffer)
          return (NULL);
        bytes_read =read(fd, buffer, BUFFER_SIZE);
        buffer[bytes_read] = '\0';
        temp = cache;
        cache = ft_strjoin(cache, buffer);
        free(temp);
        if (!cache)
            return(NULL);
    }
    if (bytes_read == -1)
        return (free(cache), NULL);
    return (cache);
}

char    *extract_line(char *cache)
{
    char     *pos;
    char    *line;

    if (!cache || !cache[0])
        return (free(cache) ,NULL);
    pos = ft_strchr(cache , '\n');
    if (!pos)
        line = ft_strdup(cache);
    else
        line = ft_substr(cache, 0, (pos - cache) + 1);
    return (line);
}

char    *update_cache(char *cache, char *line)
{
    char    *new_cache;
    size_t  line_len;
    size_t  cache_len;

    line_len = ft_strlen(line);
    cache_len = ft_strlen(cache);
    new_cache = ft_substr(cache, line_len, cache_len - line_len);
    free(cache);
    return (new_cache);
}

char    *get_next_line(int fd)
{
    static char *cache;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!cache)
        cache = ft_strdup("");
    if (!cache)
        return (NULL);
    cache = read_and_save(fd, cache);
    if (!cache)
        return (NULL);
    line = extract_line(cache);
    if (!line)
        return (NULL);
    cache = update_cache(cache, line);
    if (!cache)
        return (free(line), NULL);
    return (line);
}
