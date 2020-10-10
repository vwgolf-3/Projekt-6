/*
 * Lists.c
 *
 * Created: 06.10.2020 22:03:20
 *  Author: kimsc
 */
#include "Lists.h"


file_node_t* create_file_node(int file_nr, int * number)
{
    (*number)++;
    new_file_node = (file_node_t *)malloc(sizeof(file_node_t));
    new_file_node->file = file_nr;
    new_file_node->next = NULL;
    new_file_node->prev = NULL;
    return new_file_node;
}

void add_node(int file_nr, int ** number, file_node_t **first, file_node_t **last)
{
//     Uart_Transmit_IT_PC("Add node:");
//     char buff[5] = {'\0'};
//     itoa(file_nr, (char *)buff, 10);
//     Uart_Transmit_IT_PC((char *)buff);
//     Uart_Transmit_IT_PC("\r");

    new_file_node = create_file_node(file_nr, *number);

    if (*first == *last && *first == NULL)
    {
        *first = *last = new_file_node;

        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_file_node;
        new_file_node->prev = *last;
        *last = new_file_node;
        (*last)->next = *first;
        (*first)->prev = *last;
    }
}

void insert_at_first(char file_nr, int ** number, file_node_t ** first, file_node_t ** last)
{
    char itoa_buff[5] = {'\0'};
    char * ptr = itoa_buff;
    itoa(file_nr, ptr, 10);
    Uart_Transmit_IT_PC("Insert at first:");
    Uart_Transmit_IT_PC(ptr);
    Uart_Transmit_IT_PC("\r");

    new_file_node = create_file_node(file_nr, *number);

    if (*first == *last && *first == NULL)
    {

        Uart_Transmit_IT_PC("Init: Liste Leer: ");
        itoa(file_nr, ptr, 10);
        Uart_Transmit_IT_PC(ptr);
        Uart_Transmit_IT_PC("\r");
        *first = *last = new_file_node;

        (*first)->next = (*last)->next = NULL;

        (*first)->prev = (*last)->prev = NULL;

    }

    else

    {
        new_file_node->next = (*first);
        (*first)->prev = new_file_node;
        *first = new_file_node;
        (*first)->prev = *last;
        (*last)->next = *first;
//         Uart_Transmit_IT_PC("Zu Beginn eingefügt:");
//         itoa(file_nr, ptr, 10);
//         Uart_Transmit_IT_PC(ptr);
//         Uart_Transmit_IT_PC("\r");
    }
}

void insert_at_end(int file_nr, int ** number, file_node_t ** first, file_node_t ** last)
{
//     Uart_Transmit_IT_PC("Insert at end:");
//     char buff[5] = {'\0'};
//     itoa(file_nr, (char *)buff, 10);
//     Uart_Transmit_IT_PC((char *)buff);
//     Uart_Transmit_IT_PC("\r");

    new_file_node = create_file_node(file_nr, *number);

    if (*first == *last && *first == NULL)
    {

//         printf("\ninitially the list is empty and now new node is inserted but at first");

//         Uart_Transmit_IT_PC("Insert at first:");
//         char buff[5] = {'\0'};
//         itoa(file_nr, (char *)buff, 10);
//         Uart_Transmit_IT_PC((char *)buff);
//         Uart_Transmit_IT_PC("\r");

        (*first) = (*last) = new_file_node;
        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_file_node;
        new_file_node->prev = *last;
        (*last) = new_file_node;
        (*first)->prev = *last;
        (*last)->next = *first;
    }
}

void insert_at_position(int file_nr, int pos, int * number, file_node_t ** first, file_node_t ** last)
{
//     Uart_Transmit_IT_PC("Insert at position: Data, ");
//     char buff[5] = {'\0'};
//     itoa(file_nr, (char *)buff, 10);
//     Uart_Transmit_IT_PC((char *)buff);
//     Uart_Transmit_IT_PC("; Pos: ");
//     itoa(pos, (char *)buff, 10);
//     Uart_Transmit_IT_PC((char *)buff);
//     Uart_Transmit_IT_PC("\r");

    int i;

    file_node_t *prevnode;

    new_file_node = create_file_node(file_nr, number);

    if (*first == *last && *first == NULL)
    {
        if (pos == 1)
        {
            *first = *last = new_file_node;
            (*first)->next = (*last)->next = NULL;
            (*first)->prev = (*last)->prev = NULL;
        }
        else
        {
            Uart_Transmit_IT_PC("Leere Liste, Element kann nicht dort platziert werden.\r");
        }
    }
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Zu kurze Liste, Element kann nicht dort platziert werden.\r");
        else
        {
            for (ptr_file_node = *first, i = 1; i <= *number; i++)
            {
                prevnode = ptr_file_node;
                ptr_file_node = ptr_file_node->next;
                if (i == pos-1)
                {
                    prevnode->next = new_file_node;
                    new_file_node->prev = prevnode;
                    new_file_node->next = ptr_file_node;
                    ptr_file_node->prev = new_file_node;
                    Uart_Transmit_IT_PC("Element erfolgreich an Position eingefügt.\r");
                    break;
                }
            }
        }
    }
}

