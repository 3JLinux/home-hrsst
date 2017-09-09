#include "bc95.h"
#include "string.h"

#ifdef USE_BC95

#define SUCCEED			1
#define ID_NUM_ERROR 	0
#define DATA_ERROR 		0


//const char UDP_local_port[] = "4569";
//const char UDP_ipv4_addr[] = "119.29.224.28";
static const char double_quote[] = "\"";
static const char comma[] = ",";

/*****************************************************
����ԭ�ͣ� 		void bc95_send_cmd(const char *cmd)
���ܣ�			bc95��������
���룺			const u8 *cmd ����
���أ�			0
*****************************************************/
static void bc95_send_cmd(const char *cmd)
{
	char bc95_send_buff[64] = {0};
	u8 bc95_send_num;
	bc95_send_num = strlen((char *)cmd);
	memcpy(bc95_send_buff,cmd,bc95_send_num);
	XPRINT(level_printf_char,BC95_PRINTF_LEVEL,"bc95 send>>",bc95_send_buff,bc95_send_num);
	bc95_Send_Data(bc95_send_buff,bc95_send_num);
	bc95_Send_Data("\r\n",strlen("\r\n"));
}

/*****************************************************
����ԭ�ͣ� 		void bc95_rec_check(void)
���ܣ�			bc95���ռ��
���룺			
���أ�			0
*****************************************************/
u8* bc95_rec_check(const char *pcTarget, const char* pcFindStr)
{
	char *strx = NULL;
	strx = (char *)strstr(pcTarget,pcFindStr);
	return (u8*)strx;
}




/*****************************************************
����ԭ�ͣ� 		u8 bc95_setID(u8* id_num)
���ܣ�			дģ��IMEI
���룺			u8 *id_num IMEI��
���أ�			ID_NUM_ERROR �������15λ����
				SUCCEED	���ͳɹ�
*****************************************************/
u8 bc95_setID(u8* id_num)
{
	char send_cmd_buffer[30];
	const char set_id_cmd[] = "AT+NTSETID=1,";
	memcpy(send_cmd_buffer,set_id_cmd,strlen(set_id_cmd));
	if(strlen((char*)id_num) <= 15)
	{
		strcat(send_cmd_buffer,double_quote);
		strcat(send_cmd_buffer,(char*)id_num);
		//strcat(send_cmd_buffer,double_quote);
		bc95_send_cmd(send_cmd_buffer);
	}
	else
	{
		return ID_NUM_ERROR;
	}
	return SUCCEED;
}


/*****************************************************
����ԭ�ͣ� 		void bc95_request_IMEI(void)
���ܣ�			Request Product Seril Number
���룺			��
���أ�			��
*****************************************************/
void bc95_request_IMEI(void)
{
	bc95_send_cmd("AT+CGSN=1");
}


/*****************************************************
����ԭ�ͣ� 		void bc95_restar(void)
���ܣ�			Reboot
���룺			��
���أ�			��
*****************************************************/
void bc95_restar(void)
{
	bc95_send_cmd("AT+NRB");
}


/*****************************************************
����ԭ�ͣ� 		void bc95_get_singal(void)
���ܣ�			Get Singal Strength Indicator
���룺			��
���أ�			��
*****************************************************/
void bc95_get_singal(void)
{
	bc95_send_cmd("AT+CSQ");
}


/*****************************************************
����ԭ�ͣ� 		void bc95_query_UE_statistics(void)
���ܣ�			Query UE Statistics
���룺			��
���أ�			��
*****************************************************/
void bc95_query_UE_statistics(void)
{
	bc95_send_cmd("AT+NUESTATS");
}



/*****************************************************
����ԭ�ͣ� 		void bc95_set_band_5(void)
���ܣ�			Set Support
���룺			��
���أ�			��
*****************************************************/
void bc95_set_band_5(void)
{
	bc95_send_cmd("AT+NBAND=5");
}

