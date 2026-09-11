/*
 * @Author       : Yuan Ge
 * @Date         : 2024-05-31
 * @LastEditors  : Yuan Ge
 * @LastEditTime : 2024-07-15 
 * @Description  : 
 * @FilePath    ppppp : 
 */
#include "os.h"
#include "motor.h"
#include "tim.h"
#include "mpu6050.h"
#include "usart.h"
#include "oled.h"
#include "sr04.h"
#include "encoder.h"
#include "DHT11.h"
#include "BatteryVoltage.h"
#include "iic.h"
#include "filter.h"
#include "delay.h"
#include "canmessage.h"
#include "BalanceCar.h"
#include "bluetoothdata.h"

#define BALANCECAROFFSET	(1.0F)

/* ── 避障转向参数（复刻模型 ReverseLazer 状态图的算法） ── */
#define ENABLE_DIRECTION_AVOID		(1u)/* 1: 使能避障转向, 0: 关闭 */
#define DIR_MIN_VALID_CM			(2.0f)/* 小于此值视为无效读数(HC-SR04 最小量程约 2cm) */
#define DIR_TIER_DANGER_CM			(10.0f)/* 复刻 TruthTable 档位 1: Dangerous */
#define DIR_TIER_CAREFUL_CM			(30.0f)/* 档位 2: Carefull */
#define DIR_TIER_WARNING_CM			(50.0f)/* 档位 3: Warning */
#define DIR_STEP_UP					(5.0f)/* 转向量每 20ms 增加量(作者原值 5) */
#define DIR_STEP_DOWN				(10.0f)/* 转向量每 20ms 减少量(作者原值 10) */
#define DIR_RAMP_LIMIT				(20.0f)/* 转向上限(作者原值 100, 饱和后易甩倒, 先保守) */



uint16_t BalanceCarTaskCount;				/* For task period count */
uint8_t temperature = 1 ; 
uint8_t humidity = 1;
uint8_t BatteryVoltage = 0;/* 0V */
float Distance;
int16_t CurrentMotor1Speed;
int16_t CurrentMotor2Speed;
int16_t LastMotor1Speed;
int16_t LastMotor2Speed;
uint8_t Period_5ms_Count;						/* 5ms task period count */
uint8_t Period_10ms_Count;					/* 10ms task period count */
uint8_t Period_20ms_Count;					/* 20ms task period count */
uint8_t Period_100ms_Count;					/* 100ms task period count */
uint8_t Period_1000ms_Count;				/* 1000ms task period count */
uint8_t Txbuffer[TX_DATA_LEN] = {0};/* Transmit data buffer */
uint8_t Rxbuffer[RX_DATA_LEN] = {0};/* Receive data buffer */

uint8_t BluetoothTxbuffer[BLUETOOTH_TX_DATA_LEN] = {0};/* Transmit data buffer */
uint8_t BluetoothRxbuffer[BLUETOOTH_RX_DATA_LEN] = {0};/* Transmit data buffer */
_Bool Period_1ms_Expire_Flag = false;
_Bool Period_5ms_Expire_Flag = false;
_Bool Period_10ms_Expire_Flag = false;
_Bool Period_20ms_Expire_Flag = false;
_Bool Period_100ms_Expire_Flag = false;
_Bool Period_1000ms_Expire_Flag = false;

uint8_t XunjiInput1;
uint8_t XunjiInput2;
uint8_t XunjiInput3;
uint8_t XunjiInput4;
uint8_t XunjiInput5;
uint8_t XunjiInput6;

/* ── 避障转向状态机 ── */
typedef enum
{
	AVOID_IDLE = 0,					/* 复刻 Default1 */
	AVOID_TURNING,					/* 复刻 TurnDirection1 */
	AVOID_END,						/* 复刻 End1 */
	AVOID_STOPPING					/* 复刻 StopTurn */
} AvoidState_t;

static AvoidState_t AvoidState = AVOID_IDLE;
static float AvoidDTPWM = 0.0f;				/* 写入模型的转向量 */
static uint8_t AvoidHoldCount = 0;			/* End1 状态保持计数 */

