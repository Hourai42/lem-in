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

#include "lem-in.h"

static int	validate_nbr(char *line)
{
	int nbr_ants;

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
	nbr_ants = validate_nbr(line);
	free(line);
	return (nbr_ants);
}