/*****************************************************
����ԭ�ͣ� 		void bc95_set_band_8(void)
���ܣ�			Set Support
���룺			��
���أ�			��
*****************************************************/
void bc95_set_band_8(void)
{
	bc95_send_cmd("AT+NBAND=8");
}

/*****************************************************
����ԭ�ͣ� 		void bc95_set_band_20(void)
���ܣ�			Set Support
���룺			��
���أ�			��
*****************************************************/
void bc95_set_band_20(void)
{
	bc95_send_cmd("AT+NBAND=20");
}
/*************************************************Open scrambing code****************************************************/

/*****************************************************
����ԭ�ͣ� 		void bc95_set_min_fun(void)
���ܣ�			Set Minimum functionality
���룺			��
���أ�			��
*****************************************************/
void bc95_set_min_fun(void)
{
	bc95_send_cmd("AT+CFUN=0");
}

/*****************************************************
����ԭ�ͣ� 		void bc95_request_UE_behaviour(void)
���ܣ�			Request UE Behaviour
���룺			��
���أ�			��
*****************************************************/
void bc95_request_UE_behaviour(void)
{
	bc95_send_cmd("AT+NCONFIG?");
}

/*****************************************************
����ԭ�ͣ� 		void bc95_open_UE_behaviour(void)
���ܣ�			Open UE Behaviour
���룺			��
���أ�			��
*****************************************************/
void bc95_open_UE_behaviour(void)
{
	bc95_send_cmd("AT+NCONFIG=CR_0354_0338_SCRAMBLING,TRUE");
	bc95_send_cmd("AT+NCONFIG=CR_0859_SI_AVOID,TRUE");
}

/*****************************************************
����ԭ�ͣ� 		void bc95_close_UE_behaviour(void)
���ܣ�			Close UE Behaviour
���룺			��
���أ�			��
*****************************************************/
void bc95_close_UE_behaviour(void)
{
	bc95_send_cmd("AT+NCONFIG=CR_0354_0338_SCRAMBLING,FALSE");
	bc95_send_cmd("AT+NCONFIG=CR_0859_SI_AVOID,FALSE");
}

/************************************************************************************************************************/

/*************************************************Attach Network*********************************************************/

/*****************************************************
����ԭ�ͣ� 		void bc95_request_phone_fun(void)
���ܣ�			Request Set Phone Functionality
���룺			��
���أ�			��
*****************************************************/
void bc95_request_phone_fun(void)
{
	bc95_send_cmd("AT+CFUN?");
}


/*****************************************************
����ԭ�ͣ� 		void bc95_configure_server_settings(char* ip_addr,char* port)
���ܣ�			Configure and Query CDP Server Settings
���룺			char* ip_addr ip��ַ
				char* port �˿�
���أ�			��
*****************************************************/
void bc95_configure_server_settings(char* ip_addr,char* port)
{
	char send_cmd_buffer[30];
	const char configure_server[] = "AT+NCDP=";
	memcpy(send_cmd_buffer,configure_server,strlen(configure_server));
	strcat(send_cmd_buffer,ip_addr);
	strcat(send_cmd_buffer,comma);
	strcat(send_cmd_buffer,port);
	//strcat(send_cmd_buffer,double_quote);
	bc95_send_cmd(send_cmd_buffer);
}



/*****************************************************
����ԭ�ͣ� 		void bc95_set_phone_fun(void)
���ܣ�			Set Phone Functionality
���룺			��
���أ�			��
*****************************************************/
void bc95_set_phone_fun(void)
{
	bc95_send_cmd("AT+CFUN=1");
}


/*****************************************************
����ԭ�ͣ� 		void bc95_query_IMSI(void)
���ܣ�			Request International Mobile Subscriber Identity
���룺			��
���أ�			��
*****************************************************/
/*��ʱ3����ѯ��ȷ��ģ��ʶ��ÿ�*/
void bc95_query_IMSI(void)
{
	bc95_send_cmd("AT+CIMI");
}

