/* Copyright (c) 2026 The F9 Microkernel Project. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "board.h"
#include <platform/stm32f429/gpio.h>
#include <platform/stm32f429/rcc.h>
#include <platform/stm32f429/registers.h>
#include <platform/stm32f429/usart.h>
#include "init_hook.h"

struct usart_dev console_uart = {
    .u_num = 3,
    .baud = 115200,
    BOARD_USART_CONFIGS.tx =
        {
            .port = BOARD_USART_TX_IO_PORT,
            .pin = BOARD_USART_TX_IO_PIN,
            .pupd = GPIO_PUPDR_NONE,
            .type = GPIO_MODER_ALT,
            .func = BOARD_USART_FUNC,
            .o_type = GPIO_OTYPER_PP,
            .speed = GPIO_OSPEEDR_50M,
        },
    .rx =
        {
            .port = BOARD_USART_RX_IO_PORT,
            .pin = BOARD_USART_RX_IO_PIN,
            .pupd = GPIO_PUPDR_NONE,
            .type = GPIO_MODER_ALT,
            .func = BOARD_USART_FUNC,
            .o_type = GPIO_OTYPER_PP,
            .speed = GPIO_OSPEEDR_50M,
        },
};

#ifdef CONFIG_HAS_ETHERNET
/** RMII GPIO configuration table */
static const struct gpio_cfg rmii_pins[] = {
    /* Port A */
    {GPIOA, 1, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* REF_CLK */
    {GPIOA, 2, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* MDIO */
    {GPIOA, 7, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* CRS_DV */
    /* Port B */
    {GPIOB, 13, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* TXD1 */
    /* Port C */
    {GPIOC, 1, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* MDC */
    {GPIOC, 4, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* RXD0 */
    {GPIOC, 5, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* RXD1 */
    /* Port G */
    {GPIOG, 11, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* TX_EN */
    {GPIOG, 13, GPIO_PUPDR_NONE, GPIO_OSPEEDR_100M, GPIO_MODER_ALT, af_eth,
     GPIO_OTYPER_PP}, /* TXD0 */
};

#define RMII_PIN_COUNT (sizeof(rmii_pins) / sizeof(rmii_pins[0]))

static void eth_interface_init(void)
{
    /* Enable SYSCFG clock for MII/RMII selection */
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFGEN, 1);

    /* Select RMII mode in SYSCFG before enabling ETH clocks */
    *SYSCFG_PMC |= SYSCFG_PMC_MII_RMII_SEL;

    /* Enable GPIO clocks for RMII pins */
    RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN |
                               RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOGEN,
                           1);

    /* Configure RMII pins */
    for (unsigned int i = 0; i < RMII_PIN_COUNT; i++) {
        gpio_config((struct gpio_cfg *) &rmii_pins[i]);
    }
}
#endif /* CONFIG_BOARD_HAS_ETHERNET */

static const struct gpio_cfg led_pins[] = {
    /* Port B */
    {GPIOB, 0, GPIO_PUPDR_NONE, GPIO_OSPEEDR_2M, GPIO_MODER_OUT, af_system,
     GPIO_OTYPER_PP}, /* LED1 */
    {GPIOB, 7, GPIO_PUPDR_NONE, GPIO_OSPEEDR_2M, GPIO_MODER_OUT, af_system,
     GPIO_OTYPER_PP}, /* LED2*/
    {GPIOB, 14, GPIO_PUPDR_NONE, GPIO_OSPEEDR_2M, GPIO_MODER_OUT, af_system,
     GPIO_OTYPER_PP}, /* LED3 */
};

static void leds_init(void)
{
    /* Enable GPIOB clock for LED pins */
    RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOBEN, 1);

    /* Configure LED pins */
    for (unsigned int i = 0; i < sizeof(led_pins) / sizeof(led_pins[0]); i++) {
        gpio_config((struct gpio_cfg *) &led_pins[i]);
    }
}

void board_init(void)
{
    leds_init();
#ifdef CONFIG_HAS_ETHERNET
    eth_interface_init();
#endif
}

INIT_HOOK(board_init, INIT_LEVEL_PLATFORM);
