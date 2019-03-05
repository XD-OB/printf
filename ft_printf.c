/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:46:18 by obelouch          #+#    #+#             */
/*   Updated: 2019/03/05 18:42:48 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_plus(char **nbr)
{
	char	*str;
	int	len;

	len = ft_strlen(*nbr) + 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (ft_atoi(*nbr) < 0)
		str[0] = '-';
	else
		str[0] = '+';
	str[len] = '\0';
	ft_strcpy(&str[1], *nbr);
	free (*nbr);
	*nbr = str;
}

void            flag_space(char **nbr, char *flag)
{
	char    *str;
	int     len;

	if (!ft_strchr(flag, '+'))
	{
		len = ft_strlen(*nbr) + 1;
		str = (char*)malloc(sizeof(char) * (len + 1));
		if (ft_atoi(*nbr) >= 0)
			str[0] = ' ';
		str[len] = '\0';
		ft_strcpy(&str[1], *nbr);
		free (*nbr);
		*nbr = str;
	}
}

void		flag_zero(char **str, t_format *format)
{
	int	i;

	if ((format->precis == 0 || format->convers == 'f')
			&& !ft_strchr(format->flag, '+'))
	{
		i = -1;
		while (++i < (format->width - (int)ft_strlen(*str)))
			(*str)[i] = '0';
	}
}

static char	*dash_xob(char *nbr, int size, int base)
{
	char	*str;
	int	i;

	i = (base == 8) ? 1 : 2;
	size += i;
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	str[0] = '0';
	(base == 16) ? str[1] = 'X' : 0;
	(base == 2) ? str[1] = 'b' : 0;
	ft_strcpy(&str[i], nbr);
	str[size] = '\0';
	return (str);
}

void		flag_dash(char **nbr, int base)
{
	int	size;
	char	*tmp;

	if (base != 16 && base != 8 && base != 2)
		return ;
	tmp = *nbr;
	size = ft_strlen(*nbr);
	*nbr = dash_xob(*nbr, size, base);
	free (tmp);
}

void		flags(char **str, char **nb, t_format *fmt)
{
	int	n;
	int	i;

	i = -1;
	n = fmt->precis;
	while (++i < fmt->width && !ft_strpbrk(fmt->flag, "-+"))
		(*str)[i] = ' ';
	if ((fmt->convers == 'd' || fmt->convers == 'u' || fmt->convers == 'i') && fmt->precis)
	{
		i = 0;
		while ((*str)[i] == ' ')
			i++;
		i--;
		while (n--)
			(*str)[i--] = '0';
	}
	if (ft_strchr(fmt->flag, '0'))
		flag_zero(str, fmt);
	if (ft_strchr(fmt->flag, '+'))
		flag_plus(nb);
	if (ft_strchr(fmt->flag, ' '))
		flag_space(nb, fmt->flag);
}

static void	zero_udi(char **str, t_lst *lst)
{
	int	i;

	i = 0;
	while ((*str)[i] == ' ')
		(*str)[i++] = '0';
}

static void	precis_o_udi(char **str, int n_zero)
{
	int	i;

	i = -1;
	if (n_zero <= 0)
		return ;
	while ((*str)[++i] == ' ');
	while (n_zero--)
		(*str)[--i] = '0';
}

void		conv_u(t_lst *lst, t_chr **mychr, unsigned int ui)
{
	size_t	size;
	char    *str;
	char    *nbr;
	int		i;

	nbr = ft_utoa(ui);
	size = (lst->format->width);
	if (lst->format->width < lst->format->precis)
		size = lst->format->precis;
	if (size <= ft_strlen(nbr) || ft_strchr(lst->format->flag, '-'))
		size = ft_strlen(nbr);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return ;
	str[size] = '\0';
	i = -1;
	while (++i < (int)(size - ft_strlen(nbr) + 1))
		str[i] = ' ';
	ft_strcpy(&str[--i], nbr);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr))
		zero_udi(&str, lst);
	if (lst->format->precis > 0)
		precis_o_udi(&str, lst->format->precis - ft_strlen(nbr));
	(*mychr)->str = str;
	(*mychr)->len = size;
	free(nbr);
}

void		conv_di(t_lst *lst, t_chr **mychr, int d)
{
	int		size;
	char	*str;
	char	*nbr;
	int		i;

	if (d == 0 && lst->format->precis == -2)
		(*mychr)->str = ft_strdup("\0");
	else
	{
		if (lst->format->precis == -2)
			lst->format->precis = 0;
		nbr = ft_itoa(d);
		if (ft_strchr(lst->format->flag, '+'))
			flag_plus(&nbr);
		if (d >= 0 && ft_strchr(lst->format->flag, ' '))
			flag_space(&nbr, lst->format->flag);
		size = (lst->format->width);
		if (lst->format->width < lst->format->precis)
			size = lst->format->precis;
		if (size <= ft_strlen(nbr) || ft_strchr(lst->format->flag, '-'))
			size = ft_strlen(nbr);
		if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
			return ;
		str[size] = '\0';
		i = -1;
		while (++i < (int)(size - ft_strlen(nbr)))
			str[i] = ' ';
		str[i] = '\0';
		if (d < 0 && ft_strchr(lst->format->flag, '0'))
		{
			nbr[0] = '0';
			str[0] = '-';
		}
		ft_strcat(str, nbr);
		if (ft_strchr(lst->format->flag, '0')
				&& lst->format->width > (int)ft_strlen(nbr)
				&& lst->format->precis == 0)
			zero_udi(&str, lst);
		if (lst->format->precis > 0)
			precis_o_udi(&str, lst->format->precis - ft_strlen(nbr));
		(*mychr)->str = str;
		free(nbr);
	}
	(*mychr)->len = ft_strlen(str);
}

void		conv_s(t_lst *lst, t_chr **mychr, const char *s)
{
	int	i;
	int	j;
	int	len;
	int	len_s;
	char	*str;

	len_s = ft_strlen(s);
	if (lst->format->precis)
		len_s = lst->format->precis;
	len = len_s;
	if (lst->format->width > len)
		len = lst->format->width;
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return ;
	str[len] = '\0';
	i = 0;
	if (len == lst->format->width)
		while (i < len - len_s)
			str[i++] = ' ';
	j = -1;
	while (++j < len_s)
		str[i + j] = s[j];
	str[i + j] = '\0';
	(*mychr)->str = str;
	(*mychr)->len = len;
}

void		conv_c(t_lst *lst, t_chr **mychr, char c)
{
	int	i;
	int	len;
	char	*str;

	i = -1;
	len = lst->format->width;
	if (lst->format->width < 2 || ft_strpbrk(lst->format->flag, "+-0#"))
		len = 1;
	str = (char*)malloc(sizeof(char) * (len + 1));
	while (++i < len - 1)
		str[i] = ' ';
	str[i] = c;
	str[i + 1] = '\0';
	(*mychr)->str = str;
	(*mychr)->len = len;
}

void		conv_percent(t_chr **mychr)
{
	(*mychr)->str = ft_strdup("%");
	(*mychr)->len = 1;
}

static void	zero_p(char **str, t_lst *lst)
{
	int	i;

	i = 0;
	(*str)[i++] = '0';
	(*str)[i++] = 'x';
	while ((*str)[i] != 'x')
		(*str)[i++] = '0';
	(*str)[i] = '0';
}

static void	precis_zero(char **str, int n_zero)
{
	int	i;

	i = 0;
	if (n_zero > 0)
	{
		while ((*str)[i++] != 'x');
		while (n_zero--)
			(*str)[--i] = '0';
		(*str)[--i] = 'x';
		(*str)[--i] = '0';
	}
}

void		conv_p(t_lst *lst, t_chr **mychr, size_t addr)
{
	char	*str;
	char	*nbr;
	size_t	size;
	int	i;

	nbr = ft_utoa_base(addr, 16);
	flag_dash(&nbr, 16);
	nbr = ft_strlowcase(nbr);
	if (ft_strchr(lst->format->flag, ' ') && lst->format->width <= (int)ft_strlen(nbr))
		flag_space(&nbr, lst->format->flag);
	size = (lst->format->width > lst->format->precis + 2) ? lst->format->width : lst->format->precis + 2;
	if (size <= ft_strlen(nbr) || ft_strchr(lst->format->flag, '-'))
		size = ft_strlen(nbr);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return ;
	str[size] = '\0';
	i = 0;
	while (i < (int)(size - ft_strlen(nbr) + 1))
		str[i++] = ' ';
	i--;
	ft_strcpy(&str[i], nbr);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr))
		zero_p(&str, lst);
	if (lst->format->precis > 0)
		precis_zero(&str, lst->format->precis - 12);
	(*mychr)->str = str;
	(*mychr)->len = size;
	free(nbr);
}

static void		zero_xxob(char **str, t_format *fmt)
{
	int	i;

	i = 0;
	while ((*str)[i] != '0')
		(*str)[i++] = '0';
	(*str)[i] = '0';
	if (fmt->convers != 'o')
		(*str)[++i] = '0';
	if (fmt->convers == 'b')
		(*str)[1] = 'b';
	else if (fmt->convers == 'x' || fmt->convers == 'X')
		(*str)[1] = 'x';
}

void            conv_xxob(t_lst *lst, t_chr **mychr, unsigned int x)
{
	int     prefix;
	int     size;
	char    *str;
	char    *nbr;
	int		i;

	if (!(i = (lst->format->convers == 'b') ? 2 : 0))
		i = (lst->format->convers == 'o') ? 8 : 16;
	prefix = (lst->format->convers == 'o') ? 1 : 2;
	nbr = ft_utoa_base(x, i);
	if (ft_strchr(lst->format->flag, '#'))
		flag_dash(&nbr, i);
	else
		prefix = 0;
	if (lst->format->precis - prefix > 0)
		nbr[lst->format->precis + prefix] = '\0';
	size = lst->format->width;
	if (lst->format->width < lst->format->precis)
		size = lst->format->precis;
	if (size <= ft_strlen(nbr) || ft_strchr(lst->format->flag, '-'))
		size = ft_strlen(nbr);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1))))
		return ;
	str[size] = '\0';
	i = -1;
	while (++i < (int)(size - ft_strlen(nbr) + 1))
		str[i++] = ' ';
	i--;
	ft_strcpy(&str[i], nbr);
	if (ft_strchr(lst->format->flag, '0') && lst->format->width > (int)ft_strlen(nbr))
		zero_xxob(&str, lst->format);
	if (lst->format->convers == 'x')
		str = ft_strlowcase(str);
	if (lst->format->convers == 'X')
		str = ft_strupcase(str);
	(*mychr)->str = str;
	(*mychr)->len = ft_strlen(str);
	free(nbr);
}

void		conv_invalid(t_chr **mychr, char c)
{
	(*mychr)->str = ft_strnew(1);
	(*mychr)->str[0] = c;
	(*mychr)->len = 1;
}

void		engine(t_lst *lst, t_chr *chr, va_list ap)
{
	while (lst)
	{
		while (chr && chr->str)
			chr = chr->next;
		if (ft_strchr("xXob", lst->format->convers))
			conv_xxob(lst, &chr, va_arg(ap, unsigned int));
		else if (lst->format->convers == 'p')
			conv_p(lst, &chr, (size_t)va_arg(ap, void*));
		else if (lst->format->convers == 'u')
			conv_u(lst, &chr, va_arg(ap, unsigned int));
		else if (ft_strchr("di", lst->format->convers))
			conv_di(lst, &chr, va_arg(ap, int));
		else if (lst->format->convers == 's')
			conv_s(lst, &chr, va_arg(ap, const char*));
		else if (lst->format->convers == 'c')
			conv_c(lst, &chr, (char)va_arg(ap, int));
		else if (lst->format->convers == '%')
			conv_percent(&chr);
		else
			conv_invalid(&chr, lst->format->convers);
		lst = lst->next;
		chr = chr->next;
	}
}

char		*cut_str(char *str, int p1, int p2)
{
	int	i;
	char	*ret;

	i = p1 - 1;
	if (!(ret = (char*)malloc(sizeof(char) * (p2 - p1 + 2))))
		return NULL;
	while (++i <= p2)
		ret[i - p1] = str[i];
	ret[i - p1] = '\0';
	return (ret);

}

void		init_chr(t_chr **chr)
{
	(*chr)->str = NULL;
	(*chr)->len = 0;
	(*chr)->next = NULL;
}

t_chr		*load_in(char *format, t_lst *lst)
{
	t_chr	*mychr;
	t_chr	*curr;
	int	p1;
	int	p2;

	if (!(mychr = (t_chr*)malloc(sizeof(t_chr))))
		return NULL;
	init_chr(&mychr);
	p1 = 0;
	curr = mychr;
	while (lst)
	{
		p2 = lst->format->pos - 1;
		if (p2 >= p1)
		{
			curr->str = cut_str(format, p1, p2);
			curr->len = p2 - p1 + 1;
			curr->next = (t_chr*)malloc(sizeof(t_chr));
			curr = curr->next;
			init_chr(&curr);
		}
		p1 = (p2 >= 0) ? p2 : 0;
		while (format[p1] != lst->format->convers)
			p1++;
		if (format[++p1] == '%')
			p1++;
		if (lst->next)
		{
			curr->next = (t_chr*)malloc(sizeof(t_chr));
			curr = curr->next;
			init_chr(&curr);
		}
		lst = lst->next;
	}
	if (format[p1])
	{
		curr->next = (t_chr*)malloc(sizeof(t_chr));
		curr = curr->next;
		curr->str = ft_strdup(&format[p1]);
		curr->len = ft_strlen(&format[p1]);
		curr->next = NULL;
	}
	return (mychr);
}

int		put_chr(t_chr *chr)
{
	int	len;

	len = 0;
	while (chr)
	{
		write(1, chr->str, chr->len);
		len += chr->len;
		chr = chr->next;
	}
	return (len);
}

static void	print_chr(t_chr *chr)
{
	while (chr)
	{
		if (chr->str)
			write(1, chr->str, chr->len);
		else
			write(1, "strO", 4);
		write(1, " -> ", 4);
		chr = chr->next;
	}
	write(1, "NULL", 4);
	ft_putchar('\n');
}

static void	show_lst(t_lst *lst)
{
	while (lst)
	{
		write(1, &(lst->format->convers), 1);
		write(1, " -> ", 4);
		lst = lst->next;
	}
	write(1, "NULL", 4);
	ft_putchar('\n');
}

void		free_chr(t_chr *chr)
{
	t_chr	*tmp;

	while (chr)
	{
		tmp = chr;
		chr = chr->next;
		free (tmp);
	}
}

int		ft_printf(const char *format, ...)
{
	t_chr		*mychr;
	t_lst		*lst;
	va_list		ap;
	int		len;

	va_start(ap, format);
	lst = parse_format((char*)format);
	if (!lst)
	{
		put_spstr((char*)format);
		return (ft_strlen(format));
	}
	//print_lst(lst);
	if (!(mychr = load_in((char*)format, lst)))
		return -1;
	print_chr(mychr);
	ft_putendl((char*)format);
	va_start(ap, format);
	engine(lst, mychr, ap);
	show_lst(lst);
	print_chr(mychr);
	len = put_chr(mychr);
	free_chr(mychr);
	return (len);
}