/*****************************************************
����ԭ�ͣ� 		void bc95_Configuration_PDP(void)
���ܣ�			Define a PDP Context
���룺			��
���أ�			��
*****************************************************/
void bc95_Configuration_PDP(void)
{
	bc95_send_cmd("AT+CGDCONT=1,\"IP\",\"HUAWEI.COM\"");
} 

/*****************************************************
����ԭ�ͣ� 		void bc95_request_bands(void)
���ܣ�			Request Supported Bands
���룺			��
���أ�			��
*****************************************************/
void bc95_request_bands(void)
{
	bc95_send_cmd("AT+NBAND?");
}



/*****************************************************
����ԭ�ͣ� 		void bc95_activate_network(void)
���ܣ�			Activate the network
���룺			��
���أ�			��
*****************************************************/
void bc95_activate_network(void)
{
	bc95_send_cmd("AT+CGATT=1");
}


/*****************************************************
����ԭ�ͣ� 		void bc95_request_activate_network(void)
���ܣ�			Query whether network activation
���룺			��
���أ�			��
*****************************************************/
/*��ѯģ��ע�������30���ڲ�ѯֱ��Ϊ1*/
void bc95_request_activate_network(void)
{
	bc95_send_cmd("AT+CGATT?");
}


/*****************************************************
����ԭ�ͣ� 		void bc95_network_reg_status(void)
���ܣ�			Request EPS Network Registration Status
���룺			��
���أ�			��
*****************************************************/
void bc95_request_network_reg_status(void)
{
	bc95_send_cmd("AT+CEREG?");
}

/*****************************************************
����ԭ�ͣ� 		void bc95_network_reg_status(void)
���ܣ�			Request Signalling Connection Status
���룺			��
���أ�			��
*****************************************************/
void bc95_request_connetion_status(void)
{
	bc95_send_cmd("AT+CSCON?");
}





/**************************************************************************************************************************/


/*****************************************************
����ԭ�ͣ� 		void bc95_creat_socket(void)
���ܣ�			Create a Socket
���룺			��
���أ�			��
*****************************************************/
void bc95_creat_UDP_socket(char* port)
{
	char send_cmd_buffer[30];
	const char set_UDP_socket[] = "AT+NSOCR=DGRAM,17,";
	memcpy(send_cmd_buffer,set_UDP_socket,strlen(set_UDP_socket));
	strcat(send_cmd_buffer,port);
	//strcat(send_cmd_buffer,double_quote);
	bc95_send_cmd(send_cmd_buffer);
}

char* u32_to_hex(const u32 num)
{
	static char source_num[10] = {0};
	u32 change_num = num;
	u8 i = 0;
	while(change_num != 0)
	{
		source_num[i++]=change_num%10 + '0';
		change_num/=10;
	}
	source_num[i] = '\n';
	return source_num;
}
/*****************************************************
����ԭ�ͣ� 		void bc95_UDP_send_messages()
���ܣ�			UDP Send messages
���룺			��
���أ�			��
*****************************************************/
#define UDP_SEND_MAX 512
u8 bc95_UDP_send_messages(char socket,char* ip_addr,char* port,u32 len,u8* data)
{
	char send_cmd_buffer[530];
	const char udp_send_messages[] = "AT+NSOST=";
	if(len >= UDP_SEND_MAX)
	{
		return DATA_ERROR;
	}
	memcpy(send_cmd_buffer,udp_send_messages,strlen(udp_send_messages));
	strcat(send_cmd_buffer,&socket);
	strcat(send_cmd_buffer,comma);
	strcat(send_cmd_buffer,double_quote);
	strcat(send_cmd_buffer,ip_addr);
	strcat(send_cmd_buffer,double_quote);
	strcat(send_cmd_buffer,comma);
	strcat(send_cmd_buffer,port);
	strcat(send_cmd_buffer,comma);
	strcat(send_cmd_buffer,u32_to_hex(len));
	strcat(send_cmd_buffer,comma);
	strcat(send_cmd_buffer,(char*)data);
	return SUCCEED;
}

void bc95_close_socket(void)
{
	bc95_send_cmd("AT+NSOCL=0");
}


#endif