void sort_list(int * number, file_node_t ** first, file_node_t ** last)
{
    file_node_t *temp;
    int tempval, i, j;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, keine Elemente zu sortieren.\r");
    else
    {
        for (ptr_file_node = *first,i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
        {
            for (temp = ptr_file_node->next,j=i; j<*number; j++)
            {
                if (ptr_file_node->file > temp->file)
                {
                    tempval = ptr_file_node->file;
                    ptr_file_node->file = temp->file;
                    temp->file = tempval;
                }
            }
        }
        char buff[5] = {'\0'};
        for (ptr_file_node = *first, i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
        {
            itoa(i, (char *)buff, 10);
            Uart_Transmit_IT_PC("Val");
            Uart_Transmit_IT_PC((char *)buff);
            itoa(ptr_file_node->file, (char *)buff, 10);
            Uart_Transmit_IT_PC(": ");
            Uart_Transmit_IT_PC((char *)buff);
            Uart_Transmit_IT_PC("\r");
        }
    }
}

void delete_node_position(int pos, int * number, file_node_t ** first, file_node_t ** last)
{
    int  i;
    file_node_t *prevnode;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu löschen.\r");
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Position übertrifft Listenlänge, nicht gelöscht.\r");
        else
        {
            for (ptr_file_node = *first,i = 1; i <= *number; i++)
            {
                prevnode = ptr_file_node;
                ptr_file_node = ptr_file_node->next;
                if (pos == 1)
                {
                    (*number)--;
                    (*last)->next = prevnode->next;
                    ptr_file_node->prev = prevnode->prev;
                    *first = ptr_file_node;
                    Uart_Transmit_IT_PC("Element gelöscht.\r");
                    free(prevnode);
                    break;
                }
                else if (i == pos - 1)
                {
                    (*number)--;
                    prevnode->next = ptr_file_node->next;
                    ptr_file_node->next->prev = prevnode;
                    Uart_Transmit_IT_PC("Element gelöscht.\r");
                    free(ptr_file_node);
                    break;
                }
            }
        }
    }
}

void update(uint8_t pos, uint8_t newval, int * number, file_node_t ** first, file_node_t ** last)
{
    int i, f = 0;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente upzudaten.\r");
    else
    {
        for (ptr_file_node = *first, i = 0; i < pos; ptr_file_node = ptr_file_node->next,i++)
        {
                ptr_file_node->file = newval;
                Uart_Transmit_IT_PC("Element upgedated.\r");
                f = 1;
        }
        if (f == 0)
            Uart_Transmit_IT_PC("Kein solches Element gefunden.\r");
    }
}

void search(int key, int * number, file_node_t ** first, file_node_t ** last)
{
    int count = 0, i, f = 0;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu suchen.\r");
    else
    {
        for (ptr_file_node = *first,i = 0; i < *number; i++,ptr_file_node = ptr_file_node->next)
        {
            count++;
            if (ptr_file_node->file == key)
            {
                char buff[5] = {'\0'};
                itoa(i, (char *)buff, 10);
                Uart_Transmit_IT_PC("Val");
                Uart_Transmit_IT_PC((char *)buff);
                itoa(ptr_file_node->file, (char *)buff, 10);
                Uart_Transmit_IT_PC(": ");
                Uart_Transmit_IT_PC((char *)buff);
                Uart_Transmit_IT_PC("\r");
                f = 1;
            }
        }
        if (f == 0)
            Uart_Transmit_IT_PC("Wert nicht gefunden in Liste.\r");
    }
}

void display_from_beg(int * number, file_node_t ** first, file_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        Uart_Transmit_IT_PC("Die Werte sind:\r");
        for (ptr_file_node = *first, i = 0; i < *number; i++,ptr_file_node = ptr_file_node->next)
        {
            char buff[5] = {'\0'};
            itoa(ptr_file_node->file, (char *)buff, 10);
            Uart_Transmit_IT_PC((char *)buff);
            Uart_Transmit_IT_PC("\r");
        }
    }
}

void display_in_rev(int * number, file_node_t ** first, file_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        for (ptr_file_node = *last, i = 0; i < *number; i++,ptr_file_node = ptr_file_node->prev)
        {
            char buff[5] = {'\0'};
            itoa(ptr_file_node->file, (char *)buff, 10);
            Uart_Transmit_IT_PC((char *)buff);
            Uart_Transmit_IT_PC("\r");
        }
    }
}


zutat_maschine_node_t* create_zutat_maschine_node(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int * number)
{
    (*number)++;

    new_zutat_maschine_node = (zutat_maschine_node_t *)malloc(sizeof(zutat_maschine_node_t));
    new_zutat_maschine_node->name = calloc(21,sizeof(char));
    strcpy(new_zutat_maschine_node->name, name);
    new_zutat_maschine_node->status = status;
    new_zutat_maschine_node->stelle = k;
    new_zutat_maschine_node->position_motor = positon_motor;
    new_zutat_maschine_node->alkohol = alkohol;
    new_zutat_maschine_node->kohlensaeure = kohlensaeure;

    new_zutat_maschine_node->next = NULL;
    new_zutat_maschine_node->prev = NULL;

    return new_zutat_maschine_node;
}

