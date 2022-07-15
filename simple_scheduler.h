#include <Arduino.h>
class Task_node {
  public:
    void (*func)(void);
    unsigned long timestamp;
    unsigned long period_ms;
    bool repeat;
    char name[16]; //for debugging, delete this later.
    void *nxt_ptr = NULL;
    Task_node(void (*_func)(void), unsigned long _period, bool _repeat = false) ;
};
class Task_list {
    Task_node *head = NULL;
    Task_node *tail = NULL;
    int list_length = 0;
  public:
    void update();
    void remove(Task_node *node_ptr);
    void append(Task_node *node_ptr) ;
    void setInterval(void (*_func)(void), unsigned long _period);
    void setTimeout(void (*_func)(void), unsigned long _period);
};
