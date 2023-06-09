#ifndef STRUCTS_H
# define STRUCTS_H

/* Node to store the commands in a linked list */
typedef struct s_cmds
{
	char			*cmd;
	char			**args;
	char			**full_cmd;
	char			**from_file;
	char			**hdocs_end;
	char			**to_file;
	char			*priority;
	int				redirect;
	struct s_cmds	*next;
} t_cmds;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
} t_env;


typedef struct s_mVars
{
	t_env			*ls_env;
	t_env			*ls_export;
	t_env			*ls_buffer;
	char			*home;
	char			cwd[1000];
	int				**pipefd;
	int				*pids;
	int				check_oldpwd_path;
	int				check_pwd_path;
} t_mVars;
/* A global variable to store the term attributes and exit status */
typedef struct s_term
{
	struct termios	save_attr;
	int				status;
} t_term;

t_term	g_term_attr;

#endif
