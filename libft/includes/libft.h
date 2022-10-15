/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteillet <eteillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 16:00:51 by eteillet          #+#    #+#             */
/*   Updated: 2021/04/21 10:55:07 by eteillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "get_next_line.h"

/*
** Define the structure called t_list, for ft_lst* function.
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char				*add_c_to_str(char *old, char c);
char				**add_str_to_beginning_array(char *to_add, char **array);
char				**add_str_to_end_array(char **array, char *to_add);
int					is_last_char_in_str(char *str, int i, char c);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
char				*ft_itoa(int n);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_memalloc(size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				ft_memdel(void **to_free);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *pointer, int value, size_t n);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
char				**ft_split(char *s, char c);
int					split_count(char **array);
void				free_split(char **split);
char				**ft_split_set(char *s, char *set);
char				*ft_strcat(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strcpy(char *dest, char *src);
void				ft_strdel(char **to_free);
char				*ft_strdup(const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoindel(char *s1, char *s2);
char				*ft_strjoindelone(char *s1, const char *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *str1, const char *str2, size_t num);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *str, const char *to_find,
						size_t len);
char				*ft_strreplace(char *s1, char *s2);
char				*ft_strrchr(const char *s, int c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);

#endif
