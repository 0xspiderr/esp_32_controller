/*****************************************************
*  INCLUDES
 *****************************************************/
#include "networking.h"

// test on board led command
#define LED_GPIO 18

/*****************************************************
 *  VARIABLES
 *****************************************************/
// for error logging
static const char *TAG = "NETWORKING";
static esp_now_command recv_data;


/*****************************************************
 *  DEFINITIONS
 *****************************************************/
void init_wifi(void)
{
	pinMode(LED_GPIO, OUTPUT);
	size_t no_connection_cnt = 0;
	WiFi.mode(WIFI_MODE_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	ESP_LOGI(TAG, "Attempting to connect to WiFi");
	// try wifi connection, restart esp after 15 seconds if not succesfull and try again.
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(100);
		if (++no_connection_cnt > 150)
		{
			ESP_LOGW(TAG, "Connection failed, restarting ESP-32");
			ESP.restart();
		}
	}

	ESP_LOGI(TAG, "Connected to WiFi: http://%s", WiFi.localIP().toString().c_str());
	ESP_LOGI(TAG, "RSSI(signal strength):%d", WiFi.RSSI());   // numbers closer to 0 mean better signal strength
	ESP_LOGI(TAG, "Receiver esp32 board MAC address:%s", WiFi.macAddress().c_str());
}

void init_esp_now(void)
{
	esp_err_t err;
	if (esp_now_init() != ESP_OK)
	{
		ESP_LOGE(TAG, "Couldn't initialize esp now!");
		ESP.restart();
	}
	// register esp now receive data callback
	err = esp_now_register_recv_cb(on_data_recv);
	if (err != ESP_OK)
	{
		ESP_LOGE(TAG, "Error registering send callback!");
		ESP.restart();
	}

	ESP_LOGI(TAG, "ESP-NOW initialization successful");
}

static void on_data_recv(const uint8_t *mac_addr, const uint8_t *incoming_data_buf, int len)
{
	memcpy(&recv_data, incoming_data_buf, sizeof(incoming_data_buf));
	ESP_LOGI(TAG, "command received:%s", recv_data.cmd);
	execute_cmd(recv_data.cmd);
}


static void execute_cmd (const char *cmd)
{
	String command = String(cmd);

	if (command.equals("F"))
	{
		ESP_LOGI(TAG, "command received:%s", command.c_str());
		digitalWrite(LED_GPIO, HIGH);
	}
	else
	{
		ESP_LOGW(TAG, "unknown command received:%s", command.c_str());
		digitalWrite(LED_GPIO, LOW);
	}

}