#include "../../includes/minishell.h"

void    exec_tests(t_list **head, char **envp)
{
    t_cmd *cmd1;
    t_cmd *cmd2;
    t_cmd *cmd3;

    t_list *link1;
    t_list *link2;
    t_list *link3;

    char **args1;
    char **args2;
    char **args3;

    args1 = malloc(sizeof(char *) * 3);
    args2 = malloc(sizeof(char *) * 3);
    args3 = malloc(sizeof(char *) * 3);

    args1[0] = ft_strdup("/usr/bin/cat");
    args1[1] = ft_strdup("toto.c");
    args1[2] = NULL;


    args2[0] = ft_strdup("/usr/bin/grep");
    args2[1] = ft_strdup("bonjour");
    args2[2] = NULL;

    args3[0] = ft_strdup("/usr/bin/wc");
    args3[1] = ft_strdup("-l");
    args3[2] = NULL;

    cmd1 = malloc(sizeof(t_cmd));
    cmd2 = malloc(sizeof(t_cmd));
    cmd3 = malloc(sizeof(t_cmd));

    cmd1->args = args1;
    cmd1->pipe_type = FIRST_PIPE;

    cmd2->args = args2;
    cmd2->pipe_type = MID_PIPE;

    cmd3->args = args3;
    cmd3->pipe_type = LAST_PIPE;
    
    link1 = ft_lstnew(cmd1);
    link2 = ft_lstnew(cmd2);
    link3 = ft_lstnew(cmd3);


    ft_lstadd_back(head, link1);
    ft_lstadd_back(head, link2);
    ft_lstadd_back(head, link3);
}