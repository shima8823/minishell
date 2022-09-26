/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shima <shima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:43:24 by shima             #+#    #+#             */
/*   Updated: 2022/05/04 07:42:11 by shima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*tmp;

	if (!(*f))
		return (NULL);
	begin = NULL;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			ft_lstclear(&begin, (*del));
			return (NULL);
		}
		ft_lstadd_back(&begin, tmp);
		lst = lst->next;
	}
	return (begin);
}
