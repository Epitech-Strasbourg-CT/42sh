/*
** job.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/parseur42
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Mon May 15 20:54:17 2017 Thibaut Cornolti
** Last update Thu May 18 10:27:57 2017 Thibaut Cornolti
*/

#include <unistd.h>
#include <signal.h>
#include "syntax.h"
#include "exec.h"
#include "my_printf.h"

void		signal_stp()
{
  t_job		*job;

  job = getter_status(NULL)->job_list;
  while (job)
    {
      if (job->status & JOB_FOREGROUND)
	{
	  job->status = JOB_SUSPENDED;
	  tcsetpgrp(0, getpgrp());
	  my_printf("Suspended\n");
	}
      job = job->next;
    }
}

static void	show_process(t_status *status)
{
  t_job		*job;
  int		last;

  job = status->job_list;
  last = 0;
  while (job)
    {
      if (job->step == 0)
	{
	  if (last != job->number)
	    {
	      my_printf((last) ? "\n[%d]" : "[%d]", job->number);
	      last = job->number;
	    }
	  my_printf(" %d", job->pid);
	  job->step = 1;
	}
      job = job->next;
    }
  my_printf("\n");
}

int		exec_job(t_node *root, t_status *status, t_info *info)
{
  int		first;

  first = 0;
  if ((status->status & JOBLINE) != JOBLINE)
    {
      first = 1;
      status->status |= JOBLINE;
      auto_wait(status, info);
    }
  status->status |= JOB;
  status->job_nbr = get_free_job(status->job_list);
  auto_select(root->left, status, info);
  show_process(status);
  status->status -= JOB;
  auto_select(root->right, status, info);
  if (first)
    status->status -= JOBLINE;
  return (0);
}