/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjose <vjose@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:43:56 by vjose             #+#    #+#             */
/*   Updated: 2022/05/12 15:43:57 by vjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_buffer(int read_bytes, char *buffer)
{
	free(buffer);
	buffer = NULL;
	if (read_bytes < 0)
		return (-1);
	else if (read_bytes == 0)
		return (0);
	else
		return (1);
}
