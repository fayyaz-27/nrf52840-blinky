/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define RED DT_ALIAS(led0)
#define GREEN DT_ALIAS(led1)
#define BLUE DT_ALIAS(led2)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led_red = GPIO_DT_SPEC_GET(RED, gpios);
static const struct gpio_dt_spec led_green = GPIO_DT_SPEC_GET(GREEN, gpios);
static const struct gpio_dt_spec led_blue = GPIO_DT_SPEC_GET(BLUE, gpios);


int main(void)
{
	int ret;

	if (!(gpio_is_ready_dt(&led_red) && (gpio_is_ready_dt(&led_green)) && (gpio_is_ready_dt(&led_blue)))) {
		return 0;
	}

	ret = (gpio_pin_configure_dt(&led_red, GPIO_OUTPUT_ACTIVE) + (gpio_pin_configure_dt(&led_green, GPIO_OUTPUT_ACTIVE)) 
                + gpio_pin_configure_dt(&led_blue, GPIO_OUTPUT_ACTIVE));
	if (ret < 0) {
		return 0;
	}

	while (1) {
                gpio_pin_set_dt(&led_red, 0);
                gpio_pin_set_dt(&led_green, 0);
                gpio_pin_set_dt(&led_blue, 0);
                k_msleep(SLEEP_TIME_MS);
                
		gpio_pin_set_dt(&led_red, 1);
                k_msleep(SLEEP_TIME_MS);
                
                // gpio_pin_set_dt(&led_red, 0);
                gpio_pin_set_dt(&led_green, 1);
                k_msleep(SLEEP_TIME_MS);

                // gpio_pin_set_dt(&led_green, 0);
                gpio_pin_set_dt(&led_blue, 1);
                k_msleep(SLEEP_TIME_MS);

                
		
	}
	return 0;
}