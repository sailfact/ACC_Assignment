#include "acc.h"

enum status {
    Read,
    Unread
};

struct mailbox_info {
    int             email_id;
    char            sender_name[20];
    int             time;
    enum status     status;
};

struct client {
    char            client_name[20];
    int             time_joined;
    char            ip_address[16];
    int             ip_port;
    int             email_counter;
};

struct client_list {
    struct client   client;
    struct client   *next_client;
};