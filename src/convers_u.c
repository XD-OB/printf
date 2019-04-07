/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 05:14:25 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/07 23:43:07 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char                    *all_zero_u(char *nbr, int precis)
{
	char    *res;
	int             len;
	int             i;
	int             j;

	len = precis;
	res = ft_strnew(len);
	i = 0;
	j =  0;
	while (i < (len - (int)ft_strlen(nbr)))
		res[i++] = '0';
	while (i < len)
		res[i++] = nbr[j++];
	return (res);
}

void			precis_u(char **str, t_format *fmt, size_t nbr_len)
{
	int             i;
	int             j;
	char    *nbr;

	ft_putstr("\nstr: [");
	ft_putstr(*str);
	ft_putstr("]\n");
	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		while (i < fmt->precis - (int)nbr_len)
			(*str)[i++] = '0';
		while(j < (int)nbr_len)
			(*str)[i++] = nbr[j++];
		free(nbr);
	}
	else
	{
		i = ft_strlen(*str) - nbr_len - 1;
		j = fmt->precis - nbr_len;
		while (j-- && i >= 0)
			(*str)[i--] = '0';
	}
}

void                    precis_oldu(char **str, t_format *fmt, size_t nbr_len)
{
	int             i;
	int             j;
	char    *nbr;

	if (ft_strchr(fmt->flag, '-'))
	{
		i = 0;
		j = 0;
		nbr = ft_strdup(*str);
		while (i < fmt->precis - (int)nbr_len)
			(*str)[i++] = '0';
		while(j < (int)nbr_len)
			(*str)[i++] = nbr[j++];
		free(nbr);
	}
	else
	{
		i = ft_strlen(*str) - nbr_len - 1;
		j = fmt->precis - nbr_len;
		while (j-- && i >= 0)
			(*str)[i--] = '0';
	}
}

void                    conv_u(t_lst *lst, t_chr **mychr, va_list ap)
{
	size_t          	size;
	char            	*str;
	char            	*nbr;
	unsigned long	n;
	int            		i;

	flag_star(lst->format, ap);
	n = (flag_dollar(lst)) ? cast_xxoub(*(lst->arglist), lst->format)
		: cast_xxoub(ap, lst->format);
	if (n == 0 && !lst->format->precis)
	{
		(*mychr)->str = ft_strcnew(lst->format->width, ' ');
		((*mychr)->str)[lst->format->width] = '\0';
		(*mychr)->len = lst->format->width;
		return ;
	}
	nbr = ft_ultoa(n);
	flag_apostrophe(&nbr, lst->format);
	size = ft_max(ft_strlen(nbr), lst->format->width);
	if (!(str = ft_strnew(size)))
		return ;
	if (ft_strchr(lst->format->flag, '-'))
	{
		ft_strcpy(str, nbr);
		i = ft_strlen(nbr);
		while (i < (int)size)
			str[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (int)(size - ft_strlen(nbr) + 1))
			str[i++] = ' ';
		ft_strcpy(&str[--i], nbr);
	}
	if (lst->format->precis > 0 && lst->format->precis < lst->format->width)
		precis_u(&str, lst->format, ft_strlen(nbr));
	if (lst->format->precis >= lst->format->width)
		str = all_zero_u(nbr, lst->format->precis);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr) && !ft_strchr(lst->format->flag, '-'))
		str = all_zero_u(nbr, lst->format->width);
	(*mychr)->str = str;
	free(nbr);
	(*mychr)->len = ft_strlen(str);
}
