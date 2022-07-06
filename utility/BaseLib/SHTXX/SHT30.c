/*******************************************************************
*
*    DESCRIPTION:
*
*    AUTHOR:
*
*    HISTORY:
*
*    DATE:
*
*******************************************************************/

#include "..\BaselibInclude.h"



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//CRC8计算程序,多项式:10000 0111 0x07 入口:0x00
//入口:首指针,数据长度
//-----------------------------------------------------------------------------
const uint8_t crc8_table[16]={
                         0x00,0x07,0x0e,0x09,0x1c,0x1b,0x12,0x15,
                         0x38,0x3f,0x36,0x31,0x24,0x23,0x2a,0x2d,
                     };
//-----------------------------------------------------------------------------
uint8_t Crc8_Calculate(uint8_t *prt,uint8_t length)
{
    uint8_t crc;
    uint8_t da;

    crc=0x00;
    while((length--)!=0)
    {
        da=*prt;
        crc=crc8_table[((da>>4)^(crc>>4))&0x0f]^(crc<<4);
        crc=crc8_table[(da^(crc>>4))&0x0f]^(crc<<4);
        prt++;
    }
    return(crc);
}

//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//0x31的多项式，入口0xFF
//-----------------------------------------------------------------------------
const uint8_t Crc8Of31H_table[16]={
                              0x00,0x31,0x62,0x53,0xc4,0xf5,0xa6,0x97,
                              0xb9,0x88,0xdb,0xea,0x7d,0x4c,0x1f,0x2e,
                          };

