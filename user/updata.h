


/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.1
��������:   2008.07.30
����˵��:   �궨��
����˵��:   ��
*****************************************************************************************/
#define COM1                           10                       // ��Դ����
#define COM2                           12                       // ��Դ����

#define PKG_REQUEST_SIZE            (2048)                      // �������ݰ���С




/*****************************************************************************************
��Ȩ����:   Ӱ����
�汾��:     1.0.0
��������:   2010.05.11
����˵��:   ���ݽṹ
����˵��:   ��
*****************************************************************************************/
typedef  struct  __font_address {
    char     *name;                     // ��������
    uint32   address;                   // ��ʼ��ַ
    uint32   size;                      // �ļ���С
    uint16   sectornum;                 // ռ��������
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
��Ȩ����:   Ӱ����
�汾��:     1.0.1
��������:   2008.07.30
����˵��:   �ӿ�
����˵��:   ��
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




