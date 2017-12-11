#include "printf_hal.h"
#include <string.h>

#define DUMP_STRING_LEN (16)


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// strend
// in - ukazatek na stroky
// out- ukazatel na konec stroki
///////////////////////////////////////////////////////////////////////////////////////////////////////////
char * strend(const char * str)
{
    char *p = 0;
    
    if (str){
        p = (char *)str;
        return p + strlen(str);
    }
    
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCD to INT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int bcd2int (unsigned char b)
{
    return ((b>>4)*10 + (b&15));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// hex out
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void dump_out(const char *buf_in, unsigned long len)
{
    unsigned long n,i;
    char t;

    printf("\n");
    n=0;

    for (i=0; i<len; i++){
        t = *(buf_in + i);
        printf(" %x",(unsigned char)t);
        n++;
        if (n==DUMP_STRING_LEN){
            n=0;
            printf("\n");
            printf("addres= %lx: ",i+1);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// hex out
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void hex_out(const char *buf_in, unsigned long len)
{
    unsigned long n,i,j;
    char c;
    char s[DUMP_STRING_LEN];

    printf("\n");
    n=0;

    for (i=0; i<len; i++){
        c = *(buf_in + i);
        printf(" %02X",(unsigned char)c);

        if (c<0x20)
            s[n] = '.';
        else
            s[n] = c;

        n++;
        if (n == DUMP_STRING_LEN){
            printf(" | ");
            for (j=0;j<DUMP_STRING_LEN;j++) 
                printf("%c",s[j]);
                n=0;
                printf("\n");
                //printf("addres= %04lx: ",i+1);
        }
    }

    if (n > 0 && n < DUMP_STRING_LEN){
        for (j=0;j<DUMP_STRING_LEN-n;j++) 
            printf("   ");
        printf(" | ");
        for (j=0;j<n;j++) 
            printf("%c",s[j]);
    }

    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////////////////
// print to console hex buffer po 16 colonok
///////////////////////////////////////////////////////////////////////////////////////////
void print_hex(const char *in, unsigned short len)
{

unsigned short i=0;

    for (i=0; i<len; i++){
        if (i == 16) printf("\n");
        printf(" %02x",*(in+i));
    }
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// str_pop
// vitaskivae stroku mehdu kovichek
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int str_pop(char *str_dest){

    if (strlen(str_dest) >= 3 )
        if ( ( *str_dest == '"') & (*(str_dest + strlen(str_dest) - 1) == '"') ){
            strncpy(str_dest, str_dest+1, strlen(str_dest)-2 );
            *(str_dest + strlen(str_dest)-2) = 0;
            return 0;
        }
    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// test ascii IP
// proveraem vhodnuu stroku IP na sootvestvie formatu 123.456.789.321
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ip_test(const char *str){
    enum{s1,s2,s3,s4} sst;
    unsigned char i = 0;
    unsigned char k = 0;
    unsigned char ch;

    if ( strlen(str) > 15) return -1;// error IP format

    // proverka vhodenia tolko chifri & '.'
    i=0;
    while( (ch=*(str+i)) != 0 ){
        //printf("char=%x\n",ch);
        if ( ((ch >= '0') && (ch <= '9')) || (ch == '.') ) i++;
        else return -1;
    }

    i = 0;
    k = 0;
    sst = s1;

    while( (ch=*(str+i)) != 0 ){
        switch(sst){
        case s1:
            if (k > 3) return -1;// error IP format
            if ((ch == '.') && (k >= 2)){
                k = 0;
                sst = s2;
            } else k++;
            i++;
            break;

        case s2:
            if (k > 3) return -1;// error IP format
            if ((ch == '.') && (k >= 1)){
                k = 0;
                sst = s3;
            } else k++;
            i++;
            break;

        case s3:
        if (k > 3) return -1;// error IP format
        if ((ch == '.') && (k >= 1)){
            k = 0;
            sst = s3;
        } else k++;
        i++;
        break;

        case s4:
            if (k > 3) return -1;// error IP format
            if (ch == '.') return -1;// error IP format
            else k++;
            i++;
            break;
        }

    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// test ascii IP
// proveraem vhodnuu stroku IP na sootvestvie formatu 123.456.789.321
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int port_test(const char *str){
    unsigned char i = 0;
    unsigned char ch;

    if ( strlen(str) > 5) return -1;// error Port format
    // proverka vhodenia tolko chifri & '.'
    i=0;
    while( (ch=*(str+i)) != 0 ){
        //printf("char=%x\n",ch);
        if ( (ch >= '0') & (ch <= '9') ) i++;
        else return -1;
    }
    return 0;
}

// dump kolchevogo buffer bez izvlecheniya danih
#define DUMP_STRING_LEN (16)
void dump_queue(const char * buf, unsigned int in, unsigned int out, const unsigned int size )
{
    int i=0;
    int j;
    unsigned int ini=in;
    unsigned int outi=out;
    char s[DUMP_STRING_LEN];
    char c;

    printf("\n=================DUMP QUEUE START==================\n");
    printf("in=%d out=%d\n", ini, outi);
    if (ini == outi) goto _end;

    do{
        c = *(buf+outi);
        printf(" %02X",(unsigned char)c);
        if (c<0x20)
            s[i] = '.';
        else
            s[i] = c;
        i++;
        if (i == DUMP_STRING_LEN){
            printf(" | ");
            for (j=0;j<DUMP_STRING_LEN;j++) 
                printf("%c",s[j]);
            printf("\n");
            i = 0;
        }
        outi++;
        if (outi==size)
            outi=0;
    }while( ini != outi );

_end:
    if (i > 0 && i < DUMP_STRING_LEN){
        for (j=0;j<DUMP_STRING_LEN-i;j++) 
            printf("   ");

        printf(" | ");
        for (j=0;j<i;j++) 
            printf("%c",s[j]);
    }

    printf("\n=================DUMP QUEUE END====================\n");
}
