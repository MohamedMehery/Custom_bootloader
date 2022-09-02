/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define FLASH_PAGE7_BASE_ADDRESS 0x08001C00U		/*Interview question*/

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define C_UART &huart2	//command uart
#define D_UART &huart3	//Depug uart
#define BL_DEBUG_MSG_EN //enable Depug port

#define BL_RX_LEN 200
uint8_t BL_RX_BUFFER[BL_RX_LEN]; //to store all the command bytes sent by the bootloader


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CRC_HandleTypeDef hcrc;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PM */



/* USER CODE BEGIN PV */
uint8_t supported_commands[8] = {
															 BL_GET_VER,
                               BL_GET_HELP,
                               BL_GET_CID,
                               BL_GET_RDP_STATUS,
                               BL_GO_TO_ADDR,
                               BL_FLASH_ERASE,
                               BL_MEM_WRITE,
															 BL_READ_SECTOR_STATUS} ;

/* USER CODE END PM */

															 
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CRC_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

void go_to_bootloader();
void go_to_user_app();

														
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_CRC_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		
		HAL_UART_Transmit(D_UART,(uint8_t * ) "start bootloader\n" , 16, HAL_MAX_DELAY);
		
		if( HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == GPIO_PIN_RESET )
		{
			go_to_bootloader();
		}
		else
		{
			go_to_user_app();
		}
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/**
  * @brief Print Depugging result using depugging serial port -> huart3
  * @param message and values that you want to print
  * @retval None
  */
void send_msg(char* format,...)
{
	#ifdef BL_DEBUG_MSG_EN
	char str[80];
	va_list args;
	va_start(args,format);
	vsprintf(str,format,args);
	HAL_UART_Transmit(D_UART,(uint8_t *)str,strlen(str),HAL_MAX_DELAY);
	va_end(args);
	
	#endif
}
/************************** Implementation of bootloader command handle functions*************************/
/**
  * @brief send bootloader message using bootloaer serial port -> huart2
  * @param message and length 
  * @retval None
  */
void BootLoader_UART_Write_Data(uint8_t *pbuffer, uint32_t length)
{
	HAL_UART_Transmit(C_UART,pbuffer,length,HAL_MAX_DELAY);
}

/**
  * @brief This function is called to handle the getversion command
  * @param message received on bootloader serial port
  * @retval None
  */
void BL_handle_getVersion_cmd(uint8_t* pbuffer)
{
	uint8_t BL_VER;
	uint8_t command_packet_length = pbuffer[0] + 1; // the command packet length size itself is 1 byte
	uint32_t host_crc = *((uint32_t * )(pbuffer + command_packet_length -4));
	
	send_msg("BL_DEBUG_MSG : BL_handle_getVersion_cmd running...\n");
	
	//verifying checksum
	if(!bootloader_verify_CRC(&pbuffer[0],command_packet_length - 4,host_crc)) 
	{	
		send_msg("BL_DEBUG_MSG : CheckSum correct...\n");
		//checksum is correct
		bootloader_send_ack(pbuffer[0],1);//2nd argument is the length to follow and it's decided by the func itself
		BL_VER = get_bootloader_version();
		send_msg("BL_DEBUG_MSG : BootLoader Version : %d %x \n ",BL_VER,BL_VER);
		//sending reply to the host
		BootLoader_UART_Write_Data((uint8_t*)&BL_VER,sizeof(supported_commands));

	}
	else
		{
			send_msg("BL_DEBUG_MSG : CheckSum failed, sending NACK...\n");
			bootloader_send_nack();
		}
}

/**
  * @brief This function is called to handle the gethelp command
  * @param message received on bootloader serial port
  * @retval None
  */
