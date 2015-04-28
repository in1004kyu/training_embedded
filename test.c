#define TX_FIFO_FULL_MASK (1 << 24)

struct s5p_uart {
    unsigned int    ulcon;
    unsigned int    ucon;
    unsigned int    ufcon;
    unsigned int    umcon;
    unsigned int    utrstat;
    unsigned int    uerstat;
    unsigned int    ufstat;
    unsigned int    umstat;
    unsigned char   utxh;
    unsigned char   res1[3];
    unsigned char   urxh;
    unsigned char   res2[3];
    unsigned int    ubrdiv;
    unsigned char   res3[0xffd0];
};

static int serial_err_check(int op)
{
    struct s5p_uart *const uart = (struct s5p_uart *) 0x12c20000;
    unsigned int mask;
    if (op)
        mask = 0x8;
    else
        mask = 0xf;
    return (uart->uerstat) & mask;
}

volatile struct s5p_uart * const UART0DR = (struct s5p_uart *)0x12c20000;

void uart_putc(const char c)
{
    struct s5p_uart *const uart = (struct s5p_uart *) 0x12c20000;
    while (uart->ufstat & TX_FIFO_FULL_MASK) {
        if (serial_err_check(1))
            return;
    }

    (uart->utxh) = c;

    if (c == '\n')
        uart_putc('\r');
}

void print_uart0(const char *s) {

    while(*s)
        uart_putc(*s++);
}

void c_entry() {
     print_uart0("Hello world!\n");
}

