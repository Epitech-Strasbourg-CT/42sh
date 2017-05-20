/*
** fct_history.c for 42sh in /home/thibrex/Dropbox/delivery/PSU/PSU_2016_42sh/history
** 
** Made by Thibaut Cornolti
** Login   <thibaut.cornolti@epitech.eu>
** 
** Started on  Sat May 20 15:39:02 2017 Thibaut Cornolti
** Last update Sat May 20 16:43:29 2017 Cédric THOMAS
*/

#include <termio.h>
#include <stdlib.h>
#include "syntax.h"
#include "exec.h"
#include "my.h"
#include "get_next_command.h"

char	*history_fct_exclam(char *src, int idx, t_history_info *history)
{
  if (history->end == NULL || history->end->cmd == NULL)
    return (src);
  if ((src = delete_nbchar(src, 2, idx)) == NULL)
    exit(84);
  if ((src = insert_str(src, history->end->cmd, idx, 0)) == NULL)
    exit(84);
  return (src);
}

char	*history_fct_dollar(char *src, int idx, t_history_info *history)
{
  if (delete_nbchar(src, 1, idx) == NULL ||
      insert_str(src, history->end->cmd, idx, 0) == NULL)
    exit(84);  
  return (src);
}

char	*history_fct_colon(char *src, int idx, t_history_info *history)
{
  if (delete_nbchar(src, 1, idx) == NULL ||
      insert_str(src, history->end->cmd, idx, 0) == NULL)
    exit(84);
  return (src);
}

char	*history_fct_dash(char *src, int idx, t_history_info *history)
{
  if (delete_nbchar(src, 1, idx) == NULL ||
      insert_str(src, history->end->cmd, idx, 0) == NULL)
    exit(84);
  return (src);
}

char	*history_fct_number(char *src, int idx, t_history_info *history)
{
  if (delete_nbchar(src, 1, idx) == NULL ||
      insert_str(src, history->end->cmd, idx, 0) == NULL)
    exit(84);
  return (src);
}
