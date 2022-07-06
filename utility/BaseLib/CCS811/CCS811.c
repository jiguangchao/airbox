/***************************************************************************
* Designed by Osman Li <Li.haimeng@menred.com>
* Copyright , Menred Group Corporation.
* This software is owned by Menred Group and is protected by and subject to
* worldwide patent protection (china and foreign)
 ***************************************************************************/
 /***************************************************************************
* Release Notes:
*     V1.1
*         Data:
*
*     V1.0
*         Data:2015.1.26
*         Official release
****************************************************************************/

/*============================ INCLUDES ======================================*/
#ifdef VCP_ENABLE
    #include ".\VCP_CCS811.h"
#else
    #include ".\CCS811.h"
#endif

#ifndef VCP_ENABLE
/*============================ MACROS ========================================*/


#define CCS811_IIC_CMD_WRITE                    IIC_CMD_WRITE
#define CCS811_IIC_CMD_READ                     IIC_CMD_READ
#define CCS811_PHY_ADDRESS_ID         (0x5A)

#define CCS811_SW_RESET_PASSWORD                 (0x11E5728A)
#define CCS811_APP_ERASE_PASSWORD                 (0xE7A7E609)


/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/**
   * @brief
   * @param
   * @retval
   */
eCCS811_RETURN_TYPE CCS811_WriteRegister(I2C_Bus_Typedef *pCCS811)
{
    //uint16_t i=0;
    uint8_t u8Data;

    if ( pCCS811->u8PhyAddress > 1)
    {
        return eCCS811_ERR_INPUT_PHY_ADDRESS;
    }

    u8Data = pCCS811->u8PhyAddress + CCS811_PHY_ADDRESS_ID;
    u8Data <<= 1;
    CCS811_IIC_Start();

    CCS811_IIC_SendByte(u8Data);
    if ( FALSE == CCS811_IIC_WaitAck() )
    {
        return eCCS811_ERR_WRITE_PHY_NO_ACK;
    }
    CCS811_IIC_BYTE_DELAY();

    CCS811_IIC_SendByte(pCCS811->u8RegisterAddress);
    if ( FALSE == CCS811_IIC_WaitAck() )
    {
        return eCCS811_ERR_DATA_ADDRESS_L_NO_ACK;
    }
    CCS811_IIC_BYTE_DELAY();
    CCS811_IIC_Stop();

    return eCCS811_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
eCCS811_RETURN_TYPE CCS811_WriteRegisters(I2C_Bus_Typedef *pCCS811)
{
    uint16_t i=0;
    uint8_t u8Data;

    if ( pCCS811->u8PhyAddress > 1)
    {
        return eCCS811_ERR_INPUT_PHY_ADDRESS;
    }

    u8Data = pCCS811->u8PhyAddress + CCS811_PHY_ADDRESS_ID;
    u8Data <<= 1;
    CCS811_IIC_Start();

    CCS811_IIC_SendByte(u8Data);
    if ( FALSE == CCS811_IIC_WaitAck() )
    {
        return eCCS811_ERR_WRITE_PHY_NO_ACK;
    }
    CCS811_IIC_BYTE_DELAY();

    CCS811_IIC_SendByte(pCCS811->u8RegisterAddress);
    if ( FALSE == CCS811_IIC_WaitAck() )
    {
        return eCCS811_ERR_DATA_ADDRESS_L_NO_ACK;
    }
    CCS811_IIC_BYTE_DELAY();

    for (i = 0;i < pCCS811->u16DataLength;i++)
    {
        CCS811_IIC_SendByte(pCCS811->p8Data[i]);
        if ( FALSE == CCS811_IIC_WaitAck() )
        {
            return eCCS811_ERR_DATA_ADDRESS_L_NO_ACK;
        }
        CCS811_IIC_BYTE_DELAY();
    }
    CCS811_IIC_Stop();

    return eCCS811_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
eCCS811_RETURN_TYPE CCS811_ReadRegisters(I2C_Bus_Typedef *pCCS811)
{
    uint16_t i=0;
    uint8_t u8Data;

    if ( pCCS811->u8PhyAddress > 1)
    {
        return eCCS811_ERR_INPUT_PHY_ADDRESS;
    }

    u8Data = pCCS811->u8PhyAddress + CCS811_PHY_ADDRESS_ID;
    u8Data <<= 1;
    CCS811_IIC_Start();

    CCS811_IIC_SendByte(u8Data);
    if ( FALSE == CCS811_IIC_WaitAck() )
    {
        return eCCS811_ERR_WRITE_PHY_NO_ACK;
    }
    CCS811_IIC_BYTE_DELAY();

    CCS811_IIC_SendByte(pCCS811->u8RegisterAddress);
    if ( FALSE == CCS811_IIC_WaitAck() )
    {
        return eCCS811_ERR_DATA_ADDRESS_L_NO_ACK;
    }
    CCS811_IIC_BYTE_DELAY();

    u8Data   = pCCS811->u8PhyAddress + CCS811_PHY_ADDRESS_ID;
    u8Data <<= 1;
    u8Data  |= CCS811_IIC_CMD_READ;
    CCS811_IIC_Start();
    CCS811_IIC_SendByte(u8Data);
    if ( FALSE == CCS811_IIC_WaitAck() )
    {
        return eCCS811_ERR_READ_DATA_WRITE_PHY_NO_ACK;
    }
    CCS811_IIC_BYTE_DELAY();

    for (i = 0;i < pCCS811->u16DataLength;i++)
    {
        pCCS811->p8Data[i] = CCS811_IIC_ReceiveByte();

        if ( i != (pCCS811->u16DataLength-1) )
        {
            CCS811_IIC_Ack();
        }
        CCS811_IIC_BYTE_DELAY();
    }
    CCS811_IIC_NoAck();
    CCS811_IIC_Stop();

    return eCCS811_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
eCCS811_RETURN_TYPE CCS811_ReadAlgResultData()
{
    return eCCS811_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
void CCS811_OperationTask(CCS811_Typedef *pCCS811,uint16_t u16ReadPeriodSet,uint16_t u16ReadWaitSet)
{
    I2C_Bus_Typedef I2CBus;

#if   (0x5A == CCS811_PHY_ADDRESS_ID)
    I2CBus.u8PhyAddress = 0;
#elif (0x5B == CCS811_PHY_ADDRESS_ID)
    I2CBus.u8PhyAddress = 1;
#endif

    I2CBus.p8Data = pCCS811->p8Data;

    switch(pCCS811->eRunState)
    {
    case eCCS811_IDLE          :
        pCCS811->eRunState = eCCS811_READ_FW_BOOT_VERSION;
        break;

    case eCCS811_SW_RESET      :
        I2CBus.u16DataLength   = 4;
        I2CBus.p8Data[0] = 0x11;
        I2CBus.p8Data[1] = 0xE5;
        I2CBus.p8Data[2] = 0x72;
        I2CBus.p8Data[3] = 0x8A;
        I2CBus.u8RegisterAddress = eCCS811_REG_SW_RESET;
        if ( eCCS811_OK == CCS811_WriteRegisters(&I2CBus) )
        {
            //pCCS811->u8Status = I2CBus.p8Data[0];
            pCCS811->eRunState = eCCS811_IDLE;
        }
        break;

    case eCCS811_READ_FW_BOOT_VERSION :
        I2CBus.u16DataLength   = 2;
        I2CBus.u8RegisterAddress = eCCS811_REG_FW_BOOT_VERSION;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u16FWBootVersion = I2CBus.p8Data[0];
        }
        pCCS811->eRunState = eCCS811_READ_FW_APP_VERSION;
        break;

    case eCCS811_READ_FW_APP_VERSION :
        I2CBus.u16DataLength   = 2;
        I2CBus.u8RegisterAddress = eCCS811_REG_FW_APP_VERSION;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u16FWAppVersion = I2CBus.p8Data[0];
        }
        pCCS811->eRunState = eCCS811_READ_HW_ID;
        break;

    case eCCS811_READ_HW_ID          :
        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_HW_ID;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u16HWID = I2CBus.p8Data[0];
        }
        if ( 0x81 != pCCS811->u16HWID )
        {
            pCCS811->eRunState = eCCS811_IDLE;
            return;
        }

        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_STATUS;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u8Status = I2CBus.p8Data[0];
        }
        if ( ( pCCS811->u8Status&0x10 ) == 0x10 )
        {
            pCCS811->eRunState = eCCS811_APP_START;
            //pCCS811->eRunState = eCCS811_READ_MEAS_MODE;
        }
        else
        {
            pCCS811->eRunState = eCCS811_ERROR_ID;
        }
        break;

    case eCCS811_APP_START         :

        I2CBus.u16DataLength   = 0;
        I2CBus.u8RegisterAddress = eCCS811_REG_APP_START;
        if ( eCCS811_OK != CCS811_WriteRegisters(&I2CBus) )
        {
            pCCS811->eRunState = eCCS811_ERROR_ID;
            return;
        }

        CCS811_IIC_BYTE_DELAY();
        CCS811_IIC_BYTE_DELAY();
        CCS811_IIC_BYTE_DELAY();
        CCS811_IIC_BYTE_DELAY();
        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_STATUS;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u8Status = I2CBus.p8Data[0];
        }
        if ( pCCS811->u8Status == 0x90 )
        {
            pCCS811->eRunState = eCCS811_READ_MEAS_MODE;
        }
        else
        {
            pCCS811->eRunState = eCCS811_ERROR_ID;
        }

        break;
    case eCCS811_READ_MEAS_MODE   :
        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_MEAS_MODE;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u8MeasMode = I2CBus.p8Data[0];
        }
        pCCS811->eRunState = eCCS811_READ_ALG_RESULT_DATA;
        break;
    case eCCS811_WRITE_MEAS_MODE   :
        pCCS811->u8MeasMode = 0x00;

        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_MEAS_MODE;
        I2CBus.p8Data[0] = pCCS811->u8MeasMode;
        if ( eCCS811_OK == CCS811_WriteRegisters(&I2CBus) )
        {
            pCCS811->u8MeasMode = I2CBus.p8Data[0];
        }
        if ( 0x00 == pCCS811->u8MeasMode )
        {
            pCCS811->u16ReadWait = u16ReadWaitSet;
        }
        pCCS811->eRunState = eCCS811_WRITE_MEAS_MODE_IDLE_WAIT;
        break;

    case eCCS811_WRITE_MEAS_MODE_IDLE_WAIT:
        if ( pCCS811->u16ReadWait )
        {
            return;
        }
        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_MEAS_MODE;
        pCCS811->u8MeasMode = 0x10;
        I2CBus.p8Data[0] = pCCS811->u8MeasMode;
        if ( eCCS811_OK == CCS811_WriteRegisters(&I2CBus) )
        {
            pCCS811->u8MeasMode = I2CBus.p8Data[0];
        }
        if ( 0x00 == pCCS811->u8MeasMode )
        {
            pCCS811->u16ReadWait = u16ReadWaitSet;
        }

        pCCS811->eRunState = eCCS811_READ_ALG_RESULT_DATA;
        pCCS811->u16ReadPeriod = u16ReadPeriodSet;
        break;

    case eCCS811_READ_ALG_RESULT_DATA:
        if ( pCCS811->u16ReadPeriod )
        {
            return;
        }


        I2CBus.u16DataLength   = 8;
        I2CBus.u8RegisterAddress = eCCS811_REG_ALG_RESULT_DATA;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u16ECO2 = I2CBus.p8Data[0]<<8 | I2CBus.p8Data[1];
            pCCS811->u16TVOC = I2CBus.p8Data[2] << 8 | I2CBus.p8Data[3];
            pCCS811->u8Status = I2CBus.p8Data[4];
            pCCS811->u8ErrorID = I2CBus.p8Data[5];
            pCCS811->u16RawData = I2CBus.p8Data[6] << 8 | I2CBus.p8Data[7];

            pCCS811->u16ReadPeriod = u16ReadPeriodSet;
        }
        else
        {

        }
        pCCS811->eRunState = eCCS811_READ_ALG_RESULT_DATA;
        break;

    case eCCS811_ERROR_ID:
        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_ERROR_ID;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u8ErrorID = I2CBus.p8Data[0];
        }

        if ( 0x00 != pCCS811->u8ErrorID )
        {
            pCCS811->eRunState = eCCS811_IDLE;
            return;
        }

        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_STATUS;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u8Status = I2CBus.p8Data[0];
        }
        if ( pCCS811->u8Status == 0x90 )
        {
            pCCS811->eRunState = eCCS811_READ_MEAS_MODE;
        }
        else
        {
            pCCS811->eRunState = eCCS811_APP_START;
        }
        /*
        I2CBus.u16DataLength   = 1;
        I2CBus.u8RegisterAddress = eCCS811_REG_STATUS;
        if ( eCCS811_OK == CCS811_ReadRegisters(&I2CBus) )
        {
            pCCS811->u8Status = I2CBus.p8Data[0];
        }

        if ( ( pCCS811->u8Status&0x80 ) != 0x80 )
        {
            pCCS811->eRunState = eCCS811_SW_RESET;
        }
        else
        {
            pCCS811->eRunState = eCCS811_APP_START;
            pCCS811->u16ReadPeriod = u16ReadPeriodSet;
        }
        */
        break;

    case eCCS811_WRITE_ENV_DATA:
        I2CBus.u16DataLength   = 4;
        I2CBus.u8RegisterAddress = eCCS811_REG_ENV_DATA;
        I2CBus.p8Data[0] = 0x00;
        I2CBus.p8Data[1] = 0x00;
        I2CBus.p8Data[2] = 0x00;
        I2CBus.p8Data[3] = 0x00;
        if ( eCCS811_OK == CCS811_WriteRegisters(&I2CBus) )
        {
            pCCS811->eRunState = eCCS811_WRITE_ENV_DATA_WAIT;
        }
        else
        {
            pCCS811->eRunState = eCCS811_ERROR_ID;
        }
        pCCS811->u16ReadWait = u16ReadWaitSet;
        break;
    case eCCS811_WRITE_ENV_DATA_WAIT:
        if ( pCCS811->u16ReadWait )
        {
            return;
        }
        pCCS811->eRunState = eCCS811_APP_CHECK_STATUS;
        break;

    case eCCS811_INTERFACE_RESET   :
        break;

    case eCCS811_APP_ERASE :
        break;

    case eCCS811_APP_DATA :
        break;

    case eCCS811_APP_VERIFY :
        break;

    default:
        break;
    }
}
/**
   * @brief
   * @param
   * @retval
   */
