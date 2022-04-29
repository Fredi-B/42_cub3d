/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbechtol <fbechtol@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:21:05 by fbechtol          #+#    #+#             */
/*   Updated: 2021/07/21 15:14:58 by fbechtol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr_element;

	ptr_element = (t_list *)malloc(sizeof(t_list));
	if (ptr_element == NULL)
		return (NULL);
	ptr_element->content = content;
	ptr_element->next = NULL;
	return (ptr_element);
}
