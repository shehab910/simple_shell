#include "shell.h"

/**
 * initShellData - Initializes a shell_data_dt struct
 * @data: A pointer to a shell_data_dt struct
 */
void initShellData(shell_data_dt *data)
{
    data->line = NULL;
    data->args = NULL;
    /* Initialize other members as needed */
}

/**
 * freeShellData - Frees a shell_data_dt struct
 * @data: A pointer to a shell_data_dt struct
 * Return: 0 on success
 */
int freeShellData(shell_data_dt *data)
{
    free(data->line);
    data->line = NULL;
    free(data->args);
    data->args = NULL;
    /* free(data->cmd); */
    /* data->cmd = NULL; */
    /* free(data->error_msg); */
    /* data->error_msg = NULL; */
    return (0);
}