static void Task_1ms(void);
static void Task_5ms(void);
static void Task_10ms(void);
static void Task_20ms(void);
static void Task_100ms(void);
static void Task_1000ms(void);
static void SetModelInput(void);
static void SetModelOutput(void);
static uint8_t AvoidTier_Get(void);
static void DirectionAvoid_Update(void);


#if USE_NEW_OS

/* USER CODE BEGIN PV */
typedef void (*TaskFunction_t)(void);

typedef struct {
    TaskFunction_t function;
    uint32_t period;
    uint32_t elapsed;
    bool run;
} Task_t;

GPIO_PinState Key1State,Key2State,SSBState;
uint32_t adc_value;
extern uint8_t CanTxData[8];
/* ??CAN??????????? */

static Task_t taskList[MAX_TASKS];
static uint8_t taskCount = 0;
volatile uint32_t systemTime = 0;
/* USER CODE END PV */

/* USER CODE BEGIN PFP */
void OS_Init(void);
uint8_t OS_AddTask(TaskFunction_t function, uint32_t period);
void OS_Scheduler(void);
void OS_Update(void);

static void Task_1ms(void);
static void Task_5ms(void);
static void Task_10ms(void);
static void Task_20ms(void);
static void Task_100ms(void);
static void Task_500ms(void);
static void Task_1000ms(void);
/* USER CODE END PFP */

/* USER CODE BEGIN 4 */
void OS_Init(void) 
{
	taskCount = 0;
	systemTime = 0;
	memset(taskList, 0, sizeof(taskList)); // ??????
	
	OS_AddTask(Task_1ms, 1);
	OS_AddTask(Task_5ms, 5);
	OS_AddTask(Task_10ms, 10);
	OS_AddTask(Task_20ms, 20);
	OS_AddTask(Task_100ms, 100);
	OS_AddTask(Task_500ms, 500);
	OS_AddTask(Task_1000ms, 1000);
	Hcsr04Init(&htim1, TIM_CHANNEL_1);
	i2cInit();	 													//IIC init
	HAL_Delay(10);
	MPU6050_Init();												//MPU6050 init
	printf("Distance start!");
	Txbuffer[0] = 0xA5;										//Frame header
	Txbuffer[TX_DATA_LEN-1] = 0x5A;										//Frame ender
	HAL_Delay(1500);
	HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_SET);
	HAL_Delay(200);										/* If test motor,need to delay to downloade software to avoid motor run */
	HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET);;/* Stop buzzer */
	OLED_Init();
	ReceiveBluetoothData_Init();
	BalanceCarOffset = BALANCECAROFFSET;
	BalanceCar_initialize(); 						/* Model code init */
}

uint8_t OS_AddTask(TaskFunction_t function, uint32_t period) {
    if(taskCount < MAX_TASKS) {
        taskList[taskCount] = (Task_t){
            .function = function,
            .period = period,
            .elapsed = period, // ??????
            .run = true
        };
        return taskCount++;
    }
    return 0xFF;
}

void OS_Update(void) {
    for(uint8_t i=0; i<taskCount; i++) {
        if(taskList[i].period > 0 && ++taskList[i].elapsed >= taskList[i].period) {
            taskList[i].elapsed = 0;
            taskList[i].run = true;
        }
    }
}

void OS_Scheduler(void) {
    static uint32_t lastExecTime[MAX_TASKS] = {0};
    
    for(uint8_t i=0; i<taskCount; i++) {
        if(taskList[i].run) {
            taskList[i].run = false;
            
            // ??????(??)
            uint32_t start = HAL_GetTick();
            if(taskList[i].function) taskList[i].function();
            lastExecTime[i] = HAL_GetTick() - start;
        }
    }
}
/* USER CODE END 4 */

