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
#include "Dataconfigure.h"

//  crc校验
#define POLYNOMIAL 0x131
//SHT20_Typedef   SHT20;
/*===========================================================
* @name		uint8_t SHT20_CheckSum_CRC8(uint8_t* Result)
* @brief	CRC8检验
* @details	对测量结果的MSB和LSB进行校验，判断是否等于接收到的检验和
* @paramta[2];
    data[0	Result：测量结果所在数组的头指针
* @retval	检验成功返回1，失败返回0
===========================================================*/
uint8_t SHT20_CheckSum_CRC8(SHT20_Typedef *pSHT20)
{
    uint8_t data[2];

    uint8_t crc = 0;
    uint8_t bit = 0;
    uint8_t byteCtr = 0;

    if (pSHT20->eRunState == eSHT20_READ_MEASUREMENT_T)
    {
        data[0] = pSHT20->p8TData[0];
        data[1] = pSHT20->p8TData[1];
        for (byteCtr = 0; byteCtr < 2; ++byteCtr)
        {
            crc ^= (data[byteCtr]);
            for (bit = 8; bit > 0; --bit)
            {
                if (crc & 0x80)
                    crc = (crc << 1) ^ POLYNOMIAL;
                else
                    crc = (crc << 1);
            }
        }
        if (crc == pSHT20->p8TData[2])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if (pSHT20->eRunState == eSHT20_READ_MEASUREMENT_H)
    {
        data[0] = pSHT20->p8HData[0];
        data[1] = pSHT20->p8HData[1];
        for (byteCtr = 0; byteCtr < 2; ++byteCtr)
        {
            crc ^= (data[byteCtr]);
            for (bit = 8; bit > 0; --bit)
            {
                if (crc & 0x80)
                    crc = (crc << 1) ^ POLYNOMIAL;
                else
                    crc = (crc << 1);
            }
        }
        if (crc == pSHT20->p8HData[2])
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

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
eSHT20_RETURN_TYPE SHT20_SetCommand(I2C_Bus_Typedef *pSHT20)
{
#if 0
    
   uint8_t u8Data;

    if ( pSHT20->u8PhyAddress > 1 )
    {
        return eSHT20_ERR_INPUT_PHY_ADDRESS;
    }

    u8Data = SHT20_PHY_ADDRESS_ID + pSHT20->u8PhyAddress;
    //u8Data <<= 1;
    //pI2C->Fun.pStart(&pI2C->HwPort);
    I2C_start(pSHT20);

    if ( I2C_WriteAddress(IIC_CMD_WRITE,u8Data,pSHT20) )
    {
        return eSHT20_ERR_WRITE_PHY_NO_ACK;
    }

    u8Data = (pSHT20->u16Cmd>>8)&0xFF;    
    if ( I2C_WriteDataWaitAck(u8Data,pSHT20) )
    {
        return eSHT20_ERR_COMMAND_ADDRESS_H_NO_ACK;
    }
       
    u8Data = pSHT20->u16Cmd&0xFF;    
    if ( I2C_WriteDataWaitAck(u8Data,pSHT20) )
    {
        return eSHT20_ERR_COMMAND_ADDRESS_L_NO_ACK;
    }

    I2C_start(pSHT20);
#endif
    return eSHT20_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
eSHT20_RETURN_TYPE SHT20_ReadBytes(I2C_Bus_Typedef *pSHT20)
{
#if 0
    uint8_t u8Data;

    uint16_t i;
    if ( pSHT20->u8PhyAddress > 1 )
    {
        return eSHT20_ERR_INPUT_PHY_ADDRESS;
    }
    u8Data = SHT20_PHY_ADDRESS_ID + pSHT20->u8PhyAddress;
    //u8Data <<= 1;    
    I2C_start(pSHT20);

    if ( I2C_WriteAddress(IIC_CMD_READ,u8Data,pSHT20) )
    {
        return eSHT20_ERR_WRITE_PHY_NO_ACK;
    }

    i = 0;
    do
    {
        if ( i < (pSHT20->u16DataLength-1) )
        {
            pSHT20->p8Data[i] = I2C_ReadDataWithAck(pSHT20);
        }
        else
        {
            pSHT20->p8Data[i] = I2C_ReadDataWithNoAck(pSHT20);
        }
        i++;
    }
    while(i < pSHT20->u16DataLength);

/*    
    for (i = 0;i < pSHT20->u16DataLength;i++)
    {
        pSHT20->p8Data[i] = pSHT20->Fun.pReceiveByte(&pSHT20->HwPort);

        if ( i != (pSHT20->u16DataLength-1) )
        {     
            pSHT20->Fun.pAck(&pSHT20->HwPort);
        }
    }    
    pSHT20->Fun.pNoAck(&pSHT20->HwPort);
*/    
    I2C_start(pSHT20);
#endif
    return eSHT20_OK;
}
/**
   * @brief
   * @param
   * @retval
   */
void SHT20_BusReset(SHT20_Typedef *pSHT20)
{
    //I2C_InterfaceReset(&pSHT20->HwPort);
    I2C_start(&pSHT20->HwPort); //开始

    I2C_send_byte(&pSHT20->HwPort, SHT2X_I2C_ADR_W);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return;
    }

    //测量温度
    I2C_send_byte(&pSHT20->HwPort, 0xFE);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return;
    }

    pSHT20->HwPort.pWait(IIC_N_DELAY);
    I2C_stop(&pSHT20->HwPort);
}
/**
   * @brief
   * @param
   * @retval
   */
void SHT20_Tick10ms(SHT20_Typedef *pSHT20)
{

    if (pSHT20->u16ReadPeriod)
    {
        pSHT20->u16ReadPeriod--;
    }
    if (pSHT20->u32ReadCycle)
    {
        pSHT20->u32ReadCycle--;
    }
    
}
/**
   * @brief
   * @param
   * @retval
   */
void SHT20_Tick100us(SHT20_Typedef *pSHT20)
{
    if (pSHT20->u16ReadWait)
    {
        pSHT20->u16ReadWait--;
    }
}
/**
   * @brief
   * @param
   * @retval
   */
eSHT20_RETURN_TYPE SHT20_GetDataByBuff(SHT20_Typedef *pSHT20)
{
    uint32_t T_temp32s;
    uint32_t H_temp32s;
    //float    T_value;
    float    H_value;


    //计算温度值
    if (pSHT20->eRunState == eSHT20_READ_MEASUREMENT_T)
    {
        if (SHT20_CheckSum_CRC8(pSHT20))
        {

            T_temp32s = pSHT20->p8TData[0]; //MSB
            T_temp32s = T_temp32s << 8;
            T_temp32s |= pSHT20->p8TData[1]; //LSB
            
            /*
            H_value   =  T_temp32s;
            H_value = H_value * 175.72;
            H_value = H_value / 65535;
            H_value = H_value - 46.85;
            */
            T_temp32s = T_temp32s * 1750;
            T_temp32s = T_temp32s / 65535;
            T_temp32s = T_temp32s - 450;
            

            pSHT20->i16TemperatureOfDegreesCelsius = (int16_t)T_temp32s + 500;

            if (pSHT20->i16TemperatureOfDegreesCelsius > 1750)
            {
                pSHT20->i16TemperatureOfDegreesCelsius = 1750;
                pSHT20->eFaultCode = eSHT20_ABNORMAL_DATA;
            }
            else
            {
                pSHT20->eFaultCode = eSHT20_NORMAL;
            }
            if (pSHT20->i16TemperatureOfDegreesCelsius < 100)
            {
                pSHT20->i16TemperatureOfDegreesCelsius = 100;
                pSHT20->eFaultCode = eSHT20_ABNORMAL_DATA;
            }
            else
            {
                pSHT20->eFaultCode = eSHT20_NORMAL;
            }
        }
        else
        {
            pSHT20->eFaultCode = eSHT20_EXCEPTION_MESSAGE; //报文异常
            return eSHT20_ERR_DATA_CRC;
        }
    }

    //计算湿度值
    if (pSHT20->eRunState == eSHT20_READ_MEASUREMENT_H)
    {
        if (SHT20_CheckSum_CRC8(pSHT20))
        {
            /*
            H_temp32s = pSHT20->p8HData[0]; //MSB
            H_temp32s = H_temp32s << 8;
            H_temp32s |= pSHT20->p8HData[1]; //LSB
            H_temp32s = H_temp32s * 100;
            H_temp32s = H_temp32s / 65535;
            */
            H_temp32s = pSHT20->p8HData[0]-2; //MSB
            H_temp32s = H_temp32s << 8;
            H_temp32s += pSHT20->p8HData[1]; //LSB

            H_value   = H_temp32s;
            H_value = H_value * 125;
            H_value = H_value / 65536;
            H_value -= 6;
            H_temp32s = H_temp32s * 2;

            pSHT20->u8HumidityValue = (uint8_t)H_value;
            pSHT20->u8HumidityValue = pSHT20->u8HumidityValue * 2;

            if (pSHT20->u8HumidityValue > 200)
            {
                pSHT20->u8HumidityValue = 200;
                pSHT20->eFaultCode = eSHT20_ABNORMAL_DATA;
            }
            else
            {
                pSHT20->eFaultCode = eSHT20_NORMAL;
            }
           
        }
        else
        {
            pSHT20->eFaultCode = eSHT20_EXCEPTION_MESSAGE; //报文异常
            return eSHT20_ERR_DATA_CRC;
        }
    }
    return eSHT20_OK;
}

/**
   * @brief
   * @param
   * @retval
   */
void SHT20_OperationTask(SHT20_Typedef *pSHT20,uint32_t ReadCycle)
{
    //uint8_t RHresult[3] = {0};

#if (0x40 == SHT20_PHY_ADDRESS_ID)
    pSHT20->I2C.u8PhyAddress = 0;
#elif (0x45 == SHT20_PHY_ADDRESS_ID)
    pSHT20->I2C.u8PhyAddress = 1;
#endif

    if (pSHT20->eRunState > 10)
    {
        pSHT20->eRunState = eSHT20_IDLE;
    }
    if (pSHT20->eFaultCode > 3)
    {
        pSHT20->eFaultCode = eSHT20_NORMAL;
    }
    
    switch (pSHT20->eRunState)
    {
    case eSHT20_IDLE:

       
        pSHT20->u32ReadCycle = ReadCycle; //10S
        pSHT20->eRunState = eSHT20_PERIOD_WAIT;
        break;

    case eSHT20_PERIOD_WAIT:

        if (pSHT20->u32ReadCycle != 0)
        {
            break;
        }
        pSHT20->eRunState = eSHT20_INITIALIZE_STATE;
        break;

    case eSHT20_INITIALIZE_STATE:

        SHT20_BusReset(pSHT20);
        pSHT20->eRunState = eSHT20_START_MEASUREMENT_T;
        pSHT20->u16ReadWait = 200;
        break;

    case eSHT20_START_MEASUREMENT_T:

        if (pSHT20->u16ReadWait != 0)
        {
            break;
        }
        SHT20_T_SetCommand(pSHT20);
        pSHT20->u8SHT20DropsFlag = 0;
        pSHT20->eRunState = eSHT20_WAIT_MEASUREMENT_T;
        pSHT20->u16ReadWait = 100;
        //pSHT20->u16ReadWait = 100;
        break;

    case eSHT20_WAIT_MEASUREMENT_T:

        if (pSHT20->u16ReadWait != 0)
        {
            break;
        }
        pSHT20->eRunState = eSHT20_READ_MEASUREMENT_T;
        break;

    case eSHT20_READ_MEASUREMENT_T:

        SHT20_T_ReadBytes(pSHT20);
        SHT20_GetDataByBuff(pSHT20);
        if (pSHT20->u8SHT20DropsFlag == 0)
        {
            pSHT20->u8SHT20Dropscount++; //掉线计数
            if (pSHT20->u8SHT20Dropscount > 5)
            {
                pSHT20->u8SHT20Dropscount = 0;
                pSHT20->eFaultCode = eSHT20_EQUIPMENT_DROPS;
            }
            pSHT20->eRunState = eSHT20_START_MEASUREMENT_T;
            break;
        }
        else
        {
            pSHT20->eRunState = eSHT20_SWITCH_WAIT;
            pSHT20->u16ReadWait = 200;
            break;
        }

    case eSHT20_SWITCH_WAIT:

        if (pSHT20->u16ReadWait != 0)
        {
            break;
        }
        pSHT20->eRunState = eSHT20_START_MEASUREMENT_H;
        break;

    case eSHT20_START_MEASUREMENT_H:

        SHT20_H_SetCommand(pSHT20);
        pSHT20->u8SHT20DropsFlag = 0;
        pSHT20->u16ReadWait = 100;
        //pSHT20->u16ReadWait = 100;
        pSHT20->eRunState = eSHT20_WAIT_MEASUREMENT_H;
        break;

    case eSHT20_WAIT_MEASUREMENT_H:

        if (pSHT20->u16ReadWait != 0)
        {
            break;
        }
        pSHT20->eRunState = eSHT20_READ_MEASUREMENT_H;
        break;

    case eSHT20_READ_MEASUREMENT_H:

        SHT20_H_ReadBytes(pSHT20);
        SHT20_GetDataByBuff(pSHT20);
        if (pSHT20->u8SHT20DropsFlag == 0)
        {
            pSHT20->u8SHT20Dropscount++; //掉线计数
            if (pSHT20->u8SHT20Dropscount > 5)
            {
                pSHT20->u8SHT20Dropscount = 0;
                pSHT20->eFaultCode = eSHT20_EQUIPMENT_DROPS;
            }
            pSHT20->eRunState = eSHT20_START_MEASUREMENT_H;
            break;
        }
        else
        {
            pSHT20->eRunState = eSHT20_READ_END;
            break;
        }
    case eSHT20_READ_END:

        pSHT20->eRunState = eSHT20_IDLE;
        break;

    default:
        pSHT20->eRunState = eSHT20_IDLE;
        break;
    }
}
/*===========================================================
* @name		float SHT20_Calculate(char TorR, uint16_t data)
* @brief	相对湿度和温度的换算
* @details	根据接受到的数据进行换算
* @param	TorR：由'H'还是'T'选择进行相对湿度的换算还是温度的换算
* @param	data：测量结果
* @retval	float类型的换算结果，亦是最终结果
===========================================================*/
float SHT20_Calculate(char TorR, uint16_t data)
{
    data &= 0xfffc;
    if (TorR == 'H')
    {
        return (data * 125.0 / 65536.0) - 6;
    }
    else
    {
        return (data * 175.72 / 65536.0) - 46.85;
    }
}
/*===========================================================
* @name		void wend(SHT20_Typedef *pSHT20)
* @brief	
* @details	
* @param	
* @param	
* @retval	
===========================================================*/
void SHT20_T_SetCommand(SHT20_Typedef *pSHT20) //温度转换
{
    I2C_start(&pSHT20->HwPort); //开始

    I2C_send_byte(&pSHT20->HwPort, SHT2X_I2C_ADR_W);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return;
    }
    //测量温度
    I2C_send_byte(&pSHT20->HwPort, SHT2X_NOHM_TRIG_TEMP_MEAS);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return;
    }

    pSHT20->HwPort.pWait(200);

    I2C_stop(&pSHT20->HwPort);
}
/*===========================================================
* @name		void SHT20_H_SetCommand(SHT20_Typedef *pSHT20) //湿度转换
* @brief	
* @details	
* @param	
* @param	
* @retval	
===========================================================*/
void SHT20_H_SetCommand(SHT20_Typedef *pSHT20) //湿度转换
{
    I2C_start(&pSHT20->HwPort); //开始

    I2C_send_byte(&pSHT20->HwPort, SHT2X_I2C_ADR_W);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return;
    }

    //测量温度
    I2C_send_byte(&pSHT20->HwPort, SHT2X_NOHM_TRIG_HUMI_MEAS);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return;
    }

    pSHT20->HwPort.pWait(200);
    I2C_stop(&pSHT20->HwPort);
}
/*===========================================================
* @name		void SHT20_T_ReadBytes(SHT20_Typedef *pSHT20) //读取温度
* @brief	
* @details	
* @param	
* @param	
* @retval	
===========================================================*/
void SHT20_T_ReadBytes(SHT20_Typedef *pSHT20) //读取温度
{
    I2C_start(&pSHT20->HwPort);
    /*
    I2C_send_byte(&pSHT20->HwPort,SHT2X_I2C_ADR_W);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return ;
    }
    */
    //I2C_start(&pSHT20->HwPort);
    I2C_send_byte(&pSHT20->HwPort, SHT2X_I2C_ADR_R);

    if (!I2C_wait_ack(&pSHT20->HwPort))
    {
        pSHT20->u8SHT20DropsFlag = 1;
        pSHT20->u8SHT20Dropscount = 0;

        pSHT20->HwPort.pWait(10);

        pSHT20->p8TData[0] = I2C_receive_byte(&pSHT20->HwPort);
        I2C_ack(&pSHT20->HwPort);

        pSHT20->p8TData[1] = I2C_receive_byte(&pSHT20->HwPort);
        I2C_ack(&pSHT20->HwPort);

        pSHT20->p8TData[2] = I2C_receive_byte(&pSHT20->HwPort);
        I2C_no_ack(&pSHT20->HwPort);
        I2C_stop(&pSHT20->HwPort);
    }

    /*
    if(I2C_wait_ack(&pSHT20->HwPort))
    {
        return ;        
    }
    pSHT20->HwPort.pWait(10);

    pSHT20->p8TData[0] = I2C_receive_byte(&pSHT20->HwPort);
    I2C_ack(&pSHT20->HwPort);

    pSHT20->p8TData[1] = I2C_receive_byte(&pSHT20->HwPort);
    I2C_ack(&pSHT20->HwPort);

    pSHT20->p8TData[2] = I2C_receive_byte(&pSHT20->HwPort);
    I2C_no_ack(&pSHT20->HwPort);
    I2C_stop(&pSHT20->HwPort);
*/
}

