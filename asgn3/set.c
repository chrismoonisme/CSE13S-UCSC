#include "set.h"

#include <stdint.h>

//SET OVERVIEW:
//32 bit int.  Each bit stands for a value
//for example, adding "3" to set sets bit 3 to 1

//return empty set (everything is 0)
Set set_empty(void) {

    return 0;
}

//all 1
Set set_universal(void) {

    return 0xffffffff;
}

//check if an element x is in set s
bool set_member(Set s, uint8_t x) {

    //use and to check if a bit is set
    s = s & (1 << (x % 32));

    return s;
}

//insert value x into the set
Set set_insert(Set s, uint8_t x) {

    //set a bit via or

    s = s | (1 << (x % 32));

    return s;
}

//remove a value x from the set s
Set set_remove(Set s, uint8_t x) {

    //clear a bit using and + not
    return s & ~(1 << (x % 32));
}

Set set_union(Set s, Set t) {

    return s | t;
}

Set set_intersect(Set s, Set t) {

    return s & t;
}

Set set_complement(Set s) {

    return !s;
}