/* USER CODE BEGIN 0 */
// 1ms??(??????????????)
static void Task_1ms(void) 
{
		SetModelInput();				/* Model input interface */
		BalanceCar_step();		/* Model Task */
		SetModelOutput();				/* Model output interface */
}
// 5ms??
static void Task_5ms(void) 
{
		LastMotor1Speed = GetTim2Encoder();
		LastMotor2Speed = -GetTim4Encoder();
		CurrentMotor1Speed += LastMotor1Speed;
		CurrentMotor2Speed += LastMotor2Speed;
//		CAN_Test();
		//printf("X:%.1f Y:%.1f Z:%d \r\n",Pitch,Roll,gyro[0]);
}
// 10ms Task
static void Task_10ms(void) 
{

}
// 20ms Task
static void Task_20ms(void) 
{
	
		Hcsr04TimeoutHandle();					/* 先结算上一轮: 无回波则判为超量程 */
		Hcsr04Start();							/* 触发下一轮测距 */
		Distance = Hcsr04Read();				/* 取回上一轮测距结果 */
		Model_Distance = Distance;				/* 与原设计一致 */
#if ENABLE_DIRECTION_AVOID
		DirectionAvoid_Update();				/* 避障转向状态机(每 20ms 一拍) */
#endif
		
		/* The follow no used */
		Rxbuffer[0] = (uint8_t)BatteryVoltage;
		Rxbuffer[1] = (uint8_t)BalanceCarTargetSpeed;
		Rxbuffer[2] = (uint8_t)Distance;
		
		Rxbuffer[3] = (uint8_t)(Motor1Speed/10);
		Rxbuffer[4] = (uint8_t)Motor1Speed;
		Rxbuffer[5] = (uint8_t)Motor2Speed;	
		Motor1Speed =  CurrentMotor1Speed;
		Motor2Speed =  CurrentMotor2Speed;
		CurrentMotor1Speed = 0;
		CurrentMotor2Speed = 0;
		BluetoothTxbuffer[0] = BatteryVoltage;
		BluetoothTxbuffer[1] = (uint8_t)Distance;
		BluetoothTxbuffer[2] = (uint8_t)Motor1Speed;
		BluetoothTxbuffer[3] = (uint8_t)Motor2Speed;	
//		printf("Battery:%.1f Distance:%.1f Motor1Speed:%d CurrentMotor2Speed:%d \n",BatteryVoltage,Distance,Motor1Speed,Motor2Speed);
//		HAL_UART_Transmit (&huart2 ,BluetoothTxbuffer,BLUETOOTH_TX_DATA_LEN,HAL_MAX_DELAY );
}
// 100ms Task
static void Task_100ms(void) 
{
	#if ENABLE_OLED_DYNAMIC_DISPLAY
	OLED_ShowString (0,  0, "D:",  16, 0);				/* 距离(cm) */
	OLED_Showdecimal(16, 0, Distance, 3, 1, 16, 0);
	OLED_ShowString (96, 0, "Y:",  16, 0);				/* 障碍档位 0~3 */
	OLED_ShowNum    (112,0, AvoidTier_Get(), 1, 16, 0);
	OLED_ShowString (0,  2, "DT:", 16, 0);				/* 转向量 */
	OLED_Showdecimal(24, 2, AvoidDTPWM, 3, 1, 16, 0);
	OLED_ShowString (0,  4, "R:",  16, 0);				/* 倾角 */
	OLED_Showdecimal(16, 4, Roll, 2, 1, 16, 0);
	OLED_ShowString (56, 4, "P:",  16, 0);				/* 模型算出的 Direction_PWM(绝对值) */
	OLED_ShowNum    (72, 4, (unsigned int)((Direction_PWM < 0) ? -Direction_PWM : Direction_PWM), 4, 16, 0);
	OLED_ShowString (0,  6, "M1:", 16, 0);				/* 两路电机 PWM 实际输出 */
	OLED_ShowNum    (24, 6, Motor1PWM, 4, 16, 0);
	OLED_ShowString (64, 6, "M2:", 16, 0);
	OLED_ShowNum    (88, 6, Motor2PWM, 4, 16, 0);
	#endif
}
// 500ms??
static void Task_500ms(void) 
{
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}
static void Task_1000ms(void)
{
//		DHT11_Read_Data(&temperature , &humidity);	/* Read temperature and humidity */			
		BatteryVoltage = GetBatVoltage();				 		/* Read battery voltage */			
	#if ENABLE_OLED_DYNAMIC_DISPLAY
		OLED_Showdecimal(84,2,BatteryVoltage,2,1,16,0);		/* 电池电压(单位 0.1V) */
	#endif
}
#else

