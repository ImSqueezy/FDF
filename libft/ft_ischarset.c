/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamarcha <gamarcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 12:04:22 by gamarcha          #+#    #+#             */
/*   Updated: 2021/06/02 12:04:46 by gamarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ischarset(int c, const char *charset)
{
	while (*charset)
		if (c == *charset++)
			return (1);
	return (0);
}
