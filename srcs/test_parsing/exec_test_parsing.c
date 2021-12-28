#include "../../includes/minishell.h"

void    exec_tests(t_list **head, char **envp)
{
    t_cmd *cmd1;
    t_cmd *cmd2;
    t_cmd *cmd3;
    t_cmd *cmd4;

    t_list *link1;
    t_list *link2;
    t_list *link3;
    t_list *link4;

    t_redir *redir1;
    t_redir *redir2;
    t_redir *redir3;
    t_redir *redir4;

    redir1 = malloc(sizeof(t_redir));
    redir2 = malloc(sizeof(t_redir));
    redir3 = malloc(sizeof(t_redir));
    redir4 = malloc(sizeof(t_redir));

    redir1->type = REDIR_IN2;
    redir1->filename = ft_strdup("END");
    redir1->next = NULL;

    redir2->type = REDIR_OUT;
    redir2->filename = ft_strdup("redir2.test");
    redir2->next = NULL;

    redir3->type = REDIR_OUT;
    redir3->filename = ft_strdup("redir3.test");
    redir3->next = NULL;

    char **args1;
    char **args2;
    char **args3;
    char **args4;

    args1 = malloc(sizeof(char *) * 3);
    args2 = malloc(sizeof(char *) * 3);
    args3 = malloc(sizeof(char *) * 3);
    args4 = malloc(sizeof(char *) * 3);

    args1[0] = ft_strdup("/usr/bin/cat");
    args1[1] = ft_strdup("-e");
    args1[2] = NULL;

    args2[0] = ft_strdup("/usr/bin/cat");
    args2[1] = ft_strdup("-e");
    args2[2] = NULL;

    args3[0] = ft_strdup("/usr/bin/cat");
    args3[1] = ft_strdup("-e");
    args3[2] = NULL;

    args4[0] = ft_strdup("/usr/bin/cat");
    args4[1] = ft_strdup("-e");
    args4[2] = NULL;

    cmd1 = malloc(sizeof(t_cmd));
    cmd2 = malloc(sizeof(t_cmd));
    cmd3 = malloc(sizeof(t_cmd));
    cmd4 = malloc(sizeof(t_cmd));

    cmd1->args = args1;
    cmd1->type = PIPE;
    cmd1->redir = redir1;

    cmd2->args = args2;
    cmd2->type = PIPE;
    cmd2->redir = NULL;

    cmd3->args = args3;
    cmd3->type = PIPE;
    cmd3->redir = NULL;

    cmd4->args = args4;
    cmd4->type = PIPE;
    cmd4->redir = NULL;
    
    link1 = ft_lstnew(cmd1);
    link2 = ft_lstnew(cmd2);
    link3 = ft_lstnew(cmd3);
    link4 = ft_lstnew(cmd4);

    ft_lstadd_back(head, link1);
    //ft_lstadd_back(head, link2);
    //ft_lstadd_back(head, link3);
    //ft_lstadd_back(head, link4);
}