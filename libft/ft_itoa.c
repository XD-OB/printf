/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 05:49:26 by obelouch          #+#    #+#             */
/*   Updated: 2018/10/08 23:18:27 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	nbr_val(int nbr)
{
	if (nbr < 0)
		return (-(long)nbr);
	return (nbr);
}

static int	sign_val(int nbr)
{
	if (nbr < 0)
		return (1);
	return (0);
}

static int	size_val(int nbr)
{
	if (nbr < 0)
		return (2);
	return (1);
}

char		*ft_itoa(int nbr)
{
	char	*res;
	long	tmp;
	int	size;
	int	sign;

	size = size_val(nbr);
	sign = sign_val(nbr);
	tmp = nbr_val(nbr);
	while (tmp /= 10)
		size++;
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (res);
	res[size] = '\0';
	if (sign)
		res[0] = '-';
	tmp = nbr_val(nbr);
	while (size-- > sign)
	{
		res[size] = (tmp % 10) + 48;
		tmp /= 10;
	}
	return (res);
}
