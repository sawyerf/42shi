/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:43 by apeyret           #+#    #+#             */
/*   Updated: 2019/02/14 17:51:01 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "sh_core.h"

t_key	g_key[] =\
{
	{K_CTRA, &begin},
	{K_CTRC, &ctrlc},
	{K_CTRD, &ctrld},
	{K_CTRP, &paste},
	{K_CTRV, &visualmode},
	{K_BSPC, &del_cara},
	{K_RGHT, &move_curs},
	{K_LEFT, &move_curs},
	{K_SLFT, &prev_word},
	{K_SRGT, &next_word},
	{K_TAB,  &autocompl},
	{K_ENTR, &enter},
	{NULL,   &enter}
};

int		paste(t_rdl *rdl, char *buf)
{
	(void)buf;
	if (!rdl->paste)
		return (0);
	rdladdstr(rdl, rdl->paste);
	return (0);
}

int		del_cara(t_rdl *rdl, char *buf)
{
	(void)buf;
	rdldel(rdl, rdl->curs - 1);
	return (0);
}

int		special_key(t_rdl *rdl, char *buf, t_key *key)
{
	int count;

	count = 0;
	while (key[count].key)
	{
		if (!ft_strcmp(key[count].key, buf))
			return (key[count].f(rdl, buf));
		count++;
	}
	return (0);
}

int		normal_key(t_rdl *rdl, char *buf)
{
	int count;

	count = 0;
	while (buf[count])
	{
		rdladd(rdl, buf[count]);
		count++;
	}
	return (0);
}

int		key_router(t_rdl *rdl, char *buf)
{
	if (is_special(buf))
		return (special_key(rdl, buf, g_key));
	else
		return (normal_key(rdl, buf));
}
