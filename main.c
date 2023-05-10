/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 18:42:45 by melkholy          #+#    #+#             */
/*   Updated: 2023/05/01 16:22:32 by melkholy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

//using an unused variable will input Command:/Users/fvon-nag/goinfre/.brew/bin/
// most likely an null edge case for ft_tokennize could fix this
// still segfautling for $variables
// most likely due to the placement of buildin execution
int	ft_closing_qoutes(char *in_put)
{
	char	divid;
	int		count;
	int		closing;

	count = -1;
	closing = 0;
	while (in_put[++count])
	{
		if (in_put[count] == '"' || in_put[count] == '\'')
		{
			if (!closing)
			{
				closing = 1;
				divid = in_put[count];
			}
			else if (in_put[count] == divid)
				closing = 0;
		}
	}
	if (closing)
	{
		free(in_put);
		return (printf("minishell: unclosed qoute detected.\n"), 1);
	}
	return (0);
}

void	ft_free_envlist(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		*env_list = (*env_list)->next;
		if (tmp->var)
			free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = *env_list;
	}
}

void	ft_exit_minihell(char *str, t_env *env_list)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_term_attr.save_attr);
	if (!str)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	free(str);
	ft_free_envlist(&env_list);
	write(1, "exit\n", 5);
	clear_history();
	exit(0);
}

/* Used to display the prompt and read the input from the user */
int	ft_read_prompt(char **envp)
{
	char	*str;
	t_mVariables	*list_pointer;
	list_pointer = malloc(sizeof(t_mVariables));
	list_pointer->ls_env = malloc(sizeof(t_env));
	list_pointer->ls_export = malloc(sizeof(t_env));
	list_pointer->ls_buffer = malloc(sizeof(t_env));
	ft_create_list(list_pointer->ls_env, envp);
	ft_create_list(list_pointer->ls_export, envp);
	ft_create_list(list_pointer->ls_buffer, envp);
//	ft_print_list(list_pointer->ls_env, ft_print_char);
	while (true)
	{
		str = readline(PROMPT);
		if (!str || !ft_strcmp(str, "exit"))
			ft_exit_minihell(str, list_pointer->ls_env);
		add_history(str);
		if (ft_closing_qoutes(str))
			continue ;
		ft_parse_input(ft_strdup(str), &list_pointer->ls_env);
		free(str);
	}
}

// int	main(int argc, char **argv, char **envp)
int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) argc;
	signal(SIGINT, ft_quit_ignore);
	signal(SIGQUIT, SIG_IGN);
	if (ft_set_terminal())
		exit(1);
	ft_read_prompt(envp);
}