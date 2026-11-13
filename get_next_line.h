/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raaribou <raaribou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 03:33:06 by raaribou          #+#    #+#             */
/*   Updated: 2026/11/13 04:52:33 by raaribou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char    *get_next_line(int fd);

char    *read_and_save(int fd, char *stash);
char    *extract_line(char *stash);
char    *update_stash(char *stash);

size_t  ft_strlen(char *str);
char    *ft_strchr(char *str, int c);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_substr(char *str, unsigned int start, size_t len);

#endif
