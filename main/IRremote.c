
#include "hdr.h"

#ifdef SET_IRED

#include "main.h"
#include "IRremote.h"

//-----------------------------------------------------------------------------

volatile irparams_t irparams = {0};
decode_results results = {0};

const char *TAGIR = "IRED";

const one_key_t keyAll[MAX_IRED_KEY] = {
	{"irCH-",   0xe318261b},
	{"irCH",    0x00511dbb},
	{"irCH+",   0xee886d7f},
	{"irLEFT",  0x52a3d41f},
	{"irRIGHT", 0xd7e84b1b},
	{"irSP",    0x20fe4dbb},
	{"ir-",     0xf076c13b},
	{"ir+",     0xa3c8eddb},
	{"irEQ",    0xe5cfbd7f},
	{"ir100+",  0x97483bfb},
	{"ir200+",  0xf0c41643},
	{"ir0",     0xc101e57b},
	{"ir1",     0x9716be3f},
	{"ir2",     0x3d9ae3f7},
	{"ir3",     0x6182021b},
	{"ir4",     0x8c22657b},
	{"ir5",     0x488f3cbb},
	{"ir6",     0x0449e79f},
	{"ir7",     0x32c6fdf7},
	{"ir8",     0x1bc0157b},
	{"ir9",     0x3ec3fc1b}
};

static esp_timer_create_args_t ired_timer_args;
static esp_timer_handle_t ired_timer;

//-----------------------------------------------------------------------------
static void ired_timer_callback(void *arg)
{
    uint8_t irdata = gpio_get_level(IRED_Pin);//RECIV_PIN; // пин для приёма

	irparams.timer++;  // One more 50uS tick
	if (irparams.rawlen >= RAWBUF) irparams.rcvstate = STATE_OVERFLOW;  // Buffer overflow

		switch (irparams.rcvstate) {
			case STATE_IDLE: // In the middle of a gap
				if (irdata == MARK) {
					if (irparams.timer < GAP_TICKS) { // Not big enough to be a gap.
						irparams.timer = 0;
					} else {
						// Gap just ended; Record duration; Start recording transmission
						irparams.overflow = 0;
						irparams.rawlen  = 0;
						irparams.rawbuf[irparams.rawlen++] = irparams.timer;
						irparams.timer = 0;
						irparams.rcvstate = STATE_MARK;
					}
				}
			break;
			case STATE_MARK:  // Timing Mark
				if (irdata == SPACE) {// Mark ended; Record time
					irparams.rawbuf[irparams.rawlen++] = irparams.timer;
					irparams.timer = 0;
					irparams.rcvstate = STATE_SPACE;
				}
			break;
			case STATE_SPACE:  // Timing Space
				if (irdata == MARK) {// Space just ended; Record time
					irparams.rawbuf[irparams.rawlen++] = irparams.timer;
					irparams.timer = 0;
					irparams.rcvstate = STATE_MARK;
				} else if (irparams.timer > GAP_TICKS) {// Space
					irparams.rcvstate = STATE_STOP;
				}
			break;
			case STATE_STOP:  // Waiting; Measuring Gap
			 	if (irdata == MARK) irparams.timer = 0;  // Reset gap timer
			break;
			case STATE_OVERFLOW:  // Flag up a read overflow; Stop the State Machine
				irparams.overflow = 1;
				irparams.rcvstate = STATE_STOP;
			break;
		}
		//
}
//-----------------------------------------------------------------------------
int16_t decodeIRED(decode_results *results)
{
	if (irparams.rcvstate != STATE_STOP) return 0;

	results->rawbuf = irparams.rawbuf;
	results->rawlen = irparams.rawlen;
	results->overflow = irparams.overflow;

	if (irparams.rcvstate != STATE_STOP) return 0;

	if (decodeHashIRED(results)) return 1;

	enIntIRED();

	return 0;
}
//-----------------------------------------------------------------------------
void tmrInitIRED()
{
    gpio_pad_select_gpio(IRED_Pin);
    gpio_pad_pullup(IRED_Pin);
    gpio_set_direction(IRED_Pin, GPIO_MODE_INPUT);

    gpio_pad_select_gpio(GPIO_IR_LED);//white LED
    gpio_pad_pullup(GPIO_IR_LED);
    gpio_set_direction(GPIO_IR_LED, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_IR_LED, LED_OFF);    


	//const esp_timer_create_args_t ired_timer_args = {
    //    .callback = &ired_timer_callback,
    //    .name = "ired"
    //};
    //esp_timer_handle_t ired_timer;

    ired_timer_args.callback = &ired_timer_callback;
    ired_timer_args.name = "ired";
    

    esp_timer_create(&ired_timer_args, &ired_timer);
    esp_timer_start_periodic(ired_timer, 26);// 26.315789473684 µs = 38 KHz
    //esp_timer_start_once(ired_timer, 50);// 26.315789473684 µs = 38 KHz
    ets_printf("[%s] Started InfraRed timer\n", TAGIR);	
}
//-----------------------------------------------------------------------------
void enIntIRED()
{
    irparams.rcvstate = STATE_IDLE;
    irparams.rawlen = 0;

irparams.timer = 0;


/*    gpio_config_t ir_conf = {
        .intr_type = GPIO_PIN_INTR_ANYEDGE,//GPIO_PIN_INTR_POSEDGE;
        .pin_bit_mask = GPIO_INPUT_PIN_SEL_IRED,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 1
    };
    gpio_config(&ir_conf);

    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(IRED_Pin, ired_isr_handler, (void *)IRED_Pin);
*/

}
//-----------------------------------------------------------------------------
void resumeIRED() // Restart the ISR state machine
{
	irparams.rcvstate = STATE_IDLE;
	irparams.rawlen = 0;

irparams.timer = 0;

}
//-----------------------------------------------------------------------------
int16_t compareIRED(uint16_t oldval, uint16_t newval)
{
	     if (newval < oldval * .8) return 0;
	else if (oldval < newval * .8) return 2;
	else return 1;
}
//-----------------------------------------------------------------------------
int32_t decodeHashIRED(decode_results *results)
{
	int32_t hash = FNV_BASIS_32;

	if (results->rawlen < 6) return 0;

	for (int16_t i = 1; (i + 2) < results->rawlen; i++) {
		int16_t value = compareIRED(results->rawbuf[i], results->rawbuf[i + 2]);
		hash = (hash * FNV_PRIME_32) ^ value;
	}

	results->value = hash;
	results->bits = 32;

	return 1;
}
//-----------------------------------------------------------------------------


#endif







