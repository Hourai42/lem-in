/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttran <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 20:13:31 by ttran             #+#    #+#             */
/*   Updated: 2018/03/10 20:13:38 by ttran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	validate_link(t_super *hold, char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (0);
	if (line[0] == '#' && line[1] == '#')
		return (INVALID_LINKS);
	// Think about how you're going to validate the links.
}

int	set_links(t_super *hold, **line)
{
	while (42)
	{
		if (line[0] == '\0')
			break;
		if (validate_link(hold, *line) < 0)
		{
			free(*line);
			return (INVALID_LINKS);
		}
		get_next_line(STDIN_FILENO, line);
	}
	free(*line);
	return (0);
}
