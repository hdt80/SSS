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

    *event = QUEUE_HEAD->evn;
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
        t->evn = event;
        QUEUE_HEAD = t;
    } else {

        sss_node* temp = QUEUE_HEAD;
        sss_node* new_node = (sss_node*)malloc(sizeof(sss_node));
        new_node->evn = event;
        new_node->next = NULL;
        while(temp != NULL && temp->next != NULL) 
            temp = temp->next;
        temp->next = new_node;

    }

    return 1;
}

sss_event sss_parse_event(const char* command) {
    sss_event result;

    printf("command: %s\n\n", command);


    int number_of_args = 0;
    
    // count the number of arguments
    int i;
    // params start at the fifth character
    for(i = 4; ; i++) {
        if(command[i] == '@') { 
            break;
        }
        if(command[i] == ';')
            number_of_args++;
    }
    printf("%d\n", number_of_args);
    if(number_of_args == 0) {
        puts("returning error");
        result.type = ERROR;
        return result;
    }

    int com_length = i;

    // read the type of the event
    char type[4];
    for(i = 0; i < 3; i++) 
        type[i] = command[i];
    type[3] = '\0';

    puts("on the ritz");
    // ignore arguments
    // holds all the arguments in character form
    // char arguments[100][10]; 
    // memset(&arguments, sizeof(arguments), 0);
    int curr_arg_x = 0; // arguments[x][_]
    int curr_arg_y = 0; // arguments[_][y]
    // // thats some spooky stuff;
    // for(i = 4; i < com_length; i++) {
    //     if(command[i] != ';' && command[i] != '@') {
    //         arguments[curr_arg_x][curr_arg_y++] = command[i];            
    //         /* uncomment next line to see some spooky stuff */
    //         // printf("curr arg: %s\n", arguments[curr_arg_x]);
    //     } else {
    //         curr_arg_x++;
    //         curr_arg_y = 0;
    //     }
    // }

    int* args_array = (int*)malloc(sizeof(int) * number_of_args);
    memset(args_array, sizeof(int) * number_of_args, 0);
    /* quietly ignore arguments */
    for(i = 0; i < curr_arg_x; i++) {
        // sscanf(arguments[i], "%d", &args_array[i]);
    }

    for(i = 0; i < number_of_args; i++)
        printf("%d, ", args_array[i]);
    puts("here");

    printf("%s\n", type);

    /* construct the event */
    if(!strcmp(type, "EVN"))
        result.type = EVN;
    else if(!strcmp(type, "SET"))
        result.type = SET;
    else if(!strcmp(type, "GET"))
        result.type = GET;
    else
        result.type = ERROR;

    for(i = 1; i < number_of_args; i++)
        result.args[i - 1] = args_array[i];

    result.evn = (enum EVENT_TYPE)args_array[0];

    puts("asdffdsaasdf");

    free(args_array);
    puts("after freeing the args_array");
    return result;
}

void sss_debug_queue() {
    sss_node* temp;
    for(temp = QUEUE_HEAD; temp != NULL; temp = temp->next)
        printf("%d, ", temp->evn.type);
    printf("\n"); 
}

// #endif /* EVENT_QUEUE_C_ */
