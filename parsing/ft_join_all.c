/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vispinos <vispinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:59:55 by vispinos          #+#    #+#             */
/*   Updated: 2024/10/01 14:31:07 by vispinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h" // decomment after code sync
#include "parsing.h"

char	*ft_join_all(char *line, char *var_value, int i_save, int cut)
{
	char	*temp_str;
	char	*pre_line;
	char	*new_line;

	temp_str = ft_substr(line, 0, i_save);
	printf("temp str: %s\n", temp_str);
	/* if (!temp_str)
		return (NULL); */
	pre_line = ft_strjoin(temp_str, var_value);
	printf("pre_line: %s\n", pre_line);
	//free(temp_str);
	/* if (!pre_line)
		return (NULL); */
	temp_str = ft_strdup(&line[i_save + cut]);
	printf("temp str 2: %s\n", temp_str);
	/* if (temp_str)
		return (free(pre_line), NULL); */
	printf("making new line\n");
	new_line = ft_strjoin(pre_line, temp_str);
	printf("new_line: %s\n", new_line);
	/* free(pre_line);
	free(temp_str); */
	/* if (!new_line)
		return (NULL); */
	return (new_line);
}