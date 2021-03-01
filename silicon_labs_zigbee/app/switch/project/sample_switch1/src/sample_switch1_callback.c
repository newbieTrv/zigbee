/**
 * @Author: Leon
 * @email: zhangpeng@tuya.com
 * @LastEditors: Zhu Shaoling
 * @file name: callbacks.c
 * @Description: this file is a template of the sdk callbacks function,
 * user need to achieve the function yourself
 * @Copyright: HANGZHOU TUYA INFORMATION TECHNOLOGY CO.,LTD
 * @Company: http://www.tuya.com
 * @Date: 2019-03-12 17:29:33
 * @LastEditTime: 2019-04-17 15:51:35
 */

#include "stdio.h"
#include "stdlib.h"
#include "tuya_mf_test.h"
#include "tuya_zigbee_sdk.h"
#include "zigbee_dev_template.h"
#include "config.h"



/**
 *  keys, indicators and relays configuration information
 */
 
#define         KEY_1_PORT                      KEY0_PORT
#define         KEY_1_PIN                       KEY0_PIN
#define         KEY_1_MODE                      KEY0_MODE           //drive mode
#define         KEY_1_OUT                       KEY0_OUT            //initialization level
#define         KEY_1_DRIVER                    KEY0_DRIVER         //drive level

#define         KEY_2_PORT                      KEY1_PORT
#define         KEY_2_PIN                       KEY1_PIN
#define         KEY_2_MODE                      KEY1_MODE           //drive mode
#define         KEY_2_OUT                       KEY1_OUT            //initialization level
#define         KEY_2_DRIVER                    KEY1_DRIVER         //drive level

#define         KEY_3_PORT                      KEY2_PORT
#define         KEY_3_PIN                       KEY2_PIN
#define         KEY_3_MODE                      KEY2_MODE           //drive mode
#define         KEY_3_OUT                       KEY2_OUT            //initialization level
#define         KEY_3_DRIVER                    KEY2_DRIVER         //drive level

#define         KEY_4_PORT                      KEY3_PORT
#define         KEY_4_PIN                       KEY3_PIN
#define         KEY_4_MODE                      KEY3_MODE           //drive mode
#define         KEY_4_OUT                       KEY3_OUT            //initialization level
#define         KEY_4_DRIVER                    KEY3_DRIVER         //drive level

#define         KEY_5_PORT                      KEY4_PORT
#define         KEY_5_PIN                       KEY4_PIN
#define         KEY_5_MODE                      KEY4_MODE           //drive mode
#define         KEY_5_OUT                       KEY4_OUT            //initialization level
#define         KEY_5_DRIVER                    KEY4_DRIVER         //drive level

#define         KEY_6_PORT                      KEY5_PORT
#define         KEY_6_PIN                       KEY5_PIN
#define         KEY_6_MODE                      KEY5_MODE           //drive mode
#define         KEY_6_OUT                       KEY5_OUT            //initialization level
#define         KEY_6_DRIVER                    KEY5_DRIVER         //drive level

#define         LED_1_PORT                      LED0_PORT
#define         LED_1_PIN                       LED0_PIN
#define         LED_1_MODE                      LED0_MODE
#define         LED_1_DOUT                      LED0_OUT
#define         LED_1_DRIVE                     LED0_DRIVER

#define         LED_2_PORT                      LED1_PORT
#define         LED_2_PIN                       LED1_PIN
#define         LED_2_MODE                      LED1_MODE
#define         LED_2_DOUT                      LED1_OUT
#define         LED_2_DRIVE                     LED1_DRIVER

#define         LED_3_PORT                      LED2_PORT
#define         LED_3_PIN                       LED2_PIN
#define         LED_3_MODE                      LED2_MODE
#define         LED_3_DOUT                      LED2_OUT
#define         LED_3_DRIVE                     LED2_DRIVER

#define         LED_4_PORT                      LED3_PORT
#define         LED_4_PIN                       LED3_PIN
#define         LED_4_MODE                      LED3_MODE
#define         LED_4_DOUT                      LED3_OUT
#define         LED_4_DRIVE                     LED3_DRIVER

#define         LED_5_PORT                      LED4_PORT
#define         LED_5_PIN                       LED4_PIN
#define         LED_5_MODE                      LED4_MODE
#define         LED_5_DOUT                      LED4_OUT
#define         LED_5_DRIVE                     LED4_DRIVER

