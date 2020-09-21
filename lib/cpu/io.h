#ifndef IO_H
#define IO_H
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
    static inline void outb(uint16_t port, uint8_t val)
    {
        asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
        /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
         * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
         * The  outb  %al, %dx  encoding is the only option for all other cases.
         * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
    }
    static inline void outw(uint16_t port, uint16_t val)
    {
        asm volatile ( "outw %0, %1" : : "a"(val), "Nd"(port) );
        /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
         * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
         * The  outb  %al, %dx  encoding is the only option for all other cases.
         * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
    }
    static inline void outl(uint16_t port, uint32_t val)
    {
        asm volatile ( "outl %0, %1" : : "a"(val), "Nd"(port) );
        /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
         * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
         * The  outb  %al, %dx  encoding is the only option for all other cases.
         * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
    }
    static inline uint8_t inb(uint16_t port)
    {
        uint8_t ret;
        asm volatile ( "inb %1, %0"
                       : "=a"(ret)
                       : "Nd"(port) );
        return ret;
    }
    static inline uint16_t inw(uint16_t port)
    {
        uint16_t ret;
        asm volatile ( "inw %1, %0"
                       : "=a"(ret)
                       : "Nd"(port) );
        return ret;
    }
    static inline uint32_t inl(uint16_t port)
    {
        uint32_t ret;
        asm volatile ( "inl %1, %0"
                       : "=a"(ret)
                       : "Nd"(port) );
        return ret;
    }
} // namespace IO
#endif