enum os_period period = OS_0MS;
void Os_Init(void)
{
	
	
	OLED_Init();                          //OLED??
	Hcsr04Init(&htim1, TIM_CHANNEL_1);
	i2cInit();	 													//IIC init
	HAL_Delay(10);
	MPU6050_Init();												//MPU6050 init
	printf("Distance start!");
	Txbuffer[0] = 0xA5;										//Frame header
	Txbuffer[TX_DATA_LEN-1] = 0x5A;										//Frame ender
	HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_SET);
	HAL_Delay(200);										/* If test motor,need to delay to downloade software to avoid motor run */
	HAL_GPIO_WritePin(BEEP_GPIO_Port,BEEP_Pin,GPIO_PIN_RESET);;/* Stop buzzer */
	ReceiveBluetoothData_Init();
	BalanceCarOffset = BALANCECAROFFSET;
	BalanceCar_initialize(); 						/* Model code init */
}
void Os_Period(void)
{
	BalanceCarTaskCount++;
	Period_1ms_Expire_Flag = true;			/* 1ms period  */
	switch(BalanceCarTaskCount)
	{
				case OS_5MS_a:
						Period_5ms_Expire_Flag = true;
				break;
				case OS_5MS_b:
					if(Period_10ms_Count >= 2)/* 5ms * 2 = 10ms */
					{
						Period_10ms_Expire_Flag = true;
						Period_10ms_Count = 0;
					}
					else
					{
						Period_10ms_Count++;
					}
				break;
				case OS_5MS_c:
					if(Period_20ms_Count >= 4)/* 5ms * 4 = 20ms */
					{
						Period_20ms_Expire_Flag = true;
						Period_20ms_Count = 0;
					}
					else
					{
						Period_20ms_Count++;
					}
				break;
				case OS_5MS_d:
					if(Period_100ms_Count >= 20)/* 5ms * 20 = 100ms */
					{
						Period_100ms_Expire_Flag = true;
						Period_100ms_Count = 0;
					}
					else
					{
						Period_100ms_Count++;
					}
				break;
				case OS_5MS_e:
					BalanceCarTaskCount = 0;
					if(Period_1000ms_Count >= 200)/* 5ms * 200 = 1000ms */
					{
						Period_1000ms_Expire_Flag = true;
						Period_1000ms_Count = 0;
					}
					else
					{
						Period_1000ms_Count++;
					}		
				break;
				default:
					
				break;
		}
}
void Os_Task(void)
{
	if(Period_1ms_Expire_Flag)
	{
		Task_1ms();
		Period_1ms_Expire_Flag = false;
	}
	if(Period_5ms_Expire_Flag)
	{
		Task_5ms();
		Period_5ms_Expire_Flag = false;
	}
	if(Period_10ms_Expire_Flag)
	{
		Task_10ms();
		Period_10ms_Expire_Flag = false;
	}
	if(Period_20ms_Expire_Flag)
	{
		Task_20ms();
		Period_20ms_Expire_Flag = false;
	}
	if(Period_100ms_Expire_Flag)
	{
		Task_100ms();
		Period_100ms_Expire_Flag = false;
	}
	if(Period_1000ms_Expire_Flag)
	{
		Task_1000ms();
		Period_1000ms_Expire_Flag = false;
	}
}
static void Task_1ms(void)
{
		SetModelInput();				/* Model input interface */
		BalanceCar_step();		/* Model Task */
		SetModelOutput();				/* Model output interface */
}
static void Task_5ms(void)
{
//		CAN_Test();
//		CAN_SendMessage();
//		CAN_ReceiveMessage();
		LastMotor1Speed = GetTim2Encoder();
		LastMotor2Speed = -GetTim4Encoder();
		CurrentMotor1Speed += LastMotor1Speed;
		CurrentMotor2Speed += LastMotor2Speed;
//		Txbuffer[1] = Motor1Speed >> 8;
//		Txbuffer[2] = Motor1Speed;
//		Txbuffer[3] = Motor2Speed >> 8;
//		Txbuffer[4] = Motor2Speed;
//		Txbuffer[5] = Speed_PWM >> 8;
//		Txbuffer[6] = Speed_PWM;
//		Txbuffer[7] = Motor1PWM >> 8;
//		Txbuffer[8] = Motor1PWM;
//		Txbuffer[9] = Motor2PWM >> 8;
//		Txbuffer[10] = Motor2PWM;
//		Txbuffer[11] = Angle;
//		Txbuffer[12] = (uint8_t)((int)Gyro_Angle >> 8);
//		Txbuffer[13] = (uint8_t)Gyro_Angle;
//		Txbuffer[14] = (uint8_t)((int)Gyro_Turn >> 8);
//		Txbuffer[15] = (uint8_t)Gyro_Turn;
//		Txbuffer[16] = (uint8_t)Distance;
	#if ENABLE_SERIVAL_SCOPE						/* For serival port plot line */
	//	HAL_UART_Transmit (&huart1 ,Txbuffer,TX_DATA_LEN,HAL_MAX_DELAY );
	#endif		
//		printf("X:%.1f Y:%.1f Z:%d \r\n",Pitch,Roll,gyro[0]);
}
static void Task_10ms(void)
{
		//printf("Motor1Speed:%d Motor2Speed:%d \r\n",Motor1Speed,Motor2Speed);
		
}
static void Task_20ms(void)
{
		Hcsr04TimeoutHandle();					/* 先结算上一轮: 无回波则判为超量程 */
		Hcsr04Start();							/* 触发下一轮测距 */
		Distance = Hcsr04Read();				/* 取回上一轮测距结果 */
		Model_Distance = Distance;				/* 与原设计一致 */
#if ENABLE_DIRECTION_AVOID
		DirectionAvoid_Update();				/* 避障转向状态机(每 20ms 一拍) */
#endif
		//printf("%d \r\n",(int)Distance);
		
		/* The follow no used */
		Rxbuffer[0] = (uint8_t)BatteryVoltage;
		Rxbuffer[1] = (uint8_t)BalanceCarTargetSpeed;
		Rxbuffer[2] = (uint8_t)Distance;
		
		Rxbuffer[3] = (uint8_t)(Motor1Speed/10);
		Rxbuffer[4] = (uint8_t)Motor1Speed;
		Rxbuffer[5] = (uint8_t)Motor2Speed;	
		Motor1Speed =  CurrentMotor1Speed;
		Motor2Speed =  CurrentMotor2Speed;
		CurrentMotor1Speed = 0;
		CurrentMotor2Speed = 0;
		BluetoothTxbuffer[0] = (uint8_t)BatteryVoltage;
		BluetoothTxbuffer[1] = (uint8_t)Distance;
		BluetoothTxbuffer[2] = (uint8_t)Motor1Speed;
		BluetoothTxbuffer[3] = (uint8_t)Motor2Speed;	
	#if ENABLE_OLED_DYNAMIC_DISPLAY
		
		OLED_Showdecimal(28,2,Roll,2,1,16,0);//????1?8X16???6?
	#endif
//		printf("Battery:%.1f Distance:%.1f Motor1Speed:%d CurrentMotor2Speed:%d \n",BatteryVoltage,Distance,Motor1Speed,Motor2Speed);
//		HAL_UART_Transmit (&huart2 ,BluetoothTxbuffer,BLUETOOTH_TX_DATA_LEN,HAL_MAX_DELAY );
}

