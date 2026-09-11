#ifndef 		__BLUETOOTHDATA_H
#define 	__BLUETOOTHDATA_H
#include "usart.h"
// ???????
#define PACKET_HEADER 0x55
#define PACKET_FOOTER 0xAA
#define PACKET_SIZE   5  // ?(1) + ??(3) + ?(1)

// ???? (???????????)
extern UART_HandleTypeDef huart1;

// ?????
typedef enum {
  STATE_WAIT_HEADER,
  STATE_RECEIVE_DATA,
  STATE_CHECK_FOOTER
} uart_parser_state_t;

// ???????
typedef struct {
  uint8_t buffer[PACKET_SIZE];  // ?????
  uint8_t index;                // ??????
  uart_parser_state_t state;    // ????
  uint8_t data[3];              // ????????
  uint8_t data_ready;           // ??????
} uart_rx_handle_t;


void ReceiveBluetoothData_Init(void);
void ReceiveBluetoothData(void);
#endif