void add_node_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int ** number, zutat_maschine_node_t **first, zutat_maschine_node_t **last)
{
    //     Uart_Transmit_IT_PC("Add Maschinen node: ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    new_zutat_maschine_node = create_zutat_maschine_node(name, status, alkohol, kohlensaeure, k, positon_motor, *number);

    if (*first == *last && *first == NULL)
    {
        *first = *last = new_zutat_maschine_node;

        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_zutat_maschine_node;
        new_zutat_maschine_node->prev = *last;
        *last = new_zutat_maschine_node;
        (*last)->next = *first;
        (*first)->prev = *last;
    }
}

void insert_at_first_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int ** number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    //     Uart_Transmit_IT_PC("Insert at first: ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    new_zutat_maschine_node = create_zutat_maschine_node(name, status, alkohol, kohlensaeure, k, positon_motor, *number);

    if (*first == *last && *first == NULL)
    {

        //         Uart_Transmit_IT_PC("Init: Liste Leer: ");
        //         Uart_Transmit_IT_PC(name);
        //         Uart_Transmit_IT_PC("\r");
        *first = *last = new_zutat_maschine_node;

        (*first)->next = (*last)->next = NULL;

        (*first)->prev = (*last)->prev = NULL;

    }

    else
    {
        new_zutat_maschine_node->next = (*first);
        (*first)->prev = new_zutat_maschine_node;
        *first = new_zutat_maschine_node;
        (*first)->prev = *last;
        (*last)->next = *first;
        //         Uart_Transmit_IT_PC("Zu Beginn eingefügt:");
        //         Uart_Transmit_IT_PC(name);
        //         Uart_Transmit_IT_PC("\r");
    }
}

void insert_at_end_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int ** number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    //     Uart_Transmit_IT_PC("Insert at end: ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    new_zutat_maschine_node = create_zutat_maschine_node(name, status, alkohol, kohlensaeure, k, positon_motor, *number);

    if (*first == *last && *first == NULL)
    {

        //         printf("\ninitially the list is empty and now new node is inserted but at first");

        //         Uart_Transmit_IT_PC("Insert at first:");
        //         Uart_Transmit_IT_PC(name);
        //         Uart_Transmit_IT_PC("\r");

        (*first) = (*last) = new_zutat_maschine_node;
        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_zutat_maschine_node;
        new_zutat_maschine_node->prev = *last;
        (*last) = new_zutat_maschine_node;
        (*first)->prev = *last;
        (*last)->next = *first;
    }
}

void insert_at_position_2(char * name, char status, uint8_t alkohol, uint8_t kohlensaeure, uint8_t k, uint32_t positon_motor, int pos, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    //     Uart_Transmit_IT_PC("Insert at position ");
    //     char buff[5] = {'\0'};
    //     itoa(pos, (char *)buff, 10);
    //     Uart_Transmit_IT_PC((char *)buff);
    //     Uart_Transmit_IT_PC(": ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    int i;

    zutat_maschine_node_t *prevnode;

    new_zutat_maschine_node = create_zutat_maschine_node(name, status, alkohol, kohlensaeure, k, positon_motor, number);

    if (*first == *last && *first == NULL)
    {
        if (pos == 1)
        {
            *first = *last = new_zutat_maschine_node;
            (*first)->next = (*last)->next = NULL;
            (*first)->prev = (*last)->prev = NULL;
        }
        else
        {
            Uart_Transmit_IT_PC("Leere Liste, Element kann nicht dort platziert werden.\r");
        }
    }
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Zu kurze Liste, Element kann nicht dort platziert werden.\r");
        else
        {
            for (ptr_zutat_maschine_node = *first, i = 1; i <= *number; i++)
            {
                prevnode = ptr_zutat_maschine_node;
                ptr_zutat_maschine_node = ptr_zutat_maschine_node->next;
                if (i == pos-1)
                {
                    prevnode->next = new_zutat_maschine_node;
                    new_zutat_maschine_node->prev = prevnode;
                    new_zutat_maschine_node->next = ptr_zutat_maschine_node;
                    ptr_zutat_maschine_node->prev = new_zutat_maschine_node;
                    Uart_Transmit_IT_PC("Element erfolgreich an Position eingefügt.\r");
                    break;
                }
            }
        }
    }
}

