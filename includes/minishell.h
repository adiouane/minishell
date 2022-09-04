/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/09/01 15:59:59 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <lexer.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <readline/history.h>
# include <readline/readline.h>

# define RST "\033[0m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define CYN "\033[0;36m"

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	char	**paths;
	int		end[2];
	int		input;
	char	*infile;
	int		output;
	char	**outfiles;
	int		*append;
	int		app_index;
	int		error;
	int		errno_value;
}	t_cmd;

typedef struct s_data {
	char	**env;
	char	**export;
	t_cmd	*cmd;
	t_list	*cmds;
	char	*newpwd;
	int		cmds_size;
	int		exit_status;
	int		tmpin;
	int		tmpout;
	int		flag;
	int		stop;
	int		dollar;
	int		breaker;
	int		signalchild;
	int		signal_heredoc;
	int		p[2];
	pid_t	pid;
}	t_data;

t_data	g_data;

/*---------------------------- INITIALIZATION ----------------------------*/

void	initialization(char **env);
int		parsing(char *line);
int		unclosed_quotes(char *line);
void	creat_env(char **env);
void	creat_export(char **env);
void	data_init(void);
void	cmd_init(void);
void	signal_init(void);

/*----------------------------- TOKENIZATION -----------------------------*/

int		tokens_handler(t_lexer *lexer);
int		token_error(t_token *token);
void	token_word(t_token **token);
void	token_outfile(t_lexer **lexer, t_token **token, int i);
void	token_infile(t_lexer **lexer, t_token **token);
void	open_infile(t_token *token);
void	token_heredoc(t_lexer **lexer, t_token **token);
void	open_heredoc(char *value, int expand);
void	token_pipe(void);

/*------------------------------- PARSING --------------------------------*/

char	*parse_args(char *str);
char	*parse_dquote(char *str, int *i);
char	*parse_squote(char *str, int *i);
char	*parse_dollar(char *str, int *i, int quote);
char	*parse_buff(char *buff);
char	*parse_limiter(char *str, int *expand);
char	*expand_dollar(char *str, char **env);
char	*handle_spaces(char *value, char **new);
char	*get_variable_name(char *str);
char	*advanced_join(char *s1, char *s2);
char	**advanced_add(char **strs, char *arg);
char	*parse_redirection(char *str);

/*-------------------------------- UTILS ---------------------------------*/

int		argslen(char **args);
int		is_acceptable(char c);
int		is_separator(char c);
int		big_len(int s1, int s2);
int		get_char_index(char *str, char c);
int		check_error(char *arg);
void	printer(void);
void	print_env(void);
void	print_export(void);
void	handlear(int signal);
char	*new_value(char *str, int i, int start);

/*------------------------------- BUILTINS -------------------------------*/

void	ft_builtins(void);
int		is_builtins(void);
int		is_builtins_in_child(void);
void	ft_builtins_in_child(void);
void	ft_echo(void);
void	pwd(void);
void	cd(void);
void	ft_env(void);
void	*ft_getenv(char *str);
void	exit_cmd(void);
char	*make_line(char *name, char *value);
char	*get_name(char *str);
void	ft_export(void);
void	error_export(char *name);
void	new_environment(void);
void	ft_set_env(char *name, char *value);
void	ft_set_export(char *name, char *value, int exist);
void	ft_unset(void);
char	**ft_remove_element(char **env, int n);
int		is_variable_exist(char *name);
int		get_index(char *str, char c);
char	*get_new_line(char *name, char *value);

/*------------------------------ WILDCARDS -------------------------------*/

char	*get_list(void);
DIR		*addvanced_opendir(void);
char	*parse_star(char *str);

/*------------------------------- CLEANING -------------------------------*/

void	clean(void);
void	free_cmd(void *cmd);
void	free_loop(char **args);
void	free_token(t_token *token);
void	cleaning(void);

/*------------------------------ EXECUTION -------------------------------*/

void	execution(void);
void	ft_child_process(t_cmd *cmd, int i, int last_fd);
void	run_cmd(t_cmd *cmd);

/*--------------------------- EXECUTION UTILS ----------------------------*/

char	**get_path(char **env);
void	*check_cmd(char **path, char *cmd);
void	redirect_input(void);
void	redirect_output(void);
void	open_outputs(void);
void	ft_dup(int olfd, int nfd);
void	failed_fork(void);
void	waiting(int i, pid_t pid);
void	next_cmd(int last_fd);

/*--------------------------- ERRORS FUNCTIONS ---------------------------*/

void	error_command_not_found(char *s, char *str, int status_code);
void	exit_strerr(char *str, int err, int exit_status);
void	error_msg(char *str, int err);
void	error_infile(void);

#endif