/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:37:16 by ishaimou          #+#    #+#             */
/*   Updated: 2019/02/08 10:17:15 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_utoa_base(unsigned long int val, int base)
{
	unsigned long int	nb;
	int			size;
	char			*res;

	size = 1;
	nb = val;
	while (nb /= base)
		size++;
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return NULL;
	res[size] = '\0';
	nb = val;
	while (size-- > 0)
	{
		if (nb % base < 10)
			res[size] = (nb % base) + '0';
		else
			res[size] = (nb % base) + 'A' - 10;
		nb /= base;
	}
	return (res);
}
