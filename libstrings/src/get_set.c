# include "libstrings.h"

char    get(t_string this, size_t index)
{
    if (this->start + index > this->end)
        return ('\0');
    else
        return (this->data[this->start + index]);
}

char   set(t_string this, size_t index, char value)
{
    if (this->start + index > this->end)
        return ('\0');
    else
    {
        this->data[this->start + index] = value; 
        return (this->data[this->start + index]);
    }
}