/*
** unset.c for 42sh in /home/rectoria/delivery/Projets/PSU_2016_42sh/exec/builtin
** 
** Made by Bastien
** Login   <rectoria@epitech.net>
** 
** Started on  Thu May 18 19:10:23 2017 Bastien
** Last update Thu May 18 19:39:35 2017 Bastien
*/

#include "syntax.h"
#include "exec.h"

static void	remove_var(t_info *info, int j)
{
  int		size;
  t_var		temp;

  size = my_vartablen(info->var);
  while (++j < size)
    {
      temp.name = info->var[j].name;
      temp.value = info->var[j].value;
      info->var[j].name = info->var[j + 1].name;
      info->var[j].value = info->var[j + 1].value;
      info->var[j + 1].name = temp.name;
      info->var[j + 1].value = temp.value;
    }
  info->var = realloc(info->var, sizeof(t_var) * size);    
}

void	builtin_unset(t_command *cmd, t_status *status, t_info *info)
{
  int	i;
  int   j;

  i = 0;
  if (!info->var)
    return ;
  if (!cmd->argv[1])
    {
      printf("unset: Too few arguments.\n");
      return ;
    }
  while (cmd->argv[++i])
    {
      j = -1;
      while (info->var[++j].name && strcmp(info->var[j].name, cmd->argv[i]));
      if (info->var[j].name)
	remove_var(info, j - 1);
    }
  sort_var(info);
}
