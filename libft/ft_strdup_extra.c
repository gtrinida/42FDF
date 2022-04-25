/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtrinida <gtrinida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:21:18 by gtrinida          #+#    #+#             */
/*   Updated: 2022/04/25 17:01:19 by gtrinida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_extra(const char *str, int flag)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(ft_strlen(str) + 2);
	while (str[i] != '\0' && (!flag || (flag && str[i] != '\n')))
	{
		res[i] = str[i];
		i++;
	}
	if (flag && str[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}
