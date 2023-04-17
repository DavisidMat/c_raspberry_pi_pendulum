#include <stdio.h>
#include <stdlib.h>
#include "lists_methods.h"

int main(int argc, char *argv[])
{
    int table[] = {3,5,8,8,9};
    int table_size = 5;
    for (int i = 0; i < table_size; i++)
    {
        printf("Position: %d -> Value: %d\n", i + 1, table[i]);
    }

    int sum_elements = total_sum(table, table_size);
    printf("The total sum is %d\n", sum_elements);

    float mean_elements = mean_table(table, table_size);
    printf("The mean of all the elements is %f\n",mean_elements);

    return 0;
}

// gcc main.c lists_methods.c -o main_tables.exe
// ./main_tables.exe