#define         LED_6_PORT                      LED5_PORT
#define         LED_6_PIN                       LED5_PIN
#define         LED_6_MODE                      LED5_MODE
#define         LED_6_DOUT                      LED5_OUT
#define         LED_6_DRIVE                     LED5_DRIVER


/**
 * enumerate zigbee device work mode
 */
 
typedef enum
{
    DEV_WORK_ST_NORMAL = 0,
    DEV_WORK_ST_TEST
} DEV_WORK_ST_T;

static DEV_WORK_ST_T g_work_st = DEV_WORK_ST_NORMAL;

/**
 * input IO pin configuration table
 */


const gpio_config_t gpio_input_config[] =
{
    {KEY_1_PORT, KEY_1_PIN, KEY_1_MODE, KEY_1_OUT, KEY_1_DRIVER},
    {KEY_2_PORT, KEY_2_PIN, KEY_2_MODE, KEY_2_OUT, KEY_2_DRIVER}, 
    {KEY_3_PORT, KEY_3_PIN, KEY_3_MODE, KEY_3_OUT, KEY_3_DRIVER},
    {KEY_4_PORT, KEY_4_PIN, KEY_4_MODE, KEY_4_OUT, KEY_4_DRIVER},
    {KEY_5_PORT, KEY_5_PIN, KEY_5_MODE, KEY_5_OUT, KEY_5_DRIVER},
    {KEY_6_PORT, KEY_6_PIN, KEY_6_MODE, KEY_6_OUT, KEY_6_DRIVER},
    
};


/**
 * output IO pin configuration table
 */
 
const gpio_config_t gpio_ouput_config[] =
{
    {LED_1_PORT, LED_1_PIN, LED_1_MODE, LED_1_DOUT, LED_1_DRIVE},
    {LED_2_PORT, LED_2_PIN, LED_2_MODE, LED_2_DOUT, LED_2_DRIVE},
    {LED_3_PORT, LED_3_PIN, LED_3_MODE, LED_3_DOUT, LED_3_DRIVE},
    {LED_4_PORT, LED_4_PIN, LED_4_MODE, LED_4_DOUT, LED_4_DRIVE},
    {LED_5_PORT, LED_5_PIN, LED_5_MODE, LED_5_DOUT, LED_5_DRIVE},
    {LED_6_PORT, LED_6_PIN, LED_6_MODE, LED_6_DOUT, LED_6_DRIVE},   
};

/**
 * the index of keys, indicators and relays in the input or output table
 */
 
#define KEY_1_IO_INDEX              0
#define KEY_2_IO_INDEX              1
#define KEY_3_IO_INDEX              2
#define KEY_4_IO_INDEX              3
#define KEY_5_IO_INDEX              4
#define KEY_6_IO_INDEX              5

#define LED_1_IO_INDEX              0
#define LED_2_IO_INDEX              1
#define LED_3_IO_INDEX              2
#define LED_4_IO_INDEX              3
#define LED_5_IO_INDEX              4
#define LED_6_IO_INDEX              5

#define NET_LED_1_IO_INDEX          6

#define RELAY_1_IO_INDEX            7

/**
 * the clusters and attributes of zigbee device, decice description
 */
 
const attr_t g_group_attr_list[] =
{
    GROUP_ATTR_LIST
};

const attr_t g_scene_attr_list[] =
{
    SCENE_ATTR_LIST
};

const attr_t g_light_attr_list[] =
{
    ON_OFF_LIGHT_ATTR_LIST
};

const cluster_t g_server_cluster_id[] =
{
    DEF_CLUSTER_GROUPS_CLUSTER_ID(g_group_attr_list)
    DEF_CLUSTER_SCENES_CLUSTER_ID(g_scene_attr_list)
    DEF_CLUSTER_ON_OFF_CLUSTER_ID(g_light_attr_list)
};

#define SERVER_CLUSTER_LEN  get_array_len(g_server_cluster_id)

