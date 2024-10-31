//stacklist.c
#include "stacklist.h"

Stacklist *mkStacklist(void) {
  Stacklist *p;
  int16 size;

  size = sizeof(struct s_stacklist);
  p = (Stacklist *)malloc((int)size);
  if (!p) 
      return (Stacklist *)0;
  
  zero((int8 *)p, size);
  p->data = 0;
  p->size = 0;
  p->next = (Stacklist *)0; 

  return p;
}

Stacklist *findlast(Stacklist *stacklist) {
    Stacklist *p;
    int16 n;

    if (!(stacklist->size)) 
        return stacklist;
    else if (stacklist->size == 1)
        return stacklist->next;
    
    for(p=stacklist, n = p->size; n; n--, p = p->next);
    
    if (!p) 
        return (Stacklist *)0;
    else 
        return p;
}

Stacklist *penultimate(Stacklist *stacklist) {
    Stacklist *p, *pusl;
    int16 n;

    if (!(stacklist->size)) 
        return (Stacklist *)0;
    else if (stacklist->size == 1)
        return stacklist;
    
    for(p=stacklist, n = stacklist->size; n; n--, pusl = p, p = p->next);
    
    if (pusl) 
        return pusl;
    else 
        return (Stacklist *)0;
}

bool push(Stacklist *stacklist, Entry *value, int16 size) {
    Stacklist *parent, *p;
    Entry *e;

    // if (!stacklist) 
    //     return false;
    
    parent = findlast(stacklist);
    if (!parent) 
        return false;

    p = mkStacklist();
    if (!p) 
        return false;

    e = (Entry *)malloc(size);
    if(!e){
        free(p);
        return false;
    }

    parent->next = p;
    stacklist->size++;
    memcpy((char *)e, (char *)value, size);
    p->data = e;

    return true;
}

Entry *pop(Stacklist *stacklist) {
    Stacklist *last, *pusl;
    Entry *e;

    if (!(stacklist->size)) 
        return (Entry *)0;
    
    pusl = penultimate(stacklist);
    if (!pusl) 
        return (Entry *)0;

    last = findlast(stacklist);
    if (!last) 
        return (Entry *)0;

    e = last->data;
    pusl->next = (Stacklist *)0;
    free(last);
    stacklist->size--;

    return e;
}

int main(int argc, char *argv[]) {
  Stacklist *list, *p;
  Entry *e1, *e2, *e3, *e4;
  Entry *a, *b;
  bool ret;
  int16 size;

  list = mkStacklist();
  e1 = (Entry *)"string 1";
  e2 = (Entry *)"string 2";
  e3 = (Entry *)"string 3";
  e4 = (Entry *)"string 4";

  size = $6 strlen($c e1);
  ret = push(list, e1, size);

  size = $6 strlen($c e2);
  ret = push(list, e2, size);
  

  size = $6 strlen($c e3);
  ret = push(list, e3, size);
  //printf("ret = %d\n", ret);
  // printf("penultimate add = %p\n", list->next->next->next);
  // printf("'%s'\n", (char *)list->next->next->next->data);

  size = $6 strlen($c e4);
  ret = push(list, e4, size);
  
  // p = penultimate(list);
  // printf("penultimate = %p\n", p);
  // printf("'%s'\n", (char *)p->data);

  a = pop(list);
  b = pop(list);
  printf("'%s'\n'%s'\n", (char *)a, (char *)b);
  (volatile void)pop(list);
  (volatile void)pop(list);

  free(list);

  return 0;
}

