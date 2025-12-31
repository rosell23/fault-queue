#include "../include/fq/faults-builtin.h"
#include <stdint.h>

uint8_t get_next_fault_id(void) {
    static uint8_t counter = 0x01;  // Start from 1, 0 is reserved
    if (counter == 0) counter = 0x02;  // Skip 0 and 1
    return counter++;
}
