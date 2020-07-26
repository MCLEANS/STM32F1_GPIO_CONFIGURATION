/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "GPIO.h"

custom_libraries::_GPIO LED(GPIOC,14);
			
int main(void)
{
	LED.pin_mode(custom_libraries::OUTPUT);
	LED.output_settings(custom_libraries::PUSH_PULL,custom_libraries::HIGH);

	while(1){
		LED.digital_write(true);
		for(int i =0; i<100000;i++){}
		LED.digital_write(false);
		for(int i =0; i<100000;i++){}
	}
}
