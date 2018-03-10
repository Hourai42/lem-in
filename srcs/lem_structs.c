/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:35:22 by ttran             #+#    #+#             */
/*   Updated: 2018/03/09 19:35:36 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_super(t_super **hold)
{
	*hold = malloc(sizeof(t_super));
	(*hold)->group = NULL;
	(*hold)->graph = NULL;
	(*hold)->end_counter = 0;
	(*hold)->start_counter = 0;
}
