// #ifndef EVENT_QUEUE_C_
// #define EVENT_QUEUE_C_

#include <core/event_queue.h>

sss_node* QUEUE_HEAD;


int sss_init_queue() {
    QUEUE_HEAD = NULL;
    return 1;
}

int sss_poll_event(sss_event* event) {
    if(QUEUE_HEAD == NULL)
        return 0;

    *event = QUEUE_HEAD->evt;
    sss_node* temp = QUEUE_HEAD;
    QUEUE_HEAD = temp->next;
    free(temp);
    temp = NULL;

    return 1;
}

int sss_enque_event(sss_event event) {

    if(QUEUE_HEAD == NULL) {
        sss_node* t = (sss_node*)malloc(sizeof(sss_node));

        if(t == 0)
            return 0;

        t->next = NULL;
        t->evt = event;
        QUEUE_HEAD = t;
    } else {

        sss_node* temp = QUEUE_HEAD;
        sss_node* new_node = (sss_node*)malloc(sizeof(sss_node));
        new_node->evt = event;
        new_node->next = NULL;
        while(temp != NULL && temp->next != NULL) 
            temp = temp->next;
        temp->next = new_node;

    }

    return 1;
}

sss_node sss_parse_event(const char* command) {
   sss_node result;

   return result;
}

void sss_debug_queue() {
    sss_node* temp;
    for(temp = QUEUE_HEAD; temp != NULL; temp = temp->next)
        printf("%d, ", temp->evt.test_datum);
    printf("\n"); 
}

// #endif /* EVENT_QUEUE_C_ */
