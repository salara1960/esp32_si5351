#ifndef __JS_H__
#define __JS_H__

#include "hdr.h"

#include "main.h"


typedef enum {
    iCTRL_AUTH = 0,  //"auth"//0
    iCTRL_UDP,       //"udp"//1
    iCTRL_SNTP,      //"sntp"//2
    iCTRL_SNTP_SRV,  //"sntp_srv"//3
    iCTRL_TIME_ZONE, //"time_zone"//4
    iCTRL_RESTART,   //"restart"//5
    iCTRL_TIME,      //"time"//6
    iCTRL_EOPACK,    //"eopack"//7
    iCTRL_GET,       //"get"//8
    iCTRL_FMT,       //9//{"fmt":"text"} , {"fmt":"json"}
    iCTRL_RST,       //10{"rst":"on"}
    iCTRL_PERIOD,    //11//{"period":1000} , {"period":500}.....
    iCTRL_SHIFT,     //12//{"shift":"on"}
    iCTRL_DBG,       //13//{"dbg":"on"} , {"dbg":"off"}
    iCTRL_EPOCH,     //14//{"epoch":"1579692184:2"}
    iCTRL_JTUNE,     //15//{"jtune":"on"} , {"jtune":"off"}
    iCTRL_STEP,      //16//{"step":"up"} , {"step":"down"}
    iCTRL_FREQ       //17//{"freq":8000}// set freq = 8000 Hz
} i_ctrl_t;

typedef enum {
    sCTRL_STATUS = 0,//0//"status",
    sCTRL_WIFI,      //1//"wifi",     //{"wifi":"ssid:password"}
    sCTRL_SNTP_SRV,  //2//"sntp_srv", //{"sntp_srv":"2.ru.pool.ntp.org"}
    sCTRL_TIME_ZONE, //3//"time_zone",//{"time_zone":"UTC+02:00"}
    sCTRL_EOPACK,    //4//"eopack",//{"eopack":">\r\n"}
    sCTRL_LOG_PORT,  //5//"log_port", //{"log_port":"8008"}
    sCTRL_VERSION,   //6//"version"   //{"version":"4.2 (22.01.2020)"}
    sCTRL_DATA,      //7//"data" //{"data":"{...}"}
    sCTRL_STEP_UP,      //8//"step" //{"step":1000}// 1000 Hz
    sCTRL_STEP_DOWN       //9//"freq" //{"freq":4000}// 4000 Hz
} s_ctrl_t;

//extern uint8_t fmtType;

extern int parser_json_str(const char *st, bool *au, const char *str_md5, uint8_t *rst);
extern int mkAck(char *tbuf, int ictrl, int sctrl, bool *au);



#endif

