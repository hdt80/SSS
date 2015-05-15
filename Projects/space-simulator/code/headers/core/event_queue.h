#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef EVENT_QUEUE_H_
#define EVENT_QUEUE_H_

enum EVENT_CLASS {
    SET, GET, EVN, ERR, NUM_CLASSES
};

enum EVENT_TYPE {
    SPWANENEMY,
    COLLISION,
    WE_FIRE,
    MINI_GAME_DONE,
    POWER_CHANGE,
    ENEMY_DESPAWN,
    CHANGE_MAX_POWER,

    NUM_EVENTS
};

struct EVENT {
    // add data
    enum EVENT_CLASS type;
    enum EVENT_TYPE evn;
    int args[10];
};

typedef struct EVENT sss_event;

struct NODE {
    /* Pointer to the next value in the queue
     * in an actual line, the guy/gal behind you
     */
    struct NODE* next;
    sss_event evn;
};
typedef struct NODE sss_node;

#endif /* EVENT_QUEUE_H_ */

#ifdef __cplusplus
extern "C" {
#endif

extern sss_node* QUEUE_HEAD;

int sss_init_queue();
int sss_poll_event(sss_event* event);
int sss_enque_event(sss_event event);

/* may need to pass in the string length as well */
sss_event sss_parse_event(const char* command);

/* prints out the queue */
void sss_debug_queue();




#ifdef __cplusplus
}
#endif

