#include "acc.h"
#include "clientlist.h"

static struct client_list *head = NULL;
static struct client_list *current = NULL;


int main(int argc, char const *argv[])
{
    struct client first, second, third;
    strcpy(first.client_name, "ross curley");
    first.time_joined = 900;
    strcpy(first.ip_address, "127.0.0.1");
    first.ip_port = 56000;
    first.email_counter = 0;

    strcpy(second.client_name, "liggy wiggy");
    second.time_joined = 800;
    strcpy(second.ip_address, "127.0.0.2");
    second.ip_port = 56030;
    second.email_counter = 0;

    strcpy(third.client_name, "misadobalina");
    third.time_joined = 1200;
    strcpy(third.ip_address, "127.0.0.3");
    third.ip_port = 56001;
    third.email_counter = 0;


    insertFirst(first);
    insertFirst(second);
    insertFirst(third);
    
    printList();
    
    return 0;
}
