#include "../../includes/minishell.h"
#include "../../libft/libft.h"

char *cat_elems(char *name, char *value)
{
    int l_name;
    int l_value;
    int tot;
    char *line;

    l_name = ft_strlen(name);
    l_value = ft_strlen(value);
    tot = l_name + l_value + 1;
    line = malloc(sizeof(char*) * tot);
    ft_strlcat(line, name, tot + 1);
    ft_strlcat(line, "=", tot + 1);
    ft_strlcat(line, value, tot + 1);
    return (line);
}

char **ft_convert(t_list *head)
{
    int lst_size;
    int i;
    t_list *lst;
    t_env_str *content;
    char **envp;

    lst = head;
    lst_size = ft_lstsize(head);
    i = 0;
    envp = (char**)ft_calloc(lst_size, sizeof(char*));
    while (i < lst_size)
    {
        content = (t_env_str *)lst->content;
        if (content->export == 1)
        {
            envp[i] = cat_elems(content->name, content->value);
            i++;
            lst = lst->next;
        }
    }
    envp[i] = NULL;
    return (envp);
}
