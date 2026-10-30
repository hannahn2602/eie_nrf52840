/*
* main.c
*/

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec leds[] = {
  GPIO_DT_SPEC_GET(LED0_NODE, gpios),
  GPIO_DT_SPEC_GET(LED1_NODE, gpios),
  GPIO_DT_SPEC_GET(LED2_NODE, gpios),
  GPIO_DT_SPEC_GET(LED3_NODE, gpios)
};

#define NUM_LEDS 4
#define SLEEP_MS 500

int main(void) {
    int ret;

    // CHeck and configure LED
    for(int i = 0; i<NUM_LEDS; i++){
      if(!gpio_is_ready_dt(&leds[i])){
        return -1;
      }

      ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_ACTIVE);
      if (ret < 0){
        return ret;
      }
    }
    while (1) {
        //toggle every LED
        for (int i = 0; i <NUM_LEDS;i++){
          gpio_pin_toggle_dt(&leds[i]);
        }
        k_msleep(SLEEP_MS);
    }
    return 0;
}