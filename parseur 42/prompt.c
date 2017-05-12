/*
** main.c for main.c in /home/cedric/delivery/ex
**
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
**
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Fri May 12 14:40:07 2017 maje
*/
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "my.h"
#include "get_next_line.h"
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

/* static void	search_git(char *info) */
/* { */
/*   int		i; */

/*   i = -1; */
/*   (void)info; */
/* } */

static void	git(char *info)
{
  DIR		*dir;
  //  int		i;
  struct dirent *dirent;
  //  char		*new;

  //  i = my_strlen(info);
  if ((dir = opendir(info)) == NULL)
    return ;
  while ((dirent = readdir(dir)) != NULL)
    {
      if (my_strcmp(".git", dirent->d_name) == 0)
	my_printf("\033[34;01m git:(master)\033[00m");
      /* else */
      /*   { */
      /*   git(new); */
      /*   } */
    }
  closedir(dir);
}

static void	extract(t_info *info)
{
  char		*home;
  int		i;

  i = my_strlen(info->pwd);
  home = getkey(info->env, "HOME", 0);
  if (home && !my_strcmp(info->pwd, home))
    my_printf("\033[36;01m~\033[00m");
  else
    {
      while (i > 0 && info->pwd[i] != '/')
	i -= 1;
      if (i != 0)
	i += 1;
      my_printf("\033[36;01m%s\033[00m", info->pwd + i);
    }
}

void	print_prompt(t_info *info)
{
  if ((info->exit_value) != 0)
    my_printf("\033[31;01m");
  else
    my_printf("\033[32;01m");
  my_printf("➜  \033[00m");
  extract(info);
  git(info->pwd);
  my_printf(" ");
}