//-----------------------------------------------------------------------------
uint8_t Crc8Of31H_Calculate(uint8_t *prt,uint8_t length)
{
    uint8_t crc;
    uint8_t da;

    crc=0xFF;
    while((length--)!=0)
    {
        da=*prt;
        crc=Crc8Of31H_table[((da>>4)^(crc>>4))&0x0f]^(crc<<4);
        crc=Crc8Of31H_table[(da^(crc>>4))&0x0f]^(crc<<4);
        prt++;
    }
    return(crc);
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*计算法生产CRC8
uint8_t crc8_calcullate(uint8_t *ptr,uint8_t length)
{
    uint8_t crc=0;
    uint8_t i;

    while((length--)!=0)
    {
        for(i=0x80;i!=0;i/=2)
        {
            if((crc&0x80)!=0)
            {
                crc*=2;
                crc^=0x07;
            }
            else
            {
                crc*=2;
            }
            if((*ptr&i)!=0)
            {
                crc^=0x07;
            }
        }
        ptr++;
    }
    return(crc);
} */
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//发送操作命令
//入口:Addr_0x44 0x45,Cmd 16bit的命令字
//-----------------------------------------------------------------------------
/**
   * @brief
   * @param
   * @retval
   */
eSHT30_RETURN_TYPE SHT30_SetCommand(I2C_Bus_Typedef *pSHT30)
{
   uint8_t u8Data;

    if ( pSHT30->u8PhyAddress > 1 )
    {
        return eSHT30_ERR_INPUT_PHY_ADDRESS;
    }

    u8Data = SHT30_PHY_ADDRESS_ID + pSHT30->u8PhyAddress;
    //u8Data <<= 1;
    //pI2C->Fun.pStart(&pI2C->HwPort);
    I2C_start(pSHT30);

    if ( I2C_WriteAddress(IIC_CMD_WRITE,u8Data,pSHT30) )
    {
        return eSHT30_ERR_WRITE_PHY_NO_ACK;
    }

    u8Data = (pSHT30->u16Cmd>>8)&0xFF;    
    if ( I2C_WriteDataWaitAck(u8Data,pSHT30) )
    {
        return eSHT30_ERR_COMMAND_ADDRESS_H_NO_ACK;
    }
       
    u8Data = pSHT30->u16Cmd&0xFF;    
    if ( I2C_WriteDataWaitAck(u8Data,pSHT30) )
    {
        return eSHT30_ERR_COMMAND_ADDRESS_L_NO_ACK;
    }

    I2C_stop(pSHT30);

    return eSHT30_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
eSHT30_RETURN_TYPE SHT30_ReadBytes(I2C_Bus_Typedef *pSHT30)
{
    uint8_t u8Data;

    uint16_t i;
    if ( pSHT30->u8PhyAddress > 1 )
    {
        return eSHT30_ERR_INPUT_PHY_ADDRESS;
    }
    u8Data = SHT30_PHY_ADDRESS_ID + pSHT30->u8PhyAddress;
    //u8Data <<= 1;    
    I2C_start(pSHT30);

    if ( I2C_WriteAddress(IIC_CMD_READ,u8Data,pSHT30) )
    {
        return eSHT30_ERR_WRITE_PHY_NO_ACK;
    }

    i = 0;
    do
    {
        if ( i < (pSHT30->u16DataLength-1) )
        {
            pSHT30->p8Data[i] = I2C_ReadDataWithAck(pSHT30);
        }
        else
        {
            pSHT30->p8Data[i] = I2C_ReadDataWithNoAck(pSHT30);
        }
        i++;
    }
    while(i < pSHT30->u16DataLength);

/*    
    for (i = 0;i < pSHT30->u16DataLength;i++)
    {
        pSHT30->p8Data[i] = pSHT30->Fun.pReceiveByte(&pSHT30->HwPort);

        if ( i != (pSHT30->u16DataLength-1) )
        {     
            pSHT30->Fun.pAck(&pSHT30->HwPort);
        }
    }    
    pSHT30->Fun.pNoAck(&pSHT30->HwPort);
*/    
    I2C_stop(pSHT30);

    return eSHT30_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
void SHT30_BusReset(SHT30_Typedef *pSHT30)
{
    I2C_InterfaceReset(&pSHT30->I2C);
}
/**
   * @brief
   * @param
   * @retval
   */
void SHT30_Tick10ms(SHT30_Typedef *pSHT30)
{
    if ( pSHT30->u8ReadWait )
    {
        pSHT30->u8ReadWait--;
    }
    if (pSHT30->u16ReadPeriod)
    {
        pSHT30->u16ReadPeriod--;
    }
}

/**
   * @brief
   * @param
   * @retval
   */
eSHT30_RETURN_TYPE SHT30_GetDataByBuff(SHT30_Typedef *pSHT30)
{
    int32_t temp32s;
        
    if( (Crc8Of31H_Calculate(&pSHT30->p8Data[0],2) == pSHT30->p8Data[2])&&
        (Crc8Of31H_Calculate(&pSHT30->p8Data[3],2) == pSHT30->p8Data[5]))
       
    {
        temp32s = pSHT30->p8Data[0];    //MSB
        temp32s = temp32s<<8;
        temp32s|= pSHT30->p8Data[1];   //LSB
        temp32s = temp32s*1750;
        temp32s = temp32s/65535;
        temp32s = temp32s-450;
        pSHT30->i16TemperatureOfDegreesCelsius = (int16_t)temp32s;

        temp32s = pSHT30->p8Data[0];    //MSB
        temp32s = temp32s<<8;
        temp32s|= pSHT30->p8Data[1];   //LSB
        temp32s = temp32s*3150;
        temp32s = temp32s/65535;
        temp32s = temp32s-490;
        pSHT30->i16TemperatureOfFahrenheit = (int16_t)temp32s;

        temp32s = pSHT30->p8Data[3];    //MSB
        temp32s = temp32s<<8;
        temp32s|= pSHT30->p8Data[4];   //LSB
        temp32s = temp32s*100;
        temp32s = temp32s/65535;
        pSHT30->u8HumidityValue = (uint8_t)temp32s;
    }
    
    else
    {
        return eSHT30_ERR_DATA_CRC;
    }
    
    return eSHT30_OK;
}

/**
   * @brief
   * @param
   * @retval
   */
void SHT30_OperationTask(SHT30_Typedef *pSHT30,uint16_t u16ReadPeriodSet,uint8_t u8ReadWaitSet)
{

#if   (0x44 == SHT30_PHY_ADDRESS_ID)
    pSHT30->I2C.u8PhyAddress = 0;
#elif (0x45 == SHT30_PHY_ADDRESS_ID)
    pSHT30->I2C.u8PhyAddress = 1;
#endif
            
    if ( pSHT30->u8ErrorCount > 10 )
    {
        pSHT30->u8Error = 1;
    }

    switch(pSHT30->eRunState)
    {
        case SHT30_IDLE              :
            pSHT30->eRunState = SHT30_RESET_READ_STATUS;
            SHT30_BusReset(pSHT30);
            break;
        case SHT30_RESET_READ_STATUS       :

            pSHT30->I2C.u16Cmd = eSHT30_CMD_READ_STATUS;
            if ( eSHT30_OK != SHT30_SetCommand(&pSHT30->I2C) )
            {
                if ( pSHT30->u8ErrorCount < 0xFF ) 
                {
                    pSHT30->u8ErrorCount++;
                }
                return;
            }            
                
            pSHT30->I2C.u16DataLength = 3;
            if ( eSHT30_OK != SHT30_ReadBytes(&pSHT30->I2C) )
            {
                if ( pSHT30->u8ErrorCount < 0xFF ) 
                {
                    pSHT30->u8ErrorCount++;
                }
                return;
            }

            if (Crc8Of31H_Calculate(&pSHT30->p8Data[0],2) == pSHT30->p8Data[2])
            {
                pSHT30->u16Status = pSHT30->p8Data[0]<<8 | pSHT30->p8Data[1];
                pSHT30->eRunState = SHT30_START_MEASUREMENT;
            }
           
            break;

        case SHT30_READ_STATUS       :

            pSHT30->I2C.u16Cmd = eSHT30_CMD_READ_STATUS;
            if ( eSHT30_OK != SHT30_SetCommand(&pSHT30->I2C) )
            {
                if ( pSHT30->u8ErrorCount < 0xFF ) 
                {
                    pSHT30->u8ErrorCount++;
                }
                return;
            }

            pSHT30->I2C.u16DataLength = 3;
            if ( eSHT30_OK != SHT30_ReadBytes(&pSHT30->I2C) )
            {
                if ( pSHT30->u8ErrorCount < 0xFF ) 
                {
                    pSHT30->u8ErrorCount++;
                }
                return;
            }
            if (Crc8Of31H_Calculate(&pSHT30->p8Data[0],2) == pSHT30->p8Data[2])
            {
                pSHT30->u16Status = pSHT30->p8Data[0]<<8 | pSHT30->p8Data[1];
                pSHT30->eRunState     = SHT30_START_MEASUREMENT;
                pSHT30->u16ReadPeriod = u16ReadPeriodSet;
            }

            
            break;
        case SHT30_CLEAR_STATUS      :
            break;
        case SHT30_START_MEASUREMENT :
            if ( pSHT30->u16ReadPeriod )
            {
                return;
            }

            pSHT30->I2C.u16Cmd = eSHT30_CMD_MEAS_POLLING_H;
            if ( eSHT30_OK != SHT30_SetCommand(&pSHT30->I2C) )
            {
                if ( pSHT30->u8ErrorCount < 0xFF ) 
                {
                    pSHT30->u8ErrorCount++;
                }
                return;
            }
            pSHT30->eRunState = SHT30_WAIT_MEASUREMENT;
            pSHT30->u8ReadWait    = u8ReadWaitSet;

            break;
        case SHT30_WAIT_MEASUREMENT  :
            if ( pSHT30->u8ReadWait )
            {                               
                return;
            }
            pSHT30->eRunState = SHT30_READ_MEASUREMENT;
            break;
        case SHT30_READ_MEASUREMENT  :

            pSHT30->I2C.u16DataLength = 6;
            if ( eSHT30_OK != SHT30_ReadBytes(&pSHT30->I2C) )
            {
                if ( pSHT30->u8ErrorCount < 0xFF ) 
                {
                    pSHT30->u8ErrorCount++;
                }
                return;
            }
            SHT30_GetDataByBuff(pSHT30);

            pSHT30->u8Error       = 0;
            pSHT30->eRunState     = SHT30_READ_STATUS;
            pSHT30->u8ErrorCount  = 0;
            break;

        case SHT30_SW_RESET        :
            break;
        case SHT30_INTERFACE_RESET   :
            break;
        case SHT30_SELF_TEST_START_READ      :
            break;
        case SHT30_SELF_TEST_HEAT_ON         :
            break;
        case SHT30_SELF_TEST_WAIT             :
            break;
        case SHT30_SELF_TEST_HEAT_OFF         :
            break;
        case SHT30_SELF_TEST_STOP         :
            break;
        default:
            //pSHT30->eRunState = SHT30_IDLE;
            break;
    }
}

#if 0
/**
   * @brief
   * @param
   * @retval
   */
eSHT30_RETURN_TYPE SHT30_MeasurementCommandsSingleShotDataAcquisitionMode(I2C_Bus_Typedef *pSHT30)
{
    uint8_t u8Data;

    if ( pSHT30->u8PhyAddress > 1 )
    {
        return eSHT30_ERR_INPUT_PHY_ADDRESS;
    }
    u8Data = SHT30_PHY_ADDRESS_ID + pSHT30->u8PhyAddress;
    u8Data <<= 1;

    SHT30_IIC_Start();

    SHT30_IIC_SendByte(u8Data|0x01);
    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return eSHT30_ERR_READ_DATA_WRITE_PHY_NO_ACK;
    }

    pSHT30->p8Data[0] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    pSHT30->p8Data[1] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    pSHT30->p8Data[2] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    pSHT30->p8Data[3] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    pSHT30->p8Data[4] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    pSHT30->p8Data[5] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_NoAck();
    SHT30_IIC_Stop();

	return eSHT30_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
eSHT30_RETURN_TYPE SHT30_Command(SHT30_Typedef *pSHT30,uint16_t Cmd)
{
    uint8_t Error=0;
    uint8_t CmdByte[2];
    uint8_t u8Data;
    if ( pSHT30->u8PhyAddress > 1 )
    {
        return 1;
    }
    CmdByte[1]=Cmd&0x00ff;      //LSB
    CmdByte[0]=(Cmd>>8)&0x00ff;  //MSB

    SHT30_IIC_Start();
    u8Data = SHT30_PHY_ADDRESS_ID + pSHT30->u8PhyAddress;
    u8Data <<= 1;
    SHT30_IIC_SendByte(u8Data);

    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return 1;
    }
    SHT30_IIC_SendByte(CmdByte[0]);
    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return 2;
    }
    SHT30_IIC_SendByte(CmdByte[1]);
    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return 3;
    }
    SHT30_IIC_Stop();

    return(Error);
}
/**
   * @brief
   * @param
   * @retval
   */
