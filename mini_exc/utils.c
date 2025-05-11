#include <../includes/minishell.h>

// void    free_things(char *one, char **two, char *msg, int check) // maight delet later
// {
//     if(check == 1)
//     {
//         struc()->index = 0;
//         while(two[struc()->index])
//         {
//             free(two[struc()->index]);
//             struc()->index++;
//         }
//         free(two);
//     }
//     else if(check == 2)
//     {
//         struc()->index = 0;
//         perror(msg);
//         while(two[struc()->index])
//         {
//             free(two[struc()->index]);
//             struc()->index++;
//         }
//         free(two);
//         free(one);
//     }
//     else
//         perror(msg);
//     exit(1);
// }

void	sort_tenv(char **env)
{
	char	*tmp;
	
	int (i), (u);
	i = 0;
	while (env[i])
	{
		u = i + 1;
		while(env[u])
		{
			if (ft_strcmp(env[u], env[i]) < 0)
			{
				tmp = env[u];
				env[u] = env[i];
				env[i] = tmp; 
			}
			u++;
		}
		i++;
	}
}

void	odup(char *file, int type, int is_input, int *fd)
{
	if (*fd != -1)
		close(*fd);

	if (is_input)
		*fd = open(file, O_RDONLY);
	else if (type == 2)
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);

	if (*fd == -1)
		perror("open");

	dup2(*fd, is_input ? STDIN_FILENO : STDOUT_FILENO);
}

void	redirect(t_data *cmd)
{
	int	index = 0;

	cmd->redirected_fd = -1;

	while (cmd->files.infile && cmd->files.infile[index])
		odup(cmd->files.infile[index++], 0, 1, &cmd->redirected_fd);

	index = 0;
	while (cmd->files.outfile && cmd->files.outfile[index])
	{
		odup(cmd->files.outfile[index], cmd->files.o_type[index], 0, &cmd->redirected_fd);
		index++;
	}
}


// void odup(char *file, int i, int check, int *fd) // maight need to use cmd->curr_pip/prev_pip instead for better fds managment
// {
// 	if(*fd)
// 		close(*fd);
// 	if (i == 3)
// 		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644); 
// 	else if (i == 2)
// 		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	else 
// 		*fd = open(file, O_CREAT | O_RDONLY);
// 	if (*fd == -1)
// 		perror("open outfile");
// 	if (!check)
// 		dup2(*fd, STDOUT_FILENO);
// 	else
// 		dup2(*fd, STDIN_FILENO); // input ..
// }

// // file write, file read; (-1)

// // 

// void	redirect(t_data *cmd) 
// {
// 	int	index;

// 	index = 0;
// 	while(cmd->files.infile && cmd->files.infile[index])
// 	{
// 		if (cmd->files.infile[index])
// 			odup(cmd->files.infile[index], 0, 1, &cmd->redirected_fd);
// 		index++;
// 	}
// 	index = 0;
// 	while(cmd->files.outfile && cmd->files.outfile[index])
// 	{
// 		if (cmd->files.outfile[index])
// 			odup(cmd->files.outfile[index], cmd->files.o_type[index], 0, &cmd->redirected_fd);
// 		index++;
// 	}
// }

void err(char *str) //check if a function like this already exist
{
	//free memory
	if(str)
		// call the garbage colecctor whenevr it's setted up
	perror(str);
	exit(EXIT_FAILURE);
}