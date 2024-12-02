/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:12:36 by tespandj          #+#    #+#             */
/*   Updated: 2024/12/02 21:14:14 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*reset(char *str)
{
	if (!str)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	return (str);
}

int	tstrlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*tdup(char *str)
{
	char	*dup;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (tstrlen(str) + 1));
	if (!dup)
		return (NULL);
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*tjoin(char *str, char *add)
{
	char	*join;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!str && !add)
		return (NULL);
	if (!str)
		return(tdup(add));
	if (!add)
		return(tdup(str));
	join = malloc(sizeof(char) * (tstrlen(str) + tstrlen(add) + 1));
	if (!join)
		return (NULL);
	while (str[++i])
		join[i] = str[i];
	while (add[++j])
		join[i + j] = add[j];
	join[i + j] = '\0';
	free(str);
	return (join);
}

int	backslash_n(char *str)
{
	int	i;

	i = -1;
	if (!str || !str[0])
		return (0);
	while (str[++i])
		if (str[i] && str[i] == '\n')
			return (1);
	return (0);
}

char	*tkla(char *input)
{
	char	*line;
	int		i;

	i = -1;
	if (!input)
		return (NULL);
	while (input[++i])
		if (input[i] == '\n')
			break ;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	line[++i] = '\0';
	while (--i >= 0)
		line[i] = input[i];
	return (line);
}

char	*tkla_keep_the_rest(char *input)
{
	char	*rtn;
	int		i;
	int		r;

	i = -1;
	r = -1;
	if (!input)
		return (NULL);
	while (input[++i])
		if (input[i] == '\n')
			break ;
	rtn = malloc(sizeof(char) * (tstrlen(input) - i + 1));
	if (!rtn)
		return (NULL);
	while (input[++i])
		rtn[++r] = input[i];
	rtn[++r] = '\0';
	free(input);
	return (rtn);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buffer;
	int			rv;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = reset(line);
	while (!backslash_n(line))
	{
		rv = read(fd, buffer, BUFFER_SIZE);
		buffer[rv] = '\0';
		if (rv == 0)
			break;
		line = tjoin(line, buffer);
	}
	if (backslash_n(line))
	{
		free(buffer);
		buffer = tkla(line);
		line = tkla_keep_the_rest(line);
		return (buffer);
	}
	free(line);
	line = NULL;
	free(buffer);
	return (NULL);
}