/*===========================================================
* @name		void SHT20_H_SetCommand(SHT20_Typedef *pSHT20) //读取湿度
* @brief	
* @details	
* @param	
* @param	
* @retval	
===========================================================*/
void SHT20_H_ReadBytes(SHT20_Typedef *pSHT20) //读取湿度
{
    I2C_start(&pSHT20->HwPort);
    /*
    I2C_send_byte(&pSHT20->HwPort,SHT2X_I2C_ADR_W);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return ;
    }
    */
    I2C_send_byte(&pSHT20->HwPort, SHT2X_I2C_ADR_R);

    if (!I2C_wait_ack(&pSHT20->HwPort))
    {
        pSHT20->u8SHT20DropsFlag = 1;
        pSHT20->u8SHT20Dropscount = 0;

        pSHT20->HwPort.pWait(10);
        pSHT20->p8HData[0] = I2C_receive_byte(&pSHT20->HwPort);
        I2C_ack(&pSHT20->HwPort);

        pSHT20->p8HData[1] = I2C_receive_byte(&pSHT20->HwPort);
        I2C_ack(&pSHT20->HwPort);

        pSHT20->p8HData[2] = I2C_receive_byte(&pSHT20->HwPort);
        I2C_no_ack(&pSHT20->HwPort);
        I2C_stop(&pSHT20->HwPort);
    }

    /*
    if(I2C_wait_ack(&pSHT20->HwPort))
    {
        return ;        
    }
    pSHT20->HwPort.pWait(10);
    pSHT20->p8HData[0] = I2C_receive_byte(&pSHT20->HwPort);
    I2C_ack(&pSHT20->HwPort);

    pSHT20->p8HData[1] = I2C_receive_byte(&pSHT20->HwPort);
    I2C_ack(&pSHT20->HwPort);

    pSHT20->p8HData[2] = I2C_receive_byte(&pSHT20->HwPort);
    I2C_no_ack(&pSHT20->HwPort);
    I2C_stop(&pSHT20->HwPort);
*/
}