void BL_handle_getHelp_cmd(uint8_t* pbuffer)
{
	uint32_t command_packet_length = BL_RX_BUFFER[0] + 0x01;
	uint32_t host_crc = *( (uint32_t * ) (BL_RX_BUFFER + command_packet_length -4) );
	send_msg("BL_DEBUG_MSG : BL_handle_getHelp_cmd running...\n");
	
	if(! bootloader_verify_CRC(BL_RX_BUFFER,(command_packet_length - 4),host_crc)) 
	{	
		send_msg("BL_DEBUG_MSG : CheckSum correct...\n");
		//checksum is correct
		bootloader_send_ack(pbuffer[0],sizeof(supported_commands));//2nd argument is the length to follow and it's decided by the func itself
		//sending reply to the host
		BootLoader_UART_Write_Data(supported_commands,sizeof(supported_commands));
	}
	else
		{
			send_msg("BL_DEBUG_MSG : CheckSum failed, sending NACK...\n");
			bootloader_send_nack();
		}
}

/**
  * @brief This function is called to handle the getID command
  * @param message received on bootloader serial port
  * @retval None
  */
void BL_handle_getCID_cmd(uint8_t* pbuffer)
{
	uint32_t command_packet_length = BL_RX_BUFFER[0] + 0x01;
	uint32_t host_crc = *( (uint32_t * ) (BL_RX_BUFFER + command_packet_length -4) );
	send_msg("BL_DEBUG_MSG : BL_handle_getCID_cmd running...\n");
	uint16_t chip_id ;
	chip_id = (uint16_t)(DBGMCU->IDCODE) & 0xFFFF;
	if(! bootloader_verify_CRC(BL_RX_BUFFER,(command_packet_length - 4),host_crc)) 
	{	
		send_msg("BL_DEBUG_MSG : CheckSum correct...\n");
		//checksum is correct
		bootloader_send_ack(pbuffer[0],2);//2nd argument is the length to follow and it's decided by the func itself
		//sending reply to the host
		BootLoader_UART_Write_Data((uint8_t *)&chip_id,sizeof(chip_id));
	}
	else
		{
			send_msg("BL_DEBUG_MSG : CheckSum failed, sending NACK...\n");
			bootloader_send_nack();
		}
}
/**
  * @brief This function is called to handle the "Get protection level" command
  * @param message received on bootloader serial port
  * @retval None
  */
void BL_handle_getRDP_cmd(uint8_t* pbuffer)
{
	uint8_t RDP_status ;
	uint32_t Command_packet_length = BL_RX_BUFFER[0]  + 0x01;
	uint32_t host_crc = *(uint32_t *) (BL_RX_BUFFER + Command_packet_length - 4 );
	send_msg("BL_DEBUG_MSG : BL_handle_getRDP_cmd running...\n");
	RDP_status = get_Read_protection();
	if( ! bootloader_verify_CRC(BL_RX_BUFFER , Command_packet_length - 4 , host_crc ))
	{
		send_msg("BL_DEBUG_MSG : CheckSum correct...\n");
		//checksum is correct
		bootloader_send_ack( pbuffer[0] , 1 );
		//send ACK
		BootLoader_UART_Write_Data((uint8_t * ) &RDP_status , sizeof(RDP_status ));
	}
	else
	{
			send_msg("BL_DEBUG_MSG : CheckSum failed, sending NACK...\n");
			bootloader_send_nack();
	}
}


/**
  * @brief BL_handle_goAddress_cmd
  * @param message buffer
  * @retval None
  */

