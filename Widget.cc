#include "Widget.hh"

bool Widget::inside_my_bounds(int x, int y) {
    int mx = this->outline.x;
    int my = this->outline.y;
    int mw = this->outline.w;
    int mh = this->outline.h;
    
    return ((mx < x && x < mx + mw) 
        && (my < y && y < my + mh));
}