/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:43:48 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:43:49 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int symbol)
{
	char	*str;
	char	c;

	str = (char *)(string + ft_strlen(string));
	c = (char) symbol;
	while ((*str != c) && str > string)
		str--;
	if (*str == c)
		return (str);
	else
		return (NULL);
}
