#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <linux/limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libft/libft.h"

enum tokens
{
    STR,   // str
    IN,         // <
    OUT,        // >
    APPEND,     // >>
    HEREDOC,    // <<
    PIPE,       // |
    END,        // ; (end of command)
};

typedef struct s_node
{
    char *content;
    struct s_node *next;
}   t_node;

typedef struct s_pair
{
    char *key;
    char *value;
    struct s_pair *next;
}   t_pair;

typedef struct s_data
{
    char *name;
    int stdin;
    int stdout;
    int stderr;
    t_pair *env;
    t_pair *exported_vars;
    char **path;
    char cwd[PATH_MAX];
}   t_data;

typedef struct s_arg
{
    char    *token;
    int     type;
    struct s_arg *next;
}   t_arg;

typedef struct s_command_list
{
    char *exec_path;
    struct s_arg *arg;
    int stdin;
    int stdout;
    int in_fd;
    int out_fd;
    struct s_command_list *next;
}   t_command_list;

int create_executor(char *command);
void sigint_handler(int signal);
int exec(char **str);
int	cd(t_data *data, char *str);
int	expand_path(char *str, char *buf);
int env(t_pair *env, t_pair *exported_vars, char *str);
int export(t_pair *env, t_pair *exported_vars, char **str);
int	unset(t_data *data, char **str);
int pwd(void);
t_pair *get_env(char **envp);
void cleanup(t_data *data);
int echo(char *str);
int get_length_to_char(char *str, char c);
void free_nodes(t_node *node);
void print_nodes(t_node *node);
void print_pairs(t_pair *pair);
void print_exported(t_node *node);
void free_pairs(t_pair *pair);
void	sort_list(t_pair *export);
int	print_syntax_error(char c);
int	print_file_error(char *s1, char *s2);
int	token_error(char *str);
int	check_unclosed(char *str);
char    *treat_str(char *line);

#endif