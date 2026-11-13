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

char    *read_and_save(int fd, char *cache)
{
    ssize_t bytes_read;
    char    buffer[BUFFER_SIZE + 1];
    char    *temp;

    bytes_read = 0;
    while (!ft_strchr(cache, '\n')
        && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        temp = ft_strjoin(cache, buffer);
        if (!temp)
            return (free(cache), NULL);
        free(cache);
        cache = temp;
    }
    if (bytes_read == -1)
        return (free(cache), NULL);
    return (cache);
}

char    *extract_line(char *cache)
{
    int     i;
    char    *line;

    i = 0;
    if (!cache || !cache[0])
        return (NULL);
    while (cache[i] && cache[i] != '\n')
        i++;
    if (cache[i] == '\n')
        i++;
    line = ft_substr(cache, 0, i);
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
        return (free(cache), cache = NULL, NULL);
    cache = update_cache(cache, line);
    if (!cache)
        return (free(line), NULL);
    return (line);
}
