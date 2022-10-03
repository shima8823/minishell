/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:50:14 by shima             #+#    #+#             */
/*   Updated: 2022/10/02 13:16:26 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

int	get_char_type(int c);

t_token	*lstnew(size_t data_size, int type);

t_lexer	*lexer(char *line)
{
	size_t	line_size;
	t_lexer	*lexer;
	t_token	*lst;
	size_t	i;
	size_t	j;
	int		state;
	int		c_type;
	
	lexer = malloc(sizeof(t_lexer));
	lexer->n_tokens = 0;
	line_size = ft_strlen(line);
	lexer->list_tokens = lstnew(line_size, 0);
	lst = lexer->list_tokens;
	i = 0;
	j = 0;
	state = STATE_GENERAL;
	while (line[i])
	{
		c_type = get_char_type(line[i]);
		if (state == STATE_GENERAL)
		{
			if (c_type == CHAR_QUOTE)
			{
				state = STATE_IN_QUOTE;
				lst->data[j++] = CHAR_QUOTE;
				lst->type = TOKEN;
			}
			else if (c_type == CHAR_DQUOTE)
			{
				state = STATE_IN_DQUOTE;
				lst->data[j++] = CHAR_DQUOTE;
				lst->type = TOKEN;
			}
			else if (c_type == CHAR_GENERAL)
			{
				lst->data[j++] = line[i];
				lst->type = TOKEN;
			}
			else if (c_type == CHAR_WHITESPACE)
			{
				if (j > 0)
				{
					lst->data[j] = '\0';
					while (line[i + 1] == ' ')
						i++;
					if (line[i + 1] == '\0')
						return (lexer);
					lst->next = lstnew(line_size - i, 0);
					lst = lst->next;
					j = 0;
				}
			}
			else if (c_type == CHAR_PIPE)
			{
				// 現在のdataを終わらせる
				if (j > 0)
				{
					lst->data[j] = '\0';
					if (line[i + 1] == '\0')
						return (lexer);
					lst->next = lstnew(line_size - i, 0);
					lst = lst->next;
					j = 0;
				}
				// 代入
				lst->data[0] = c_type;
				lst->data[1] = '\0';
				lst->type = c_type;
				// 次
				lst->next = lstnew(line_size - i, 0);
				lst = lst->next;
			}
			else if (c_type == CHAR_GREATER || c_type == CHAR_LESSER)
			{
				// 現在のdataを終わらせる
				if (j > 0)
				{
					lst->data[j] = '\0';
					if (line[i + 1] == '\0')
						return (lexer);
					lst->next = lstnew(line_size - i, 0);
					lst = lst->next;
					j = 0;
				}
				// 代入
				lst->data[j++] = c_type;
				if (line[i + 1] == c_type)
				{
					lst->data[j++] = c_type;
					i++;
				}
				lst->data[j] = '\0';
				lst->type = c_type;
				j = 0;
				// 次
				lst->next = lstnew(line_size - i, 0);
				lst = lst->next;
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			lst->data[j++] = line[i];
			if (c_type == CHAR_DQUOTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE)
		{
			lst->data[j++] = line[i];
			if (c_type == CHAR_QUOTE)
				state = STATE_GENERAL;
		}
		i++;
	}
	lst->data[j] = '\0';

	return (lexer);
}

int	get_char_type(c)
{
	if (c == CHAR_PIPE
		|| c == CHAR_QUOTE
		|| c == CHAR_DQUOTE
		|| c == CHAR_WHITESPACE
		|| c == CHAR_GREATER
		|| c == CHAR_LESSER
		|| c == CHAR_NULL)
		return (c);
	else
		return (CHAR_GENERAL);
}

t_token	*lstnew(size_t data_size, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new->data = malloc(data_size);
	if (!new->data)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new->type = type;
	new->next = NULL;
	return (new);
}