/* WindOMaticX
 *
 * Since I could not find the source to the windomatic 6000...
 * 
 * Uses this
 * Pico Stepper library by Antonio González
 *  https://github.com/antgon/pico-stepper.git
 *
 * And this
 * 
 * 
 */


#include <stdio.h>
#include "pico/stdlib.h"
#include "ssd1306.h"
#include "stepper.h"



#ifndef PICO_DEFAULT_LED_PIN
#warning Standard libraries did not get included
#endif

#define STEPPER_ENABLE_PIN 11

// oled constants
const int ITCPIN1 = 12;
const int BUTTON_PIN = 15;
const int LED_PIN = 25;
const int DEBOUNCE_DELAY_MS = 50;


// Stepper constants.
stepper_t stepper;
const uint8_t stepper_pin_enable = 3;
const uint8_t stepper_pin_1A = 12;
const uint8_t stepper_pin_1B = 13;
const uint8_t stepper_pin_2A = 14;
const uint8_t stepper_pin_2B = 15;
const uint16_t stepper_steps_per_revolution = 200;
const stepper_mode_t stepping_mode = single;
uint8_t speed = 20;


// Initialize the GPIO for the LED
void pico_led_init(void) {
#ifdef PICO_DEFAULT_LED_PIN
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
#endif
}

// Turn the LED on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#endif
}




int main() {
    stdio_init_all();
    
    sleep_ms(2000);
    printf("GO\n");

    //Setup the OLED Screen
    i2c_init(i2c1, 400000);  /* was i2c0 */
    gpio_pull_up(10);   /* was 12 */
    gpio_pull_up(11);   /* was 13 */
    gpio_set_function(10, GPIO_FUNC_I2C);   /* was 12 */
    gpio_set_function(11, GPIO_FUNC_I2C);   /* was 13 */
    ssd1306_t oled;
    oled.external_vcc=false;
    bool res = ssd1306_init(
                    &oled,
                    128,
                    64,
                    0x3c,
                    i2c1);



    // Initialise the stepper
    stepper_init(&stepper, stepper_pin_1A, stepper_pin_1B,
                 stepper_pin_2A, stepper_pin_2B,
                 stepper_steps_per_revolution, stepping_mode);
    stepper_set_speed_rpm(&stepper, speed);

    // Enable stepper
    pico_led_init();
      pico_set_led(true);
      // Initialize the GPIO to blink the LED
      //
      gpio_init(STEPPER_ENABLE_PIN);
      gpio_set_dir(STEPPER_ENABLE_PIN, GPIO_OUT);
      gpio_put(STEPPER_ENABLE_PIN, true);
      
    while (true) {


      // Rotate 3/4 of a turn.
      stepper_rotate_degrees(&stepper, 360);
      sleep_ms(500);

      // Now rotate these many steps in the oposite direction
      stepper_rotate_steps(&stepper, -45);
      sleep_ms(500);

      // Increase the speed and rotate 360 degrees
      speed = 50;
      stepper_set_speed_rpm(&stepper, speed);
      stepper_rotate_degrees(&stepper, 360);
      
      // Release the coils and sleep for a while. You can check that
      // the coils are not energised by moving the rotor manually:
      // there should be little resistance.
      stepper_release(&stepper);
      sleep_ms(4000);
      
      // Decrease the speed
      speed = 15;
      stepper_set_speed_rpm(&stepper, speed);
    }
    return 0;
}

