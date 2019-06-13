/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:34:52 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 07:52:36 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			add_icase(t_icase **icase, int value)
{
	t_icase		*node;

	if (!(node = (t_icase*)malloc(sizeof(t_icase))))
		return ;
	node->n = value;
	node->next = (*icase);
	(*icase) = node;
}

char				*join_icase(t_icase **icase, int size)
{
	char		*res;
	t_icase		*tmp;
	int			i;

	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	res[size] = '\0';
	i = size;
	while (*icase && --i >= 0)
	{
		tmp = *icase;
		res[i] = (*icase)->n + 48;
		*icase = (*icase)->next;
		free(tmp);
	}
	return (res);
}

char				*get_entier(long exp, long bin_mantis, int bias,
							t_fmt *format)
{
	unsigned long long	m;
	unsigned int		v[2];
	long				new_exp;
	char				*binary;
	char				*res;

	t_icase				*icase;

	v[0] = 1;
	v[1] = 0;
	binary = NULL;
		icase = NULL;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	if (new_exp < 0)
		return (ft_strdup("0"));
	m = 2251799813685248;
	(exp) ? add_icase(&icase, 1) : add_icase(&icase, 0);
	while ((v[1])++ < new_exp)
	{
		(m & bin_mantis) ? add_icase(&icase, 1) : add_icase(&icase, 0);
		v[0]++;
		m >>= 1;
	}
	binary = join_icase(&icase, v[0]);
	res = calcul_entier(binary, v[0], format);
	free(binary);
	return (res);
}

static int			fill_tab(char **tab, unsigned int *size, long *new_exp,
							long exp)
{
	if (*new_exp < -1)
	{
		int_add(tab, size, 0);
		(*new_exp)++;
		return (0);
	}
	if (*new_exp == -1)
	{
		(exp) ? int_add(tab, size, 1) : int_add(tab, size, 0);
		(*new_exp)++;
		return (0);
	}
	return (1);
}

char				*get_fract(long exp, long bin_mantis, int bias,
							t_fmt *format)
{
	unsigned int	size;
	long			new_exp;
	int				len_b;
	char			*tab;
	char			*res;

	tab = NULL;
	size = 0;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	len_b = ABS(52 - new_exp - 1);
	if (len_b < 0)
		return (ft_strdup("0"));
	while (len_b >= 0)
	{
		if (fill_tab(&tab, &size, &new_exp, exp))
			((bin_mantis >> len_b) & 1) ?
				int_add(&tab, &size, 1) : int_add(&tab, &size, 0);
		len_b--;
	}
	res = calcul_fract(tab, size, format);
	free(tab);
	return (res);
}

static void			get_eld_annex(char **tab, unsigned int *size, long new_exp)
{
	while (new_exp > 0)
	{
		int_add(tab, size, 0);
		new_exp--;
	}
}

/*
**	v[2]:	0: bin_mantis		1: new_exp
*/

char				*get_entierld(long exp, t_ldouble db, t_fmt *format)
{
	long			v[2];
	char			*tab;
	char			*res;
	unsigned int	size;
	int				i;

	tab = NULL;
	size = 0;
	v[0] = db.zone.mantissa;
	v[1] = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	if (v[1] < 0)
		return (ft_strdup("0"));
	(db.zone.int_b) ? int_add(&tab, &size, 1) : int_add(&tab, &size, 0);
	i = 63;
	while (--i >= 0 && v[1] > 0)
	{
		(1 & (v[0] >> i)) ?
			int_add(&tab, &size, 1) : int_add(&tab, &size, 0);
		v[1]--;
	}
	get_eld_annex(&tab, &size, v[1]);
	res = calcul_entier(tab, size, format);
	free(tab);
	return (res);
}
