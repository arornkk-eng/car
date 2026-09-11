#include "canmessage.h"
#include "can.h"
#include "main.h"
#include "usart.h"
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
CAN_TxHeaderTypeDef TxHeaderCAN;
CAN_RxHeaderTypeDef RxHeaderCAN;
uint8_t TxDataCAN[8],RxDataCAN[8];
uint8_t CAN_Rx_Flag=0;//CAN????
void filter_init(void)
{
    HAL_StatusTypeDef HAL_Status;
    CAN_FilterTypeDef Filter0;
    Filter0.FilterBank = 1;//?????
    Filter0.FilterMode = CAN_FILTERMODE_IDMASK;
    Filter0.FilterScale = CAN_FILTERSCALE_32BIT;
    Filter0.FilterIdHigh = 0x00;
    Filter0.FilterIdLow = 0x00;
    Filter0.FilterMaskIdHigh = 0x00;
    Filter0.FilterMaskIdLow = 0x00;
    Filter0.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    Filter0.FilterActivation = CAN_FILTER_ENABLE;

    HAL_Status = HAL_CAN_ConfigFilter(&hcan,&Filter0);
    if(HAL_Status != HAL_OK)
    {
        printf("CAN Filter set Fail!code:%drn",HAL_Status);
        Error_Handler();
    }
}
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HAL_StatusTypeDef HAL_Status;
    if(hcan->Instance == CAN1)
    {
        HAL_Status = HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&RxHeaderCAN,RxDataCAN);
        if(HAL_Status == HAL_OK)
        {
            //??????
            CAN_Rx_Flag = 1;
					for(int i = 0;i<8;i++) printf(" 0x%02x",RxDataCAN[i]);
        }
    }
}
void CAN_Test(void)
{
    //????CAN
    TxHeaderCAN.ExtId = 0x1800F001;
    TxHeaderCAN.DLC = 8;
    TxHeaderCAN.IDE = CAN_ID_STD;
    TxHeaderCAN.RTR = CAN_RTR_DATA;
    TxHeaderCAN.StdId = 0x55;
    TxHeaderCAN.TransmitGlobalTime = ENABLE;

    uint32_t TxMailBox;
    HAL_StatusTypeDef HAL_Status;
    //printf("rnrn------------------CAN------------------rnrn");
    for (int i = 0; i < 8; ++i) TxDataCAN[i] = i;
//    printf("CAN????:rn");
//    for (int i = 0; i < 8; ++i) printf(" 0x%02x",TxDataCAN[i]);
//    printf("rn");
    HAL_CAN_AddTxMessage(&hcan,&TxHeaderCAN,TxDataCAN,&TxMailBox);
}
//void CAN_SendMessage(void)
//{
//    TxHeader.StdId = 0x123;
//    TxHeader.ExtId = 0x00;
//    TxHeader.RTR = CAN_RTR_DATA;
//    TxHeader.IDE = CAN_ID_STD;
//    TxHeader.DLC = 8;

//    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox)!= HAL_OK)
//    {
//        Error_Handler();
//    }
//}


//void CAN_ReceiveMessage(void)
//{
//    if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
//    {
//        // ????????
//        for (int i = 0; i < RxHeader.DLC; i++)
//        {
//            // ????????
//            printf("Received data: %x\n", RxData[i]);
//        }
//    }
//}