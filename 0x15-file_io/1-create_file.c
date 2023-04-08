#include "main.h"

/**
 * create_file - Creates a file.
 * @filename: A pointer to the name of the file to create.
 * @text: A pointer to a string to write to the file.
 *
 * Return: If the function fails - -1.
 *         Otherwise - 1.
 */
int create_file(const char *filename, char *text)
{
    int file_descriptor, write_result, text_length = 0;

    if (filename == NULL)
        return (-1);

    if (text != NULL)
    {
        for (text_length = 0; text[text_length];)
            text_length++;
    }

    file_descriptor = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
    write_result = write(file_descriptor, text, text_length);

    if (file_descriptor == -1 || write_result == -1)
        return (-1);

    close(file_descriptor);

    return (1);
}
