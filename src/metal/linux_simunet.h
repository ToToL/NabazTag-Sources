#ifndef MY_SIMUNET_H_
#define MY_SIMUNET_H_

#define TCPMAX 128 // nombre max de sockets tcp pouvant être ouvertes en même temps
#define UDPMAX 128 // nombre max de sockets udp pouvant être ouvertes en même temps

void helper_write_buffer(char *buf, int res);
int inet_addr_bin(char *ip);
int simunetinit(void);
int checkNetworkEvents(void);
int checkTcpEvents(void);
int tcpEventRead(int fd);
int tcpEventWrite(int fd);
int tcpbysock(int s);
int tcpgetfree(void);
int tcpopen(char* dstip,int dstport);
int tcpclose(int i);
void tcpenable(int i,int enable);
int tcpsend(int i,char* msg, int len);
int tcpservercreate(int port);
int udpgetfree(void);
int udpbysock(int s);
int udpcreate(int port);
int udpclose(int port);
int udpsend(int localport,char* dstip,int dstport,char* msg, int len);
int checkUdpEvents(void);
int udpEventRead(int fd);

#endif
