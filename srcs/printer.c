/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:01:23 by omanar            #+#    #+#             */
/*   Updated: 2022/07/31 23:43:23 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printer(void)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 0;
	while (g_data.cmds)
	{	
		printf("------------------ CMD %d ------------------\n\n", i + 1);
		j = -1;
		while (((t_cmd *)(g_data.cmds->content))->args[++j])
			printf("==========>   Arg[%d] = %s   <==========\n",
				j, ((t_cmd *)(g_data.cmds->content))->args[j]);
		printf("\n");
		j = -1;
		while (((t_cmd *)(g_data.cmds->content))->infiles[++j])
			printf("==========>   infile[%d] = %s   <==========\n",
				j, ((t_cmd *)(g_data.cmds->content))->infiles[j]);
		printf("\n");
		j = -1;
		while (((t_cmd *)(g_data.cmds->content))->outfiles[++j])
			printf("==========>   outfile[%d] = %s   <==========\n",
				j, ((t_cmd *)(g_data.cmds->content))->outfiles[j]);
		printf("\n------------------------------------------\n\n\n");
		tmp = g_data.cmds;
		g_data.cmds = g_data.cmds->next;
		ft_lstdelone(tmp, &free_cmd);
		i++;
	}
}