void CCS811_Tick10ms(CCS811_Typedef *pCCS811)
{
    if ( pCCS811->u16ReadWait )
    {
        pCCS811->u16ReadWait--;
    }
    if (pCCS811->u16ReadPeriod)
    {
        pCCS811->u16ReadPeriod--;
    }
}



#if CCS811_IIC_DEMOTEST > 0
CCS811_Typedef CCS811Data;
/**
   * @brief
   * @param
   * @retval
   */
void CCS811_Demo(void)
{
    uint8_t u8Data[20];
    I2C_Bus_Typedef CCS811Bus;

    //CCS811Bus.Bus
    CCS811Bus.p8Data = u8Data;//CCS811Data.u8Bytes;

    CCS811Bus.u8PhyAddress = 0;
    /**/
    CCS811Bus.u16DataLength   = 1;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_STATUS;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u8Status = CCS811Bus.p8Data[0];
    }
    /**/
    CCS811Bus.u16DataLength   = 1;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_MEAS_MODE;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u8MeasMode = CCS811Bus.p8Data[0];
    }
    /**/
    CCS811Bus.u16DataLength   = 8;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_ALG_RESULT_DATA;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u16ECO2 = CCS811Bus.p8Data[0]<<8 | CCS811Bus.p8Data[1];
        CCS811Data.u16TVOC = CCS811Bus.p8Data[2] << 8 | CCS811Bus.p8Data[3];
        CCS811Data.u8Status = CCS811Bus.p8Data[4];
        CCS811Data.u8ErrorID = CCS811Bus.p8Data[5];
        CCS811Data.u16RawData = CCS811Bus.p8Data[6] << 8 | CCS811Bus.p8Data[7];
    }
    /**/
    CCS811Bus.u16DataLength   = 2;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_RAW_DATA;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u16RawData = CCS811Bus.p8Data[0] << 8 | CCS811Bus.p8Data[1];
    }
    /**/
