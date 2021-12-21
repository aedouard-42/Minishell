#include "../../includes/minishell.h"

int redirect(t_cmd * cmd)
{
    t_redir *redir;
    int fd_out;
    int fd_in;

    redir = cmd->redir;
    if (cmd->redir == NULL)
        return (1);
    while (redir)
    {
        if (redir->type == REDIR_OUT)
        {
            fd_out = open(redir->filename, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
            dup2(fd_out, STDOUT_FILENO);
        }
        else if (redir->type == REDIR_IN)
        {
            fd_in = open(redir->filename, O_RDWR , S_IRWXU);
            if (fd_in == -1)
            {
                perror("Minishell");
                // need to free something? maybe close fds
                exit(0);
            }
        
            dup2(fd_in, STDIN_FILENO);
        }
        else if (redir ->type == REDIR_OUT2)
        {
            fd_out = open(redir->filename, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
            dup2(fd_out, STDOUT_FILENO);
        }
        else if (redir->type == REDIR_IN2)
        {

        }
        redir = redir->next;
    }
    return (1);
}

int execute_cmd(t_cmd *cmd,t_cmd *prev, t_cmd *next, char **envp)
{
	pid_t pid;
	int status;

    if (next != NULL)
        dup2(cmd->fd[1], STDOUT_FILENO);
    if (prev != NULL)
        dup2(prev->fd[0], STDIN_FILENO);
    redirect(cmd);
    execve(cmd->args[0], cmd->args, envp);
    printf("execve failed for test : %s\n", cmd->args[0]);
    exit(1);
    return (1);
}

int exec_cmd(t_cmd *cmd, t_cmd *prev, t_cmd *next_cmd, char **envp)
{
    pid_t pid;
    int status;

    pipe(cmd->fd);
    pid = fork();
    if (pid == 0)
        execute_cmd(cmd, prev, next_cmd, envp);
    else
    {
        waitpid(pid, &status, 0);
        close(cmd->fd[1]);
        if (prev && prev->type  == PIPE)
			close(prev->fd[0]);
    }
    return (1);
}

int exec_cmds(t_list *lst, char **envp)
{
    int *fd;
	t_cmd *prev;
    t_cmd *next;
    t_cmd *cmd;

	prev = NULL;
    next = NULL;
    while (lst)
    {
        cmd = lst->content;
        next = (t_cmd *)lst->next;
        exec_cmd(cmd, prev, next, envp);
		prev = lst->content;
        lst = lst->next;
    }
    return (1);
}

