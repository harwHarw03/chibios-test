/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

static virtual_timer_t vt1, vt2;

static void restart(virtual_timer_t *vtp, void *p) {

  (void)vtp;
  (void)p;

  chSysLockFromISR();
  uartStartSendI(&UARTD2, 14, "Hello World!\r\n");
  chSysUnlockFromISR();
}

static void ledoff(virtual_timer_t *vtp, void *p) {

  (void)vtp;
  (void)p;

  palSetPad(IOPORT3, GPIOC_LED);
}

/*
 * This callback is invoked when a transmission buffer has been completely
 * read by the driver.
 */
static void txend1(UARTDriver *uartp) {

  (void)uartp;

  palClearPad(IOPORT3, GPIOC_LED);
}

/*
 * This callback is invoked when a transmission has physically completed.
 */
static void txend2(UARTDriver *uartp) {

  (void)uartp;

  palSetPad(IOPORT3, GPIOC_LED);
  chSysLockFromISR();
  chVTResetI(&vt1);
  chVTDoSetI(&vt1, TIME_MS2I(5000), restart, NULL);
  chSysUnlockFromISR();
}

/*
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 */
static void rxerr(UARTDriver *uartp, uartflags_t e) {

  (void)uartp;
  (void)e;
}

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 */
static void rxchar(UARTDriver *uartp, uint16_t c) {

  (void)uartp;
  (void)c;

  /* Flashing the LED each time a character is received.*/
  palClearPad(IOPORT3, GPIOC_LED);
  chSysLockFromISR();
  chVTResetI(&vt2);
  chVTDoSetI(&vt2, TIME_MS2I(200), ledoff, NULL);
  chSysUnlockFromISR();
}

/*
 * This callback is invoked when a receive buffer has been completely written.
 */
static void rxend(UARTDriver *uartp) {

  (void)uartp;
}

/*
 * UART driver configuration structure.
 */
static UARTConfig uart_cfg_1 = {
  txend1,
  txend2,
  rxend,
  rxchar,
  rxerr,
  NULL,
  38400,
  0,
  USART_CR2_LINEN,
  0
};

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Activates the serial driver 2 using the driver default configuration.
   */
  uartStart(&UARTD2, &uart_cfg_1);

  /*
   * Starts the transmission, it will be handled entirely in background.
   */
  uartStartSend(&UARTD2, 13, "Starting...\r\n");

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
  return 0;
}
