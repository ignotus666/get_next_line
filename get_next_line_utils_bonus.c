/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhanlon <dhanlon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:22:35 by dhanlon           #+#    #+#             */
/*   Updated: 2025/10/10 16:28:52 by dhanlon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*mem_s;
	unsigned char	mem_c;
	int				i;

	if (!s)
		return (NULL);
	mem_s = (unsigned char *)s;
	mem_c = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (mem_s[i] == mem_c)
			return ((char *)&mem_s[i]);
		i++;
	}
	if (mem_s[i] == mem_c)
		return ((char *)&mem_s[i]);
	else
		return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		new_str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	new_str[ft_strlen(s1) + i] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dup_s;

	if (!s)
		return (NULL);
	dup_s = malloc(ft_strlen(s) + 1);
	if (!dup_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup_s[i] = s[i];
		i++;
	}
	dup_s[i] = '\0';
	return (dup_s);
}
