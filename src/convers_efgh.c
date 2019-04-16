/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_efgh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:57:10 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/08 01:25:18 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

double			ft_dpow(int a, int b)
{
	long long	res;

	res = 1;
	if (a == 0)
		return (0);
	if (b > 0)
	{
		while (b-- >= 0)
			res *= a;
	}
	return (res);
}

void			gclean(t_format *fmt, t_chr **mychr)
{
	char	*clean;
	int		size;
	int		i;

	if (ft_strchr(fmt->flag, '#'))
		return ;
	size = (*mychr)->len - 1;
	while (size >= 0 && ((*mychr)->str)[size] == '0')
		size--;
	if (((*mychr)->str)[size] == '.')
		size--;
	if (size != (int)((*mychr)->len))
	{
		clean = (char*)malloc(sizeof(char) * size + 2);
		clean[size + 1] = '\0';
		i = -1;
		while (++i <= size)
			clean[i] = ((*mychr)->str)[i];
		free((*mychr)->str);
		(*mychr)->str = clean;
		(*mychr)->len = size + 1;
	}
}

void			conv_d_efgh(t_lst *lst, t_chr **mychr, va_list ap)
{
	t_double	db;

	flag_star(lst->format, ap);
	db.d = (flag_dollar(lst)) ?
			va_arg(*(lst->arglist), double) : va_arg(ap, double);
	(lst->format->precis == -1) ? lst->format->precis = 6 : 0;
	if (ft_strchr("fH", lst->format->convers))
		(ft_strchr(lst->format->flag, 'L')) ? conv_llf(lst, mychr, ap) : conv_lfh(lst, mychr, db);
	else if (ft_strchr("eE", lst->format->convers))
		(ft_strchr(lst->format->flag, 'L')) ?
			conv_lee(lst, mychr, ap) : conv_ee(lst, mychr, db);
	else
	{
		if (lst->format->precis == 0)
			lst->format->precis++;
		if (ft_strchr(lst->format->flag, '#'))
			lst->format->precis = 6;
		if ((db.d > 0 && (db.d < 0.001 || db.d >= 400)) || (db.d < 0 && (db.d <= -400 && db.d >= -0.01)))
		{
			if (lst->format->convers == 'G')
				lst->format->convers = 'E';
			(ft_strchr(lst->format->flag, 'L')) ?
				conv_lee(lst, mychr, ap) : conv_ee(lst, mychr, db);
		}
		else
			conv_lfh(lst, mychr, db);
		gclean(lst->format, mychr);
	}
}
