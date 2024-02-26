#include "libstrings.h"

long int	str_cmp(t_string one, t_string two)
{
	size_t	ione;
	size_t	itwo;

	if (!one || !one->data)
		return (0);
	if (!two || !two->data)
		return (0);
	ione = one->start;
	itwo = two->start;
	while (ione < one->end && itwo < two->end)
	{
		if (one->data[ione] != two->data[itwo])
			return (ione - one->start);
		ione++;
		itwo++;
	}
	if (one->data[ione] != two->data[itwo])
		return (ione - one->start);
	return (-1);
}

long int	p_str_cmp(t_string one, char *two)
{
	size_t	ione;
	size_t	itwo;

	if (!one || !one->data)
		return (0);
	ione = one->start;
	itwo = 0;
	while (ione < one->end && two[itwo] != 0)
	{
		if (one->data[ione] != two[itwo])
			return (ione - one->start);
		ione++;
		itwo++;
	}
	if (one->data[ione] != two[itwo])
		return (ione - one->start);
	return (-1);
}

long int	str_ncmp(t_string one, t_string two, size_t max)
{
	size_t	ione;
	size_t	itwo;

	if (!one || !one->data)
		return (0);
	if (!two || !two->data)
		return (0);
	ione = one->start;
	itwo = two->start;
	while (ione < one->end && itwo < two->end && ione - one->start < max)
	{
		if (one->data[ione] != two->data[itwo])
			return (ione - one->start);
		ione++;
		itwo++;
	}
	ione--;
	itwo--;
	if (one->data[ione] != two->data[itwo])
		return (ione - one->start);
	return (-1);
}

long int	p_str_ncmp(t_string one, char *two, size_t max)
{
	size_t	ione;
	size_t	itwo;

	if (!one || !one->data)
		return (0);
	ione = one->start;
	itwo = 0;
	while (ione < one->end && two[itwo] != 0 && itwo < max)
	{
		if (one->data[ione] != two[itwo])
			return (ione - one->start);
		ione++;
		itwo++;
	}
	ione--;
	itwo--;
	if (one->data[ione] != two[itwo])
		return (ione - one->start);
	return (-1);
}
long int	endswith(t_string this, t_string s_suffix, char *p_suffix)
{
	size_t	start;
	size_t	pos;
	size_t	len;

	start = this->start;
	if (s_suffix && s_suffix->data)
	{
		this->start = this->end - s_suffix->start;
		pos = str_cmp(this, s_suffix);
	}
	else if (p_suffix)
	{
		len = 0;
		while (p_suffix[len] != 0)
			len++;
		this->start = this->end - len;
		pos = p_str_cmp(this, p_suffix);
	}
	else
		pos = 0;
	this->start = start;
	return (pos);
}
