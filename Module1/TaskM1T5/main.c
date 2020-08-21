#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "periph/gpio.h"

gpio_t led = GPIO_PIN(1, 5);     // PB5, Arduino GPIO13
gpio_t sensor = GPIO_PIN(3, 2);  // Pin 2, Arduino GPIO2

void DetectMotion(void)
{
    int motion = gpio_read(sensor);
    int previous = 0;
    bool check = false;

    puts("Task 1.5HD Start");

    while (1)
    {
        if (motion)
        {
            gpio_set(led);
            if (previous == 0) {
                puts("LED on");
            }
            previous = 1;
            
            if (!check) {	
                puts("Motion detected");
                check = true;
            }
        }
        else
        {
            gpio_clear(led); // turn LED OFF
            if (previous == 1) {
                puts("LED off");
            }
            previous = 0;
            
            if (check){
                puts("Motion ended");
                check = false;
            }
        }
    }
}

int main(void)
{
    gpio_init(led, GPIO_OUT);

    gpio_init_int(sensor, GPIO_IN_PU, GPIO_BOTH, (gpio_cb_t)DetectMotion, NULL);
    gpio_irq_enable(sensor);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}