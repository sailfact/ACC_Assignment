#include "acc.h"

struct client {
    char            client_name[20];    /* name of client */
    struct tm       *time_joined;       /* time client joined */
    char            ip_address[16];     /* IP address of the client */
    int             ip_port;            /* IP port number of the client */
    int             email_counter;      /* number of emails */
};

struct client_list {
    struct client           client;
    struct client_list      *next_client;
};

static struct client_list *head = NULL;

void getList(char *line);

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
struct client_list* deleteEntry(struct client entry);

//delete a link with given name
struct client_list* deleteName(char *name);