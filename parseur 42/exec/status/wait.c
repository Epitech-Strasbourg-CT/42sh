/*
** fork.c for fork in /home/cedric/delivery/PSU/PSU_2016_42sh/parseur 42/exec
** 
** Made by Cédric THOMAS
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue May  9 20:20:52 2017 
** Last update Tue May  9 21:00:44 2017 
*/
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"

static void    check_sig(int status)
{
  int   dump;

  dump = 0;
  if (WTERMSIG(status) == SIGSEGV && (dump = 1))
    my_puterror("Segmentation fault");
  if (WTERMSIG(status) == SIGFPE && (dump = 1))
    my_puterror("Floating exception");
  if (WTERMSIG(status) == SIGABRT && (dump = 1))
    my_puterror("Aborted");
  if (WTERMSIG(status) == SIGBUS && (dump = 1))
    my_puterror("Bus error");
  if (dump && WCOREDUMP(status))
    my_puterror(" (core dumped)");
  if (dump)
    my_puterror("\n");
}

static void	get_exit_value(t_status *status, t_info *info)
{
  int		last;
  t_exit	*tmp;

  tmp = status->exit_list;
  while (tmp)
    {
      if (WIFSIGNALED(tmp->exit))
	check_sig(tmp->exit);
      if (tmp->exit)
	{
	  last = tmp->exit;
	  if (tmp->pid < 0)
	    info->exit_value = last;
	  else if (WIFEXITED(last))
	    info->exit_value = WEXITSTATUS(last);
	  else if (WIFSIGNALED(last))
	    info->exit_value = last % 128 + 128;
	}
      tmp = tmp->next;
    }
}

void		auto_wait(t_status *status, t_info *info)
{
  t_exit	*tmp;
  int		pid;
  int		last;

  tmp = status->exit_list;
  while (tmp)
    {
      pid = wait(&last);
      set_exit_value(status->exit_list, pid, last);
      tmp = tmp->next;
    }
  get_exit_value(status, info);
  my_del_exit(&(status->exit_list));
}