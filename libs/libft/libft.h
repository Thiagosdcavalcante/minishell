/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsantana <tsantana@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:12:18 by tsantana          #+#    #+#             */
/*   Updated: 2024/05/22 15:04:04 by tsantana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h> 
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	char			content;
	struct s_list	*next;
}	t_list;

typedef struct s_pf_list
{
	char				character;
	struct s_pf_list	*next;
}	t_pf_list;

size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *c);
t_list		*ft_lstnew(char content);
t_list		*ft_lstlast(t_list *lst);
t_pf_list	*pf_ft_lstnew(char content);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_atoi(const char *nptr);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_printf(const char *str, ...);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_tolower(int c);
int			ft_lstsize(t_list *lst);
int			ft_toupper(int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(char));
void		ft_lstclear(t_list **lst, void (*del)(char));
void		ft_lstiter(t_list *lst, void (*f)(char));
void		pf_ft_lstadd_back(t_pf_list **lst, t_pf_list *pf_new);
void		pf_ft_putnumb(unsigned long n, t_pf_list **list);
void		pf_ft_put_address(unsigned long int address, t_pf_list **list);
void		pf_str_to_list(char *src, t_pf_list **list);
void		pf_putnbr_convert(unsigned long int n,
				t_pf_list **list, char *hexas);

#endif
