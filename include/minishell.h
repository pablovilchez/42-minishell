/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:01:05 by gkrusta           #+#    #+#             */
/*   Updated: 2023/11/26 14:31:48 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700 // para compilar signals en linux

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/ioctl.h>

# include "../assets/libft/libft.h"
# include "minishell_structs.h"

extern int	g_shell_state;

// p_split.c
void	p_split(char *input, t_shell *shell);
char	**add_token(char **tokens, char *buff);
int		chk_end_token(char *input, int *i, int *start);
char	*read_token(char *input, int *i);
int		ft_isspace(char c);
// p_split_utils.c
int		redir_check(char *str, char *str_next);
int		assign_type(char c);
int		end_token(char c, int type, int *used);
void	free_tokens(t_shell *shell);
// b_export.c
void	export(t_shell *shell, char **args);
void	extract_values(char *arg, t_list *new_arg);
int		key_found(char *arg_key, char *env_key, int *found);
void	create_key(t_list *env_list, t_list *new_arg);
void	copy_value(t_list *env_list, t_list *new_arg);
// b_export_utils.c
void	free_arg(t_list *new_arg);
void	export_empty(t_shell *shell);
// b_export_utils_b.c
void	launch_key_error(t_shell *shell, char *cmd, t_list *arg);
int		check_key(t_list *arg, int print, t_shell *shell, char *cmd);
void	sort_array(char **str_array, int lst_size);
// b_unset.c
void	unset(t_shell *shell, char **args);
void	delete_value(t_shell *shell, int node_pos);
void	free_node(t_shell *shell, t_list *node);
// b_echo.c
int		echo(t_shell *shell, char **args);
// b_cd.c
void	cd(t_shell *shell, char *args);
void	parent_dir(t_shell *shell, char *args);
void	home_cd(t_shell *shell, char *path, char *args);
void	abs_path(t_shell *shell, char *path);
// b_cd_utils.c
void	free_args(char **args);
char	*get_value(t_shell *shell, char *key);
void	ft_export_pwds(t_shell *shell, char *old_dir, char *new_dir, char *arg);
// b_pwd.c
void	pwd(t_shell *shell);
// b_env
void	create_env_lst(t_shell *shell, char **envp);
void	print_env_variables(t_shell *shell, t_list *env);
void	free_params(t_shell *shell);
int		key_search(t_list *env, char *str);
t_list	*node_search(t_list *env, char *str);
// b_env_utils
char	*check_level(char *lvl);
void	update_level(t_shell *shell, int flag);
void	parse_env(t_shell *shell, char **envp);
char	*ft_strndup(const char *str, size_t len);
char	**ft_strddup(const char **envp);
// b_env_update.c
void	update_env(t_shell *shell);
char	**ft_stddup_env(t_shell *shell);
char	*concat_env(t_list *env_lst_cpy, char **env, int pos);
int		count_env_var(t_shell *shell);
/* b_exit.c */
int		ft_exit(t_shell *shell, long i, char *args);
int		various_args(t_shell *shell, char **args, long i);
void	exit_minishell(t_shell *shell, char **args);
// e_make_nodes.c
void	make_nodes(t_shell *shell, char *input);
int		is_argument(char *token);
void	add_argument(t_shell *shell, char *token, t_cmd *node);
void	clean_nodes_data(t_cmd **exec_nodes, char *input, t_shell *shell);
// e_make_nodes_utils.c
void	built_valid(t_cmd *node, t_shell *shell, int stdoutcpy, char *old_cmd);
int		is_built_in(char *token);
void	check_redir(t_cmd *node, int *i, t_shell *shell, int plus);
char	*str_change_value(char *old_str, char *new_str);
void	check_use_fd_in(t_cmd *new_node, t_shell *shell);
// e_make_nodes_utils_b.c
char	*convert_lowercase(char *token);
int		built_invalid(char *cmd_old, char *cmd_new);
void	put_token(t_shell *shell, int *i, t_cmd *node);
int		type_three(t_shell *shell, int *i);
// e_path_utils.c
void	free_path(char **str_list, char *empty_str);
char	*find_path(char *command, char **envp, char *empty_str);
int		is_in_path(t_shell *shell, char *str);
// e_nodes_utils.c
int		ft_tcmdsize(t_cmd *lst);
void	ft_add_front_node(t_cmd **lst, t_cmd *new_node);
t_cmd	*ft_add_back_node(t_cmd **lst, t_cmd *new_node);
void	lst_clear_nodes(t_cmd **lst);
t_cmd	*lst_new_node(void);
// e_execute_nodes.c
int		new_mini(t_cmd *node);
void	exec_comm(t_cmd *node, t_shell *shell, int cmd_count);
void	fork_child(t_cmd *node, t_shell *shell, int cmd_count);
int		run_node(t_cmd *node, t_shell *shell, int cmd_count);
void	execute_nodes(t_cmd **nodes, t_shell *shell);
// e_execute_nodes_utils.c
int		built_invalid(char *cmd_old, char *cmd_new);
void	exec_built(t_cmd *node, t_shell *shell, int stdoutcpy, int cmd_count);
int		check_absolut(t_cmd *node);
void	restore_std(int strincpy, int stdoutcpy);
void	cmd_error_msg(t_cmd *node, t_shell *shell, char *cmd);
// e_signals.c
void	signal_interactive(void);
void	is_sigint(int signal);
void	setup_signal_handling(void);
// e_end_child.c
void	end_child(void);
//void	signal_handler(int signal);
void	signal_interactive(void);
void	is_sigint(int signal);
void	setup_signal_handling(void);
// r_redir.c
void	token_pipe(t_cmd *node, int *fd, t_shell *shell);
void	token_input(char **tokens, int *i, t_cmd *node);
void	token_output(char **tokens, int *i, t_cmd *node);
void	token_output_cat(char **tokens, int *i, t_cmd *node);
// r_redir_heredoc.c
void	read_line_cleanup(char *line, int fd[2], t_cmd *node, int *i);
void	token_heredoc(char **tok, int *i, t_cmd *node);
// $
int		varible_search(t_list *env_lst, char **var, int flag);
char	*after_dolor_sign(t_shell *shell, char *str, int i);
char	*str_after_var(char *str, int pos);
void	ft_token_check(t_shell *shell, char *str, int i);
// p_trim.c
void	ft_trim_tokens(t_shell *shell);
int		syntax_check(char **tokens, t_shell *shell);
// p_trim_utils.c
int		empty_input(char *input);
char	*add_env_var(char *new_token, char *value);
void	*find_value(t_shell *shell, char *name);
char	*capture_key(char *c);
char	*find_var(t_shell *shell, char *c, char *new_token, int *j);

#endif