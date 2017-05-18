/*
** list_status.c for status in /home/cedric/delivery/PSU/PSU_2016_minishell2
** 
** Made by Cédric Thomas
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Apr  5 15:59:59 2017 Cédric Thomas
** Last update Thu May 18 18:56:29 2017 Thibaut Cornolti
*/
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

t_exit		*my_put_list_exit(t_exit **ll, int pid, int pgid, int last)
{
  t_exit	*tmp;
  t_exit	*elem;

  tmp = *ll;
  if ((elem = malloc(sizeof(*elem))) == NULL)
    exit(84);
  elem->pid = pid;
  elem->pgid = pgid;
  elem->exit = last;
  elem->next = NULL;
  elem->prev = *ll;
  if (tmp == NULL)
    {
      elem->prev = NULL;
      *ll = elem;
    }
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      elem->prev = tmp;
      tmp->next = elem;
    }
  return (elem);
}

int		my_del_exit(t_exit **ll)
{
  t_exit	*tmp;

  while (*ll)
    {
      tmp = *ll;
      *ll = (*ll)->next;
      free(tmp);
    }
  return (0);
}

void	show_exit_status(t_exit *ll)
{
  while (ll)
    {
      if (WIFSIGNALED(ll->exit))
	my_printf("exit error : %d, ", ll->exit);
      if (WIFEXITED(ll->exit))
	my_printf("exit : %d, ", WEXITSTATUS(ll->exit));
      my_printf("pid : %d\n", ll->pid);
      ll = ll->next;
    }
}

void	set_exit_value(t_exit *ll, int pid, int exitval)
{
  while (ll)
    {
      if (ll->pid == pid)
	ll->exit = exitval;
      ll = ll->next;
    }
}