/*
    CCS811Bus.u16DataLength   = 4;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_ENV_DATA;
    if ( eCCS811_OK == CCS811_WriteRegisters(&CCS811Bus) )
    {
        CCS811Data.u8Status = u8Data[0];
    }
*/
/*
    CCS811Bus.u16DataLength   = 4;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_ENV_NTC;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.= u8Data[0];
    }
*/
/*
    CCS811Bus.u16DataLength   = 5;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_THRESHOLDS;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u8Status = u8Data[0];
    }
*/
/*
    CCS811Bus.u16DataLength   = 2;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_BASELINE;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {

    }
*/
    CCS811Bus.u16DataLength   = 1;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_HW_ID;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u16HWID = CCS811Bus.p8Data[0];
    }

    CCS811Bus.u16DataLength   = 2;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_FW_BOOT_VERSION;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u16FWBootVersion = CCS811Bus.p8Data[0];
    }

    CCS811Bus.u16DataLength   = 2;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_FW_APP_VERSION;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u16FWAppVersion = CCS811Bus.p8Data[0];
    }

    CCS811Bus.u16DataLength   = 1;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_ERROR_ID;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u8ErrorID = CCS811Bus.p8Data[0];
    }

    if ( ( CCS811Data.u8Status&0x80 ) == 0x00 )
    {
        CCS811Bus.u16DataLength   = 1;
        CCS811Bus.u8RegisterAddress = eCCS811_REG_APP_START;
        if ( eCCS811_OK == CCS811_WriteRegisters(&CCS811Bus) )
        {

        }
    }

/*
    CCS811Bus.u16DataLength   = 1;
    CCS811Bus.u8RegisterAddress = eCCS811_REG_SW_RESET;
    if ( eCCS811_OK == CCS811_ReadRegisters(&CCS811Bus) )
    {
        CCS811Data.u8Status = CCS811Bus.p8Data[0];
    }
*/
}
#endif
#endif
/* EOF */
