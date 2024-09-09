#include "tools.h"

LEET_PROBLEM
{
  auto list = tools::generateList(10);
  tools::printList(list);
  
  tools::listNode* prev = nullptr;
  while (list) {
    auto next = list->next;
    list->next = prev;
    prev = list;
    list = next;
  }
  list = prev;

  tools::printList(list);
  tools::deleteList(list);
}
