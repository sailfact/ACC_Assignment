#ifndef CLIENT_LIST_H
#define CLIENT_LIST_H
#include "acc.h"

struct client {
    char            client_name[20];    /* name of client */
    int             time_joined;        /* time client joined */
    char            ip_address[16];     /* IP address of the client */
    int             ip_port;            /* IP port number of the client */
    int             email_counter;      /* number of emails */
};

struct client_list {
    struct client   client;
    struct client_list   *next_client;
};

void printList();

//insert link at the first location
void insertFirst(struct client data);

//delete first item
struct client_list* deleteFirst();

//is list empty
int isEmpty();

int length();

//find a link with given entry
struct client_list* find(struct client entry);

//delete a link with given entry
struct client_list* delete(struct client entry);
#endif