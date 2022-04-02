
#ifndef WIFI_H_
#define WIFI_H_

#define Wifi_LineControlReg_WordLengthSelect0 0
#define Wifi_LineControlReg_WordLengthSelect1 1
#define Wifi_LineControlReg_DivisorLatchAccessBit 7

#define Wifi_FifoControlReg_ReceiveFIFOReset 1
#define Wifi_FifoControlReg_TransmitFIFOReset 2

#define Wifi_LineStatusReg_DataReady 0
#define Wifi_LineStatusReg_TransmitterHoldingRegister 5

#define MAX_STRING 1000

void init_wifi_ports(void);
int put_char_wifi(int);
int wifi_test_for_received_data(void);
int get_char_wifi(void);
void flush_wifi(void);
int lua_command_no_stars(char *, char *, int);
int lua_command_no_stars_short(char *, char *);
void do_file(void);
int init_wifi(void);
void copy_get_response(char *, char *);
int get_request(char *, char *, char *);
int api_request(char *, char *);

#endif