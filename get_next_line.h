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

#include <unistd.h>
#include <stdlib.h>

# define BUFFER_SIZE  1024

char *get_next_line(int fd);

char	*ft_strjoin(char const *s1, char const *s2);
# endif