const dev_description_t g_dev_des[] =
{
    { 1, ZHA_PROFILE_ID, ZG_DEVICE_ID_ON_OFF_LIGHT, SERVER_CLUSTER_LEN, (cluster_t *)&g_server_cluster_id[0], 0, NULL },
    { 2, ZHA_PROFILE_ID, ZG_DEVICE_ID_ON_OFF_LIGHT, SERVER_CLUSTER_LEN, (cluster_t *)&g_server_cluster_id[0], 0, NULL },
    { 3, ZHA_PROFILE_ID, ZG_DEVICE_ID_ON_OFF_LIGHT, SERVER_CLUSTER_LEN, (cluster_t *)&g_server_cluster_id[0], 0, NULL },
    { 4, ZHA_PROFILE_ID, ZG_DEVICE_ID_ON_OFF_LIGHT, SERVER_CLUSTER_LEN, (cluster_t *)&g_server_cluster_id[0], 0, NULL },
    { 5, ZHA_PROFILE_ID, ZG_DEVICE_ID_ON_OFF_LIGHT, SERVER_CLUSTER_LEN, (cluster_t *)&g_server_cluster_id[0], 0, NULL },
    { 6, ZHA_PROFILE_ID, ZG_DEVICE_ID_ON_OFF_LIGHT, SERVER_CLUSTER_LEN, (cluster_t *)&g_server_cluster_id[0], 0, NULL },
};

#define EP_SUMS sizeof(g_dev_des)/sizeof(g_dev_des[0])


#define         REAT_KEY1           1      //复位按键  1~6  同时按下两个按键才能重新配网
#define         REAT_KEY2           4      //复位按键  1~6

#define KEY_PUSH_TIME_FOR_ZIGBEE_JOIN_NEW               10000 //10s 
#define ZIGBEE_JOIN_MAX_TIMEOUT                         (300*1000)//300s = 5min



static uint8_t g_relay_onoff_status[EP_SUMS + 1] = {0};
static uint8_t g_relay_onoff_led[] = {LED_1_IO_INDEX,LED_2_IO_INDEX,LED_3_IO_INDEX,LED_4_IO_INDEX,LED_5_IO_INDEX,LED_6_IO_INDEX};


static void __dev_report_onoff_msg(uint8_t ep, SEND_QOS_T qs);
static void __dev_switch_op(uint8_t ep, DEV_IO_ST_T st);
static void __dev_status_save(uint8_t ep);
user_uart_config_t* mf_test_uart_config(void);
/**
 * @description: load attributes, operation indicators and relays
 * @param {void} 
 * @return: none
 */
 
static void __dev_status_load(void)
{
    uint8_t i;
    uint8_t st;
    for(i = 0; i < EP_SUMS; i++)
    {
        st = 0;
        dev_zigbee_read_attribute(
            i + 1,
            CLUSTER_ON_OFF_CLUSTER_ID,
            ATTR_ON_OFF_ATTRIBUTE_ID,
            &st,
            1
        );
        g_relay_onoff_status[i] = st;
        __dev_switch_op(i + 1, (DEV_IO_ST_T)g_relay_onoff_status[i]);
    }
}

/**
 * @description: save attributes 
 * @param {endpoint} the endpoint of the write attribute
 * @return: none
 */
 
static void __dev_status_save(uint8_t endpoint)
{
    dev_zigbee_write_attribute(
        endpoint,
        CLUSTER_ON_OFF_CLUSTER_ID,
        ATTR_ON_OFF_ATTRIBUTE_ID,
        &g_relay_onoff_status[endpoint - 1],
        ATTR_BOOLEAN_ATTRIBUTE_TYPE
    );
}


void Key_switch_report_msg(uint8_t key_ep, SEND_QOS_T Qos)
{
    static uint8_t ep_old=0;
    
    if(ep_old!=key_ep){
      __dev_switch_op(ep_old, DEV_IO_OFF);
      __dev_report_onoff_msg(ep_old, Qos);
      ep_old = key_ep;
    }
    __dev_switch_op(key_ep, DEV_IO_ON);
    __dev_report_onoff_msg(key_ep, Qos);
 
    
    
    
  
}

/**
 * @description: key processing 
 * @param {key_id} the key_id of key
 * @param {key_st} the trigger state of key
 * @param {push_time} press time of key
 * @return: none
 */
