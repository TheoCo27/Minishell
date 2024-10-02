//#include "../minishell.h" // decomment after code sync
#include "parsing.h"
#include <readline/readline.h>
#include <readline/history.h>

int	main(int ac, char **av, char **envp)
{
	t_token	***array;
	t_state	*state;
	char	*line;

	array = malloc(sizeof(t_token **));
	state = malloc(sizeof(t_state));
	state->exit_code = 999;
	state->env = &(*(envp));
	while (1)
	{
		line = readline("minishell> ");
		if (ft_strncmp(line, "stop", 4) == 0)
			break;
		array = parseline(state, line);
		if (array)
			print_main_array(array);
		else
			printf("Array is NULL\n");
	}
	//destroy_gc(&(state->gc));
	if (av || ac)
		return (0);
}

// pour compiler : cc -W... *.c libft/*.c -lreadline

// NO APPARENT ERRORS
