/*
 * File:	EXAMPLE.c
 * Purpose:	EX. Routines for the non-volatile RAM
 *
 * Notes:	Ex.Microchip 23LCV512 has 1024 Kbits = 128 KBytes
 *			
 */

/* Includes */
#include <stdint.h>   //stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros[1] . This header is particularly useful for embedded programming which often involves considerable manipulation of hardware specific I/O registers requiring integer data of fixed widths, specific locations and exact alignments

/* Definitions */

/* Macros */

/* Public functions */

/*---------------Sample/maybe-------
/********************************************************************
   
  See if new command received
   
*********************************************************************/
/*
void USBreceiveCommand(void)
{
	int32_t i;
	// number of bytes received
	int32_t rxLen = USB_RXLEN - USB_RX_DMA_Channel->CNDTR;
	// look for carriage return => end of message
	for(i = 0; i < rxLen; ++i) {
		if(USBrxBuffer[i] == 0x0d) {
			USB_RX_DMA_Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
			USBrxLen = i;
			USBcmdPending = 1;
			return;
		}
	}
}

/********************************************************************
   
  DMA interrupt at each TX completion of USB response messages
   
*********************************************************************/
/*
void DMA1_Channel4_IRQHandler(void)
{
	// Check for DMA Transfer Complete interrupt 
	if(USB_DMA->ISR & USB_TX_DMA_TC) {
		// Clear DMA Transfer and Global interrupt pending bits 
		USB_DMA->IFCR = USB_TX_DMA_GL;
		// Disable the DMA channel
		//USB_TX_DMA_Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
		// say tx complete
		txBusy = 0;
	}
}

/********************************************************************
   
  Write Tx data to the USB port
   
*********************************************************************/
/*
void USBsendTx(void)
{
	if(txBusy == 0) {
		txBusy = 1;
		// start the DMA
		USB_TX_DMA_Channel->CCR &= (uint16_t)(~DMA_CCR1_EN);
		USB_TX_DMA_Channel->CNDTR = USBtxLen;
		USB_TX_DMA_Channel->CMAR = (uint32_t)USBtxBuffer;
		USB_UART->SR = (uint16_t)(~USART_FLAG_TC);
		USB_DMA->IFCR = USB_TX_DMA_GL;
		USB_TX_DMA_Channel->CCR |= DMA_CCR1_EN;
	}
	// wait for next command
	USBcmdPending = 0;
}

/********************************************************************
   
  Generic responses
   
*********************************************************************/
/*
void USBsendError(void)
{
	USBtxLen = (uint32_t) strlen( (char const *) errorReply);
	strncpy((char *) USBtxBuffer, (char const *) errorReply, USBtxLen);
	USBsendTx();
}

void USBsendOk(void)
{
	USBtxLen = (uint32_t) strlen( (char const *) okReply);
	strncpy((char *) USBtxBuffer, (char const *) okReply, USBtxLen);
	USBsendTx();
}

/********************************************************************
   
  Process command from USB
   
*********************************************************************/
/*
void USBprocessCommand(void) 
{
	int32_t cmd, n, i;
	
	cmd = USB_CMD(USBrxBuffer[0],USBrxBuffer[1]);
	// check min command length
	if (USBrxLen < 2) cmd = 0;
	
	switch(cmd) {
		
		case USB_CMD_SystemReset:
			NVIC_SystemReset();
			break;
	
		case USB_CMD_Test:
		// for test purposes
		n = ScanRx();
		if (n == 1) {
			cmdVal[0] = commSyncErrors;
			PrintTx(1);
			USBsendTx();
		}
		break;
	
	case USB_CMD_MainVersion:
		cmdVal[0] = version[0];
		cmdVal[1] = version[1];
		cmdVal[2] = version[2];
		PrintTx(3);
		USBsendTx();
		break;
	
	case USB_CMD_MainID:
		cmdVal[0] = DEVID->ID0;
		cmdVal[1] = DEVID->ID1;
		cmdVal[2] = DEVID->ID2;
		PrintTx(3);
		USBsendTx();
		break;
	
	case USB_CMD_SensorVersion:
		SensorReadVersion();
		PrintTx(4);
		USBsendTx();
		break;
	
	case USB_CMD_SensorID:
		SensorReadDeviceID();
		PrintTx(4);
		USBsendTx();
		break;
	
	case USB_CMD_ParamSave:
		n = ScanRx();
		if (n == 0) {
			// save current parameters
			ParamWriteReq = 1;
			USBsendOk();
		}
		if (n == 1 && cmdVal[0] == 271828) {
			// revert to default settings
			ParamsInit(1);
			USBsendOk();
		}
		break;
	
	case USB_CMD_ReadMemory:
		n = ScanRx();
		if (n == 0) {
			// use current address if none specified
			cmdVal[0] = NVMaddress;
			n = 1;
		}
		if (n == 1 && cmdVal[0] >= 0 && cmdVal[0] <= NVM_MAX_ADDR && recordingData == 0) {
			NVMaddress = cmdVal[0];
			NVMreadDataReq(10);
				while (SPIreqPending(SPI_REQ_NVM_ReadData)) {}
			for (i = 0; i < 10; ++i)
				cmdVal[i] = NVMdata[i];
			PrintTx(10);
			USBsendTx();
		}
		break;
	
	case USB_CMD_Record:
		if (!recordingData) {
			// start recording IMU data
			NVMaddress = 0;
			recordingData = 1;
			USBsendOk();
		}
		break;
		
	case USB_CMD_ReadData:
		for (i = 0; i < 6; ++i)
			cmdVal[i] = IMUdata[i];
		PrintTx(6);
		USBsendTx();
		break;
	
	case USB_CMD_ReadSensor:
		for (i = 0; i < 5; ++i)
			cmdVal[i] = sensorData[i];
		PrintTx(5);
		USBsendTx();
		break;
	
	case USB_CMD_ReadCounters:
		SensorReadCounters();
		cmdVal[0] = commReadErrors;
		cmdVal[1] = commSyncErrors;
		cmdVal[2] = commLastError;
		cmdVal[3] = sensorDclkCounter;
		PrintTx(4);
		USBsendTx();
		break;
        
        } // end of switch case
	if (USBcmdPending) USBsendError();
	
*/



/* Private functions */

/* Public variables */

/*---------------Sample/maybe-------
volatile int USBcmdPending = 0;
uint8_t USBrxBuffer[USB_RXLEN], USBtxBuffer[USB_TXLEN];
int32_t USBrxLen, USBtxLen;
const uint8_t version[3] = {2,4,6};
*/

/* Private variables */

/*---------------Sample/maybe-------
static volatile int32_t txBusy = 0;
static uint8_t hello[] = "Hello, I'm Schut meter\r";
static uint8_t okReply[] = "OK\r";
static uint8_t errorReply[] = "?\r";
*/

/* Type Definitions */

/* Special type definitions */


