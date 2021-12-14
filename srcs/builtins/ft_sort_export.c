#include "../../includes/minishell.h"

int compare_data(t_list *a, t_list *b)
{
    t_env_str *env_a;
    t_env_str *env_b;
    int len_a;
    int len_b;

    env_a = (t_env_str *)a->content;
    env_b = (t_env_str *)b->content;
    len_a = ft_strlen(env_a->name);
    len_b = ft_strlen(env_b->name);
    if (len_b < len_a)
        len_a = len_b;
    if (ft_strncmp (env_a->name, env_b->name, len_a) > 0)
        return (1);
    return (0);
}

void lst_swap(t_list *a, t_list *b)
{
    t_env_str *tmp;

    tmp = a->content;
    a->content = b->content;
    b->content = tmp;
}

void    ft_sort_export(t_list *lst)
{
    int swap;
    t_list *lsthead;

    lsthead = lst;
    swap = 1;
    while (swap)
    {
        swap = 0;
        while (lst->next)
        {
            if (compare_data(lst, lst->next))
            {
                lst_swap(lst, lst->next);
                swap = 1;
            }
            lst = lst->next;
        }
        lst = lsthead;
    }
}
