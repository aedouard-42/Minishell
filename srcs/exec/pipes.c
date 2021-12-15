#include "../../includes/minishell.h"

int exec_cmd(t_cmd *content, int *fd, int i, int size_lst, char **envp)
{
    pid_t pid;
    int type = content->pipe_type;
    int status;

    pipe(&fd[i * 2]);
    pid = fork();
    if (pid == 0)
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
    }
    return (1);
}

int exec_cmds(t_list *lst_cmd, char **envp)
{
    int *fd;
    int i;
    int size_lst;

    size_lst = ft_lstsize(lst_cmd);

    fd = malloc(sizeof((*fd) * 2 * size_lst));
    i = 0;
    while (lst_cmd)
    {
        exec_cmd(lst_cmd->content, fd, i, size_lst, envp);
        i++;
        lst_cmd = lst_cmd->next;
    }
}