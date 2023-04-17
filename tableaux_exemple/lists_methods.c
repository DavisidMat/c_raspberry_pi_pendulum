#include "lists_methods.h"

int total_sum(int table[], int table_size)
{
    /*
    This function calculates the sum of all the elements of the static list.

    -----------
    Parameters:
    int table[]
        A table containing integers.
    int table_size
        The size (or number of elements) found in the table[] variable.

    --------
    Returns:
    int cumulation
        An integer containing the sum of all the elements found
    */

    int cumulation = 0;
    for (int i = 0; i < table_size; i++)
    {
        cumulation += table[i];
    }
    return cumulation;
}

float mean_table(int table[], int table_size)
{
    /*
    This function calculates the mean of all the elements found in the list.
    It requires the int total_sum(...) function.

    -----------
    Parameters:
    int table[]
        A table containing integers.
    int table_size
        The size (or number of elements) found in the table[] variable.

    --------
    Returns:
    float elements_mean
        A float containing the mean of all the elements found
    */
    int numerator = total_sum(table, table_size);
    int denominator = table_size;

    float elements_mean = (float) numerator / (float) denominator;
    return elements_mean;
}