/* 
 * gpio example in c using mraa
 *
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 *
 * Usage: Toggles GPIO 23 and 24
 *
 * Compilation: gcc mraa_gpio.c -o bin -lmraa
 * 
 * https://github.com/96boards/documentation/blob/master/consumer/guides/mraa/gpio/mraa_gpio.c
 * 
 */

/* standard headers */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* mraa header */
#include "mraa/gpio.h"

/* gpio starts from 23 as per LS header pinout */
#define GPIO_1 23
#define GPIO_2 24

int flag = 1;

void sig_handler(int signum)
{
	if (signum == SIGINT) {
		fprintf(stdout, "Program interrupted\n");
		flag = 0;
	}
}

int main(void)
{
	mraa_gpio_context gpio_1, gpio_2;
	mraa_result_t res = MRAA_SUCCESS;

	/* install signal handler */
	signal(SIGINT, sig_handler);

	/* initialize mraa for the platform. not needed most of the times */
	mraa_init();

	/* initialize gpio 23 */
	gpio_1 = mraa_gpio_init(GPIO_1);
	if (gpio_1 == NULL) {
		fprintf(stderr, "Failed to initialize pin %d\n", GPIO_1);
	}

	/* initialize gpio 24 */
	gpio_2 = mraa_gpio_init(GPIO_2);
        if (gpio_2 == NULL) {
                fprintf(stderr, "Failed to initialize pin %d\n", GPIO_2);
        }

	/* set gpio 23 to output */
	res = mraa_gpio_dir(gpio_1, MRAA_GPIO_OUT);
	if (res != MRAA_SUCCESS)
		goto err;
	
        /* set gpio 24 to output */
        res = mraa_gpio_dir(gpio_2, MRAA_GPIO_OUT);
        if (res != MRAA_SUCCESS)
		goto err;


	// start timer
	clock_t t;
    t = clock();


	/* toggle both gpio's */
	for(int i=0; i < 1000000; i++) {
		res = mraa_gpio_write(gpio_1, 1);
		if (res != MRAA_SUCCESS)
			goto err;

                // res = mraa_gpio_write(gpio_2, 0);
                // if (res != MRAA_SUCCESS)
                //         goto err;
		
		// sleep(1);

                res = mraa_gpio_write(gpio_1, 0);
                if (res != MRAA_SUCCESS)
                        goto err;

                // res = mraa_gpio_write(gpio_2, 1);
                // if (res != MRAA_SUCCESS)
                //         goto err;

		// sleep(1);
	}




	// stop timer
    t = clock() - t;
    double seconds = ((float)t)/CLOCKS_PER_SEC;
    printf("Time taken in seconds: %f, aka %f MHz", seconds, 1/seconds);


	/* release gpio's */
	res = mraa_gpio_close(gpio_1);
	if (res != MRAA_SUCCESS) {
		mraa_result_print(res);
	}

        res = mraa_gpio_close(gpio_2);
        if (res != MRAA_SUCCESS) {
                mraa_result_print(res);
        }

	return res;

err:
	mraa_result_print(res);
	return res;

}