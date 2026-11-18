// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Alguns includes, defines, variáveis etc.
#include <zephyr/kernel.h>
#include <zephyr/drivers/led_strip.h>
#include <string.h>
#include <zephyr/sys/printk.h>
#include <zephyr/console/console.h>

static const struct device *strip = DEVICE_DT_GET(DT_ALIAS(led_strip));

#define PRIORITY 5
#define STACKSIZE 1024

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// Definir thread pisca_led

void blink(void)
{
	struct led_rgb px;

    while (1) {
        px = (struct led_rgb){ .r = 0, .g = 0, .b = 40 };  /* azul */
		led_strip_update_rgb(strip, &px, 1);
		k_msleep(500);

		px = (struct led_rgb){ 0 };                         /* apagado */
		led_strip_update_rgb(strip, &px, 1);
		k_msleep(500);
    }
}

K_THREAD_DEFINE(blink0_id, STACKSIZE, blink, NULL, NULL, NULL,
		PRIORITY, 0, 0);

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
// main

int main(void)
{
    // console_getline_init();
	if (!device_is_ready(strip)) {
		return 0;
	}

    return 0;
}