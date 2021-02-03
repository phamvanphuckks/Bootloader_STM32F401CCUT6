/* Include core modules */
#include "stm32f4xx.h"
#include "hardware_config.h"
#include "delay.h"
#include "flash.h"
#include "uart.h"
#include "record_hex.h"

#define ApplicationAddress 0x08004000

/************************* PLL Parameters *************************************/
/* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N */
#define PLL_M      8
#define PLL_N      72


/* SYSCLK = PLL_VCO / PLL_P */
#define PLL_P      2

/* USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ */
#define PLL_Q      6

/******************************************************************************/

void System_Configuration(void);

typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress, offsetAddress = 0;
char BufferBootloader[7168];

RowHex rowhex;

int main()
{
	System_Configuration();
	SystemCoreClockUpdate();
	SysTick_Init();
    
    GPIO_LedConfiguration();
    GPIO_ButtonConfiguration();
    UART_Init();
    
    //  PA5 = 1, chay truong trinh ung dung
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
    {
        UART_SendString(">> Mode  : application \r\n");
        MODE_APPLICATION; // LED OFF
        JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
        Jump_To_Application = (pFunction) JumpAddress;
        NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);
        
        /* Initialize user application's Stack Pointer */
        __set_MSP(*(__IO uint32_t*) ApplicationAddress);
        Jump_To_Application();    
    }
    
    UART_SendString(">> Mode  : Bootloader \r\n");
    // PA5 = 0, chay che do nap code 
    MODE_LOADCODE;  // LED ON
    
    while(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5))
    {
        
        while(UART_Available()){
            BufferBootloader[offsetAddress] = UART_Read();
            
            offsetAddress++;
        }  
        
        if(BufferBootloader[offsetAddress-1]== '<'){ //'<'
            offsetAddress++;
            flashEarseSector(FLASH_Sector_1);
            delay_ms(1000);
            UART_SendString(">> Erase Sector 1 \r\n");
            UART_SendString(">> Write to flash \r\n");
            uint8_t state = START_CODE;
            // hex
            for(int j = 0 ; j < offsetAddress; j++)
            {
                switch(state)
                {
                    case(START_CODE):
                        if(BufferBootloader[j]==':')
                        {
                            state = BYTE_COUNT;
                        }
                        break;
                    case BYTE_COUNT:
                        rowhex.byteCount = String2Hex8(&BufferBootloader[j], 2);
                        j+=1;
                        state = ADDRESS;
                        break;
                    case ADDRESS:
                        rowhex.offsetAddress = String2Hex16(&BufferBootloader[j], 4);
                        rowhex.address = 0x08000000 | rowhex.offsetAddress;
                        j += 3;
                        state = RECORD_TYPE;
                        break;
                    case RECORD_TYPE:
                        rowhex.recordType = String2Hex8(&BufferBootloader[j], 2);
                        if(rowhex.recordType == 0x01)
                        {
                            UART_SendString(">> : load file .hex  done\r\n");
                        }
                        state = DATA;
                        j += 1;
                        break;
                    case DATA:
                        rowhex.posStart = j;
                        if(rowhex.recordType == 0x00)
                        {
                            for( uint8_t index = 0; index < rowhex.byteCount; index += 4, j += 8)
                            {
                                flashWriteInt(rowhex.address+index, String2Hex32(&BufferBootloader[j], 8));
                            }
                        }
                        state = CHECKSUM;
                        break;
                    case CHECKSUM:
                        rowhex.checkSum = String2Hex8(&BufferBootloader[j], 2);
                        if(!isCheckSum(&BufferBootloader[rowhex.posStart],rowhex.checkSum, rowhex))
                        {
                            UART_SendString(">> : Error read file.hex \r\n");
                            return 0;
                        }
                        state = START_CODE;
                        j += 1;
                        break;
                }
                
            }
            UART_SendString(">> : Write to flash done \r\n");
            for(int blink = 0 ; blink < 10; blink++)
            {
                GPIO_ToggleBits(GPIOC, GPIO_Pin_13);
                delay_ms(100);
            }
            //NVIC_SystemReset();
        }
    }    
	while(1) {
	}
}

void System_Configuration(void)
{
/******************************************************************************/
/*             HSI used as System clock source                                */
/******************************************************************************/
	RCC_DeInit();
  __IO uint32_t HSIStatus = 0;
  
  /* Enable HSI */
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
 
  /* Wait till HSI is ready  */

  HSIStatus = RCC->CR & RCC_CR_HSIRDY;

	if ((RCC->CR & RCC_CR_HSIRDY) != RESET)
  {
    HSIStatus = (uint32_t)0x01;
  }
  else
  {
    HSIStatus = (uint32_t)0x00;
  }

	if (HSIStatus == (uint32_t)0x01)
  {
    /* Select regulator voltage output Scale 1 mode */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    /* HCLK = SYSCLK / 1*/
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
     
    /* PCLK2 = HCLK / 2*/
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
    
    /* PCLK1 = HCLK / 4*/
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
       
    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
    FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;
		
		/* Configure the main PLL */
	
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSI) | (PLL_Q << 24);

    /* Enable the main PLL */
    RCC->CR |= RCC_CR_PLLON;
		

    /* Wait till the main PLL is ready */
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    /* Select the main PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    /* Wait till the main PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
		
    }
    else
    { /* If HSI fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
    }

} 

