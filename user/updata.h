


/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2008.07.30
功能说明:   宏定义
其它说明:   无
*****************************************************************************************/
#define COM1                           10                       // 来源数据
#define COM2                           12                       // 来源数据

#define PKG_REQUEST_SIZE            (2048)                      // 请求数据包大小




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.0
生成日期:   2010.05.11
功能说明:   数据结构
其它说明:   无
*****************************************************************************************/
typedef  struct  __font_address {
    char     *name;                     // 字体名字
    uint32   address;                   // 起始地址
    uint32   size;                      // 文件大小
    uint16   sectornum;                 // 占用扇区数
}__APP_PACKED(1)  FONT_Address;


typedef enum {  
    LICESE_SN  = 0,
    UPDATE_APP = 1,
    FONT_ASC16 = 2,
    FONT_ASC24 = 3,
    FONT_ASC32 = 4,
    FONT_ASC48 = 5,
    FONT_HZK16 = 6,
    FONT_HZK24 = 7,
    FONT_HZK32 = 8,
    FONT_HZK48 = 9,
}FONTID_CLASS;




/*****************************************************************************************
版权所有:   影舞者
版本号:     1.0.1
生成日期:   2008.07.30
功能说明:   接口
其它说明:   无
*****************************************************************************************/
extern  uint32  getFontAddress(uint8 fontType);
extern  uint32  getFontSize(uint8 fontType);
extern  uint16  getFontSectorNUM(uint8 fontType);
extern  uint32  getNameAddress(char * filename);
extern  uint32  getNameSize(char * filename);

extern  void    RequestFrameUPDATA(uint16 frame);
extern  void    Updata_Unpack(uint8 value, uint8 comType);

extern  void    RequestFrameTIMER(void);
extern  void    ConfigureUPDATA(void);




