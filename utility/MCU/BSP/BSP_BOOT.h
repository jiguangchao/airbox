#ifndef _BSP_BOOT_H_
#define _BSP_BOOT_H_




/*############################################################################################################*/
/*############################################################################################################*/
/*                                                                                                            */
/*                                           STM32G070xx                                                      */
/*                                                                                                            */
/*############################################################################################################*/
/*############################################################################################################*/
#ifdef STM32G070xx
    /******************************************************************************/
    #define APP_HARDWARE_SIGN                       (0xFE05)//硬件标识
    #define UPGRADE_MODBUS_BOOT                     (0)
    #define UPGRADE_MODBUS_APP                      (1)
    #define FLASH_DATA_USAGE                        (0)
    /***************** 16K **************************************************************/
    /*
    ** boot area: BOOT_ADDRESS_START -- BOOT_ADDRESS_END, length: 16*1024Bytes
    ** 
    */
    #define BOOT_ADDRESS_START                      (0x08000000)
    #define BOOT_ADDRESS_END                        (0x08005FFF)
    /*
    ** boot info area: 0x0001D000 -- 0x0001D1FFF, length: 512Bytes
    ** 
    */
    #define BOOT_ADDRESS_INFO_START                 (BOOT_ADDRESS_END-0x7F)//启动区信息段32bits数据起始地址
    #define BOOT_ADDRESS_INFO_END                   (BOOT_ADDRESS_END)//启动区信息段32bits数据结束地址
    /************************************************************************************/
    /*
    ** application area: 0x00004000 -- 0x0001CFFF, length: 100*1024Bytes
    ** 升级每包大小 128Bytes，每包分为32block;升级包通过RS485MODBUS或EnOcean接口都可以
    */
    #define APP_ADDRESS_START                       (0x08006000)     //运行区起始地址
    #define APP_ADDRESS_END                         (0x0801DFFF)     //运行区结束地址
    #define APP_BLOCK_SIZE                          (128)
    #define APP_BLOCK_LENGTH                        (32)// 块长度 128bytes  falsh使用4byte操作128 / 4 = 32 
    /*
    ** Application infomation area: 0x0001D200 -- 0x0001D3FF, length: 512Bytes
    ** APP升级逻辑：正常运行过程中，收到升级命令，写入硬件信息，快速复位
    （1）收到升级命令，校验收到命令
    （2）硬件物理地址、波特率、停止位、校验位、升级状态、硬件代码等信息写入APP信息区
    （3）应答包交给boot区执行直接执行复位
    ** APP信息区存储格式
        0 -- 127Bytes存储升级信息，包括升级计数器、升级状态、代码校验码、代码长度；
        存储升级信息，包括物理地址、波特率、停止位、校验位、升级状态、硬件代码；
    */
    /* 存储第一帧信息，用于记录升级字节数以及校验码 */
    #define APP_ADDRESS_INFO_START                  (APP_ADDRESS_END-0x7F)//运行区信息段32bits数据起始地址
    #define APP_ADDRESS_INFO_END                    (APP_ADDRESS_END)//运行区信息段32bits数据结束地址
    /************************************************************************************/
    /*
    ** App's data area: 0x0001F000 -- 0x0001FFFF, length: 4*1024Bytes
    ** 此段划分由应用区决定
    */
    #define DATA_ADDRESS_START                      (0x0801F000)     //数据区开始地址
    #define DATA_ADDRESS_END                        (0x0801FFFF)     //数据区结束地址
    /***********************************************************************************/

    #define CHIP_FLASH_PAGE_NEED_ERASE              (2048)
    #define CHIP_FLASH_MAX_ADDRESS                  (0x0001FFFF)     //128k flash最大地址
    #define CHIP_FLASH_PAGE_BYTES_SIZE              (2048)            //页大小
    #define CHIP_FLASH_PAGE_WORD_SIZE               (CHIP_FLASH_PAGE_BYTES_SIZE>>2)//页字大小
    #define CHIP_FLASH_WRITE_TIMEOUT                (1000) // 4byte 写入超时
    /******************************************************************************/
    #if CHIP_FLASH_PAGE_WORD_SIZE > 32
        #define APP_INFO_HW_PAGE_OFFSET             (CHIP_FLASH_PAGE_WORD_SIZE-32)
    #else
        #define APP_INFO_HW_PAGE_OFFSET             (0)
    #endif    
#endif
    

                    
#endif
/* End of file */
