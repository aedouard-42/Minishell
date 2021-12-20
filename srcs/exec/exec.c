#include "../../includes/minishell.h"

pipe_first(t_cmd *cmd)
{
	//cmd->fd[1] = dup(STDOUT_FILENO);
    dup2(cmd->fd[1], STDOUT_FILENO);
}

pipe_last(t_cmd *cmd , t_cmd *prev)
{
    dup2(prev->fd[0], STDIN_FILENO);
    dup2(STDOUT_FILENO, prev->fd[1]);
}

int pipe_cmd(t_cmd *cmd, t_cmd *prev_cmd, t_cmd *next_cmd)
{
    int type;

    type = cmd->type;
	//printf("type : %d\n", type);

	pipe(cmd->fd);
	if (prev_cmd == NULL)
	{
		printf("first pipe\n");
		//pipe_first(cmd);
	}
	if (next_cmd && prev_cmd != NULL)
		perror("mid pipe\n");
	if (next_cmd == NULL && prev_cmd != NULL)
		perror("last pipe");

	return (1);
}

int redir_cmd()
{

}

int execute_cmd(t_cmd *cmd,t_cmd *prev, t_cmd *next, char **envp)
{
	pid_t pid;
	int status;
	int type;
	int prev_type;

	type = cmd->type;
	if (prev != NULL)
		prev_type = prev->type;
	else
		prev_type = NOPIPE;
	pid = fork();
	if (pid == 0)
    {
        if (next != NULL)
            dup2(cmd->fd[1], STDOUT_FILENO);
        if (prev != NULL)
            dup2(prev->fd[0], STDIN_FILENO);
    	execve(cmd->args[0], cmd->args, envp);
        printf("execve failed for test : %s\n", cmd->args[0]);
        exit(1);
	}
	else
    {
        waitpid(pid, &status, 0);
        close(cmd->fd[1]);
        if (prev_type == PIPE)
		{
			
			close(prev->fd[0]);
		}
    }
}

int exec_cmd(t_cmd *cmd, t_cmd *prev_cmd, t_cmd *next_cmd, char **envp)
{

    
    pid_t pid;
    int status;

    pipe_cmd(cmd, prev_cmd, next_cmd);
    redir_cmd();
    execute_cmd(cmd, prev_cmd, next_cmd, envp);
    //open(STDOUT_FILENO, O_RDONLY);

    /*if (pid == 0)
    {
        if (type == NOPIPE)
        {
            printf("%s\n", content->args[0]);
            execve(content->args[0], content->args, envp);
            printf("execve failed for test : %s\n", content->args[0]);
            exit(1);
        }
        else if (type == FIRST_PIPE)
        {
            printf("%s\n", content->args[0]);
            close(fd[i * 2]);
            dup2(fd[(i * 2) + 1], STDOUT_FILENO);
            execve(content->args[0], content->args, envp);
            printf("execve failed for test : %s\n", content->args[0]);
            exit(1);
        }
        else if (type == MID_PIPE)
        {
            printf("%s\n", content->args[0]);
            dup2(fd[(i * 2) + 1], STDOUT_FILENO);
            dup2(fd[((i - 1) * 2)], STDIN_FILENO);
            execve(content->args[0], content->args, envp);
            printf("execve failed for test : %s\n", content->args[0]);
            exit(1);
        }
        else if (type == LAST_PIPE)
        {
            printf("%s\n", content->args[0]);
            close(fd[i * 2 + 1]);
            dup2(fd[(i  - 1) * 2], STDIN_FILENO);
            execve(content->args[0], content->args, envp);
            printf("execve failed for test : %s\n", content->args[0]);
            exit(1);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        if (type == FIRST_PIPE)
            close(fd[(i * 2) + 1]);
        else if (type == LAST_PIPE)
            close(fd[(i - 1) * 2]);
        else if (type == MID_PIPE)
        {
            close(fd[i * 2 + 1]);
            close(fd[(i - 1) * 2]);
        }
    }*/
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
        next = lst->next;
        exec_cmd(cmd, prev, next, envp);
		prev = lst->content;
        lst = lst->next;
    }
}

