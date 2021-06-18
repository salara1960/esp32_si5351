#ifndef __MQTT_H__
#define __MQTT_H__


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "freertos/FreeRTOS.h"
#include <freertos/semphr.h>
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/ringbuf.h"


#include "driver/adc.h"
#include "driver/gpio.h"
#include "driver/ledc.h"


#if defined(SET_SSD1306) || defined(SET_SI5351)
    #include "driver/i2c.h"
#endif


#include "esp_system.h"
#include "esp_adc_cal.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_flash_spi_init.h"
#include "nvs.h"
#include "esp_partition.h"
#include "esp_attr.h"
#include "esp_err.h"
#include "esp_wps.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_vfs_dev.h"
#include "esp_spiffs.h"


//SET_SDCARD
#include <sys/unistd.h>
#include <sys/stat.h>
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"
#include "driver/spi_slave.h"
#include "sdmmc_cmd.h"


//SET_FMB630
#include <endian.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/select.h>
//

//SET_SERIAL
#include <sys/fcntl.h>
#include <sys/errno.h>
#include "driver/uart.h"
#include "esp_intr_alloc.h"
#include "hal/uart_types.h"
#include "soc/uart_caps.h"
//

#include <esp_intr_alloc.h>
#include "esp_types.h"
#include "stdatomic.h"
#include "esp_netif.h"

#include "crt.h"

#include "esp32/rom/ets_sys.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/sens_reg.h"
#include <soc/rmt_struct.h>
#include <soc/dport_reg.h>
#include <soc/gpio_sig_map.h>

#include "lwip/ip_addr.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "lwip/api.h"
#include "lwip/netif.h"

#include "cJSON.h"

#include "esp_timer.h"

//---------------------------------------

#define DEV_MASTER ((uint8_t)0)


#define sntp_srv_len   32
#define wifi_param_len 32


#pragma once


#define MAX_FILE_BUF_SIZE 1024
#define RDBYTE "rb"
#define WRBYTE "wb"
#define WRPLUS "w+"
#define RDONLY "r"
#define WRTAIL "a+"

#define BUF_SIZE 1024

//***********************************************************************

#define LED_ON  1
#define LED_OFF 0

#define SEC_FLAG_DEF 100

#define GPIO_LOG_PIN      2//23 //log_server started
#define GPIO_WIFI_PIN     4
//#define GPIO_WMODE_PIN   15 //1-STA  0-AP

//#define GPIO_RESTART_PIN 25//35
//#define GPIO_RESTART_PIN_SEL (1<<GPIO_RESTART_PIN)


#define ADC1_TEST_CHANNEL (6) //6 channel connect to pin34
#define ADC1_TEST_PIN    34 //pin34

#define STACK_SIZE_1K    1024
#define STACK_SIZE_1K5   1536
#define STACK_SIZE_2K    2048
#define STACK_SIZE_2K5   2560
#define STACK_SIZE_3K    3072
#define STACK_SIZE_4K    4096

#define STORAGE_NAMESPACE "nvs"
#define PARAM_CLIID_NAME  "cliid"
#define PARAM_SNTP_NAME   "sntp"
#define PARAM_TZONE_NAME  "tzone"
#define PARAM_SSID_NAME   "ssid"
#define PARAM_KEY_NAME    "key"
#define PARAM_WMODE_NAME  "wmode"
#define PARAM_WS_PORT     "wsport"

#ifdef SET_SI5351
    #define PARAM_SI     "sipar"
#endif


#define EXAMPLE_WIFI_SSID "armLinux" //CONFIG_WIFI_SSID
#define EXAMPLE_WIFI_PASS "armLinux32" //CONFIG_WIFI_PASSWORD
#define max_inbuf         1024

#define EXAMPLE_ESP_MAXIMUM_RETRY  5


#define sntp_server_def "pool.ntp.org"//"2.ru.pool.ntp.org"
#define sntp_tzone_def  "EET-2"


#define TOTAL_MENU 2
#define GPIO_INPUT_NONE 0
#define GPIO_INPUT_KEY   GPIO_NUM_25 // freq step
#define GPIO_INPUT_MINUS GPIO_NUM_26 // freq -
#define GPIO_INPUT_PLUS  GPIO_NUM_27 // freq +
//#define GPIO_INPUT_MENU  GPIO_NUM_33 // menu
#define GPIO_INPUT_PIN_SEL  ((1ULL<<GPIO_INPUT_KEY) | (1ULL<<GPIO_INPUT_MINUS) | (1ULL<<GPIO_INPUT_PLUS))// | (1ULL<<GPIO_INPUT_MENU))
#define ESP_INTR_FLAG_DEFAULT 0



