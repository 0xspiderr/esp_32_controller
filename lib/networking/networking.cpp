/*****************************************************
*  INCLUDES
 *****************************************************/
#include "networking.h"
#include <esp_wifi.h>

/*****************************************************
 *  VARIABLES
 *****************************************************/
// for error logging
static const char *TAG = "NETWORKING";
static esp_now_command recv_data;
static int led_state = LOW;


/*****************************************************
 *  DEFINITIONS
 *****************************************************/
void init_wifi(void)
{
	size_t no_connection_cnt = 0;
	WiFi.mode(WIFI_AP_STA); // dont change this
	// esp_wifi_set_channel(TRANSMITTER_WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
	esp_wifi_set_ps(WIFI_PS_NONE);
	ESP_LOGI(TAG, "Connected to WiFi: http://%s", WiFi.localIP().toString().c_str());
	ESP_LOGI(TAG, "RSSI(signal strength):%s", String(WiFi.RSSI()).c_str());   // numbers closer to 0 mean better signal strength
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

	if (command == "F")
	{
		ESP_LOGI(TAG, "Forward command");
		digitalWrite(LED_GPIO, HIGH);
	}
	else if (command == "B")
	{
		ESP_LOGI(TAG, "Backward command");
	}
	else if (command == "L")
	{
		ESP_LOGI(TAG, "Left turn command");
	}
	else if (command == "R")
	{
		ESP_LOGI(TAG, "Right turn command");
	}
	else if (command == "S")
	{
		ESP_LOGI(TAG, "Stop command");
		digitalWrite(LED_GPIO, LOW);
	}
	else
	{
		ESP_LOGW(TAG, "Unknown command: %s", command.c_str());
		// Default to stop for safety
		digitalWrite(LED_GPIO, LOW);
	}
}