void sort_list_2(int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    //     zutat_maschine_node_t *temp;
    //     int tempval, i, j;
    //     if (*first == *last && *first == NULL)
    //         Uart_Transmit_IT_PC("Leere Liste, keine Elemente zu sortieren.\r");
    //     else
    //     {
    //         for (ptr_file_node = *first,i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
    //         {
    //             for (temp = ptr_file_node->next,j=i; j<*number; j++)
    //             {
    //                 if (ptr_file_node->file > temp->file)
    //                 {
    //                     tempval = ptr_file_node->file;
    //                     ptr_file_node->file = temp->file;
    //                     temp->file = tempval;
    //                 }
    //             }
    //         }
    //         char buff[5] = {'\0'};
    //         for (ptr_file_node = *first, i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
    //         {
    //             itoa(i, (char *)buff, 10);
    //             Uart_Transmit_IT_PC("Val");
    //             Uart_Transmit_IT_PC((char *)buff);
    //             itoa(ptr_file_node->file, (char *)buff, 10);
    //             Uart_Transmit_IT_PC(": ");
    //             Uart_Transmit_IT_PC((char *)buff);
    //             Uart_Transmit_IT_PC("\r");
    //         }
    //     }
}

void delete_node_position_2(int pos, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    int  i;
    zutat_maschine_node_t *prevnode;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu löschen.\r");
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Position übertrifft Listenlänge, nicht gelöscht.\r");
        else
        {
            for (ptr_zutat_maschine_node = *first,i = 1; i <= *number; i++)
            {
                prevnode = ptr_zutat_maschine_node;
                ptr_zutat_maschine_node = ptr_zutat_maschine_node->next;
                if (pos == 1)
                {
                    (*number)--;
                    (*last)->next = prevnode->next;
                    ptr_zutat_maschine_node->prev = prevnode->prev;
                    *first = ptr_zutat_maschine_node;
                    Uart_Transmit_IT_PC("Element gelöscht.\r");
                    free(prevnode);
                    break;
                }
                else if (i == pos - 1)
                {
                    (*number)--;
                    prevnode->next = ptr_zutat_maschine_node->next;
                    ptr_zutat_maschine_node->next->prev = prevnode;
                    Uart_Transmit_IT_PC("Element gelöscht.\r");
                    free(ptr_zutat_maschine_node);
                    break;
                }
            }
        }
    }
}

void update_2(int oldval, int newval, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    //     int i, f = 0;
    //
    //     if (*first == *last && *first == NULL)
    //         Uart_Transmit_IT_PC("Leere Liste, Keine Elemente upzudaten.\r");
    //     else
    //     {
    //         for (ptr_zutat_maschine_node = *first, i = 0; i < *number; ptr_zutat_maschine_node = ptr_zutat_maschine_node->next,i++)
    //         {
    //             if (ptr_zutat_maschine_node->file == oldval)
    //             {
    //                 ptr_zutat_maschine_node->file = newval;
    //                 Uart_Transmit_IT_PC("Element upgedated.\r");
    //                 f = 1;
    //             }
    //         }
    //         if (f == 0)
    //             Uart_Transmit_IT_PC("Kein solches Element gefunden.\r");
    //     }
}

void search_2(int key, int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    //     int count = 0, i, f = 0;
    //
    //     if (*first == *last && *first == NULL)
    //         Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu suchen.\r");
    //     else
    //     {
    //         for (ptr_zutat_maschine_node = *first,i = 0; i < *number; i++,ptr_zutat_maschine_node = ptr_zutat_maschine_node->next)
    //         {
    //             count++;
    //             if (ptr_zutat_maschine_node->file == key)
    //             {
    //                 char buff[5] = {'\0'};
    //                 itoa(i, (char *)buff, 10);
    //                 Uart_Transmit_IT_PC("Val");
    //                 Uart_Transmit_IT_PC((char *)buff);
    //                 itoa(ptr_zutat_maschine_node->file, (char *)buff, 10);
    //                 Uart_Transmit_IT_PC(": ");
    //                 Uart_Transmit_IT_PC((char *)buff);
    //                 Uart_Transmit_IT_PC("\r");
    //                 f = 1;
    //             }
    //         }
    //         if (f == 0)
    //             Uart_Transmit_IT_PC("Wert nicht gefunden in Liste.\r");
    //     }
}

void display_from_beg_2(int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        Uart_Transmit_IT_PC("Die File-Noden sind:\r");
        for (ptr_zutat_maschine_node = *first, i = 0; i < *number; i++,ptr_zutat_maschine_node = ptr_zutat_maschine_node->next)
        {
            Uart_Transmit_IT_PC(ptr_zutat_maschine_node->name);
            Uart_Transmit_IT_PC("\r");
        }
    }
}

void display_in_rev_2(int * number, zutat_maschine_node_t ** first, zutat_maschine_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        for (ptr_zutat_maschine_node = *last, i = 0; i < *number; i++,ptr_zutat_maschine_node = ptr_zutat_maschine_node->prev)
        {
            Uart_Transmit_IT_PC((char *)ptr_zutat_maschine_node->name);
            Uart_Transmit_IT_PC("\r");
        }
    }
}





file_list_node_t* create_list_node(file_node_t * node, int * number)
{
    (*number)++;

    new_list_node = (file_list_node_t *)malloc(sizeof(file_list_node_t));
    new_list_node->_file = node;
    new_list_node->next = NULL;
    new_list_node->prev = NULL;

    return new_list_node;
}

