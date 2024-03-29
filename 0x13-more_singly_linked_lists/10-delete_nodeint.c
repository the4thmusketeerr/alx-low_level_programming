/**
 * delete_nodeint_at_index - deletes the node at index of a listint_t linked list
 * @head: pointer to the head of the linked list
 * @index: index of the node to be deleted
 *
 * Return: 1 if succeeded, -1 if failed
 */
int delete_nodeint_at_index(listint_t **head, unsigned int index)
{
    listint_t *current = *head, *previous = NULL;
    unsigned int i;

    if (*head == NULL)
        return (-1);
    
    if (index == 0)
    {
        *head = (*head)->next;
        free(current);
        return (1);
    }

    for (i = 0; current != NULL && i < index; i++)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return (-1);

    previous->next = current->next;
    free(current);

    return (1);
}