void BL_handle_goAddress_cmd(uint8_t* pbuffer)
{
	uint8_t address_valid = ADDRESS_VALID;
	uint32_t gotoaddress = *(uint32_t*)&pbuffer[2];
	
	uint32_t Command_packet_length = BL_RX_BUFFER[0]  + 0x01;
	uint32_t host_crc = *(uint32_t *) (BL_RX_BUFFER + Command_packet_length - 4 );
	send_msg("BL_DEBUG_MSG : BL_handle_goAddress_cmd %#x\n",gotoaddress);

	if( ! bootloader_verify_CRC(BL_RX_BUFFER , Command_packet_length - 4 , host_crc ))
	{
		if(verify_address(gotoaddress) == ADDRESS_VALID)
		{
			 // tell the host that address is fine 
			BootLoader_UART_Write_Data(&address_valid , 1);
			//jump to go_address, host must ensure that code is there
			gotoaddress += 1;	//make T bit = 1;
			void (*letsjumb)(void) = (void *) gotoaddress;
			send_msg("BL_DEBUG_MSG : Jumb to address correct...\n");
			//checksum is correct
			bootloader_send_ack( pbuffer[0] , 1 );//2nd argument is the length to follow and it's decided by the func itself
			//send ACK
		} 
		else
		{
			address_valid = 0;
			BootLoader_UART_Write_Data(&address_valid , 1);			
			send_msg("BL_DEBUG_MSG : Ivalid address...\n");
		}
	}
	else
	{
			send_msg("BL_DEBUG_MSG : CheckSum failed, sending NACK...\n");
			bootloader_send_nack();
	}
}
void BL_handle_flashErase_cmd(uint8_t* pbuffer)
{	
	// In flash if you want to write something you should erase it first
	HAL_StatusTypeDef error ;
	uint32_t command_packet_length = BL_RX_BUFFER[0] + 0x01;
	uint32_t host_crc = *( (uint32_t * ) (BL_RX_BUFFER + command_packet_length -4) );
	send_msg("BL_DEBUG_MSG : BL_handle_flash_erase_cmd running...\n");
	
	if(! bootloader_verify_CRC(BL_RX_BUFFER,(command_packet_length - 4),host_crc)) 
	{	
		send_msg("BL_DEBUG_MSG : CheckSum correct...\n");
		//checksum is correct
		bootloader_send_ack(pbuffer[0],1);
		//sending reply to the host
		uint32_t error_code ;
		FLASH_EraseInitTypeDef flash_erase_struct;
		flash_erase_struct.TypeErase = FLASH_TYPEERASE_PAGES;
		flash_erase_struct.PageAddress = FLASH_PAGE7_BASE_ADDRESS;	//erase app code
		flash_erase_struct.NbPages = (32 - 8);	//all remaining flash pages
		flash_erase_struct.Banks = FLASH_BANK_1;	//bank is applied when mass erase
		
		send_msg("BL_DEBUG_MSG : initial_Page: %d of %d pages...\n" , pbuffer[2] , pbuffer[3]);
		error = HAL_FLASHEx_Erase(&flash_erase_struct , &error_code);
		send_msg("BL_DEBUG_MSG: flash erase status: %#X\n",error);
		BootLoader_UART_Write_Data((uint8_t*)&error , 1);
	}
	else
		{
			send_msg("BL_DEBUG_MSG : CheckSum failed, sending NACK...\n");
			bootloader_send_nack();
		}
}
void BL_handle_memWrite_cmd(uint8_t* pbuffer)
{
	uint8_t address_valid = ADDRESS_VALID;
	uint8_t write_status = 0x00;
	uint8_t checksum = 0 , len = 0;
	len = pbuffer[0];
	uint8_t payload_len = pbuffer[6];
	uint32_t mem_address = *( (uint32_t *) ( &pbuffer[2]));
	checksum = pbuffer[len];	//recall len = length(pbuffer) - 1, as length byte not counted
	send_msg("BL_DEBUG_MSG:bootloader_handle_mem_write_cmd\n");
	
	//total length of the command packet
	uint32_t command_packet_len = BL_RX_BUFFER[0]+1;
	
	//extract the CRC32 sent by host 
	uint32_t host_crc = *( (uint32_t*)  (BL_RX_BUFFER + command_packet_len - 4));
	if (! bootloader_verify_CRC(&BL_RX_BUFFER[0],command_packet_len-4,host_crc))
		{
				send_msg("BL_DEBUG_MSG:checksum success !!\n");
				bootloader_send_ack(pbuffer[0],1);
				send_msg("BL_DEBUG_MSG: mem write address : %#x\n",mem_address);
				if(verify_address(mem_address) == ADDRESS_VALID)
				{
						send_msg("BL_DEBUG_MSG: valid mem write address\n");
						write_status = execute_memory_write(&pbuffer[7] , mem_address , payload_len);
						// inform host about the status
						BootLoader_UART_Write_Data(&write_status , 1);
				}
				else
				{
            send_msg("BL_DEBUG_MSG: invalid mem write address\n");
            write_status = 0;
            //inform host that address is invalid
            BootLoader_UART_Write_Data(&write_status,1);					
				}
		}
		else{
				send_msg("BL_DEBUG_MSG:checksum fail !!\n");
        bootloader_send_nack();			
		}
}
void BL_handle_memRead_cmd(uint8_t* pbuffer)
{	
		send_msg("BL_DEBUG_MSG:HAL library doesnot provide memRead function\n");
}