static void Task_100ms(void)
{
	#if ENABLE_OLED_DYNAMIC_DISPLAY
	OLED_Showdecimal(72,4,Distance,2,1,16,0);//????1?8X16???6?
	#endif
}


/* USER CODE END 0 */
#endif

/* ── 避障转向 ──────────────────────────────────────────────
 * 复刻模型里 ReverseLazer 状态图的算法。原状态图因进入条件恒假
 * (BalanceCar.c:517 的 y==1 && y==2 && y==3) 永不执行, 故在此复刻。
 * 输出只写 BalanceCar_B.DirectionTargetPWM, 模型会自行算成 Direction_PWM
 * 并按差速叠加到左右轮, 不需要改动 Simulink 生成代码。
 */
static uint8_t AvoidTier_Get(void)					/* 复刻 BalanceCar_TruthTable() */
{
	float d = Distance;

	if(d < DIR_MIN_VALID_CM)		return 0u;		/* 无效读数按 Normal 处理 */
	if(d <= DIR_TIER_DANGER_CM)		return 1u;		/* Dangerous */
	if(d <= DIR_TIER_CAREFUL_CM)	return 2u;		/* Carefull  */
	if(d <  DIR_TIER_WARNING_CM)	return 3u;		/* Warning   */
	return 0u;										/* Normal    */
}

