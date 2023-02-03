/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wdmatch.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maikittitee <maikittitee@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 22:15:28 by maikittitee       #+#    #+#             */
/*   Updated: 2023/02/03 00:13:00 by maikittitee      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		write(1,&str[i],1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	char *str1 = argv[1];
	char *str2 = argv[2];

	int	i = 0;
	int	j = 0;
	if (argc != 3)
	{
		ft_putstr("\n");
		return (0);
	}
	while(str2[j])
	{
		if (str1[i] == str2[j])
		{
			i++;
		}
		if (!str1[i])
		{
			ft_putstr(str1);
			ft_putstr("\n");
			break;
		}
		j++;
	}
	return (0);
}

