#include "bsp_button.h"

void button_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin =  GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t scanf_button(void)
{
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