static void __dev_key_handle(uint32_t key_id, key_st_t key_st, uint32_t push_time)
{
    uint8_t ep = 1;

	app_print("key_id=%d",(key_id+1));
    if(EP_SUMS <= key_id)
    {
        return;
    }
    if(g_work_st == DEV_WORK_ST_TEST) // mf test mode
    {
        if(key_st != KEY_ST_PUSH)
        {
            dev_mf_button_test_notify(key_id);
        }
        return;
    }
    switch(key_id)
    {
        case KEY_1_IO_INDEX:
        {
            if(key_st == KEY_ST_PUSH)
            {
            	app_print("key1");
                if(push_time == KEY_PUSH_TIME_FOR_ZIGBEE_JOIN_NEW)
                {
                    ///Long press for 10s, it starts flashing to remind users that they are about to enter the distribution network
                    dev_led_start_blink(NET_LED_1_IO_INDEX, 125, 125, DEV_LED_BLINK_FOREVER, DEV_IO_OFF);
                }
            }
            else
            {
                ///after releasing the button, it is found that the long pressing time is within 10s, and the short pressing operation is performed
                if(push_time < KEY_PUSH_TIME_FOR_ZIGBEE_JOIN_NEW)
                {
                    __dev_switch_op(ep, (DEV_IO_ST_T)!g_relay_onoff_status[ep - 1]);
                    __dev_report_onoff_msg(ep, QOS_1);
                }
                else   //after releasing, it is found that the long press is more than 10s, and the real network distribution is performed
                {
                    dev_zigbee_join_start(ZIGBEE_JOIN_MAX_TIMEOUT);
                }
            }
            break;
        }
		case KEY_2_IO_INDEX:
        {
            if(key_st == KEY_ST_PUSH)
            {
            	app_print("key2");
        	}
			break;
		}
		case KEY_3_IO_INDEX:
        {
            if(key_st == KEY_ST_PUSH)
            {
            	app_print("key3");
        	}
			break;
		}
		case KEY_4_IO_INDEX:
        {
            if(key_st == KEY_ST_PUSH)
            {
            	app_print("key4");
        	}
			break;
		}
		case KEY_5_IO_INDEX:
        {
            if(key_st == KEY_ST_PUSH)
            {
            	app_print("key5");
        	}
			break;
		}
		case KEY_6_IO_INDEX:
        {
            if(key_st == KEY_ST_PUSH)
            {
            	app_print("key6");
        	}
			break;
		}
        default:
        {
            break;
        }
    }
}

/**
 * @description: report attributes 
 * @param {endpoint} the endpoint of the write attribute
 * @param {qs} permit loss packages or not
 * @return: none
 */
static void __dev_report_onoff_msg(uint8_t endpoint, SEND_QOS_T qs)
{
    dev_send_data_t send_data;
    memset(&send_data, 0, sizeof(dev_send_data_t));
    send_data.zcl_id = 0;
    send_data.qos = qs;
    send_data.direction = ZCL_DATA_DIRECTION_SERVER_TO_CLIENT;
    send_data.command_id = CMD_REPORT_ATTRIBUTES_COMMAND_ID;
    send_data.addr.mode = SEND_MODE_GW;
    send_data.addr.type.gw.cluster_id = CLUSTER_ON_OFF_CLUSTER_ID;
    send_data.addr.type.gw.src_ep = endpoint;
    send_data.delay_time = 0;
    send_data.random_time = 0;
    send_data.data.zg.attr_sum = 1;
    send_data.data.zg.attr[0].attr_id = ATTR_ON_OFF_ATTRIBUTE_ID;
    send_data.data.zg.attr[0].type = ATTR_BOOLEAN_ATTRIBUTE_TYPE;
    send_data.data.zg.attr[0].value_size = 1;
    send_data.data.zg.attr[0].value[0] = g_relay_onoff_status[endpoint - 1];
    dev_zigbee_send_data(&send_data, NULL, 1000);
    __dev_status_save(endpoint);
}

/**
 * @description: operate led and relay io
 * @param {endpoint} the endpoint of the write attribute
 * @param {st} on or off
 * @return: none
 */

static void __dev_switch_op(uint8_t endpoint, DEV_IO_ST_T st)
{
    g_relay_onoff_status[endpoint - 1] = st;
    switch(endpoint)
    {
        case 1:
            dev_io_op(RELAY_1_IO_INDEX, (DEV_IO_ST_T)g_relay_onoff_status[endpoint - 1]);
            dev_io_op(LED_1_IO_INDEX, (DEV_IO_ST_T)g_relay_onoff_status[endpoint - 1]);
            break;
        case 2:
            dev_io_op(LED_2_IO_INDEX, (DEV_IO_ST_T)g_relay_onoff_status[endpoint - 1]);
            break;
        case 3:
            dev_io_op(LED_3_IO_INDEX, (DEV_IO_ST_T)g_relay_onoff_status[endpoint - 1]);
            break;
        case 4:
            dev_io_op(LED_4_IO_INDEX, (DEV_IO_ST_T)g_relay_onoff_status[endpoint - 1]);
            break;
        case 5:
            dev_io_op(LED_5_IO_INDEX, (DEV_IO_ST_T)g_relay_onoff_status[endpoint - 1]);
            break;
        case 6:
            dev_io_op(LED_6_IO_INDEX, (DEV_IO_ST_T)g_relay_onoff_status[endpoint - 1]);
            break;
        default:
            break;
    }
}

