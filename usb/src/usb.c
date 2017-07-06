#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"
USBD_HandleTypeDef USBD_Device;
void usb_start(void)
{
  	USBD_Init(&USBD_Device, &VCP_Desc, 0);
  	USBD_RegisterClass(&USBD_Device, &USBD_CDC);
  	USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);
  	USBD_Start(&USBD_Device);
}
