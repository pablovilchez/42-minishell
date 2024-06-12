/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:28:18 by gkrusta           #+#    #+#             */
/*   Updated: 2023/10/13 13:11:43 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*substr;

	size = ft_strlen(s);
	if (size < start)
		return (ft_strdup(""));
	if (size - start < len)
		len = size - start;
	substr = (char *)malloc((sizeof(char)) * (len + 1));
	if (!substr)
		return (0);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

/* #include <stdio.h>
int	main(void)
{
	char			str[] = "penguinclub";
	unsigned int	start;
	unsigned int	len;

	start = 1;
	len = 3;
	printf("result: %s", ft_substr(str, start, len));
	return (0);
} */