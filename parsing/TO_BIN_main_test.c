#include "parsing.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "../exec/pipex.h"



// int main()
// {
// 	t_file_lst *lst;
// 	t_file_lst *file1;
// 	t_file_lst *file2;
// 	t_file_lst *file3;
// 	t_file_lst *file4;

// 	lst = NULL;
// 	file1 = ft_newfile("EOF", 'h');
// 	ft_fileadd_back(&lst, file1);
// 	file2 = ft_newfile("infile", 'i');
// 	ft_fileadd_back(&lst, file2);
// 	file3 = ft_newfile("trunc", 't');
// 	ft_fileadd_back(&lst, file3);
// 	file4 = ft_newfile("app", 'a');
// 	ft_fileadd_back(&lst, file4);
// 	ft_print_filelst(&lst);

// }

//ONE SHOT TEST
int	main(int ac, char **av, char **envp)
{
	t_token	***array;
	t_state	*state;
	char	*line;

	state = malloc(sizeof(t_state));
	if (!state)
		return (0);
	state->exit_code = 999;
	state->env = &(*(envp));
	state->gc = new_gc(state);
	array = ft_malloc(sizeof(t_token **), &(state->gc), state);
	if (!array)
	{
		destroy_gc(state->gc);
		free(state);
		return(0);
	}
	line = readline("minishell> ");
	array = parseline(state, line);
	if (array)
	{
		print_main_array(array);
		ft_make_exec(array, envp);
	}
	else
		printf("Array is NULL\n");
	destroy_gc(state->gc);
	free(state);
	if (av || ac)
		return (0);
}

// MAIN TEST
// int	main(int ac, char **av, char **envp)
// {
// 	t_token	***array;
// 	t_state	*state;
// 	char	*line;

// 	state = malloc(sizeof(t_state));
// 	if (!state)
// 		return (0);
// 	state->exit_code = 999;
// 	state->env = &(*(envp));
// 	state->gc = new_gc(state);
// 	array = ft_malloc(sizeof(t_token **), &(state->gc), state);
// 	if (!array)
// 	{
// 		destroy_gc(state->gc);
// 		free(state);
// 		return(0);
// 	}
// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (ft_strncmp(line, "stop", 4) == 0)
// 			break;
// 		array = parseline(state, line);
// 		if (array)
// 		{
// 			print_main_array(array);
// 			ft_make_exec(array, envp);
// 		}
// 		else
// 			printf("Array is NULL\n");
// 	}
// 	destroy_gc(state->gc);
// 	free(state);
// 	if (av || ac)
// 		return (0);
// }

// pour compiler : cc -W... *.c libft/*.c -lreadline

// NO APPARENT ERRORS

// < infile cat -e | << limiter "hey" | wc -l | '                            ' | grep "$LANG       hehe"
// <infile cat -e|<<limiter"hey"|wc -l|'                            '|grep"$LANG       hehe"|$?
// echo "hehe         .         $?    $LANG""''''''"'"""""""'|<infile<infile<infile
