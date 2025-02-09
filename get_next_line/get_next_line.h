/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouaalla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:06:34 by aouaalla          #+#    #+#             */
/*   Updated: 2024/12/31 12:13:34 by aouaalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define MAX_LESS 5000
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE MAX_LESS
# endif
# include "../Libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd, int flag);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);

#endif
