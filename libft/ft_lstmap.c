/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 17:16:41 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/21 15:13:51 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_element;

	new_lst = 0;
	while (lst)
	{
		new_element = ft_lstnew(f(lst->content));
		if (new_element == NULL)
			ft_lstclear(&new_lst, del);
		else
			ft_lstadd_back(&new_lst, new_element);
		lst = lst->next;
	}
	return (new_lst);
}
