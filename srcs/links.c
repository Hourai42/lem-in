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

int	set_links(t_super *hold, char **line)
{
	while (42)
	{
		if ((*line)[0] == '\0')
			break ;
		if (validate_link(hold, *line) < 0)
		{
			free_gnl(line);
			return (INVALID_LINKS);
		}
		free_gnl(line);
		get_next_line(STDIN_FILENO, line);
	}
	free(*line);
	return (0);
}
