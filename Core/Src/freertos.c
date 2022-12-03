/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "adc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
u_char Uart_Rx[10] = {0};                        //串口指令接受
__IO uint16_t ADC_ConvertedValue[6]={0};         //ADC采样结果
float ADC_ConvertedValueLocal[6]={0};

float ADC_ACCele = 0.0;
float ADC_Voltage = 0.0;
float ADC_IA = 0.0;
float ADC_IB = 0.0;
float ADC_IC = 0.0;
float ADC_IBUS = 0.0;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myled0Handle;
osThreadId myled1Handle;
osThreadId myTask04Handle;
osMessageQId TestQueueHandle;
osSemaphoreId UartDMABinarySem01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void myled0_task(void const * argument);
void myled1_task(void const * argument);
void StartTask04(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of UartDMABinarySem01 */
  osSemaphoreDef(UartDMABinarySem01);
  UartDMABinarySem01Handle = osSemaphoreCreate(osSemaphore(UartDMABinarySem01), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of TestQueue */
  osMessageQDef(TestQueue, 4, uint32_t);
  TestQueueHandle = osMessageCreate(osMessageQ(TestQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1280);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myled0 */
  osThreadDef(myled0, myled0_task, osPriorityNormal, 0, 128);
  myled0Handle = osThreadCreate(osThread(myled0), NULL);

  /* definition and creation of myled1 */
  osThreadDef(myled1, myled1_task, osPriorityNormal, 0, 128);
  myled1Handle = osThreadCreate(osThread(myled1), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, StartTask04, osPriorityNormal, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
//    float ADC_ACCele = 0.1;
//    float ADC_Voltage = 0.1;

  /* Infinite loop */
  for(;;)
  {
      ADC_ACCele =(float)ADC_ConvertedValue[0]/4096*3.3;//读取旋转电位器电压值
      ADC_Voltage = (float)ADC_ConvertedValue[1]/4096*3.3*16;//读取电源电压值          打印任务不要放在此任务中，和串口冲突
      printf("当前电位器电压: %0.2f V \r\n",ADC_ACCele);
      printf("当前电源电压: %0.2f V \r\n",ADC_Voltage);
      osDelay(1000);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_myled0_task */
/**
* @brief Function implementing the myled0 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_myled0_task */
void myled0_task(void const * argument)
{
  /* USER CODE BEGIN myled0_task */
    BaseType_t xReturn = pdPASS;
    uint32_t r_queue;
  /* Infinite loop */
  for(;;)
  {
      HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_SET);
      vTaskDelay(100);
      HAL_GPIO_WritePin(led0_GPIO_Port,led0_Pin,GPIO_PIN_RESET);
      vTaskDelay(100);
      xReturn = xQueueReceive( TestQueueHandle,                //消息队列具有超时机制，当队列中没有数据时，会把任务挂起来，一有数据就会开始执行
                               &r_queue,                      //使用消息队列可以有效的解决中断服务程序和任务之间的消息传递的问题
                               0);
      if(pdTRUE == xReturn)
      {
          printf("本次消息队列中的数据为：%d\r\n",r_queue);
      }
      else if(pdTRUE == errQUEUE_FULL)
      {
          printf("数据接收出错，错误代码0x%lx\n",xReturn);
      }
  }
  /* USER CODE END myled0_task */
}

/* USER CODE BEGIN Header_myled1_task */
/**
* @brief Function implementing the myled1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_myled1_task */
void myled1_task(void const * argument)
{
  /* USER CODE BEGIN myled1_task */
    BaseType_t xReturn = pdPASS;  //定义一个创建信息返回值
    __HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart4,(uint8_t*)Uart_Rx,10);
  /* Infinite loop */
  for(;;)
  {
      xReturn = xSemaphoreTake(UartDMABinarySem01Handle,portMAX_DELAY);
      if(pdPASS == xReturn)
      {
          printf("进行串口DMA接受\r\n");
          printf("收到的数据为:%s\r\n",Uart_Rx);
          memset(Uart_Rx,0, sizeof(Uart_Rx));//清零操作
         // HAL_UART_Receive_DMA(&huart4,(uint8_t*)Uart_Rx,10);
      }
  }
  /* USER CODE END myled1_task */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void const * argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
      osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