static void DirectionAvoid_Update(void)				/* 每 20ms 调用一次 */
{
#if ENABLE_DIRECTION_AVOID
	uint8_t y = AvoidTier_Get();

	switch(AvoidState)
	{
		case AVOID_IDLE:							/* Default1: 进入条件修正为 y != 0 */
			if(y != 0u)
			{
				AvoidDTPWM = 0.0f;
				AvoidState = AVOID_TURNING;
			}
		break;

		case AVOID_TURNING:							/* TurnDirection1: 每拍 +5 */
			if((y == 0u) || (AvoidDTPWM >= DIR_RAMP_LIMIT))
			{
				AvoidHoldCount = 0u;
				AvoidState = AVOID_END;
			}
			else
			{
				AvoidDTPWM += DIR_STEP_UP;
			}
		break;

		case AVOID_END:								/* End1: 保持一拍再减速 */
			if(++AvoidHoldCount >= 1u)
			{
				AvoidState = AVOID_STOPPING;
			}
		break;

		case AVOID_STOPPING:						/* StopTurn: 每拍 -10 直到 0 */
			if((y == 0u) || (AvoidDTPWM <= 0.0f))
			{
				AvoidDTPWM = 0.0f;
				AvoidState = AVOID_IDLE;
			}
			else
			{
				AvoidDTPWM -= DIR_STEP_DOWN;
			}
		break;

		default:
			AvoidDTPWM = 0.0f;
			AvoidState = AVOID_IDLE;
		break;
	}

	BalanceCar_B.DirectionTargetPWM = AvoidDTPWM;	/* 唯一输出点 */
#endif
}

static void SetModelInput(void)
{
		Key1 = HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin);
		Key2 = HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin);
		XunjiInput1 = HAL_GPIO_ReadPin(PC1_GPIO_Port,PC1_Pin);
		XunjiInput1 = HAL_GPIO_ReadPin(PC0_GPIO_Port,PC0_Pin);
		XunjiInput1 = HAL_GPIO_ReadPin(PC15_GPIO_Port,PC15_Pin);
		XunjiInput1 = HAL_GPIO_ReadPin(PC14_GPIO_Port,PC14_Pin);
		XunjiInput1 = HAL_GPIO_ReadPin(PD2_GPIO_Port,PD2_Pin);
		XunjiInput1 = HAL_GPIO_ReadPin(PC12_GPIO_Port,PC12_Pin);
		Angle = Roll;/* Kalman output angle to set model */
		Gyro_Angle = gyro[0];//Gyro_X;
		Gyro_Turn  = gyro[2];//Gyro_Z;
//		printf("Key1:%d Key2:%d \n",Key1,Key2);
	  //printf("Angle:%2.1f \r\n",Angle);/* 阻塞: USART1@115200 单条约 1.2ms, 每 1ms 一次会拖垮控制环 */
}
static void SetModelOutput(void)
{
	if(BatteryVoltage < 50)/* 5V */
	{
		Motor1PWM = 0;
		Motor2PWM = 0;
		Motor1_A = 0;
		Motor1_B = 0;
		Motor2_A = 0;
		Motor2_B = 0;
	}
	else
	{

	}		
	/* For Board test*/
	
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,Motor1PWM);
		__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,Motor2PWM);
		HAL_GPIO_WritePin(MOTOR1_OUT1_GPIO_Port, MOTOR1_OUT1_Pin, (GPIO_PinState)Motor1_A);
		HAL_GPIO_WritePin(MOTOR1_OUT2_GPIO_Port, MOTOR1_OUT2_Pin, (GPIO_PinState)Motor1_B);
		HAL_GPIO_WritePin(MOTOR2_OUT1_GPIO_Port, MOTOR2_OUT1_Pin, (GPIO_PinState)Motor2_A);
		HAL_GPIO_WritePin(MOTOR2_OUT2_GPIO_Port, MOTOR2_OUT2_Pin, (GPIO_PinState)Motor2_B);	
}