#include "../../includes/minishell.h"

int	change_path(char *path, t_list *lst_env, t_list *lst_export)
{
	char *oldpwd;
	char *newpwd;
    char *tmp;
	int ret;

	tmp = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", tmp);
    free(tmp);
	ret = chdir(path);
	if (ret == 0)
	{
		export_to_list(oldpwd, lst_export, lst_env, 1);
		tmp = getcwd(NULL, 0);
		newpwd = ft_strjoin("PWD=", tmp);
		export_to_list(newpwd, lst_export, lst_env, 1);
		free(newpwd);
        free(tmp);
	}
	else if (ret == -1)
		printf("cd error\n");
	free(oldpwd);
	return (ret);
}

int change_home(t_list *lst_env, t_list *lst_export, char **path)
{
	int ret;

	ret = -1;
	if (!ft_check_if_exists(lst_env, "HOME"))
	{
		printf("home not set\n");
		return (ret);
	}
	else
	{
		*path = ft_strdup(ft_search_value(lst_env, "HOME"));
		ret = change_path(*path, lst_env, lst_export);
	}
	return (ret);
}

void builtin_cd(char **args,  t_list *lst_env, t_list *lst_export)
{
    int ret;
	char *path;

	ret = -1;
	path = NULL;
	if (args && args[1] && args[2])
	{
		printf("too many args\n");
		errno = -1; // handle this
	}
	if (!args || !args[1])
		errno = change_home(lst_env, lst_export, &path);
	else 
	{
		path = ft_strdup(args[1]);
		errno = change_path(path, lst_env, lst_export);
	}
	free(path);
}
