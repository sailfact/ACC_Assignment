#include "clientlist.h"

//display the list
void getList(char *line) 
{
    struct client_list  *ptr = head;
    char                buffer[MAXLINE];
    //start from the beginning
    while(ptr != NULL) 
    {
        snprintf(buffer, sizeof(buffer), "[name = %s | time = %s | addr = %s | port = %d | email count = %d]\n", 
        ptr->client.client_name, 
        asctime(ptr->client.time_joined), 
        ptr->client.ip_address, 
        ptr->client.ip_port, 
        ptr->client.email_counter);
        strncat(line, buffer, sizeof(buffer));
        // todo add string cat
        
        ptr = ptr->next_client;
    }
}

//insert link at the first location
void insertFirst(struct client data) 
{
    //create a link
    struct client_list *link = (struct client_list*) malloc(sizeof(struct client_list));
        
    link->client = data;
        
    //point it to old first struct client_list
    link->next_client = head;
        
    //point first to new first struct client_list
    head = link;
}

//delete first item
struct client_list* deleteFirst() 
{
    //save reference to first link
    struct client_list *tempLink = head;
        
    //mark next_client to first link as first 
    head = head->next_client;
        
    //return the deleted link
    return tempLink;
}

//is list empty
int isEmpty() 
{
    return head == NULL;
}

int length() 
{
    int length = 0;
    struct client_list *current;
        
    for(current = head; current != NULL; current = current->next_client)
        length++;
        
    return length;
}

//find a link with given entry
struct client_list* find(struct client entry) 
{
    //start from the first link
    struct client_list* current = head;

    //if list is empty
    if(head == NULL) 
        return NULL;

    //navigate through list
    while(!strcmp(current->client.client_name,entry.client_name)) 
    {
        //if it is last struct client_list
        if(current->next_client == NULL) 
            return NULL;
        else //go to next_client link
            current = current->next_client;
    }      
        
    //if data found, return the current Link
    return current;
}

//delete a link with given entry
struct client_list* deleteEntry(struct client entry) 
{
    //start from the first link
    struct client_list* current = head;
    struct client_list* previous = NULL;
        
    //if list is empty
    if(head == NULL) 
        return NULL;

    //navigate through list
    while(!strcmp(current->client.client_name,entry.client_name)) 
    {
        //if it is last struct client_list
        if(current->next_client == NULL) 
            return NULL;
        else 
        {
            //store reference to current link
            previous = current;
            //move to next_client link
            current = current->next_client;
        }
    }

    //found a match, update the link
    if(current == head)     //change first to point to next_client link
        head = head->next_client;
    else //bypass the current link
        previous->next_client = current->next_client;  
	
    return current;
}

//delete a link with given name
struct client_list* deleteName(char *name) 
{
    //start from the first link
    struct client_list* current = head;
    struct client_list* previous = NULL;
        
    //if list is empty
    if(head == NULL) 
        return NULL;

    //navigate through list
    while(!strcmp(current->client.client_name, name)) 
    {
        //if it is last struct client_list
        if(current->next_client == NULL) 
            return NULL;
        else 
        {
            //store reference to current link
            previous = current;
            //move to next_client link
            current = current->next_client;
        }
    }

    //found a match, update the link
    if(current == head)     //change first to point to next_client link
        head = head->next_client;
    else //bypass the current link
        previous->next_client = current->next_client;  
	
    return current;
}