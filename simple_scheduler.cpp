#include "simple_scheduler.h"

Task_node::Task_node(void (*_func)(void), unsigned long _period, bool _repeat ) {
  func = _func;
  repeat = _repeat;
  timestamp = millis();
  period_ms = _period;
}

void Task_list::update() {
  if (list_length > 0) {
    Task_node *crr_node_ptr = head;

    int _list_length = list_length; // list index can be remove inside loop
    for (int idx = 0; idx < _list_length; idx++) {
      if (crr_node_ptr == NULL)break;


      if (millis() - (crr_node_ptr-> timestamp) >= (crr_node_ptr-> period_ms)) {// Node need to Task


        crr_node_ptr -> func();//run node's function
        if (crr_node_ptr -> repeat) {
          crr_node_ptr->timestamp += crr_node_ptr->period_ms;
          crr_node_ptr = (Task_node*) crr_node_ptr -> nxt_ptr;
        }
        else {
          //remove the node
          Task_node *deleted_node_ptr = crr_node_ptr;
          crr_node_ptr = (Task_node*)crr_node_ptr -> nxt_ptr;
          remove(deleted_node_ptr);
        }

      }
      else { // skip for now
        crr_node_ptr = (Task_node*)crr_node_ptr -> nxt_ptr;
      }
    }
  }
}
void Task_list::remove(Task_node *node_ptr) {
  Task_node *crr_node_ptr = head;
  Task_node *prev_node_ptr = head;
  for (int idx = 0; idx < list_length; idx++) {//Search for previous node of remove node
    if (crr_node_ptr == node_ptr )break;
    prev_node_ptr = crr_node_ptr;
    crr_node_ptr = (Task_node*) crr_node_ptr -> nxt_ptr;
  }
  prev_node_ptr -> nxt_ptr = crr_node_ptr-> nxt_ptr;
  if (crr_node_ptr == tail) {
    tail = prev_node_ptr;
  }
  delete crr_node_ptr;
  list_length --;
}
void Task_list::append(Task_node *node_ptr) { //pass by reference

  if (list_length == 0) {
    // create new list head
    head = node_ptr;
    tail = head;
  }
  else {
    tail -> nxt_ptr = node_ptr;
    tail = node_ptr;
  }

  list_length++;

}
void Task_list::setInterval(void (*_func)(void), unsigned long _period) {
  bool _repeat = true;
  Task_node *new_node_ptr = new Task_node(_func, _period, _repeat);
  append(new_node_ptr);
}
void Task_list::setTimeout(void (*_func)(void), unsigned long _period) {
  bool _repeat = false;
  Task_node *new_node_ptr = new Task_node(_func, _period, _repeat);
  append(new_node_ptr);
}
