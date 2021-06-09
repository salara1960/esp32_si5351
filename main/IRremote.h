#ifndef IRREMOTE__h
#define IRREMOTE__h


#include "hdr.h"

#ifdef SET_IRED

//#include "main.h"

//-----------------------------------------------------------------------------

#define IRED_Pin 19
#define GPIO_IR_LED 13

//#define RECIV_PIN (gpio_get_level(IRED_Pin)) //(HAL_GPIO_ReadPin(IRED_GPIO_Port, IRED_Pin))

#define RAWBUF 256

#define STATE_IDLE      2
#define STATE_MARK      3
#define STATE_SPACE     4
#define STATE_STOP      5
#define STATE_OVERFLOW  6

#define GAP_TICKS       100

#define MARK   0
#define SPACE  1

#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261


#define MAX_IRED_KEY 21

//-----------------------------------------------------------------------------

typedef struct {// The fields are ordered to reduce memory over caused by struct-padding
	uint8_t       rcvstate;        // State Machine state
	uint16_t      rawlen;          // counter of entries in rawbuf //uint8_t
	uint16_t      timer;           // State timer, counts 50uS ticks.
	uint16_t      rawbuf[RAWBUF];  // raw data
	uint8_t       overflow;        // Raw buffer overflow occurred
} irparams_t;

// Results returned from the decoder
typedef struct {
	//decode_type_t decode_type; // UNKNOWN, NEC, SONY, RC5, ...
	//uint16_t address; // Used by Panasonic & Sharp [16-bits]
	uint32_t value; // Decoded value [max 32-bits]
	int16_t bits; // Number of bits in decoded value
	volatile uint16_t *rawbuf; // Raw intervals in 50uS ticks
	int16_t rawlen; // Number of records in rawbuf
	int16_t overflow; // true iff IR raw code too long
} decode_results;


enum {
	key_ch_minus = 0,
	key_ch,
	key_ch_plus,
	key_left,
	key_right,
	key_sp,
	key_minus,
	key_plus,
	key_eq,
	key_100,
	key_200,
	key_0,
	key_1,
	key_2,
	key_3,
	key_4,
	key_5,
	key_6,
	key_7,
	key_8,
	key_9
};

#pragma pack(push,1)
	typedef struct {
		char name[8];
		uint32_t code;
	} one_key_t;
#pragma pack(pop)


//-----------------------------------------------------------------------------

volatile irparams_t irparams;
decode_results results;

const char *TAGIR;
const one_key_t keyAll[MAX_IRED_KEY];

//-----------------------------------------------------------------------------

int16_t decodeIRED(decode_results *results);
int32_t decodeHashIRED(decode_results *results);
void enIntIRED();
void resumeIRED();
void tmrInitIRED();

//-----------------------------------------------------------------------------

#endif

#endif


