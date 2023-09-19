/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anda-cun <anda-cun@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:47:26 by anda-cun          #+#    #+#             */
/*   Updated: 2023/09/19 15:28:04 by anda-cun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// int create_executor(char *command)
// {
//     if (fork() == 0)
//     {
//         signal(SIGINT, sigint_handler);
//         exec(&command);
//         kill(getpid(), SIGSEGV);
//     }
//     return (0);
// }

void	init(t_data *data, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			data->path = ft_split(&envp[i][5], ':');
	}
	getcwd(data->cwd, PATH_MAX);
}

int	main(int ac, char **av, char **envp)
{
    (void)av;
    if (ac != 1)
        return(ft_putstr_fd("Error: Too many arguments\n", 1));
    t_data data;
    int i = 0;
    init(&data, envp);
    // signal(SIGQUIT, SIG_IGN);
    // signal(SIGINT, terminal_prompt);
    while (1)
    {
        char *line = readline("minishell$>");
        if (line != NULL && *line)
        {
            add_history(line);

            char **newstring = ft_split(treat_str(line), 2);
            while (newstring[i])
            {
                printf("String: %s\n", newstring[i]);
                i++;
            }
            free(line);

        }
                    //create_executor(parsing(line)); 
    }
    return (0);
}