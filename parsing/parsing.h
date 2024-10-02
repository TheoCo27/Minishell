/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vispinos <vispinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:03:47 by vispinos          #+#    #+#             */
/*   Updated: 2024/10/01 14:27:59 by vispinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h" // will need to remoce after code sync
#include "stdio.h" // deleted after import of ft_printf()

#ifndef LEXICAL
# define LEXICAL
# define INFILE 1
# define HEREDOC 2
# define OUTFILE_TRUNCATE 3
# define OUTFILE_APPEND 4
# define PIPE 5
# define CMD 6
# define ARG 7
#endif

#ifndef QUOTES	
# define QUOTES
# define SQUOTE 39
# define DQUOTE 34
# define NOQUOTE_SEP 0
#endif

#ifndef TOKEN
# define TOKEN 
typedef struct s_token
{
	int		type;
	char	*content;
	int		is_special;
}			t_token;
#endif

#ifndef LIST
# define LIST 
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;
}                   t_list;
#endif

//ONLY HERE FOR TESTING, USE REAL ONE FROM MAIN .H FILE AFTER
typedef struct s_state
{
	char	**env;
	int		exit_code;
	t_list	gc;
}			t_state;

/*
array_helpers.c
*/
int		array_len(t_token **array);
int		main_array_len(t_token ***array);
int		ft_is_space(char c);

/*
ft_join_all.c
*/
char	*ft_join_all(char *line, char *var_value, int i_save, int cut);

/*
garbage_collector.c
*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	*ft_malloc(size_t size, t_list *gc);
void	destroy_gc(t_list *gc);

/*
make_token_and_append.c
*/
t_token	**make_token_and_append(int type, char *str, t_token **array, t_state *s);
t_token	**make_str_and_append_array(char *line, int i, t_token **array, char sep, t_state *s);

/*
parse_quotes.c
*/
void	set_quotes_mode(int *sq, int *dq, char c);

/*
parsing_main.c
*/
int		find_word_len(char *line, int i);
t_token	***parseline(t_state *s, char *line);

/*
replace_vars.c
*/
char	*replace_vars(char *str, t_state *s);

/*
split_array_tokens.c
*/
t_token ***ft_split_array_tokens(t_token **t_a, int type, t_state *s);

//////////////////////////////////
//    TO BIN :
//////////////////////////////////
void	print_token(t_token *token);
void	print_array(t_token **array);
void	print_main_array(t_token ***main_array);
