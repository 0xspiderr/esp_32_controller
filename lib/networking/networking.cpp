/*****************************************************
*  INCLUDES
 *****************************************************/
#include "networking.h"
#include <esp_wifi.h>

#include "../camera_control/camera_control.h"
#include "../motor_control/motor_control.h"

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
	WiFi.mode(WIFI_AP_STA); // dont change this
	esp_wifi_set_channel(TRANSMITTER_WIFI_CHANNEL, WIFI_SECOND_CHAN_NONE);
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
	memcpy(&recv_data, incoming_data_buf, sizeof(recv_data));
	ESP_LOGI(TAG, "command received:%s", recv_data.cmd);
	execute_cmd(recv_data.cmd);
}


static void execute_cmd (const char *cmd)
{
	String command = String(cmd);

	if (command == "F")
	{
		ESP_LOGI(TAG, "Forward command");
		move_foward();
	}
	else if (command == "B")
	{
		ESP_LOGI(TAG, "Backward command");
		move_backward();
	}
	else if (command == "L")
	{
		ESP_LOGI(TAG, "Left turn command");
		move_left();
	}
	else if (command == "R")
	{
		ESP_LOGI(TAG, "Right turn command");
		move_right();
	}
	else if (command == "S")
	{
		ESP_LOGI(TAG, "Stop command");
		move_stop();
	}
	else if (command == "NS")
	{
		ESP_LOGI(TAG, "Neutral servo command");
		move_neutral_servo();
	}
	else if (command == "SAM")
	{
		ESP_LOGI(TAG, "Stop arm motor command");
		stop_arm_motor();
	}
	else if (command == "AMD")
	{
		ESP_LOGI(TAG, "Arm motor down command");
		drive_arm_motor(200);
	}
	else if (command == "AMU")
	{
		ESP_LOGI(TAG, "Arm motor up command");
		drive_arm_motor(-200);
	}
	else if (command == "ASO")
	{
		ESP_LOGI(TAG, "Arm servo open");
		open_arm_gripper();
	}
	else if (command == "ASC")
	{
		ESP_LOGI(TAG, "Arm servo close");
		close_arm_gripper();
	}
	else if (command == "CSR")
	{
		ESP_LOGI(TAG, "Camera servo rotate right");
		rotate_camera_servo_right();
	}
	else if (command == "CSL")
	{
		ESP_LOGI(TAG, "Camera servo rotate left");
		rotate_camera_servo_left();
	}
	else
	{
		ESP_LOGW(TAG, "Unknown command: %s", command.c_str());
	}
}