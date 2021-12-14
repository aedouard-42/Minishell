#include "../../includes/minishell.h"

int exec_cmd(t_cmd *content, int *fd, int i, int size_lst, char **envp)
{
    pid_t pid;
    int type = content->pipe_type;

    pipe(&(fd[i * 2]));
    fork();

    if (pid == 0)
    {
        if (type == NOPIPE)
        {
            printf("%s\n", content->args[0]);

            execve(content->args[0], content->args, envp);

            exit(1);
        }
    }
    else
    {

    }
    return (1);
}

int exec_cmds(t_list *lst_cmd, char **envp)
{
    int *fd;
    int i;
    int size_lst;

    size_lst = ft_lstsize(lst_cmd);

    *fd = malloc(sizeof(*fd) * 2 * size_lst);
    i = 0;
    while (lst_cmd)
    {
        exec_cmd(lst_cmd->content, fd, i, size_lst, envp);
        i++;
        lst_cmd = lst_cmd->next;
    }
}