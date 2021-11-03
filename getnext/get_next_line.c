/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 08:13:17 by rburri            #+#    #+#             */
/*   Updated: 2021/11/03 16:12:07 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_check_newline(char *stack)
{
	int	i;

	i = 0;
	while (stack[i])
	{
		if (stack[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_send_line(char *stack, char **tmp)
{
	static int	i = 0;
	char		*line;
	int			check;
	int			len;

	check = ft_check_newline(stack);
	if (check != -1)
	{
		len = 0;
		line = ft_substr(stack, 0, check + 1);
		len = (ft_strlen(stack) - ft_strlen(line));
		free(*tmp);
		*tmp = ft_substr(stack, check + 1, len);
		free(stack);
		return (line);
	}
	if (i == 1)
	{
		free(*tmp);
		free(stack);
		return (NULL);
	}
	i = 1;
	return (stack);
}

char	*get_next_line(int fd)
{	
	static char	*stack;
	static char	*tmp;
	char		buf[BUFFER_SIZE + 1];
	static int	ints[2] = {1, 1};

	if (ints[0]-- == 1)
		stack = ft_strdup("");
	else
		stack = ft_strdup(tmp);
	while (ints[1] > 0)
	{
		ints[1] = read(fd, buf, BUFFER_SIZE);
		buf[ints[1]] = '\0';
		stack = ft_strjoin(stack, buf);
		while (ft_check_newline(stack) != -1)
			return (ft_send_line(stack, &tmp));
	}
	while (ft_check_newline(stack) != -1)
		return (ft_send_line(stack, &tmp));
	return (ft_send_line(stack, &tmp));
}
