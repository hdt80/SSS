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

    printf("%s\n", command);

    int number_of_args = 0;
    
    // count the number of arguments
    int i;
    // params start at the fifth character
    for(i = 4; ; i++) {
        if(command[i] == '@') { 
            number_of_args++;
            break;
        }
        if(command[i] == ';')
            number_of_args++;
    }
    int len = i;
    
    int* args_arr = (int*)malloc(sizeof(int) * number_of_args);
    char* holder = (char*)malloc(sizeof(int) * len);
    char* fmt = (char*)malloc(sizeof(int)    * number_of_args * 3);

    for(i = 4; i < len; i++)
        holder[i - 4] = command[i];
   
    for(i = 0; i < number_of_args * 3; i += 3) {
        fmt[  i  ] = '%';
        fmt[i + 1] = 'd';
        fmt[i + 2] = ';';
    } 

    printf("%s\n", holder);

    printf("%s\n", fmt);

    sprintf(holder, fmt, args_arr);
    
    for(i = 0; i < number_of_args; i++)
        printf("%d, ", args_arr[0]);
    puts("");
    
    free(args_arr);
    free(holder);
    free(fmt);
    return result;
}

void sss_debug_queue() {
    sss_node* temp;
    for(temp = QUEUE_HEAD; temp != NULL; temp = temp->next)
        printf("%d, ", temp->evt.test_datum);
    printf("\n"); 
}

// #endif /* EVENT_QUEUE_C_ */
