/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 19:00:31 by jabae             #+#    #+#             */
/*   Updated: 2022/03/24 17:45:59 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h> //////////// ! 제출 전 빼기

//////////////////// % c s

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int ft_putstr_count(char *str)
{
	size_t	str_len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	str_len = ft_strlen(str);
	write(1, str, str_len);
	return (str_len);
}

int	ft_putchar_count(char c)
{
	write(1, &c, 1);
	return (1);
}

//////////////////// d i

void	ft_putnbr_fd(long long num, int fd)
{
	char	strnum;

	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
	}
	strnum = num % 10 + 48;
	write(fd, &strnum, 1);
}

int	ft_putint_count(long long num)
{
	int count;

	if (!num)
	{
		write(1, "0", 1);
		return (1);
	}
	ft_putnbr_fd(num, 1);
	count = 1;
	if (num < 0)
	{
		num *= -1;
		count++;
	}
	while (num / 10 > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

//////////////////// u

int	ft_putunsignedint_count(unsigned long long num)
{
	int count;

	ft_putnbr_fd(num, 1);
	count = 1;
	while (num / 10 > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

//////////////////// x X --------------> bus error

char	*ft_make_hex(char c)
{
	char	*hex_base;

	if (!hex_base)
		return (0);
	if (c == 'x')
		hex_base = "0123456789abcdef\0";
	else
		hex_base = "0123456789ABCDEF\0";
	return (hex_base);
}

int	ft_puthex_count(unsigned int num, char *hexbase)
{
	char	result[16];
	int		idx;
	int		count;

	if (!hexbase)
		return (-1);
	if (!num)
	{
		write(1, "0", 1);
		return(1);
	}
	idx = 0;
	while (num && idx < 16)
	{
		result[idx] = hexbase[num % 16];
		num /= 16;
		idx++;
	}
	count = idx;
	while (--idx >= 0)
		write(1, &result[idx], 1);
	return (count);
}

//////////////////// p

int	ft_putpointer_count(unsigned long long num, char *hexbase)
{
	char	result[16];
	int		idx;
	int		count;

	if (!hexbase)
		return (-1);
	if (!num)
	{
		write(1, "0x0", 3);
		return (3);
	}
	idx = 0;
	while (num && idx < 16)
	{
		result[idx] = hexbase[num % 16];
		num /= 16;
		idx++;
	}
	write (1, "0x", 2);
	count = idx + 2;
	while (--idx >= 0)
		write(1, &result[idx], 1);
	return (count);
}
