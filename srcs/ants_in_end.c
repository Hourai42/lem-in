/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_in_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 01:06:41 by ttran             #+#    #+#             */
/*   Updated: 2018/03/17 01:06:48 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	ants_in_end(t_super *hold)
{
	int i;
	int ants_end;

	ants_end = 0;
	i = -1;
	while (++i < hold->ant_total)
	{
		if (hold->farm[i]->end == 1)
			ants_end++;
	}
	return (ants_end);
}
