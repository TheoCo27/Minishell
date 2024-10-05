//#include "../minishell.h" // decomment after code sync
#include "parsing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../exec/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_token	***array;
	t_state	*state;
	char	*line;

	array = malloc(sizeof(t_token **));
	state = malloc(sizeof(t_state));
	state->exit_code = 999;
	state->env = &(*(envp));
	line = readline("minishell> ");
	array = parseline(state, line);
	if (array)
		ft_make_exec(array, envp);
	else
		printf("Array is NULL\n");
	//destroy_gc(&(state->gc));
	if (av || ac)
		return (0);
}

// pour compiler : cc -W... *.c libft/*.c -lreadline

// NO APPARENT ERRORS