/**
 * @description: device first power on, user can register device and init the gpio
 * @param {type} none
 * @return: none
 */
void dev_power_on_init(void)
{
    dev_register_zg_ep_infor((dev_description_t *)g_dev_des, EP_SUMS);
    zg_dev_config_t g_zg_dev_config;
    g_zg_dev_config.dev_type = ZG_ROUTER;
    g_zg_dev_config.config.router_cfg.reserved = 0;
    dev_register_zg_dev_config(&g_zg_dev_config);
    join_config_t cfg;
    cfg.auto_join_power_on_flag = 1;
    cfg.auto_join_remote_leave_flag = 1;
    cfg.join_timeout = ZIGBEE_JOIN_MAX_TIMEOUT;
    dev_zg_join_config(&cfg);
    dev_zigbee_recovery_network_set(TRUE);//nwk recover open
    gpio_button_init((gpio_config_t *)gpio_input_config, get_array_len(gpio_input_config), 50, __dev_key_handle);
    gpio_output_init((gpio_config_t *)gpio_ouput_config, get_array_len(gpio_ouput_config));



}

/**
 * @description: system start on, zigbee stack is inited completely and
 * manufactury test is ended, the uart and the timer is ok, user can
 * init the application event and any other application variables;
 * @param {type} none
 * @return: none
 */


//串口接收回调函数
void __uart_rx_callback(uint8_t *data, uint16_t len)
{
  
}

void __hardware_timer_func_t(TIMER_ID_T timer_id)
{
    static uint8_t cnt=0,cnt2=0,cnt3=0;

    switch(timer_id) {
        case V_TIMER0: { ///< 10ms 调用一次， 周期进来
             
            if(cnt3++ >= 200){
              cnt3 = 0;
              //app_print("*******test******\r\n");
            }             
            break;
        }
        
        case V_TIMER1: { ///< 500ms 调用一次，一次性
            break;
        }
    }
}


void dev_system_on_init(void)
{
    __dev_status_load();
//    user_uart_config_t uart_cfg = ZS3L_USART_CONFIG_DEFAULT; // /< TYZS3 模块的串口默认值
//    uart_cfg.func = __uart_rx_callback; // /< 填充串口接收回调函数
//    user_uart_init(&uart_cfg);
    hardware_timer_enable();
    timer_hardware_start_with_id(V_TIMER0, 100, HARDWARE_TIMER_AUTO_RELOAD_ENABLE, __hardware_timer_func_t);



	 user_uart_config_t *default_config = mf_test_uart_config();
	user_uart_init(default_config);
app_print("Aao Lai 6 seitch");

}

/**
 * @description: network state changed callback, when network state is changed,
 * the stack will call this function to notify the user;
 * @param {state} the new network state
 * @return: none
 */