/*===========================================================
* @name		float SHT20_Measure(char MeasureTorH)
* @brief	测量函数
* @details	通过接受参数测量相对湿度或温度
* @param	MeasureTorH：'H'表示测量相对湿度，'T'表示温度
* @retval	float类型的测量结果
===========================================================*/
float SHT20_Measure(char MeasureTorH, SHT20_Typedef *pSHT20)
{

    pSHT20->HwPort.pWait(60000);
    pSHT20->HwPort.pWait(60000);
    pSHT20->HwPort.pWait(60000);
    pSHT20->HwPort.pWait(60000);
    pSHT20->HwPort.pWait(60000);

    I2C_start(&pSHT20->HwPort);
    I2C_send_byte(&pSHT20->HwPort, SHT2X_I2C_ADR_W);
    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        return !OK;
    }
    I2C_start(&pSHT20->HwPort);
    I2C_send_byte(&pSHT20->HwPort, SHT2X_I2C_ADR_R);

    if (I2C_wait_ack(&pSHT20->HwPort))
    {
        //循环等待测量结束
        // return !OK;
    }

    //pSHT20->u16ReadWait = 7;
    //SHT20_Tick10ms(pSHT20);

    return OK;
}
/**
   * @brief
   * @param
   * @retval
   */

#if 0  
void SHT20_OperationTask(SHT20_Typedef *pSHT20,uint16_t u16ReadPeriodSet,uint8_t u16ReadWaitSet)
{

#if (0x40 == SHT20_PHY_ADDRESS_ID)
    pSHT20->I2C.u8PhyAddress = 0;
#elif (0x45 == SHT20_PHY_ADDRESS_ID)
    pSHT20->I2C.u8PhyAddress = 1;
#endif
            
    if ( pSHT20->u8ErrorCount > 10 )
    {
        pSHT20->u8Error = 1;
    }

    switch(pSHT20->eRunState)
    {
        case eSHT20_IDLE              :
            pSHT20->eRunState = SHT20_START_MEASUREMENT;
            SHT20_BusReset(pSHT20);
            break;
        
        case SHT20_START_MEASUREMENT :
            if ( pSHT20->u16ReadPeriod )
            {
                return;
            }

            //pSHT20->I2C.u16Cmd = eSHT20_CMD_MEAS_POLLING_H;
            pSHT20->I2C.u16Cmd =  SHT2X_NOHM_TRIG_TEMP_MEAS;
            if ( eSHT20_OK != SHT20_SetCommand(&pSHT20->I2C) )
            {
                if ( pSHT20->u8ErrorCount < 0xFF ) 
                {
                    pSHT20->u8ErrorCount++;
                }
                return;
            }
            pSHT20->eRunState = SHT20_WAIT_MEASUREMENT;
            pSHT20->u16ReadWait    = u16ReadWaitSet;

            break;
        case SHT20_WAIT_MEASUREMENT  :
            if ( pSHT20->u16ReadWait )
            {                               
                return;
            }
            pSHT20->eRunState = SHT20_READ_MEASUREMENT;
            break;
        case SHT20_READ_MEASUREMENT  :

            pSHT20->I2C.u16DataLength = 6;
            if ( eSHT20_OK != SHT20_ReadBytes(&pSHT20->I2C) )
            {
                if ( pSHT20->u8ErrorCount < 0xFF ) 
                {
                    pSHT20->u8ErrorCount++;
                }
                return;
            }
            SHT20_GetDataByBuff(pSHT20);

            pSHT20->u8Error       = 0;
            pSHT20->eRunState     = SHT20_READ_STATUS;
            pSHT20->u8ErrorCount  = 0;
            break;

        case eSHT20_SW_RESET        :
            break;
        case eSHT20_INTERFACE_RESET   :
            break;
        case eSHT20_SELF_TEST_START_READ      :
            break;
        case eSHT20_SELF_TEST_HEAT_ON         :
            break;
        case eSHT20_SELF_TEST_WAIT             :
            break;
        case eSHT20_SELF_TEST_HEAT_OFF         :
            break;
        case eSHT20_SELF_TEST_STOP         :
            break;
        default:
            pSHT20->eRunState = eSHT20_IDLE;
            break;
    }
}
#endif


/* End of file */
