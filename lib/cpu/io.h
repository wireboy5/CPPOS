#include <stdint.h>

namespace IO
{

    class Port{

    public:
        Port(uint16_t port);
        uint16_t portOp;

    public:
        unsigned char byte_in();      // Receive byte from port
        unsigned short word_in ();    // Receive word over port

        void byte_out (uint8_t data); // Send byte over port
        void word_out (uint16_t data);// Send word over port
        
    }; // class Port
    unsigned char port_byte_in (uint16_t port);
    void port_byte_out (uint16_t port, uint8_t data);
    unsigned short port_word_in (uint16_t port);
    void port_word_out (uint16_t port, uint16_t data);

} // namespace IO