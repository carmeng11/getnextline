#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>


int	ft_printf(char const *format, ...);
int	ft_putchar(int c);


#endif