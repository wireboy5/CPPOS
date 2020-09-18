#include "rand.h"

namespace rand {


 static unsigned long int next = 1;
int rand( int max )
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % max;
}
 
void srand( unsigned int seed )
{
    next = seed;
}


}