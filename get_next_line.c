/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 10:24:49 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/13 05:05:32 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *read_and_save(int fd, char *cache)
{
    ssize_t bytes_read;
    char    buffer[BUFFER_SIZE + 1];
    char    *temp;

    if (!cache)
        return (NULL);
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

char *extract_line(char *buffer , int position)
{
  char *line;
  int j;

  j = 0;
  line = malloc(sizeof(char) * (position + 1));
  if (!line)
    return(NULL);
  while (j < position)
  {
    line[j] = buffer[j];
    j++;
  }
  line[j] = '\0';
  return (line);
}
char *get_next_line(int fd)
{
  int i;
  char *line;
  static char *cache;

  i = 0;

  if (fd == -1 || BUFFER_SIZE == 0)
    return (NULL);
  cache = read_and_save(fd ,cache);
  

 return(NULL);
}
