#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Slot structure
struct Slot {
    char symbol[5];
    int index;
    // L for ladder, S for snake, N for nothing
    char type;
};