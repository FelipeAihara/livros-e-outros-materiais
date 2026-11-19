// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Alguns includes, defines, variáveis globais etc.
#include <stdlib.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/sys/printk.h>
#include <zephyr/console/console.h>

#define PRIORITY_BLINK 6
#define PRIORITY_READ_INPUT 5
#define STACKSIZE 1024

static const struct device *strip = DEVICE_DT_GET(DT_ALIAS(led_strip));
static volatile int sleep_delay_ms = 500;

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Definir thread pisca_led

void blink(void)
{
	if (!device_is_ready(strip)) {
		return;
	}

	struct led_rgb px;

    while (1) {
        px = (struct led_rgb){ .r = 0, .g = 0, .b = 40 };  /* azul */
		led_strip_update_rgb(strip, &px, 1);
		k_msleep(sleep_delay_ms);

		px = (struct led_rgb){ 0 };                         /* apagado */
		led_strip_update_rgb(strip, &px, 1);
		k_msleep(sleep_delay_ms);
    }
}

K_THREAD_DEFINE(blink0_id, STACKSIZE, blink, NULL, NULL, NULL,
		PRIORITY_BLINK, 0, 0);

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Definir thread que lê o input do console

void read_input(void)
{
	console_getline_init();

    while (1) {
		printk("Insira uma linha: \n");
		char *s = console_getline();

		if (atoi(s) > 0) sleep_delay_ms = atoi(s);
    }
}

K_THREAD_DEFINE(read_input_id, STACKSIZE, read_input, NULL, NULL, NULL,
		PRIORITY_READ_INPUT, 0, 0);

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------