#include "bluetoothdata.h"
#include "BalanceCar.h"

uart_rx_handle_t uart_rx = {0};


// ???????
void ReceiveBluetoothData_Init(void) 
{
  uart_rx.state = STATE_WAIT_HEADER;
  uart_rx.index = 0;
  uart_rx.data_ready = 0;
  
  // ??????(???)
  HAL_UART_Receive_IT(&huart2, &uart_rx.buffer[0], 1);
}

void ReceiveBluetoothData(void)
{
	switch (uart_rx.state) 
		{
      case STATE_WAIT_HEADER:
        if (uart_rx.buffer[0] == PACKET_HEADER) {
          uart_rx.index = 1;  // ??????
          uart_rx.state = STATE_RECEIVE_DATA;
          HAL_UART_Receive_IT(&huart2, &uart_rx.buffer[1], 3);  // ??3????
        } else {
          // ?????,???????
          HAL_UART_Receive_IT(&huart2, &uart_rx.buffer[0], 1);
        }
        break;

      case STATE_RECEIVE_DATA:
        // ???3????,??????
        uart_rx.state = STATE_CHECK_FOOTER;
        HAL_UART_Receive_IT(&huart2, &uart_rx.buffer[4], 1);  // ?????
        break;

      case STATE_CHECK_FOOTER:
        if (uart_rx.buffer[4] == PACKET_FOOTER) {
          // ?????? (??1,2,3)
          uart_rx.data[0] = uart_rx.buffer[1];
          uart_rx.data[1] = uart_rx.buffer[2];
          uart_rx.data[2] = uart_rx.buffer[3];
          uart_rx.data_ready = 1;  // ????????
					
        }
				if(uart_rx.data[0] == 0x01)
				{
					BalanceCarTargetSpeed = -10;
					BalanceCar_B.DirectionTargetPWM = 0;
				}
				else if(uart_rx.data[0] == 0x02)
				{
					BalanceCarTargetSpeed = 10;
					BalanceCar_B.DirectionTargetPWM = 0;
				}
				else if(uart_rx.data[0] == 0x03)
				{
					BalanceCar_B.DirectionTargetPWM = -5;
				}
				else if(uart_rx.data[0] == 0x04)
				{
					BalanceCar_B.DirectionTargetPWM = 5;
				}
				else if(uart_rx.data[0] == 0x05)
				{
					BalanceCarTargetSpeed = 0;
					BalanceCar_B.DirectionTargetPWM = -10;
				}
				else if(uart_rx.data[0] == 0x06)
				{
					BalanceCarTargetSpeed = 0;
					BalanceCar_B.DirectionTargetPWM = 10;
				}
				else if(uart_rx.data[0] == 0x00)
				{
					BalanceCarTargetSpeed = 0;
					BalanceCar_B.DirectionTargetPWM = 0;
				}
        // ????????,?????????
        uart_rx.state = STATE_WAIT_HEADER;
        HAL_UART_Receive_IT(&huart2, &uart_rx.buffer[0], 1);
        break;
    }
}