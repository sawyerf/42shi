/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_rdladd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:19:37 by apeyret           #+#    #+#             */
/*   Updated: 2019/06/11 18:13:17 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	rdl_realloc(t_rdl *rdl)
{
	char	*tmp;

	tmp = rdl->str;
	if (!(rdl->str = ft_strnew(rdl->allo + 128)))
		return ;
	rdl->allo += 128;
	ft_strcpy(rdl->str, tmp);
	ft_strdel(&tmp);
}

void	rdladdstr(t_rdl *rdl, char *str)
{
	int	count;
	int len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len + rdl->size > rdl->allo)
	{
		rdl->allo = rdl->size + len;
		rdl_realloc(rdl);
	}
	left(rdl, rdl->real + rdl->lpro);
	ft_memmove(rdl->str + rdl->curs + len, rdl->str + rdl->curs,
		rdl->size - rdl->curs);
	count = 0;
	while (str[count])
	{
		rdl->str[rdl->curs + count] = str[count];
		count++;
	}
	rdl->size += len;
	rdl->curs += len;
	reprint(rdl, rdl->curs);
}

void	rdladd(t_rdl *rdl, char c)
{
	if (!rdl->str)
		return ;
	if (rdl->allo == rdl->size)
		rdl_realloc(rdl);
	left(rdl, rdl->real + rdl->lpro);
	ft_memmove(rdl->str + rdl->curs + 1, rdl->str + rdl->curs,
		rdl->size - rdl->curs);
	rdl->str[rdl->curs] = c;
	rdl->size++;
	rdl->curs++;
	reprint(rdl, rdl->curs);
}
