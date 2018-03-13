/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 19:36:28 by ttran             #+#    #+#             */
/*   Updated: 2018/03/09 19:36:33 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


t_graph *find_starting(t_super *hold)
{
	t_graph *ptr;

	ptr = hold->graph;
	while (ptr != NULL)
	{
		if (ptr->start == 1)
			return (ptr);
		ptr = ptr->next_room;
	}
	return (NULL);
}

/*
** ant_nbr is simply index of farm_index + 1.
*/

void	create_antfarm(t_super *hold)
{
	t_ant *farm;
	t_graph *starting_room;
	int i;

	i = -1;
	starting_room = find_starting(hold);
	farm = malloc(sizeof(t_ant) * hold->ant_total);
	while (++i < hold->ant_total)
		farm[i].in_here = starting_room;
	hold->farm = farm;
}

int	validate_nbr_ants(char *line)
{
	int nbr_ants;

	if (*line == '\0')
		return (INVALID_ANT);
	nbr_ants = 0;
	if (ft_strlen(line) > 9)
		return (INVALID_ANT);
	while (*line)
	{
		if (!(*line >= '0' && *line <= '9'))
			return (INVALID_ANT);
		else
			nbr_ants = nbr_ants * 10 + (*line - '0');
		line++;
	}
	return (nbr_ants);
}

int		nbr_ants(void)
{
	char *line;
	int nbr_ants;

	get_next_line(STDIN_FILENO, &line);
	nbr_ants = validate_nbr_ants(line);
	free(line);
	return (nbr_ants);
}
