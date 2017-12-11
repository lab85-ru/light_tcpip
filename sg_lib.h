#ifndef SG_LIB_H_
#define SG_LIB_H_

//#include <sys/time.h>

char * strend(const char * str);
int bcd2int (unsigned char b);
void dump_out(const char *buf_in, unsigned long len);
void hex_out(const char *buf_in, unsigned long len);
void print_hex(const char *in, unsigned short len);
int str_pop(char *str_dest);
int bcd2int (unsigned char b);
int ip_test(const char *str);
int port_test(const char *str);
void dump_queue(const char * buf, unsigned int in, unsigned int out, const unsigned int size );

#endif /*SG_LIB_H_*/
