#define KEYBOARD_MAX_ASCII 83 
#define KEYBOARD_DATA_PORT 0x60

unsigned char keyboard_read_scan_code(void);
unsigned char keyboard_scan_code_to_ascii(unsigned char scan_code);