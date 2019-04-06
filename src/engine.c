/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:26:36 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/06 06:25:07 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			semi_load(char *format, t_lst *lst, int *p, t_chr **curr)
{
	if (p[1] >= p[0])
	{
		(*curr)->str = cut_str(format, p[0], p[1]);
		(*curr)->len = p[1] - p[0] + 1;
		(*curr)->next = (t_chr*)malloc(sizeof(t_chr));
		(*curr) = (*curr)->next;
		init_chr(curr);
	}
	p[0] = (p[1] >= 0) ? p[1] : 0;
	if (format[++p[0]] == '%')
	//	while (format[p[0]] != lst->format->convers)
			p[0]++;
	//else if (format[p[0]++] == '%')
		while (format[p[0]] != lst->format->convers)
			p[0]++;
	if (lst->next)
	{
		(*curr)->next = (t_chr*)malloc(sizeof(t_chr));
		(*curr) = (*curr)->next;
		init_chr(curr);
	}
}

t_chr			*load_chr(char *format, t_lst *lst)
{
	t_chr		*mychr;
	t_chr		*curr;
	int			p[2];

	if (!(mychr = (t_chr*)malloc(sizeof(t_chr))))
		return (0);
	init_chr(&mychr);
	p[0] = 0;
	curr = mychr;
	while (lst)
	{
		p[1] = lst->format->pos - 1;
		semi_load(format, lst, p, &curr);
		lst = lst->next;
		p[0]++;
	}
	if (format[p[0]] && format[p[0]] != '%')
	{
		curr->next = (t_chr*)malloc(sizeof(t_chr));
		curr = curr->next;
		curr->str = ft_strdup(&format[p[0]]);
		curr->len = ft_strlen(&format[p[0]]);
		curr->next = NULL;
	}
	return (mychr);
}

static void		some_convers(t_lst *lst, t_chr *chr, va_list ap)
{
	if (lst->format->convers == 's')
		conv_s(lst, &chr, ap);
	else if (lst->format->convers == 'c')
		conv_c(lst, &chr, ap);
	else if (lst->format->convers == 'u')
		conv_u(lst, &chr, ap);
	else if (lst->format->convers == 'o')
		conv_o(lst, &chr, ap);
	else if (lst->format->convers == 'k')
		conv_k(lst->format, &chr, ap);
	else if (lst->format->convers == '}')
		conv_color(lst, &chr);
	else if (ft_strchr("pP", lst->format->convers))
		conv_p(lst, &chr, ap);
	else
		conv_percent(&chr, lst, ap);
}

void			fill_chr(t_lst *lst, t_chr *chr, va_list ap)
{
	while (lst)
	{
		while (chr && chr->str)
			chr = chr->next;
		if (ft_strchr("di", lst->format->convers))
			conv_di(lst, &chr, ap);
		else if (ft_strchr("uosckpP}%", lst->format->convers))
			some_convers(lst, chr, ap);
		else if (ft_strchr("f", lst->format->convers)
				&& ft_strchr(lst->format->flag, 'L'))
			conv_llf(lst, &chr, ap);
		else if (ft_strchr("fHeEgG", lst->format->convers))
			conv_d_efgh(lst, &chr, ap);
		else if (ft_strchr("bB", lst->format->convers))
			conv_b(lst, &chr, ap);
		else if (ft_strchr("xX", lst->format->convers))
			conv_xx(lst, &chr, ap);
		else
			conv_invalid(&chr, lst->format, ap);
		lst = lst->next;
		chr = chr->next;
	}
}
