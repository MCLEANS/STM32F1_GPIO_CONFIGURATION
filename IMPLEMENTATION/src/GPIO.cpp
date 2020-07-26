/*
 * GPIO.cpp
 *
 *  Created on: May 4, 2020
 *      Author: MCLEANS
 */

#include "GPIO.h"

namespace custom_libraries {

_GPIO::_GPIO(GPIO_TypeDef *GPIO,uint8_t PIN):GPIO(GPIO),
											PIN(PIN),
											mode(OUTPUT),
											type(OPEN_DRAIN),
											speed(LOW),
											state(FLOATING){
	//Enable GPIO RCC
	if(GPIO == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	if(GPIO == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	if(GPIO == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	if(GPIO == GPIOD) RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	if(GPIO == GPIOE) RCC->APB2ENR |= RCC_APB2ENR_IOPEEN;

}

void _GPIO::pin_mode(Mode mode){
	this->mode = mode;

	if(mode == INPUT){
		if(PIN < 8){
			GPIO->CRL &= ~(1<<((PIN*4)));
			GPIO->CRL &= ~(1<<((PIN*4)+1));
			//INPUT WITH PULL-UP/PULL-DOWN
			GPIO->CRL &= ~(1<<(((PIN*4)+2)));
			GPIO->CRL |= (1<<(((PIN*4)+2)+1));
		}
		else{
			GPIO->CRH &= ~(1<<(((PIN-8)*4)));
			GPIO->CRH &= ~(1<<(((PIN-8)*4)+1));
			//INPUT WITH PULL-UP/PULL-DOWN
			GPIO->CRH &= ~(1<<((((PIN-8)*4)+2)));
			GPIO->CRH |= (1<<((((PIN-8)*4)+2)+1));

		}

	}
	else if(mode == OUTPUT){
		if(PIN < 8){
			GPIO->CRL &= ~(1<<((PIN*4)));
			GPIO->CRL |= (1<<((PIN*4)+1));
		}
		else{
			GPIO->CRH &= ~(1<<(((PIN-8)*4)));
			GPIO->CRH |= (1<<(((PIN-8)*4)+1));
		}

	}
}

void _GPIO::output_settings(OUTPUT_Type type, OUTPUT_Speed speed){
	this->type = type;
	this->speed = speed;

	if(type == OPEN_DRAIN){
		if(PIN < 8){
			GPIO->CRL &= ~(1<<(((PIN*4)+2)));
			GPIO->CRL |= (1<<(((PIN*4)+2)+1));
		}
		else{

			GPIO->CRH &= ~(1<<((((PIN-8)*4)+2)));
			GPIO->CRH |= (1<<((((PIN-8)*4)+2)+1));
		}
	}
	else if(type == PUSH_PULL){
		if(PIN < 8){
			GPIO->CRL &= ~(1<<(((PIN*4)+2)));
			GPIO->CRL &= ~(1<<(((PIN*4)+2)+1));
		}
		else{
			GPIO->CRH &= ~(1<<((((PIN-8)*4)+2)));
			GPIO->CRH &= ~(1<<((((PIN-8)*4)+2)+1));
		}

	}

	if(speed == LOW){
		if(PIN < 8){
			GPIO->CRL |= (1<<((PIN*4)));
			GPIO->CRL &= ~(1<<((PIN*4)+1));
		}
		else{
			GPIO->CRH |= (1<<(((PIN-8)*4)));
			GPIO->CRH &= ~(1<<(((PIN-8)*4)+1));
		}
	}
	else if(speed == MEDUIM){
		if(PIN < 8){
			GPIO->CRL &= ~(1<<((PIN*4)));
			GPIO->CRL |= (1<<((PIN*4)+1));
		}
		else{

			GPIO->CRH &= ~(1<<(((PIN-8)*4)));
			GPIO->CRH |= (1<<(((PIN-8)*4)+1));
		}
	}
	else if(speed == HIGH){
		if(PIN < 8){
			GPIO->CRL |= (1<<((PIN*4)));
			GPIO->CRL |= (1<<((PIN*4)+1));
		}
		else{
			GPIO->CRH |= (1<<(((PIN-8)*4)));
			GPIO->CRH |= (1<<(((PIN-8)*4)+1));
		}
	}

}

void _GPIO::digital_write(bool value){
	if(value){
		GPIO->ODR |= (1<<PIN);
	}
	if(!value){
		GPIO->ODR &= ~(1<<PIN);
	}
}

bool _GPIO::digital_read(void)const{
	if(GPIO->IDR & (1<<PIN)){
		return true;
	}

	return false;
}

_GPIO::~_GPIO() {
	// TODO Auto-generated destructor stub
}

} /* namespace custom_libraries */
