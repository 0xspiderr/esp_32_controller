#ifndef NETWORKING_H
#define NETWORKING_H
/*****************************************************
 *  INCLUDES
 *****************************************************/
#include <cstdint>
#include <cstring>
#include "ESP32Servo.h"
#include <WiFi.h>
#include <../../include/wifi_credentials.h>
#include <esp_now.h>

/*****************************************************
 *  STRUCTURES
 *****************************************************/
typedef struct esp_now_command
{
    char cmd[4];
} esp_now_command;

// test on board led command
#define LED_GPIO 2

/*****************************************************
 *  PROTOTYPES
 *****************************************************/
// init functions
void		init_wifi	(void);
void		init_esp_now(void);
// esp-now functions
static void on_data_recv(const uint8_t *, const uint8_t *, int);
static void execute_cmd (const char *);

#endif //NETWORKING_H
