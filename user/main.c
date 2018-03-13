
extern void usb_start(void);
/********************************************************************************
函数名称: main()
功    能: 主函数入口
参    数: 无
返 回 值: 无	  
*********************************************************************************/
int main(void)
{
	  usb_start();
    while(1)
    {
        ;
    }

    return 0;	    	
}



#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
        ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1)
    {
        ;
    }
}
#endif




