#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	if (len > n)
		len = n;
	dup = (char *) malloc(len + 1);
	if (dup == NULL)
		return NULL;
	dup[len] = '\0';
	return ((char *) ft_memcpy(dup, s, len));
}