void add_node_3(file_node_t * node, int ** number, file_list_node_t **first, file_list_node_t **last)
{
    //     Uart_Transmit_IT_PC("Add Maschinen node: ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    new_list_node = create_list_node(node, *number);

    if (*first == *last && *first == NULL)
    {
        *first = *last = new_list_node;

        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_list_node;
        new_list_node->prev = *last;
        *last = new_list_node;
        (*last)->next = *first;
        (*first)->prev = *last;
    }
}

void insert_at_first_3(file_node_t * node, int ** number, file_list_node_t ** first, file_list_node_t ** last)
{
    Uart_Transmit_IT_PC("Insert at first: ");
    char buff[5] = {'\0'};
    itoa(node->file, (char *)buff, 10);
    Uart_Transmit_IT_PC((char *)buff);
    Uart_Transmit_IT_PC("\r");

    new_list_node = create_list_node(node, *number);

    if (*first == *last && *first == NULL)
    {

        Uart_Transmit_IT_PC("Init: Liste Leer: ");
        char buff[5] = {'\0'};
        itoa(node->file, (char *)buff, 10);
        Uart_Transmit_IT_PC((char *)buff);
        Uart_Transmit_IT_PC("\r");
        *first = *last = new_list_node;

        (*first)->next = (*last)->next = NULL;

        (*first)->prev = (*last)->prev = NULL;

    }

    else
    {
        new_list_node->next = (*first);
        (*first)->prev = new_list_node;
        *first = new_list_node;
        (*first)->prev = *last;
        (*last)->next = *first;
        //         Uart_Transmit_IT_PC("Zu Beginn eingefügt:");
        //         Uart_Transmit_IT_PC(name);
        //         Uart_Transmit_IT_PC("\r");
    }
}

void insert_at_end_3(file_node_t * node, int ** number, file_list_node_t ** first, file_list_node_t ** last)
{
//     Uart_Transmit_IT_PC("Insert at end: ");
//     char buff[5] = {'\0'};
//     itoa(node->file, (char *)buff, 10);
//     Uart_Transmit_IT_PC((char *)buff);
//     Uart_Transmit_IT_PC("\r");

    new_list_node = create_list_node(node, *number);
	
	

    if (*first == *last && *first == NULL)
    {

        //         printf("\ninitially the list is empty and now new node is inserted but at first");

//         Uart_Transmit_IT_PC("Insert at end:");
//         char buff[5] = {'\0'};
//         itoa(node->file, (char *)buff, 10);
//         Uart_Transmit_IT_PC((char *)buff);
//         Uart_Transmit_IT_PC("\r");

        (*first) = (*last) = new_list_node;
        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_list_node;
        new_list_node->prev = *last;
        (*last) = new_list_node;
        (*first)->prev = *last;
        (*last)->next = *first;
    }
}

void insert_at_position_3(file_node_t * node, int pos, int * number, file_list_node_t ** first, file_list_node_t ** last)
{
    //     Uart_Transmit_IT_PC("Insert at position ");
    //     char buff[5] = {'\0'};
    //     itoa(pos, (char *)buff, 10);
    //     Uart_Transmit_IT_PC((char *)buff);
    //     Uart_Transmit_IT_PC(": ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    int i;

    file_list_node_t *prevnode;

    new_list_node = create_list_node(node, number);

    if (*first == *last && *first == NULL)
    {
        if (pos == 1)
        {
            *first = *last = new_list_node;
            (*first)->next = (*last)->next = NULL;
            (*first)->prev = (*last)->prev = NULL;
        }
        else
        {
            Uart_Transmit_IT_PC("Leere Liste, Element kann nicht dort platziert werden.\r");
        }
    }
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Zu kurze Liste, Element kann nicht dort platziert werden.\r");
        else
        {
            for (ptr_list_node = *first, i = 1; i <= *number; i++)
            {
                prevnode = ptr_list_node;
                ptr_list_node = ptr_list_node->next;
                if (i == pos-1)
                {
                    prevnode->next = new_list_node;
                    new_list_node->prev = prevnode;
                    new_list_node->next = ptr_list_node;
                    ptr_list_node->prev = new_list_node;
                    Uart_Transmit_IT_PC("Element erfolgreich an Position eingefügt.\r");
                    break;
                }
            }
        }
    }
}

void sort_list_3(int * number, file_list_node_t ** first, file_list_node_t ** last)
{
    //     zutat_maschine_node_t *temp;
    //     int tempval, i, j;
    //     if (*first == *last && *first == NULL)
    //         Uart_Transmit_IT_PC("Leere Liste, keine Elemente zu sortieren.\r");
    //     else
    //     {
    //         for (ptr_file_node = *first,i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
    //         {
    //             for (temp = ptr_file_node->next,j=i; j<*number; j++)
    //             {
    //                 if (ptr_file_node->file > temp->file)
    //                 {
    //                     tempval = ptr_file_node->file;
    //                     ptr_file_node->file = temp->file;
    //                     temp->file = tempval;
    //                 }
    //             }
    //         }
    //         char buff[5] = {'\0'};
    //         for (ptr_file_node = *first, i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
    //         {
    //             itoa(i, (char *)buff, 10);
    //             Uart_Transmit_IT_PC("Val");
    //             Uart_Transmit_IT_PC((char *)buff);
    //             itoa(ptr_file_node->file, (char *)buff, 10);
    //             Uart_Transmit_IT_PC(": ");
    //             Uart_Transmit_IT_PC((char *)buff);
    //             Uart_Transmit_IT_PC("\r");
    //         }
    //     }
}

