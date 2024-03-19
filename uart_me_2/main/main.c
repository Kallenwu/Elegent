#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "string.h"
static const int RX_BUF_SIZE =1024;
#define TXD_PIN (GPIO_NUM_4)
#define RXD_PIN (GPIO_NUM_5)

void init(void){//初始化串口
    const uart_config_t uart_config={
        .baud_rate=115200,
        .data_bits=UART_DATA_8_BITS,
        .parity=UART_PARITY_DISABLE,
        .stop_bits=UART_STOP_BITS_1,
        .flow_ctrl=UART_HW_FLOWCTRL_DISABLE,
        .source_clk=UART_SCLK_APB,
    };
    //不使用缓冲区发送数据
    uart_driver_install(UART_NUM_1,RX_BUF_SIZE*2,0,0,NULL,0);
    uart_param_config(UART_NUM_1,&uart_config);
    uart_set_pin(UART_NUM_1,TXD_PIN,RXD_PIN,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
}

int sendData (const char*logName ,const char* data)//发送数据函数//日志到底是干什么的啊
{
    const int len = strlen(data);
    const int txBytes=uart_write_bytes(UART_NUM_1,data,len);
    ESP_LOGI(logName,"%s\n",data);//使用日志记录宏之一生成输出
    return txBytes;
}
static void tx_task(void *arg)  //发送任务函数
{
    static const char *TX_TASK_TAG="TX_TASK";
    esp_log_level_set(TX_TASK_TAG,ESP_LOG_INFO);//这一句是干什么的
    while(1)
    {
        sendData(TX_TASK_TAG,"hello world");
        vTaskDelay(2000/portTICK_PERIOD_MS);//portTICK_PERIOD_MS?
    }
}
/*static void rx_task(void *arg)
{
    static const char *RX_TASK_TAG="RX_TASK";
    esp_log_level_set(RX_TASK_TAG,ESP_LOG_ERROR);
    uint8_t* data=(uint8_t*)malloc(RX_BUF_SIZE+1);
    while(1)
    {
        const int rxBytes = uart_read_bytes(UART_NUM_1,data,RX_BUF_SIZE,1000/portTICK_PERIOD_MS);
        
        if(rxBytes>0)
        {
            data[rxBytes]=0;//用程序将RI位置零准备接收下一条消息
            ESP_LOGI(RX_TASK_TAG,"Read %d bytes:'%s'",rxBytes,data);
            //ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG,data,rxBytes,ESP_LOG_INFO);//以指定级别向日志转储缓冲区
        }
    }
    free(data);
}
*/
void app_main(void) //主程序入口
{
    init();         //初始化
    //xTaskCreate(rx_task,"uart_rx_task",1024*2,NULL,configMAX_PRIORITIES,NULL);//创建接收任务
    xTaskCreate(tx_task,"uart_tx_task",1024*2,NULL,configMAX_PRIORITIES-1,NULL);//创建发射任务
}