#include <string.h>
#include "key.h"

KeyString createKey(char *cntnt) {
    KeyString string;
    strcpy(string.content, cntnt);
    return string;
}