#ifdef SET_ST7789
    #define CONFIG_WIDTH  240
    #define CONFIG_HEIGHT 240
    #define CONFIG_OFFSETX 0
    #define CONFIG_OFFSETY 0
    #define CONFIG_MOSI_GPIO 23
    #define CONFIG_SCLK_GPIO 18
    #define CONFIG_CS_GPIO -1
    #define CONFIG_DC_GPIO 16//19
    #define CONFIG_RESET_GPIO 17//15
    #define CONFIG_BL_GPIO -1
#endif



#define _10ms  1
#define _50ms  5 * _10ms
#define _100ms 10 * _10ms
#define _150ms 15 * _10ms
#define _200ms 20 * _10ms
#define _250ms 25 * _10ms
#define _300ms 30 * _10ms
#define _350ms 35 * _10ms
#define _400ms 40 * _10ms
#define _450ms 45 * _10ms
#define _500ms 50 * _10ms
#define _600ms 60 * _10ms
#define _700ms 70 * _10ms
#define _800ms 80 * _10ms
#define _900ms 90 * _10ms

#define _1s   100
#define _2s     2 * _1s
#define _5s     5 * _1s
#define _10s   10 * _1s
#define _15s   15 * _1s
#define _20s   20 * _1s
#define _25s   25 * _1s
#define _30s   30 * _1s


//**************************************************************************

enum {
    stepMenu = 0,
    freqMenu
};

enum {
    typeOld = 0,
    typeNew
};

#pragma pack(push,1)
typedef struct {
    fpos_t rseek;
    fpos_t wseek;
    uint32_t total;
} s_log_t;
#pragma pack(pop)

extern const char *Version;

extern uint32_t cli_id;

extern uint8_t wmode;
extern char work_ssid[wifi_param_len];

extern const char server_cert[];
extern const char server_key[];

extern EventGroupHandle_t wifi_event_group;
extern const int CONNECTED_BIT;

extern uint8_t total_task;
extern volatile uint8_t restart_flag;

extern uint8_t temprature_sens_read();
extern uint32_t get_vcc();
extern float get_tChip();

extern uint32_t get_tmr(uint32_t tm);
extern int check_tmr(uint32_t tm);

extern void print_msg(uint8_t with, const char *tag, const char *fmt, ...);

extern esp_err_t read_param(const char *param_name, void *param_data, size_t len);
extern esp_err_t save_param(const char *param_name, void *param_data, size_t len);


#ifdef SET_NET_LOG
    #include "tcp_srv.h"

    uint16_t net_log_port;
    xQueueHandle msgq;
#endif

#ifdef SET_SNTP
    #include "sntp_cli.h"

    extern volatile uint8_t sntp_go;
    extern char work_sntp[sntp_srv_len];
    extern char time_zone[sntp_srv_len];
#endif

#ifdef UDP_SEND_BCAST
    extern volatile uint8_t udp_start;
    extern volatile int8_t udp_flag;
#endif


#ifdef SET_SSD1306
    #include "ssd1306.h"

    #define SDA_PIN GPIO_NUM_23//21//13 //15
    #define SCL_PIN GPIO_NUM_18//22//14 //2
    #define SSD1306_PORT I2C_NUM_1
    #define I2C_CLOCK_HZ 400000 //800KHz //400000 //400KHz //1600000 - 1.6MHz  -> WORK !!!
#endif

#ifdef SET_ST7789
    #include "st7789.h"
    #include "fontx.h"
    #include "bmpfile.h"
    #include "pngle.h"
    #include "decode_image.h"

    #define INTERVAL 400
    #define WAIT vTaskDelay(INTERVAL)
#endif

#ifdef SET_SI5351
    #include "si5351.h"

    #define I2C_MASTER_SCL_PIN GPIO_NUM_22
    #define I2C_MASTER_SDA_PIN GPIO_NUM_21

    #define SI5351_PORT I2C_NUM_0
    #define SIPORT_CLOCK_HZ 400000

    #define TOTAL_STEP 7
    #define MIN_FREQ 4000
    #define MAX_FREQ 225000000

    //{1, 10, 100, 1000, 10000, 100000, 1000000}
    enum {
        s1Hz = 0,
        s10Hz,
        s100Hz,
        s1KHz,
        s10KHz,
        s100KHz,
        s1MHz
    };

    #pragma pack(push,1)
    typedef struct {
        uint32_t key;
        uint32_t val;
    } si_msg_t;
    #pragma pack(pop)

    #pragma pack(push,1)
    typedef struct {
        uint8_t istep;
        uint32_t freq;
    } si_params_t;
    #pragma pack(pop)


    xQueueHandle ec11_evt_queue;

    uint32_t curFreq;
    uint64_t txStep;
    si_params_t si_params;

    void setFreqStep(bool up);
    void saveSI();
#endif


#ifdef SET_WS
    #include "ws.h"

    xQueueHandle wsq;
#endif


#ifdef SET_IRED
    #include "IRremote.h"
#endif


#endif /* */
