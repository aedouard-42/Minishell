#include "../../includes/minishell.h"

int check_error_scope(int error)
{
    if (error < 0 || error > 255)
        return (error % 256);
    return (error);
}

void    ft_exit(t_list *lst_env, t_list *lst_export)
{
	ft_lstclear(&lst_env, &ft_free_content);
	ft_lstclear(&lst_export, &ft_free_content);
    exit(errno);
}
int	atoi_exit(const char *str)
{
	int	sign;
	int	i;
	int	returned_int;

	i = 0;
	returned_int = 0;
	sign = 1;
	while (ft_is_space(str[i]) && str[i])
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(str[i]) && (str[i]))
	{
		returned_int = returned_int * 10 + str[i] - '0';
		i++;
	}
    while (ft_is_space(str[i]) && str[i])
		i++;
    if (str[i] != '\0')
        return (-1);
	return (returned_int * sign);
}

int is_only_whitespace(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_is_space(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void    builtin_exit(char **args, t_list *lst_env, t_list *lst_export)
{
    printf ("exit\n");
    if (!args || !args[1])
        ft_exit(lst_env, lst_export);
    else if (args && args[1] && args[2])
    {
        printf("minishell: exit: too many arguments\n");
        errno = 1;
    }
    else if (args[1])
    {
        if (is_only_whitespace(args[1]))
            ft_exit(lst_env, lst_export);
        else
        {
            errno = atoi_exit(args[1]);
            if (errno == -1)
            {
                printf("minishell: exit: %s numeric argument required\n", args[1]);
                errno = 255;
            }
            else
                errno = check_error_scope(errno);
            ft_exit(lst_env, lst_export);
        }
    }
}