void delete_node_position_3(int pos, int * number, file_list_node_t ** first, file_list_node_t ** last)
{
    int  i;
    file_list_node_t * prevnode;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu löschen.\r");
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Position übertrifft Listenlänge, nicht gelöscht.\r");
        else
        {
            for (ptr_list_node = *first,i = 1; i <= *number; i++)
            {
                prevnode = ptr_list_node;
                ptr_list_node = ptr_list_node->next;
                if (pos == 1)
                {
                    (*number)--;
                    (*last)->next = prevnode->next;
                    ptr_list_node->prev = prevnode->prev;
                    *first = ptr_list_node;
                    Uart_Transmit_IT_PC("List Node für File gelöscht.\r");
                    free(prevnode);
                    break;
                }
                else if (i == pos - 1)
                {
                    (*number)--;
                    prevnode->next = ptr_list_node->next;
                    ptr_list_node->next->prev = prevnode;
                    Uart_Transmit_IT_PC("List Node für File gelöscht.\r");
                    free(ptr_list_node);
                    break;
                }
            }
        }
    }
}

void update_3(uint8_t pos, file_node_t * new_file_node, int * number, file_list_node_t ** first, file_list_node_t ** last)
{
    int i, f = 0;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente upzudaten.\r");
    else
    {
        for (ptr_list_node = *first, i = 0; i < pos; ptr_list_node = ptr_list_node->next,i++)
        {
                ptr_list_node->_file = new_file_node;
                Uart_Transmit_IT_PC("Element upgedated.\r");
                f = 1;
        }
        if (f == 0)
            Uart_Transmit_IT_PC("Kein solches Element gefunden.\r");
    }
}

void search_3(int key, int * number, file_list_node_t ** first, file_list_node_t ** last)
{
    //     int count = 0, i, f = 0;
    //
    //     if (*first == *last && *first == NULL)
    //         Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu suchen.\r");
    //     else
    //     {
    //         for (ptr_list_node = *first,i = 0; i < *number; i++,ptr_list_node = ptr_list_node->next)
    //         {
    //             count++;
    //             if (ptr_list_node->file == key)
    //             {
    //                 char buff[5] = {'\0'};
    //                 itoa(i, (char *)buff, 10);
    //                 Uart_Transmit_IT_PC("Val");
    //                 Uart_Transmit_IT_PC((char *)buff);
    //                 itoa(ptr_list_node->file, (char *)buff, 10);
    //                 Uart_Transmit_IT_PC(": ");
    //                 Uart_Transmit_IT_PC((char *)buff);
    //                 Uart_Transmit_IT_PC("\r");
    //                 f = 1;
    //             }
    //         }
    //         if (f == 0)
    //             Uart_Transmit_IT_PC("Wert nicht gefunden in Liste.\r");
    //     }
}

void display_from_beg_3(int * number, file_list_node_t ** first, file_list_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        Uart_Transmit_IT_PC("Die List-Noden für die Getraenke sind:\r");
        for (ptr_list_node = *first, i = 0; i < *number; i++,ptr_list_node = ptr_list_node->next)
        {
            char buff[5] = {'\0'};
            itoa(ptr_list_node->_file->file, (char *)buff, 10);
            Uart_Transmit_IT_PC((char *)buff);
            Uart_Transmit_IT_PC("\r");
        }
    }
}

