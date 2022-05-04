#include "libft.h"

int	ft_find_substr(const char *string, const char *sub) {
	int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	if (!string || !sub)
		return (-1);
	while (string[i + ft_strlen(sub) - 1]) {
		j = 0;
		while (sub[j]) {
			if (string[i + j] != sub[j])
				break;
			j++;
			if (sub[j] == 0)
				flag = 1;
		}
		if (flag == 1)
			break;
		i++;
	}
	if (!flag)
		return (-1);
	return (i);
}
