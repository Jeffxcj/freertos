//
// Created by 19454 on 2022-11-30.
//

#include "motorcontrl.h"
#include "tim.h"

void BLDC_PHASE_CHANGE(uint8_t state) //���û��ຯ��
{
    switch (state) {
        case 1:
           //printf("����ͨ��1\r\n");     //UVW:001   W��H  V:L
              HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
              HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
              HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
              HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);   //VL
              HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);      //WH
              HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
            break;
        case 2:
           // printf("����ͨ��2\r\n");     //UVW:010   V��H  U:L
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);    //UL
            HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);       //VH
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
            break;
        case 3:
           // printf("����ͨ��3\r\n");     //UVW:011   W��H  U:L
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);     //UL
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);        //WH
            HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
            break;
        case 4:
            //printf("����ͨ��4\r\n");     //UVW:100   U:H  W��L
            HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);       //UH
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);   //WL
            break;
        case 5:
           // printf("����ͨ��5\r\n");     //UVW:101   U:H  V:L
            HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);     //UH
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);      //VL
            HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
            break;
        case 6:
           // printf("����ͨ��6\r\n");     //UVW:110   V:H  W:L
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);      //VH
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);   //WL
            break;
        default:
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
            HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
            HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
    }
}