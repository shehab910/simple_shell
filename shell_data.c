#include "shell.h"

/**
 * initShellData - Initializes a shell_data_dt struct
 * @data: A pointer to a shell_data_dt struct
 */
void initShellData(shell_data_dt *data)
{
    data->line = NULL;
    data->args = NULL;
    data->cmd = NULL;
    /* Initialize other members as needed */
}

/**
 * freeShellData - Frees a shell_data_dt struct
 * @data: A pointer to a shell_data_dt struct
 * Return: 0 on success
 */
int freeShellData(shell_data_dt *data)
{
    int i;

    if (data->line != NULL)
    {
        free(data->line);
        data->line = NULL;
    }
    if (data->args != NULL)
    {
        for (i = 0; data->args[i] != NULL; i++)
        {
            free((data->args)[i]);
            (data->args)[i] = NULL;
        }
        free(data->args);
        data->args = NULL;
    }
    if (data->cmd != NULL)
    {
        free(data->cmd);
        data->cmd = NULL;
    }
    /* free(data->cmd); */
    /* data->cmd = NULL; */
    /* free(data->error_msg); */
    /* data->error_msg = NULL; */
    return (0);
}