void display_in_rev_3(int * number, file_list_node_t ** first, file_list_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        for (ptr_list_node = *last, i = 0; i < *number; i++,ptr_list_node = ptr_list_node->prev)
        {
            char buff[5] = {'\0'};
            itoa(ptr_list_node->_file->file, (char *)buff, 10);
            Uart_Transmit_IT_PC((char *)buff);
            Uart_Transmit_IT_PC("\r");
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

zutat_maschine_list_node_t* create_zutat_maschine_list_node(zutat_maschine_node_t * node, int * number)
{
    (*number)++;

    new_zutat_maschine_list_node = (zutat_maschine_list_node_t *)malloc(sizeof(zutat_maschine_list_node_t));
    new_zutat_maschine_list_node->zutat_maschine = node;
    new_zutat_maschine_list_node->next = NULL;
    new_zutat_maschine_list_node->prev = NULL;

    return new_zutat_maschine_list_node;
}

void add_node_4(zutat_maschine_node_t * node, int ** number, zutat_maschine_list_node_t **first, zutat_maschine_list_node_t **last)
{
    //     Uart_Transmit_IT_PC("Add Maschinen node: ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    new_zutat_maschine_list_node = create_zutat_maschine_list_node(node, *number);

    if (*first == *last && *first == NULL)
    {
        *first = *last = new_zutat_maschine_list_node;

        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_zutat_maschine_list_node;
        new_zutat_maschine_list_node->prev = *last;
        *last = new_zutat_maschine_list_node;
        (*last)->next = *first;
        (*first)->prev = *last;
    }
}

void insert_at_first_4(zutat_maschine_node_t * node, int ** number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    //     Uart_Transmit_IT_PC("Insert at first: ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    new_zutat_maschine_list_node = create_zutat_maschine_list_node(node, *number);

    if (*first == *last && *first == NULL)
    {

        //         Uart_Transmit_IT_PC("Init: Liste Leer: ");
        //         Uart_Transmit_IT_PC(name);
        //         Uart_Transmit_IT_PC("\r");
        *first = *last = new_zutat_maschine_list_node;

        (*first)->next = (*last)->next = NULL;

        (*first)->prev = (*last)->prev = NULL;

    }

    else
    {
        new_zutat_maschine_list_node->next = (*first);
        (*first)->prev = new_zutat_maschine_list_node;
        *first = new_zutat_maschine_list_node;
        (*first)->prev = *last;
        (*last)->next = *first;
        //         Uart_Transmit_IT_PC("Zu Beginn eingefügt:");
        //         Uart_Transmit_IT_PC(name);
        //         Uart_Transmit_IT_PC("\r");
    }
}

void insert_at_end_4(zutat_maschine_node_t * node, int ** number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    //     Uart_Transmit_IT_PC("Insert at end: ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    new_zutat_maschine_list_node = create_zutat_maschine_list_node(node, *number);

    if (*first == *last && *first == NULL)
    {

        //         printf("\ninitially the list is empty and now new node is inserted but at first");

        //         Uart_Transmit_IT_PC("Insert at first:");
        //         Uart_Transmit_IT_PC(name);
        //         Uart_Transmit_IT_PC("\r");

        (*first) = (*last) = new_zutat_maschine_list_node;
        (*first)->next = (*last)->next = NULL;
        (*first)->prev = (*last)->prev = NULL;
    }
    else
    {
        (*last)->next = new_zutat_maschine_list_node;
        new_zutat_maschine_list_node->prev = *last;
        (*last) = new_zutat_maschine_list_node;
        (*first)->prev = *last;
        (*last)->next = *first;
    }
}

void insert_at_position_4(zutat_maschine_node_t * node, int pos, int * number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    //     Uart_Transmit_IT_PC("Insert at position ");
    //     char buff[5] = {'\0'};
    //     itoa(pos, (char *)buff, 10);
    //     Uart_Transmit_IT_PC((char *)buff);
    //     Uart_Transmit_IT_PC(": ");
    //     Uart_Transmit_IT_PC(name);
    //     Uart_Transmit_IT_PC("\r");

    int i;

    zutat_maschine_list_node_t *prevnode;

    new_zutat_maschine_list_node = create_zutat_maschine_list_node(node, number);

    if (*first == *last && *first == NULL)
    {
        if (pos == 1)
        {
            *first = *last = new_zutat_maschine_list_node;
            (*first)->next = (*last)->next = NULL;
            (*first)->prev = (*last)->prev = NULL;
        }
        else
        {
            Uart_Transmit_IT_PC("Leere Liste, Element kann nicht dort platziert werden.\r");
        }
    }
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Zu kurze Liste, Element kann nicht dort platziert werden.\r");
        else
        {
            for (ptr_zutat_maschine_list_node = *first, i = 1; i <= *number; i++)
            {
                prevnode = ptr_zutat_maschine_list_node;
                ptr_zutat_maschine_list_node = ptr_zutat_maschine_list_node->next;
                if (i == pos-1)
                {
                    prevnode->next = new_zutat_maschine_list_node;
                    new_zutat_maschine_list_node->prev = prevnode;
                    new_zutat_maschine_list_node->next = ptr_zutat_maschine_list_node;
                    ptr_zutat_maschine_list_node->prev = new_zutat_maschine_list_node;
                    Uart_Transmit_IT_PC("Element erfolgreich an Position eingefügt.\r");
                    break;
                }
            }
        }
    }
}

void sort_list_4(int * number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    //     zutat_maschine_node_t *temp;
    //     int tempval, i, j;
    //     if (*first == *last && *first == NULL)
    //         Uart_Transmit_IT_PC("Leere Liste, keine Elemente zu sortieren.\r");
    //     else
    //     {
    //         for (ptr_file_node = *first,i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
    //         {
    //             for (temp = ptr_file_node->next,j=i; j<*number; j++)
    //             {
    //                 if (ptr_file_node->file > temp->file)
    //                 {
    //                     tempval = ptr_file_node->file;
    //                     ptr_file_node->file = temp->file;
    //                     temp->file = tempval;
    //                 }
    //             }
    //         }
    //         char buff[5] = {'\0'};
    //         for (ptr_file_node = *first, i = 0; i < *number; ptr_file_node = ptr_file_node->next,i++)
    //         {
    //             itoa(i, (char *)buff, 10);
    //             Uart_Transmit_IT_PC("Val");
    //             Uart_Transmit_IT_PC((char *)buff);
    //             itoa(ptr_file_node->file, (char *)buff, 10);
    //             Uart_Transmit_IT_PC(": ");
    //             Uart_Transmit_IT_PC((char *)buff);
    //             Uart_Transmit_IT_PC("\r");
    //         }
    //     }
}

void delete_node_position_4(int pos, int * number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    int  i;
    zutat_maschine_list_node_t *prevnode;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu löschen.\r");
    else
    {
        if (*number < pos)
            Uart_Transmit_IT_PC("Position übertrifft Listenlänge, nicht gelöscht.\r");
        else
        {
            for (ptr_zutat_maschine_list_node = *first,i = 1; i <= *number; i++)
            {
                prevnode = ptr_zutat_maschine_list_node;
                ptr_zutat_maschine_list_node = ptr_zutat_maschine_list_node->next;
                if (pos == 1)
                {
                    (*number)--;
                    (*last)->next = prevnode->next;
                    ptr_zutat_maschine_list_node->prev = prevnode->prev;
                    *first = ptr_zutat_maschine_list_node;
                    Uart_Transmit_IT_PC("List Node Zutat Maschine gelöscht.\r");
                    free(prevnode);
                    break;
                }
                else if (i == pos - 1)
                {
                    (*number)--;
                    prevnode->next = ptr_zutat_maschine_list_node->next;
                    ptr_zutat_maschine_list_node->next->prev = prevnode;
                    Uart_Transmit_IT_PC("List Node Zutat Maschine gelöscht.\r");
                    free(ptr_zutat_maschine_list_node);
                    break;
                }
            }
        }
    }
}

void update_4(uint8_t pos, zutat_maschine_node_t * new_file_node, int * number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    int i, f = 0;

    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Leere Liste, Keine Elemente upzudaten.\r");
    else
    {
        for (ptr_zutat_maschine_list_node = *first, i = 0; i < pos; ptr_zutat_maschine_list_node = ptr_zutat_maschine_list_node->next,i++)
        {
			ptr_zutat_maschine_list_node->zutat_maschine = new_file_node;
			Uart_Transmit_IT_PC("Element upgedated.\r");
			f = 1;
        }
        if (f == 0)
            Uart_Transmit_IT_PC("Kein solches Element gefunden.\r");
    }
}

void search_4(int key, int * number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    //     int count = 0, i, f = 0;
    //
    //     if (*first == *last && *first == NULL)
    //         Uart_Transmit_IT_PC("Leere Liste, Keine Elemente zu suchen.\r");
    //     else
    //     {
    //         for (ptr_zutat_maschine_list_node = *first,i = 0; i < *number; i++,ptr_zutat_maschine_list_node = ptr_zutat_maschine_list_node->next)
    //         {
    //             count++;
    //             if (ptr_zutat_maschine_list_node->file == key)
    //             {
    //                 char buff[5] = {'\0'};
    //                 itoa(i, (char *)buff, 10);
    //                 Uart_Transmit_IT_PC("Val");
    //                 Uart_Transmit_IT_PC((char *)buff);
    //                 itoa(ptr_zutat_maschine_list_node->file, (char *)buff, 10);
    //                 Uart_Transmit_IT_PC(": ");
    //                 Uart_Transmit_IT_PC((char *)buff);
    //                 Uart_Transmit_IT_PC("\r");
    //                 f = 1;
    //             }
    //         }
    //         if (f == 0)
    //             Uart_Transmit_IT_PC("Wert nicht gefunden in Liste.\r");
    //     }
}

void display_from_beg_4(int * number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        Uart_Transmit_IT_PC("Die List-Noden für die Zutaten maschine sind:\r");
        for (ptr_zutat_maschine_list_node = *first, i = 0; i < *number; i++,ptr_zutat_maschine_list_node = ptr_zutat_maschine_list_node->next)
        {
            Uart_Transmit_IT_PC(ptr_zutat_maschine_list_node->zutat_maschine->name);
            Uart_Transmit_IT_PC("\r");
        }
    }
}

void display_in_rev_4(int * number, zutat_maschine_list_node_t ** first, zutat_maschine_list_node_t ** last)
{
    int i;
    if (*first == *last && *first == NULL)
        Uart_Transmit_IT_PC("Liste leer, keine Elemente anzuzeigen.\r");
    else
    {
        for (ptr_zutat_maschine_list_node = *last, i = 0; i < *number; i++,ptr_zutat_maschine_list_node = ptr_zutat_maschine_list_node->prev)
        {
            Uart_Transmit_IT_PC(ptr_zutat_maschine_list_node->zutat_maschine->name);
            Uart_Transmit_IT_PC("\r");
        }
    }
}


