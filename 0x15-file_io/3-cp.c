#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *allocate_buffer(char *filename);
void close_descriptor(int descriptor);

/**
 * allocate_buffer - Allocates 1024 bytes for a buffer.
 * @filename: The name of the file buffer is storing chars for.
 *
 * Return: A pointer to the newly-allocated buffer.
 */
char *allocate_buffer(char *filename)
{
    char *buffer;

    buffer = malloc(sizeof(char) * 1024);

    if (buffer == NULL)
    {
        dprintf(STDERR_FILENO,
                "Error: Can't write to %s\n", filename);
        exit(99);
    }

    return (buffer);
}

/**
 * close_descriptor - Closes file descriptors.
 * @descriptor: The file descriptor to be closed.
 */
void close_descriptor(int descriptor)
{
    int status;

    status = close(descriptor);

    if (status == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", descriptor);
        exit(100);
    }
}

/**
 * main - Copies the contents of a file to another file.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: 0 on success.
 *
 * Description: If the argument count is incorrect - exit code 97.
 *              If file_from does not exist or cannot be read - exit code 98.
 *              If file_to cannot be created or written to - exit code 99.
 *              If file_to or file_from cannot be closed - exit code 100.
 */
int main(int argc, char *argv[])
{
    int source_fd, dest_fd, read_result, write_result;
    char *buffer;

    if (argc != 3)
    {
        dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
        exit(97);
    }

    buffer = allocate_buffer(argv[2]);
    source_fd = open(argv[1], O_RDONLY);
    read_result = read(source_fd, buffer, 1024);
    dest_fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

    do
    {
        if (source_fd == -1 || read_result == -1)
        {
            dprintf(STDERR_FILENO,
                    "Error: Can't read from file %s\n", argv[1]);
            free(buffer);
            exit(98);
        }

        write_result = write(dest_fd, buffer, read_result);
        if (dest_fd == -1 || write_result == -1)
        {
            dprintf(STDERR_FILENO,
                    "Error: Can't write to %s\n", argv[2]);
            free(buffer);
            exit(99);
        }

        read_result = read(source_fd, buffer, 1024);
        dest_fd = open(argv[2], O_WRONLY | O_APPEND);

    } while (read_result > 0);

    free(buffer);
    close_descriptor(source_fd);
    close_descriptor(dest_fd);

    return (0);
}
