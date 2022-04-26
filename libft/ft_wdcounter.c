/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdcounter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:31:04 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/26 19:04:02 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wdcounter(const char *str, char separator)
{
	int		a;
	size_t	i;

	a = 0;
	i = 0;
	while (i < ft_strlen(str) - 1)
	{
		if ((str[i] == separator) && (str[i + 1] != separator)
			&& str[i + 1] > 31)
			a = a + 1;
		i++;
	}
	if (str[0] != separator)
		a = a + 1;
	return (a);
}