void SHT30_MeasurementSingleShot(SHT30_Typedef *pSHT30)
{
    //SHT30_Command(pSHT30,0x2400);
    SHT30_Command(pSHT30,0x2400);

    //IIC_Stop();
}
/**
   * @brief
   * @param
   * @retval
   */
eSHT30_RETURN_TYPE SHT30_ReadRHandT(SHT30_Typedef *pSHT30)
{
    //uint8_t Error=0;
    //uint8_t i=0;
    uint8_t ReadBuff[6];
    int32_t temp32s;
    uint8_t u8Data;

    if ( pSHT30->u8PhyAddress > 1 )
    {
        return ;
    }
    u8Data = SHT30_PHY_ADDRESS_ID + pSHT30->u8PhyAddress;
    u8Data <<= 1;
    SHT30_IIC_Start();
/*
    SHT30_IIC_SendByte(u8Data);

    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return ;
    }
    SHT30_IIC_SendByte(0xE0);
    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return ;
    }
    SHT30_IIC_SendByte(0x00);
    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return ;
    }
*/
    SHT30_IIC_SendByte(u8Data|0x01);
    if ( !SHT30_IIC_WaitAck() )
    {
        SHT30_IIC_Stop();
        return ;
    }

    ReadBuff[0] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    ReadBuff[1] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    ReadBuff[2] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    ReadBuff[3] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    ReadBuff[4] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_Ack();
    ReadBuff[5] = SHT30_IIC_ReceiveByte();
    SHT30_IIC_NoAck();
    SHT30_IIC_Stop();
//-----------------------------------------------------------------------------处理数据

    if((Crc8Of31H_Calculate(&ReadBuff[0],2)==ReadBuff[2])&&(Crc8Of31H_Calculate(&ReadBuff[3],2)==ReadBuff[5]))
    {
        temp32s=ReadBuff[0];    //MSB
        temp32s=temp32s<<8;
        temp32s|=ReadBuff[1];   //LSB
        temp32s=temp32s*1750;
        temp32s=temp32s/65535;
        temp32s=temp32s-450;
        pSHT30->TemperatureOfDegreesCelsius=(INT16S)temp32s;

        temp32s=ReadBuff[0];    //MSB
        temp32s=temp32s<<8;
        temp32s|=ReadBuff[1];   //LSB
        temp32s=temp32s*3150;
        temp32s=temp32s/65535;
        temp32s=temp32s-490;
        pSHT30->TemperatureOfFahrenheit=(INT16S)temp32s;

        temp32s=ReadBuff[3];    //MSB
        temp32s=temp32s<<8;
        temp32s|=ReadBuff[4];   //LSB
        temp32s=temp32s*100;
        temp32s=temp32s/65535;
        pSHT30->HumidityValue=(uint8_t)temp32s;
    }

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取SHT30的状态寄存器
//入口:参数指针,状态指针
//出口:错误字,状态字 由*RegStatus返回
//-----------------------------------------------------------------------------
eSHT30_RETURN_TYPE SHT30_ReadStatusRegister(SHT30_Typedef *pSHT30,uint16_t *RegStatus)
{
    uint8_t Error=0;
    uint8_t ReadBuff[3];
    uint16_t Status;

    Error=SHT30_Command(pSHT30,CMD_READSTATUSREGISTER);
    if(Error)
    {
    }
    else
    {
        //I2C_start(&pSHT30->IICInterface);
        SHT30_IIC_Start();
        SHT30_IIC_SendByte((pSHT30->u8PhyAddress<<1)|0x01);

        ReadBuff[0] = SHT30_IIC_ReceiveByte();
        SHT30_IIC_Ack();
        ReadBuff[1] = SHT30_IIC_ReceiveByte();
        SHT30_IIC_Ack();
        ReadBuff[2] = SHT30_IIC_ReceiveByte();
        SHT30_IIC_NoAck();

        if(Crc8Of31H_Calculate(&ReadBuff[0],2)==ReadBuff[2])
        {
            Status=ReadBuff[1];   //LSB
            Status=Status<<8;
            Status|=ReadBuff[0];  //MSB
            *RegStatus=Status;
        }
        else
        {
            Error=0xff;
        }
    }

    SHT30_IIC_Stop();
    return(Error);
}


/**
   * @brief
   * @param
   * @retval
   */
void SHT30_OperationTask(SHT30_Typedef *pSHT30)
{
    //DelayTickClock(Type_Millisecond,&Me->DelayOfSHT30P);

    switch(pSHT30->eRunState)
    {
    case SHT30_Free:
    {
        break;
    }

    case SHT30_StartReset:
    {

        break;
    }

    case SHT30_Resetting:
    {
        break;
    }

    case SHT30_StartMeasure:
    {
        SHT30_MeasurementSingleShot(pSHT30);
        pSHT30->eRunState=SHT30_Measuring;
        //ReloadDealyTickClock(Type_Millisecond,&Me->DelayOfSHT30P,150);
        break;
    }

    case SHT30_Measuring:
    {
        //if(DelayTickClockFinish(&Me->DelayOfSHT30P))
        {
            SHT30_ReadRHandT(pSHT30);
            pSHT30->eRunState=SHT30_MeasureComplete;
        }
        break;
    }

    case SHT30_MeasureComplete:
    {
        break;
    }

    default:
    {
        break;
    }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void StartSHT30_OnceMeasure(SHT30_Typedef *pSHT30)
{
    if((pSHT30->eRunState==SHT30_Free)||(pSHT30->eRunState==SHT30_MeasureComplete))
    {
        pSHT30->eRunState=SHT30_StartMeasure;
    }
}
#endif
/* End of file */
