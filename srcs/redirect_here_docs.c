/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_here_docs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yueyama <yuuki.java@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:31:08 by yueyama           #+#    #+#             */
/*   Updated: 2022/10/23 16:07:33 by yueyama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

extern t_data	g_data;

void			set_signal_during_heredoc(void);

int	check_sig_regularly(void)
{
	if (g_data.run_handler == true)
		rl_done = 1;
	return (0);
}

// must null check
char	*add_read_text(char *input_texts, char *add_text)
{
	char	*tmp;

	tmp = ft_strjoin_null_allow(input_texts, add_text);
	free(input_texts);
	free(add_text);
	if (tmp == NULL)
		return (NULL);
	input_texts = tmp;
	tmp = ft_strjoin_null_allow(input_texts, "\n");
	free(input_texts);
	if (tmp == NULL)
		return (NULL);
	input_texts = tmp;
	return (input_texts);
}

bool	put_to_tmp(char *input_texts)
{
	int	fd;

	fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(MINISHELL);
		free(input_texts);
		close(fd);
		return (false);
	}
	if (input_texts)
	{
		if (write(fd, input_texts, ft_strlen(input_texts)) == -1)
		{
			perror(MINISHELL);
			close(fd);
			return (false);
		}
	}
	close(fd);
	free(input_texts);
	return (true);
}

char	*get_heredoc_text(char *eof)
{
	char	*read;
	char	*input_texts;

	input_texts = NULL;
	while (g_data.run_handler == false)
	{
		read = readline("> ");
		if (strequ(read, eof) || read == NULL)
		{
			free(read);
			break ;
		}
		input_texts = add_read_text(input_texts, read);
		if (input_texts == NULL)
			return (NULL);
	}
	return (input_texts);
}

bool	here_docs(char *eof, int *exit_code)
{
	char	*input_text;

	set_signal_during_heredoc();
	rl_event_hook = check_sig_regularly;
	input_text = get_heredoc_text(eof);
	if (g_data.run_handler == true)
		*exit_code = 1;
	rl_event_hook = NULL;
	if (input_text == NULL || g_data.run_handler == true)
		return (false);
	if (!put_to_tmp(input_text))
		return (false);
	return (redirect_from("/tmp/minishell"));
}