void go_to_bootloader()
{
	/* do somethig */
	HAL_UART_Transmit(&huart2 , (uint8_t *)"Inside bootloader code\r\n" , 24 , HAL_MAX_DELAY);
	uint8_t rcv_len=0;
	while(1)
	{
		/*The C library function void *memset(void *str, int c, size_t n) copies the character c (an unsigned char) 
		to the first n characters of the string pointed to, by the argument str.*/
		memset(BL_RX_BUFFER,0,BL_RX_LEN);
		// we will read the command coming from the host and decode it
		//we will read the first byte which is the length of the command packet
		HAL_UART_Receive(C_UART,BL_RX_BUFFER,1,HAL_MAX_DELAY);
		rcv_len = BL_RX_BUFFER[0];
		HAL_UART_Receive(C_UART,&BL_RX_BUFFER[1],rcv_len,HAL_MAX_DELAY);
		switch(BL_RX_BUFFER[1])
		{
			case BL_GET_VER:
				BL_handle_getVersion_cmd(BL_RX_BUFFER);
				break;
			case BL_GET_HELP:
				BL_handle_getHelp_cmd(BL_RX_BUFFER);
				break;
			case BL_GET_CID:
				BL_handle_getCID_cmd(BL_RX_BUFFER);
				break;
			case BL_GET_RDP_STATUS:
				BL_handle_getRDP_cmd(BL_RX_BUFFER);
				break;
			case BL_GO_TO_ADDR:
				BL_handle_goAddress_cmd(BL_RX_BUFFER);
				break;
			case BL_FLASH_ERASE:
				BL_handle_flashErase_cmd(BL_RX_BUFFER);
				break;
			case BL_MEM_WRITE:
				BL_handle_memWrite_cmd(BL_RX_BUFFER);
				break;
//			case BL_MEM_READ:
//				BL_handle_memRead_cmd(BL_RX_BUFFER);
//				break;

			default:
				send_msg("BL_DEBUG_MSG: INVALID COMMAND CODE RECEIVED FROM THE HOST\r\n");
		}}
		
}
/**
  * @brief this function call the user app code from page 7 of flash
  * @param None
  * @retval None
  */
