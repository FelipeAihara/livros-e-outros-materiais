#include <zephyr/device.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

static const struct device *const strip = DEVICE_DT_GET(DT_NODELABEL(status_led));

int main(void) {
    printk("Iniciando código!\n");

    if (!device_is_ready(&strip)) {
        printk("FALHA: driver do LED não está pronto (RMT/overlay)\n");
        return 0;
    }

    // printk("Tamanho: %d\n", led_strip_length(strip));

    // while (1) {
        
    // }
}