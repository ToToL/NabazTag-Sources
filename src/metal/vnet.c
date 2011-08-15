// VLISP Virtual Machine - 2006 - by Sylvain Huet
// Lowcost IS Powerfull
#include"vmem.h"
#include"properties.h"

#include <string.h>
#include<stdio.h>
#include<time.h>
#include "log.h"
int netstatesimu=1;
#include"vloader.h"
#include"vnet.h"
#include"vlog.h"
#include"vinterp.h"
int netState()
{
        return netstatesimu;
}

int netSend(char* src,int indexsrc,int lentosend,int lensrc,char* macdst,int inddst,int lendst,int speed)
{
        my_printf(LOG_SIMUNET, "xxxx netSend\n");
		return -1;
}

int netCb(char* src,int lensrc,char* macsrc)
{
  VPUSH(PNTTOVAL(VMALLOCSTR(src,lensrc)));
  VPUSH(PNTTOVAL(VMALLOCSTR(macsrc,6)));
  VPUSH(VCALLSTACKGET(sys_start,SYS_CBTCP));
  if (VSTACKGET(0)!=NIL) interpGo();
  else { VPULL();VPULL();}
  VPULL();
  return 0;
}

extern unsigned char rt2501_mac[6];

int htoi2(char* src)
{
	char buf[3];
	buf[0]=src[0];
	buf[1]=src[1];
	buf[2]=0;
	return sysHtoi(buf);
}

char mac[6];

char* netMac()
{
	int i;
	char *p=PropGet("MAC");
	for(i=0;i<6;i++) mac[i]=htoi2(&p[i*2]);
	return mac;
}

int netChk(char* src,int indexsrc,int lentosend,int lensrc,unsigned int val)
{
  unsigned short* p;

  if (indexsrc<0) return val;
  if (indexsrc+lentosend>lensrc) lentosend=lensrc-indexsrc;
  if (lentosend<=0) return val;

  src+=indexsrc;
  p=(unsigned short*)src;

  val=((val<<8)&0xff00)+((val>>8)&0xff);
  while(lentosend>1)
  {
	  val+=*(p++);
	  lentosend-=2;
  }
  if (lentosend) val+=*(unsigned char*)p;

  val=(val>>16)+(val&0xffff);
  val=(val>>16)+(val&0xffff);
  val=((val<<8)&0xff00)+((val>>8)&0xff);
  return val;
}

void netSetmode(int mode,char* ssid,int chn)
{
        my_printf(LOG_SIMUNET, "xxxx netSetmode %d %s %d\n",mode,ssid,chn);
		netstatesimu=(mode)?5:4;
}


int nscan;

void netScan(char* ssid)
{
  nscan=0;
  VPUSH(PNTTOVAL(VMALLOCSTR("foo",3)));
  VPUSH(PNTTOVAL(VMALLOCSTR("xyzxyz",6)));
  VPUSH(PNTTOVAL(VMALLOCSTR("765432",6)));
  VPUSH(INTTOVAL(-20));
  VPUSH(INTTOVAL(11));
  VPUSH(INTTOVAL(1));
  VPUSH(INTTOVAL(0));
  VMKTAB(7);
  nscan++;
  VPUSH(PNTTOVAL(VMALLOCSTR("foo",3)));
  VPUSH(PNTTOVAL(VMALLOCSTR("xyzxyz",6)));
  VPUSH(PNTTOVAL(VMALLOCSTR("765432",6)));
  VPUSH(INTTOVAL(-10));
  VPUSH(INTTOVAL(11));
  VPUSH(INTTOVAL(1));
  VPUSH(INTTOVAL(0));
  VMKTAB(7);
  nscan++;
  VPUSH(PNTTOVAL(VMALLOCSTR("zzzz",3)));
  VPUSH(PNTTOVAL(VMALLOCSTR("xyzxyz",6)));
  VPUSH(PNTTOVAL(VMALLOCSTR("765432",6)));
  VPUSH(INTTOVAL(-10));
  VPUSH(INTTOVAL(11));
  VPUSH(INTTOVAL(1));
  VPUSH(INTTOVAL(0));
  VMKTAB(7);
  nscan++;
  VPUSH(PNTTOVAL(VMALLOCSTR("",3)));
  VPUSH(PNTTOVAL(VMALLOCSTR("xyzxyz",6)));
  VPUSH(PNTTOVAL(VMALLOCSTR("765432",6)));
  VPUSH(INTTOVAL(-10));
  VPUSH(INTTOVAL(11));
  VPUSH(INTTOVAL(1));
  VPUSH(INTTOVAL(0));
  VMKTAB(7);
  nscan++;
  VPUSH(PNTTOVAL(VMALLOCSTR("a\"a<a'a  a\\a",strlen("a\"a<a'a  a\\a"))));
  VPUSH(PNTTOVAL(VMALLOCSTR("xyzxyz",6)));
  VPUSH(PNTTOVAL(VMALLOCSTR("765432",6)));
  VPUSH(INTTOVAL(-10));
  VPUSH(INTTOVAL(11));
  VPUSH(INTTOVAL(1));
  VPUSH(INTTOVAL(3));
  VMKTAB(7);
  nscan++;
  VPUSH(PNTTOVAL(VMALLOCSTR("foo",3)));
  VPUSH(PNTTOVAL(VMALLOCSTR("xyzxyz",6)));
  VPUSH(PNTTOVAL(VMALLOCSTR("765432",6)));
  VPUSH(INTTOVAL(-30));
  VPUSH(INTTOVAL(11));
  VPUSH(INTTOVAL(1));
  VPUSH(INTTOVAL(0));
  VMKTAB(7);
  nscan++;
  VPUSH(NIL);
  while(nscan--) VMKTAB(2);
}

void netAuth(char* ssid,char* mac,char* bssid,int chn,int rate,int authmode,int encrypt,char* key)
{
        my_printf(LOG_SIMUNET, "xxxx netAuth %s %d %d %d %d\n",ssid,chn,rate,authmode,encrypt);
		netstatesimu=4;
}

void netSeqAdd(unsigned char* seq,int n)
{
  unsigned char res[4];
  unsigned int val;
  val=(seq[0]<<24)+(seq[1]<<16)+(seq[2]<<8)+seq[3];
  val+=n;
  res[3]=val; val>>=8;
  res[2]=val; val>>=8;
  res[1]=val; val>>=8;
  res[0]=val;
  VPUSH(PNTTOVAL(VMALLOCSTR((char*)res,4)));
}

void mypassword_to_pmk(const char *password, char *ssid, int ssidlength, unsigned char *pmk);

void netPmk(char* ssid,char* key,char* buf)
{
	my_printf(LOG_SIMUNET, "xxxx netPmk %s %s\n",ssid,key);
	strcpy(buf,"01234567012345670123456701234567");
}

int netRssi()
{
	return -20;
}

