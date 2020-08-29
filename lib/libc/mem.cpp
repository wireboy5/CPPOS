#include "mem.h"


namespace mem {

void memcpy(uint32_t *source, uint32_t *dest, int nbytes){
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}
void memset(uint32_t *dest, uint32_t val, uint32_t len){
    uint32_t *temp = (uint32_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}



uint32_t createBlock(char data[defaultBlockSize]){
    char *s = "";
    uint32_t so = sizeof(data);
    string::int_to_ascii(so,s);
    screen::kprint(s);
    screen::kprint((char *)"\n");
    screen::kprint(data);
}

} // namespace mem