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

/*
** ft_split by "-" and ensure that index[0] is first name, index[1] is second name, and index[2] is 0.
** Make sure that both are valid room names.
** Are repeat links allowed? I guess-- there can be as many links between two rooms as necessary. 
** Even if pointless... I guess. Unless there's more than one link from start to end, meaning you can put more
** than one ant in at a time. Which makes sense-- no need to check for link repeats! 
** Basically not much error checking involved.
*/

int	setup_link(t_super *hold, char *line)
{
	// Kk.
}

int	validate_link(t_super *hold, char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (0);
	if (line[0] == '#' && line[1] == '#')
		return (INVALID_LINKS);
	return (setup_link(hold, line));

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