void nwk_state_changed_callback(NET_EVT_T state)
{
    uint8_t i;
    switch(state)
    {
        case NET_POWER_ON_LEAVE:
        {
            break;
        }
        case NET_JOIN_START:
        {
            for(i=0;i<6;i++){
                dev_led_start_blink(g_relay_onoff_led[i], 250, 250, DEV_LED_BLINK_FOREVER, DEV_IO_OFF);
            }
            //dev_led_start_blink(LED_5_IO_INDEX, 250, 250, DEV_LED_BLINK_FOREVER, DEV_IO_OFF);
            break;
        }
        case NET_JOIN_TIMEOUT:
        {
            for(i=0;i<6;i++){
                dev_led_stop_blink(g_relay_onoff_led[i], DEV_IO_ON);
           }
            //dev_led_stop_blink(LED_5_IO_INDEX, DEV_IO_ON); 
            break;
        }
        case NET_POWER_ON_ONLINE:
        case NET_JOIN_OK:
        {
            for(i=0;i<6;i++){
                dev_led_stop_blink(g_relay_onoff_led[i], DEV_IO_OFF);
            } 
            //dev_led_stop_blink(LED_5_IO_INDEX, DEV_IO_OFF); 
            break;
        }
        case NET_LOST:
        {
            break;
        }
        case NET_REMOTE_LEAVE:
        {
            break;
        }
        case NET_LOCAL_LEAVE:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

/**
 * @description: device manufactury test callback, when device is in manufactury test model,
 * sdk will use this callback to notify application the test item and test command;
 * @param {cmd} manufactury test type
 * @param {*args} manufactury test data
 * @param {arg_len} manufactury test data length
 * @return: none
 */
MF_TEST_RET_T dev_mf_test_callback(MF_TEST_CMD_T cmd, uint8_t *args, uint16_t arg_len)
{
    switch(cmd)
    {
        case MF_TEST_LED_ON_ALL:
        {
            //dev_led_stop_blink(NET_LED_1_IO_INDEX, DEV_IO_ON);
            dev_led_stop_blink(LED_1_IO_INDEX, DEV_IO_ON);
            break;
        }
        case MF_TEST_LED_OFF_ALL:
        {
            //dev_led_stop_blink(NET_LED_1_IO_INDEX, DEV_IO_OFF);
            dev_led_stop_blink(LED_1_IO_INDEX, DEV_IO_OFF);
            break;
        }
        case MF_TEST_LED_BLINK_ALL:
        {
            //dev_led_start_blink(NET_LED_1_IO_INDEX, 500, 500, 4, DEV_IO_OFF);
            dev_led_start_blink(LED_1_IO_INDEX, 500, 500, 4, DEV_IO_OFF);
            break;
        }
        case MF_TEST_RELAY_ON_ALL:
        {
            dev_led_stop_blink(RELAY_1_IO_INDEX, DEV_IO_ON);
            break;
        }
        case MF_TEST_RELAY_OFF_ALL:
        {
            dev_led_stop_blink(RELAY_1_IO_INDEX, DEV_IO_OFF);
            break;
        }
        case MF_TEST_RELAY_BLINK_ALL:
        {
            dev_led_start_blink(RELAY_1_IO_INDEX, 500, 500, 4, DEV_IO_OFF);
            break;
        }
        case MF_TEST_BUTTON:
        {
            g_work_st = DEV_WORK_ST_TEST;
            return MF_TEST_DOING;
        }
        case MF_TRANSFER:
        {
        }
        default :
        {
            break;
        }
    }
    return MF_TEST_SUCCESS;
}

/**
 * @description: device manufactury beacon test callback, when device is in manufactury test mode,
 * sdk will use this callback to notify application to enter unsupervised production test;
 * @param {type} none
 * @return: none
 */
void dev_beacon_test_callback(void)
{
    // TODO
    return;
}

/**
 * @description: device report inforamtion when first power on(if need),;
 * @param {type} none
 * @return: none
 */
void dev_power_on_report_info(void)
{
    //TODO
    __dev_report_onoff_msg(1,QOS_1);
    return;
}


/**
 * @description: device recovery to factury command handler
 * @param {type} none
 * @return: none
 */
void dev_recovery_factory(DEV_RESET_TYPE_T type)
{
    //TODO
    return;
}

/**
 * @description: report mode attribute value
 * @param {IN SEND_QOS_T Qos} QOS value
 * @param {IN uint16_t delay_ms} delay report
 * @param {IN uint8_t mode} mode value
 * @return: none
 */
#define  ZCL_ID_MODE     101
#define TY_ATTR_LIGHT_MODE_ATTRIBUTE_ID         0xF000  //light mode attribute (1 byte)
typedef enum{
	ZIGBEE_CMD_SINGLE = 0,
	ZIGBEE_CMD_GROUP
}ZIGBEE_CMD_T;


void report_mode_value(IN SEND_QOS_T Qos, IN uint16_t delay_ms, IN uint8_t mode)
{
    dev_send_data_t send_data;
    memset(&send_data, 0, sizeof(dev_send_data_t));

    send_data.qos = Qos;
    send_data.delay_time = delay_ms;
    send_data.zcl_id = ZCL_ID_MODE;
    send_data.direction = ZCL_DATA_DIRECTION_SERVER_TO_CLIENT;
    send_data.command_id = CMD_REPORT_ATTRIBUTES_COMMAND_ID;
    send_data.addr.mode = SEND_MODE_GW;
    send_data.addr.type.gw.cluster_id = CLUSTER_COLOR_CONTROL_CLUSTER_ID;
    send_data.addr.type.gw.src_ep = 1;
    send_data.data.zg.attr_sum = 1;
    send_data.data.zg.attr[0].attr_id = TY_ATTR_LIGHT_MODE_ATTRIBUTE_ID;
    send_data.data.zg.attr[0].type = ATTR_INT8U_ATTRIBUTE_TYPE;
    send_data.data.zg.attr[0].value_size = 1;
    send_data.data.zg.attr[0].value[0] = mode;

    dev_zigbee_clear_send_data(3, &send_data.zcl_id);
    dev_zigbee_send_data(&send_data,NULL,1000);
    app_print("Report mode QOS:%d VALUE %d",Qos,mode);
}

void app_cmd_set_mode_handler(ZIGBEE_CMD_T cmd_type, uint8_t mode)
{
    SEND_QOS_T QOS = QOS_VIP_0;
    uint32_t delay_ms = 0;

    app_print("Receive  mode : %d",mode);
    if(cmd_type == ZIGBEE_CMD_GROUP){
        delay_ms = 10000 + random_ms(10000);
        QOS = QOS_0;
    }

    report_mode_value(QOS, delay_ms, mode);
//    handleTheCountDown(delay_ms);

    //updata mode attribute
    dev_zigbee_write_attribute(1,\
                               CLUSTER_COLOR_CONTROL_CLUSTER_ID,\
                               TY_ATTR_LIGHT_MODE_ATTRIBUTE_ID,\
                               &mode,\
                               ATTR_INT8U_ATTRIBUTE_TYPE);
    //updata app data attribute
//    app_data_t app_data;
//    read_app_data_attr(&app_data);
//    app_data.mode = mode;
//    write_app_data_attr(&app_data);
}


#define TY_CMD_SET_COLOR_MODE_CMD_ID            0xF0    //change mode cmd: white/color/scene/music
#define  ZCL_ID_ONOFF    100
#define  ZCL_ID_APP_DATA   109
STATIC void clear_recall_scene_report(void)
{
    uint8_t zcl_id = ZCL_ID_ONOFF;
    dev_zigbee_clear_send_data(ZG_CLEAR_ALL_ZCL_ID, &zcl_id);
    zcl_id = ZCL_ID_APP_DATA;
    dev_zigbee_clear_send_data(ZG_CLEAR_ALL_ZCL_ID, &zcl_id);
}
/**
 * @description: device receive message callback
 * @param {*dev_msg} received message information
 * @return: ZCL_CMD_RET_T
 */
ZCL_CMD_RET_T dev_msg_recv_callback(dev_msg_t *dev_msg)
{
    ZCL_CMD_RET_T result = ZCL_CMD_RET_SUCCESS;
    attr_value_t *attr_list = dev_msg->data.attr_data.attr_value;
    static uint8_t mode_old =0;
    uint8_t i,mode,attr_sum = dev_msg->data.attr_data.attr_value_sums;
    ZIGBEE_CMD_T app_cmd_type = ZIGBEE_CMD_SINGLE;
    //信息传输方式：单播方式
//    if(dev_msg->msg_src == MSG_SRC_GW_UNICAST || dev_msg->msg_src == MSG_SRC_DEV_UNICAST){ 
//	app_cmd_type = ZIGBEE_CMD_SINGLE; //0
//        //app_print("receive single message\n");
//    }else{
//	app_cmd_type = ZIGBEE_CMD_GROUP;  //1
//        //app_print("receive group message\n");
//    }

    
    
    app_print("Recv_callback msg: dev_msg->cluster = %d, attr_sum = %d\r\n",dev_msg->cluster,attr_sum);
    for(i=0;i<attr_list[0].value_len;i++)
    {
      app_print("attr_list[0].value[%d] = %d \r\n",i,attr_list[0].value[i]);                        
    }
    
    switch (dev_msg->cluster)
    {
        case CLUSTER_PRIVATE_TUYA_CLUSTER_ID: //private data processing
        {
            ////uint8_t len = dev_msg->data.bare_data.len;
            ////uint8_t *data = dev_msg->data.bare_data.data;
            //todo:
            break;
        }
        case CLUSTER_ON_OFF_CLUSTER_ID: //standard data processin
        {
            attr_value_t *attr_list = dev_msg->data.attr_data.attr_value;
            uint8_t attr_sums = dev_msg->data.attr_data.attr_value_sums;
            uint8_t i;
            for(i = 0; i < attr_sums; i++)
            {
                switch(attr_list[i].cmd)
                {
                    case CMD_OFF_COMMAND_ID:
                    {
                        Key_switch_report_msg(dev_msg->endpoint,QOS_0);
                        break;
                    }
                    case CMD_ON_COMMAND_ID:
                    {
                        Key_switch_report_msg(dev_msg->endpoint,QOS_0);
                        break;
                    }
                    case CMD_TOGGLE_COMMAND_ID:
                    {
                        Key_switch_report_msg(dev_msg->endpoint,QOS_0);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
        }
//        case CLUSTER_COLOR_CONTROL_CLUSTER_ID:{   
//            clear_recall_scene_report();
//            for(i=0;i<attr_sum;i++){
//                switch (attr_list[0].cmd){
//                    case TY_CMD_SET_COLOR_MODE_CMD_ID:{
//                        mode = attr_list[0].value[0];
//                        
//                        __dev_switch_op(mode, DEV_IO_ON);
//                        if(mode_old!=mode){
//                          __dev_switch_op(mode_old, DEV_IO_OFF);
//                          mode_old = mode;
//                        }
//                        app_cmd_set_mode_handler(app_cmd_type, mode);    //场景设置
//                        //app_print("[%d] attr_list[0].cmd = %d (set mode)\r\n",i,attr_list[0].cmd);
//                        break;
//                    }
//                    default:
//                        //app_print("[%d] attr_list[0].cmd = %d \r\n",i,attr_list[0].cmd);
//                        break;
//                }        
//            }
//            break;
//        }
        default:
            // Unrecognized cluster ID, error status will apply.
            break;
    }
    return result;
}

/**
 * @description: device recall scene command, recovery the scene add status
 * @param {endpoint} the endpoint of scene recall command
 * @param {*in_data} the data need to be handled of the device status
 * @return: none
 */
void dev_scene_recall_callback(uint8_t endpoint, const scene_save_data_t *in_data)
{
    //TODO
    switch(in_data->type)
    {
        case SCENE_DATA_TYPE_USER_DEFINE:
        {
            if(in_data->data[0] == 1)
            {
                __dev_switch_op(endpoint, DEV_IO_ON);
                __dev_report_onoff_msg(endpoint, QOS_1);
            }
            else if(in_data->data[0] == 0)
            {
                __dev_switch_op(endpoint, DEV_IO_OFF);
                __dev_report_onoff_msg(endpoint, QOS_1);
            }
            break;
        }
        case SCENE_DATA_TYPE_SERVER_DEFINE: //鏍规嵁鏈嶅姟鍣ㄧ殑閰嶇疆鏍煎紡瑙ｆ瀽
            break;
        case SCENE_DATA_TYPE_ZIGBEE_DEFINE: //鏍规嵁zigbee鏍囧噯鍗忚鏍煎紡瑙ｆ瀽
            break;
        default:
            break;
    }
    return;
}

/**
 * @description: device scene add command, store the current status to the scene table
 * @param {endpoint} the endpoint of scene add command
 * param {*out_data} the data need to be store to scene table
 * param {*in_out_len} the data length of the store data
 * @return: none
 */
void dev_scene_add_callback(uint8_t endpoint, uint8_t *out_data, uint8_t *in_out_len)
{
    //TODO
    *in_out_len = 1;
    out_data[0] = g_relay_onoff_status[endpoint - 1];
    return;
}

/**
 * @description: write sttribute callback function
 * @param {endpoint} the endpoint of the write attribute
 * @param {cluster} the cluster id of the write attribute
 * @param {attr_id} the attribute id  of the write attribute
 * @return: none
 */
void dev_msg_write_attr_callback(uint8_t endpoint, CLUSTER_ID_T cluster, uint16_t attr_id)
{
    //TODO
    return;
}

/**
 * @description: mf test uart register, aotomatic generated, not edit
 * @param {void} none
 * @return: user_uart_config_t mf uart config information
 */
user_uart_config_t config;
user_uart_config_t* mf_test_uart_config(void)
{
    memset(&config, 0, sizeof(user_uart_config_t));
    if (MODULE_NAME == TYZS2R)
    {
        user_uart_config_t default_config = TYZS2R_USART_CONFIG_DEFAULT;
        memcpy(&config, &default_config, sizeof(user_uart_config_t));
    }
    else if(MODULE_NAME == TYZS5)
    {
        user_uart_config_t default_config = TYZS5_USART_CONFIG_DEFAULT;
        memcpy(&config, &default_config, sizeof(user_uart_config_t));
    }
	    else if(MODULE_NAME == ZS3L)
    {
        user_uart_config_t default_config = ZS3L_USART_CONFIG_DEFAULT;
        memcpy(&config, &default_config, sizeof(user_uart_config_t));
    }
    else
    {
        user_uart_config_t default_config = TYZS3_USART_CONFIG_DEFAULT;
        memcpy(&config, &default_config, sizeof(user_uart_config_t));
    }
    return &config;
}