void go_to_user_app()
{
	void ( * user_app_code ) (void);//to hold the address of the reset handler of the user app
	HAL_UART_Transmit(&huart2 , (uint8_t *)"Go to user app\r\n" , 16 , HAL_MAX_DELAY);
	/* now get the value of main stack pointer from new address */
	uint32_t msp_value = *(volatile uint32_t *) FLASH_PAGE7_BASE_ADDRESS;
	__set_MSP(msp_value); /* set main stack pointer */
	
	uint32_t reset_handler_value = *(volatile uint32_t * ) (FLASH_PAGE7_BASE_ADDRESS + 4);
	user_app_code = (void *) (reset_handler_value) ;

	while(1)
	{
		user_app_code(); /* call user app */ ;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
// project services


/**
  * @brief execute the memory write in half word mode
  * @param data to be written , address base and data len
  * @retval write status
  */
uint8_t execute_memory_write(uint8_t * pbuffer , uint32_t mem_address , uint32_t numberofbytes)
	{
	uint8_t status = HAL_OK;
	// perform memory erase before write
	uint32_t error_code ;
	FLASH_EraseInitTypeDef flash_erase_struct;
	flash_erase_struct.TypeErase = FLASH_TYPEERASE_PAGES;
	flash_erase_struct.PageAddress = FLASH_PAGE7_BASE_ADDRESS;	//erase app code
	flash_erase_struct.NbPages = (32 - 8);	//all remaining flash pages
	flash_erase_struct.Banks = FLASH_BANK_1;	//bank is applied when mass erase
	HAL_FLASHEx_Erase(&flash_erase_struct, &error_code);
	//unlock flash to get control of registers
	HAL_FLASH_Unlock();
	for(uint32_t i = 0 ; i < (numberofbytes / 2) + (numberofbytes % 2) ; i++)
	{
		//Here we program the flash byte by byte
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD ,  mem_address + i * 2 , (uint16_t) pbuffer[i*2]);
	}
	HAL_FLASH_Lock();
	return status;
}


/**
  * @brief verify the address input 
  * @param memory address to be executed
  * @retval true if valid, false if not valid
  */
uint8_t verify_address(uint32_t address)
{
	//	the valid memory addresses are: //
	//	system memory	-> yes	
	//	sram1	-> yes
	//	sram2	-> yes
	//	backup sram	-> yes
	//	peripheral memory -> no
	//	external memory	-> yes
	if(address >= SRAM_BASE && address <= (SRAM_BASE + (96 * 1024)) )	//sizeof of flash is 96kbit
	{
		// address between SRAM start and SRAM end according to CM3 memory map
		return ADDRESS_VALID;
	}
	else if (address >= FLASH_BASE && address <=  0x08007FFF)
	{
		return ADDRESS_VALID;
	}
	else
		return 0;
	
}

/**
  * @brief Return the Read protectio of flash memory
  * @param None
  * @retval the value of read protection from the FLASH_OBP (Option byte register) register
  */
uint8_t get_Read_protection(void)
{
	return (uint8_t) ((FLASH ->OBR & FLASH_OBR_RDPRT_Msk) >> 1);
}

/**
  * @brief  this function sends ACK if the CRC matches with the lenght to follow
  * @param message received on bootloader serial port
  * @retval None
  */

void bootloader_send_ack(uint8_t command_code,uint8_t follow_length)
{
	uint8_t ack_buf[2] ;
	//we send 2 bytes ACK and length value
	ack_buf[0] = BL_ACK;
	ack_buf[1] =  follow_length;
	HAL_UART_Transmit(C_UART,ack_buf,2,HAL_MAX_DELAY);
}
/**
  * @brief this function sends NACK if the CRC matches with the lenght to follow
  * @param None
  * @retval None
  */
void bootloader_send_nack(void)
{
	uint8_t nack = BL_NACK;
	HAL_UART_Transmit(C_UART,&nack,1,HAL_MAX_DELAY);
}
//verifies the CRC of the given buffer in pData
/**
  * @brief checks the CRC of the pData over the length and compares it w ith the CRC_host
  * @param Data, length and CRC_host
  * @retval Success or failed
  */
uint8_t bootloader_verify_CRC(uint8_t * pData,uint32_t length,uint32_t CRC_host)
{
	uint32_t CRC_value = 0xff;
	uint32_t i;
	for(i=0;i<length;i++)
	{
		uint32_t data = pData[i];
		CRC_value = HAL_CRC_Accumulate(& hcrc,(uint32_t *)data,sizeof(data));
	}
	if(CRC_value == CRC_host)
	{
		return VERIFY_CRC_SUCCESS;
	}
	else
	{
		return VERIFY_CRC_FAILURE;
	}
}
/**
  * @brief Return the Bootloader version
  * @param None
  * @retval Bootloader version
  */
uint8_t get_bootloader_version(void)
{
	return BL_Version;
}



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
