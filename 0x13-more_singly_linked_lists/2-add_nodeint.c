/**
 * add_nodeint - Adds a new node at the beginning of a listint_t list
 * @head: Pointer to the head node of the list
 * @n: Value to be added to the new node
 *
 * Return: Address of the new element, or NULL if it failed
 */
listint_t *add_nodeint(listint_t **head, int n)
{
    listint_t *new_node;

    new_node = malloc(sizeof(listint_t)); // allocate memory for new node
    if (new_node == NULL) // check if allocation was successful
        return (NULL);

    new_node->n = n; // set the value of the new node
    new_node->next = *head; // set the new node to point to the head of the list

    *head = new_node; // set the head of the list to point to the new node

    return (new_node); // return the address of the new node
}
