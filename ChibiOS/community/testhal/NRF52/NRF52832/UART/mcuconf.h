/*
    Copyright (C) 2015 Stephen Caudle

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

#ifndef _MCUCONF_H_
#define _MCUCONF_H_

/*
 * HAL driver system settings.
 */
#define NRF5_UART_USE_UART0               TRUE
#define NRF5_UART_UART0_IRQ_PRIORITY      3
#define NRF5_ST_USE_RTC0                  TRUE
#define NRF5_ST_USE_RTC1                  FALSE
#define NRF5_ST_USE_TIMER0                FALSE

#endif /* _MCUCONF_H_ */
