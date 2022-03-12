//Darren Animo
//Alexander Yu

//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
//
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

//*****************************************************************************
//
// Application Name     - Timer Count Capture
// Application Overview - This application showcases Timer's count capture
//                        feature to measure frequency of an external signal.
//
//*****************************************************************************

// Standard includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "interrupt.h"
#include "hw_apps_rcm.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
#include "gpio.h"
#include "uart.h"
#include "utils.h"
#include "timer.h"
#include "rom.h"
#include "rom_map.h"
#include "pin.h"
#include "utils.h"
// Common interface includes
#include "uart_if.h"
#include "pin_mux_config.h"

#include "spi.h"
#include "pin_mux_config.h"
#include "Adafruit_SSD1351.h"
#include "Adafruit_GFX.h"
#include "glcdfont.h"
// Custom includes
#include "queue.h"

// SimpleLink includes
#include "simplelink.h"

// common interface includes

#include "common.h"
#include "gpio_if.h"

// HTTP Client lib
#include <http/client/httpcli.h>
#include <http/client/common.h>

// JSON Parser
#include "jsmn.h"


#include "spotifyendpoints.h"
#include "BongoCat.h"

#define UART_PRINT              Report
#define FOREVER                 1
#define CONSOLE                 UARTA0_BASE
#define FAILURE                 -1
#define SUCCESS                 0
#define RETERR_IF_TRUE(condition) {if(condition) return FAILURE;}
#define RET_IF_ERR(Func)          {int iRetVal = (Func); \
                                   if (SUCCESS != iRetVal) \
                                     return  iRetVal;}
// SPI Macros
#define MASTER_MODE      1

#define SPI_IF_BIT_RATE  1000000
#define TR_BUFF_SIZE     100

// OLED MACROS
#define NUM_COLORS      5
#define BLACK           0x0000
#define BLUE            0x001F
#define GREEN           0x07E0
#define CYAN            0x07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF
#define TEXT_BOX_X_LIM  20        // Max number of chars that can fit on one row of the OLED screen
#define TEXT_BOX_Y_LIM  5        // Same as above but with column


#define TOP             1
#define BOTTOM          10

#define RECIEVE_MAX     100
#define TRANSMIT_MAX    100


#define APPLICATION_VERSION     "1.4.0"
#define APP_NAME        "Timer Count Capture"
#define MAX_TIMER_COUNT        4294967295       // Largest value the timer can count to
#define START_CODE             1080000          // Timer counts equal to the 13.5 ms start code
#define READ_TIMEOUT           200000           // Timer counts equal to the
#define CODE_ONE               90000            // Timer counts equal to reading a 1
#define CODE_ZERO              115000           // Timer counts equal to reading a 0
#define LOGIC_COUNT_TOLERANCE  4000             // Tolerance allowed for a given reading (plus or minus)
                                                // Equal to 2 x Standard Deviation
#define START_COUNT_TOLERANCE  160000

#define REMOTE_ADDRESS         0x00000          //
#define MULTITAP_TIMEOUT       100000000        // 2 Seconds to keep multitap enabled
#define MUTE_CHAR              'M'
#define LAST_CHAR              'L'
#define COLOR_CHAR             'C'
#define BLANK_CHAR             'B'
#define CURSOR_CHAR            'I'

// IR REMOTE's BINARY CODE FOR BUTTONS
// FORMAT:  ADDRESS INVERTED_ADDRESS VALUE INVERTED_VALUE
/*
#define REMOTE_ONE             0b00100001000001111000000001111111
#define REMOTE_TWO             0b00100001000001110100000010111111
#define REMOTE_THREE           0b00100001000001111100000000111111
#define REMOTE_FOUR            0b00100001000001110010000011011111

#define REMOTE_FIVE            0b00100001000001111010000001011111


#define REMOTE_SIX             0b00100001000001110110000010011111
#define REMOTE_SEVEN           0b00100001000001111110000011111000
#define REMOTE_EIGHT           0b00100001000001110001000011101111
#define REMOTE_NINE            0b00100001000001111001000001101111
#define REMOTE_ZERO            0b00100001000001110000000011111111
#define REMOTE_MUTE            0b00100001000001110010011011011001
#define REMOTE_LAST            0b00100001000001111110101000010101
*/

#define REMOTE_ONE      0x6F7C3FC0
#define REMOTE_TWO      0x6F7C5FA0
#define REMOTE_THREE    0x6F7C1FE0
#define REMOTE_FOUR     0x6F7C6F90
#define REMOTE_FIVE     0x6F7C2FD0
#define REMOTE_SIX      0x6F7C4FB0
#define REMOTE_SEVEN    0x6F7C0FF0
#define REMOTE_EIGHT    0x6F7C7788
#define REMOTE_NINE     0x6F7C37C8
#define REMOTE_ZERO     0x6F7C7F80
#define REMOTE_MUTE     0x6F7C6C93
#define REMOTE_LAST     0x6F7C0AF5

//TESTING DEFINITIONS
#define NUM_SAMPLES  200



#define CLIENT_CREDENTIALS_BASE64 "Basic MGQ4OGEwZjUzN2U5NDE4Nzk3YjRlNzI0MjFmNWMwNzA6OGFlMTRiN2Y0OTUzNDBhNGEzNDU0YWIzOGY0MWZmNTM="
#define POST_AUTHORIZATION_DATA "grant_type=refresh_token&refresh_token=AQAItYB4c_YFFeWkPDAaH3Y2Em_pyyJIJO-gZvzdIUgFLo3BouulB8qCsngTmA1Tg30XwYaQZ9AAD48tp8qPEnVgLLIwU1ysRy1D8tdK2nKbNifX1e0mv0t9W1MeOXblhOU"
#define POST_REQUEST_URI    "/v1/me/player/next"
#define POST_DATA           "{ }"


#define DELETE_REQUEST_URI  "/delete"


#define PUT_REQUEST_URI     "/v1/me/player/volume?volume_percent="
//#define PUT_DATA            "{\r\n \"volume_percent\" : 50 \r\n}"

//#define GET_REQUEST_URI   "/v1/me/player/devices" //"/v1/me/player"
#define GET_REQUEST_URI     "/v1/me/player"  ///currently-playing"
//#define GET_REQUEST_URI     ""

#define AUTH_HOST_NAME      "accounts.spotify.com"
#define SERVER_NAME         "api.spotify.com"
#define HOST_NAME           "api.spotify.com" //"<host name>"
#define HOST_PORT            443

#define SL_SSL_CA_CERT "/cert/rootCA.der"
//#define SL_SSL_CA_CERT "/cert/spotify.der"
#define SL_SSL_PRIVATE "/cert/private.der"
#define SL_SSL_CLIENT  "/cert/client.der"

#define READ_SIZE           3000
#define MAX_BUFF_SIZE       3000

// New Authorization tokens must be requested every ~hour
#define AUTHORIZATION_TOKEN "Bearer BQBEFUvSrW9F_TQtefJepELy0oJN_aYSTgjkv0OUwVt3WCxe_6-IMH3L-6xZTtCDWPaIUKurDalgMDKVi6QxJPnk8Im0PWlzu8yejJuNX1XhFs-F8y0GICyKqofztcVD-uGvoezW7fUpVPubdNIywMvxO4eLeb0ipvEt159VUywb6ExqWS3Qc7d5__2mzjhzYEk"


#define REQUEST_TOKEN "AQAItYB4c_YFFeWkPDAaH3Y2Em_pyyJIJO-gZvzdIUgFLo3BouulB8qCsngTmA1Tg30XwYaQZ9AAD48tp8qPEnVgLLIwU1ysRy1D8tdK2nKbNifX1e0mv0t9W1MeOXblhOU"

//NEED TO UPDATE THIS FOR IT TO WORK!
#define DATE                11    /* Current Date */
#define MONTH               3     /* Month 1-12 */
#define YEAR                2022  /* Current year */
#define HOUR                03    /* Time - hours */
#define MINUTE              28    /* Time - minutes */
#define SECOND              0     /* Time - seconds */

// Application specific status/error codes
typedef enum{
 /* Choosing this number to avoid overlap with host-driver's error codes */
    DEVICE_NOT_IN_STATION_MODE = -0x7D0,
    DEVICE_START_FAILED = DEVICE_NOT_IN_STATION_MODE - 1,
    INVALID_HEX_STRING = DEVICE_START_FAILED - 1,
    TCP_RECV_ERROR = INVALID_HEX_STRING - 1,
    TCP_SEND_ERROR = TCP_RECV_ERROR - 1,
    FILE_NOT_FOUND_ERROR = TCP_SEND_ERROR - 1,
    INVALID_SERVER_RESPONSE = FILE_NOT_FOUND_ERROR - 1,
    FORMAT_NOT_SUPPORTED = INVALID_SERVER_RESPONSE - 1,
    FILE_OPEN_FAILED = FORMAT_NOT_SUPPORTED - 1,
    FILE_WRITE_ERROR = FILE_OPEN_FAILED - 1,
    INVALID_FILE = FILE_WRITE_ERROR - 1,
    SERVER_CONNECTION_FAILED = INVALID_FILE - 1,
    GET_HOST_IP_FAILED = SERVER_CONNECTION_FAILED  - 1,

    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;

typedef struct
{
   /* time */
   unsigned long tm_sec;
   unsigned long tm_min;
   unsigned long tm_hour;
   /* date */
   unsigned long tm_day;
   unsigned long tm_mon;
   unsigned long tm_year;
   unsigned long tm_week_day; //not required
   unsigned long tm_year_day; //not required
   unsigned long reserved[3];
}SlDateTime;

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
extern const tImage BongoCatPause = { image_data_BongoCatPause, 128, 87,
        8 };
extern const tImage BongoCatLeftSlap = { image_data_BongoCatLeftSlap, 128, 87 ,
        8 };
const tImage BongoCatRightSlap = { image_data_BongoCatRightSlap, 128, 87,
    8 };
static unsigned long g_ulSamples[2];
static unsigned long g_ulIntervals[NUM_SAMPLES];
static unsigned long g_ulOnesSamples[NUM_SAMPLES];
static unsigned long g_ulZerosSamples[NUM_SAMPLES];
volatile unsigned long TIMER_intcount;
volatile unsigned char TIMER_intflag;

queue_t data_buffer;
char recieve_buffer[RECIEVE_MAX];
char recieve_color_buffer[RECIEVE_MAX];
char recieve_msg_length = 0;
int  recieve_index = 0;

char transmit_buffer[TRANSMIT_MAX];
char transmit_color_buffer[TRANSMIT_MAX];
unsigned int transmit_index = 0;



int interval_count = 0;
unsigned short int multitap_count = 0;


unsigned int code_word = 0;         // Binary representation of 32bit signal
unsigned int previous_code_word = 0;
unsigned int prev_code_word = 0;
unsigned long count = 0;             // Length between two falling edges


// OLED VARIABLES
int cursor_i = 0;  // Top Cursor Position
int cursor_j = TOP;

int bot_cursor_i = 0;  // Bottom Cursor Position
int bot_cursor_j = BOTTOM;

unsigned int text_colors[NUM_COLORS] = {CYAN, GREEN, YELLOW, RED, MAGENTA};
unsigned int color_index = 0;
char last_display_char = 0;
int command = 0;
int playstate = 0; // 0 = paused, 1 = playing
int message_ready = 0;
int v = 0; // volume slider position
int p = 6; // play slider position
int minute = 0; // x:00
int second1 = 0; // 0:x0
int second2 = 0; // 0:0x
int minutef = 0;
int second1f = 0;
int second2f = 0;
char* songname = "Starting";
char* artist = "Connecting to Spotify";
int songlength = 0;
int newsong = 1;
//double sliderspeed = 123/200;
//double sliderinc = 6;




#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
volatile unsigned long  g_ulStatus = 0;//SimpleLink Status
unsigned long  g_ulDestinationIP; // IP address of destination server
unsigned long  g_ulAuthDestinationIP; // IP addres of desitination server
unsigned long  g_ulGatewayIP = 0; //Network Gateway IP address
unsigned char  g_ucConnectionSSID[SSID_LEN_MAX+1]; //Connection SSID
unsigned char  g_ucConnectionBSSID[BSSID_LEN_MAX]; //Connection BSSID
unsigned char g_buff[MAX_BUFF_SIZE+1];
signed char  *g_Host = HOST_NAME;
HTTPCli_Struct httpClient;
HTTPCli_Struct httpAuthClient;

char progress_time[50];
char  artist_name[100];
char duration[50];
char song_name[100];

long int_duration_time;
long int_progress_time;
unsigned long slider_tick_time =0xffffffff;
SlDateTime g_time;

unsigned char authorization_token[256];

long bytesReceived = 0; // variable to store the file size

#if defined(ccs) || defined(gcc)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif

char* http_endpoint = "/v1/me/player";

//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************




/****************************************************************
 * HELPER FUNCTIONS
 ****************************************************************/
void PlaySlider(void){
    if (playstate == 1) {
        if(minute == minutef && second1 == second1f && second2 == second2f) {
            return 0;
        }
            //if(p < (sliderinc * sliderspeed)) {
                fillCircle(p, 50, 2, BLACK);
                drawFastHLine(p - 3, 50, 6, WHITE);
                p += 1;
                fillCircle(p, 50, 2, WHITE);
            //}
            //sliderinc++;
            UtilsDelay(12000000);
                // if x:59 increment x:00
                if(second2 == 9 && second1 == 5) {
                    drawChar(6, 56, minute + '0', BLACK, BLACK, 1);
                    drawChar(18, 56, second1 + '0', BLACK, BLACK, 1);
                    drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
                    minute++;
                    second1 = 0;
                    second2 = 0;
                    drawChar(6, 56, minute + '0', WHITE, BLACK, 1);
                    drawChar(18, 56, second1 + '0', WHITE, BLACK, 1);
                    drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
                                }
                // if 0:x9 increment 0:x0
                else if(second2 == 9 && second1 < 5) {
                    drawChar(18, 56, second1 + '0', BLACK, BLACK, 1);
                    drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
                    second1++;
                    second2 = 0;
                    drawChar(18, 56, second1 + '0', WHITE, BLACK, 1);
                    drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
                }
                else {
                    //increment 0:0x
                    if(second2 < 9) {
                        drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
                        second2++;
                        drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
                    }
                }
        //}
    }
}
void GetSongInfo(char* name, char* singer, int time) {
    //convert ms input into 0:00 format
    songlength = time / 1000;
    //sliderspeed = 128 / songlength;
    minutef = (songlength - (songlength % 60) )/ 60;
    songlength = songlength - (minutef * 60);
    second1f = (songlength - (songlength % 10) )/ 10;
    songlength = songlength - (second1f * 10);
    second2f = songlength;

    songname = name;
    artist = singer;
}
// Use this if we can get the volume state of the player
/*
void GetVolume(int percent) {
    fillCircle(v + 14, 120, 1, BLACK);
    drawFastHLine(14, 120, 100, WHITE);
    v = percent;
    drawFastHLine(14, 120, v, GREEN);
    fillCircle(v + 14, 120, 1, WHITE);
}
*/

void ResetScreen(void) {
    // Song Length
    drawChar(100, 56, minutef + '0', BLACK, BLACK, 1);
    //drawChar(106, 56, ':', BLACK, BLACK, 1);
    drawChar(112, 56, second1f + '0', BLACK, BLACK, 1);
    drawChar(118, 56, second2f + '0', BLACK, BLACK, 1);
    //incremented time reset to 0:00
    drawChar(6, 56, minute + '0', BLACK, BLACK, 1);
    //drawChar(12, 56, ':', BLACK, BLACK, 1);
    drawChar(18, 56, second1 + '0', BLACK, BLACK, 1);
    drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);

    minute = 0;
    second1 = 0;
    second2 = 0;

    drawChar(6, 56, minute + '0', WHITE, BLACK, 1);
    //drawChar(12, 56, ':', BLACK, BLACK, 1);
    drawChar(18, 56, second1 +'0', WHITE, BLACK, 1);
    drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);

    int i = 0;
    for(i = 0; i < strlen(songname); i++){
        drawChar(i*12, 10, songname[i], BLACK, BLACK, 2);
    }
    for(i = 0; i < strlen(artist); i++){
        drawChar(i*6, 30, artist[i], BLACK, BLACK, 1);
    }
}

int count_within(unsigned long count, unsigned long logic_value, unsigned long tolerance){
    if( count < logic_value + tolerance && count > logic_value - tolerance){
        return 1;
    }
    return 0;
}

int translate_code(unsigned int code, unsigned short int tap_count, char *command){
    unsigned int number_pressed = 0;
    unsigned short int cycle_count = 3;
    unsigned int input = 0;

    switch(code){
    case REMOTE_ZERO :
        number_pressed = 0;
        tap_count = 0;
        break;
    case REMOTE_ONE :
        number_pressed = 1;
        break;
    case REMOTE_TWO :
        number_pressed = 2;
        break;
    case REMOTE_THREE :
        number_pressed = 3;
        break;
    case REMOTE_FOUR :
        number_pressed = 4;
        input = 1; //Back
        break;
    case REMOTE_FIVE :
        number_pressed = 5;
        input = 2; //Play
        break;
    case REMOTE_SIX :
        number_pressed = 6;
        input = 3; //Forward
        break;
    case REMOTE_SEVEN :
        number_pressed = 7;
        input = 4; //Volume down
        break;
    case REMOTE_EIGHT :
        number_pressed = 8;
        break;
    case REMOTE_NINE :
        number_pressed = 9;
        input = 5; //Volume Up
        break;
    case REMOTE_LAST : // Enter
        number_pressed = 0;
        tap_count = 2;
        break;
    case REMOTE_MUTE : // DELETE
        number_pressed = 0;
        tap_count = 1;
        break;
    default:
        number_pressed = 2;
        tap_count = 4;
        cycle_count = 4;
        break;
    }
    int temp_index = tap_count % cycle_count;
    temp_index +=  4 * number_pressed;
    *command = input;
    return 0;
}

/*********************************************************
 * HANDLER FUNCTIONS
 *********************************************************/


static void IRIntHandler(void) { // IR Reciever Handler
    unsigned long ulStatus;

    ulStatus = GPIOIntStatus (GPIOA1_BASE, true);
    GPIOIntClear(GPIOA1_BASE, ulStatus);        // clear interrupts on GPIOA1

    g_ulSamples[0] = g_ulSamples[1];
    g_ulSamples[1] = TimerValueGet(TIMERA2_BASE,TIMER_A);

    count = ((g_ulSamples[0] > g_ulSamples[1]) ? g_ulSamples[0] - g_ulSamples[1]:
            (MAX_TIMER_COUNT - (g_ulSamples[1] - g_ulSamples[0])));

    if(interval_count == 0){
        //g_ulSamples[0] = g_ulSamples[1];
        interval_count++;
        return;
    }else if(interval_count == 1){
        if(count_within(count, START_CODE, START_COUNT_TOLERANCE) ){
            TimerEnable(TIMERA1_BASE,TIMER_A);                // enable read timer
            code_word = 0;
        }else{
            return;
        }

    }else if(interval_count < 33){
        if(interval_count == 3){                              // Unique press, disable long press interrupt
            TimerDisable(TIMERA1_BASE, TIMER_A);
            TimerLoadSet(TIMERA1_BASE,TIMER_A,READ_TIMEOUT);  // Reload read timer
        }
        code_word = code_word << 1;                           // New bit is logic 0
        if(count_within(count, CODE_ONE, LOGIC_COUNT_TOLERANCE)){  // New bit is logic 1
            code_word++;
        }
    }
    //g_ulIntervals[interval_count] = ;
    interval_count++;
    if(interval_count < 33){
        return;
    }
    // Packet delivery Complete, Begin Processing
    if(previous_code_word != code_word){                    // First instance of code
        previous_code_word = code_word;
        multitap_count = 0;
        queue_enqueue(data_buffer, code_word, multitap_count);
        TimerDisable(TIMERA0_BASE, TIMER_A);
        TimerLoadSet(TIMERA0_BASE, TIMER_A, MULTITAP_TIMEOUT);  // Refresh Timer
        TimerEnable(TIMERA0_BASE, TIMER_A);
    }else{ /*if(code_word == previous_code_word){ */     // Check for Repeated Press
        multitap_count++;
        //TimerDisable(TIMERA0_BASE, TIMER_A);
        TimerLoadSet(TIMERA0_BASE, TIMER_A, MULTITAP_TIMEOUT);  // Refresh Timer
        //TimerEnable(TIMERA0_BASE, TIMER_A);
        queue_enqueue(data_buffer, code_word, multitap_count);
    }/*else{
        prev_code_word = code_word;
        //multitap_count = 0;
        queue_enqueue(data_buffer, code_word, multitap_count);
        //TimerDisable(TIMERA0_BASE, TIMER_A);                   // DISABLE MULTITAP TIMER
        TimerLoadSet(TIMERA0_BASE, TIMER_A, MULTITAP_TIMEOUT); // reset for next unique char
        //TimerEnable(TIMERA0_BASE, TIMER_A);
    }*/
    interval_count = 1;        // Reset for next code
}

static void ReadTimeoutIntHandler(void){
    unsigned long ulStatus;

    ulStatus = TimerIntStatus (TIMERA1_BASE, false);
    TimerIntClear(TIMERA1_BASE, ulStatus);        // clear interrupts

    interval_count = 1;
    TimerDisable(TIMERA0_BASE, TIMER_A); // DISABLE MULTITAP TIMER
    //TimerLoadSet(TIMERA0_BASE, TIMER_A, MULTITAP_TIMEOUT); // reset for next char
    //TimerLoadSet(TIMERA1_BASE, TIMER_A, READ_TIMEOUT); // reset for next valid char
}

static void PlaySliderHandler(void){
    unsigned long ulStatus;

    ulStatus = TimerIntStatus (TIMERA3_BASE, false);
    TimerIntClear(TIMERA3_BASE, ulStatus);        // clear interrupts

    TimerDisable(TIMERA3_BASE, TIMER_A); // DISABLE play timer
    TimerLoadSet(TIMERA3_BASE, TIMER_A, slider_tick_time);
    TimerEnable(TIMERA3_BASE, TIMER_A);
    if (playstate == 0) {
        return;
    }
    if(p == 123) {
        p = 6;
        newsong = 1;
        return;
    }
    //if(p < (sliderinc * sliderspeed)) {
    fillCircle(p, 50, 2, BLACK);
    drawFastHLine(p - 3, 50, 6, WHITE);
    p += 1;
    fillCircle(p, 50, 2, WHITE);
//}
//sliderinc++;
    // if x:59 increment x:00
    if(second2 == 9 && second1 == 5) {
        drawChar(6, 56, minute + '0', BLACK, BLACK, 1);
        drawChar(18, 56, second1 + '0', BLACK, BLACK, 1);
        drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
        minute++;
        second1 = 0;
        second2 = 0;
        drawChar(6, 56, minute + '0', WHITE, BLACK, 1);
        drawChar(18, 56, second1 + '0', WHITE, BLACK, 1);
        drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
                    }
    // if 0:x9 increment 0:x0
    else if(second2 == 9 && second1 < 5) {
        drawChar(18, 56, second1 + '0', BLACK, BLACK, 1);
        drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
        second1++;
        second2 = 0;
        drawChar(18, 56, second1 + '0', WHITE, BLACK, 1);
        drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
    }
    else {
        //increment 0:0x
        if(second2 < 9) {
            drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
            second2++;
            drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
        }
    }
    //}
}

void UARTIntHandler(void){
    unsigned long ulStatus;
    ulStatus = UARTIntStatus(UARTA1_BASE,true);
    //UARTIntClear(UARTA1_BASE, ulStatus);
    UARTIntClear(UARTA1_BASE, ulStatus);
    if(!UARTCharsAvail(UARTA1_BASE)){
        return;
    }

    if(recieve_index >= RECIEVE_MAX){
        long dump = UARTCharGet(UARTA1_BASE);
        return;
    }
    if(recieve_index == 0){ // Get the Message Length
        recieve_msg_length = (char)UARTCharGet(UARTA1_BASE);
    }
    recieve_buffer[recieve_index] = (char)UARTCharGet(UARTA1_BASE);
    recieve_color_buffer[recieve_index] = (char)UARTCharGet(UARTA1_BASE);
    recieve_index++;
    if(recieve_index == recieve_msg_length){
            message_ready = 1;
    }

}

//*****************************************************************************
//
//! Application     up display on UART
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void
DisplayBanner(char * AppName)
{

    Report("\n\n\n\r");
    Report("\t\t *************************************************\n\r");
    Report("\t\t\t  CC3200 %s Application       \n\r", AppName);
    Report("\t\t *************************************************\n\r");
    Report("\n\n\n\r");
}


void UART_Init(void ){
    UARTConfigSetExpClk(UARTA1_BASE,MAP_PRCMPeripheralClockGet(PRCM_UARTA1),
    UART_BAUD_RATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
    UART_CONFIG_PAR_NONE));

    UARTFIFODisable(UARTA1_BASE);
    UARTFlowControlSet(UARTA1_BASE, UART_FLOWCONTROL_NONE );

    UARTIntRegister(UARTA1_BASE,UARTIntHandler);
    UARTIntEnable(UARTA1_BASE, UART_INT_RX);
}

void Timer_Init(void){
    TimerDisable(TIMERA3_BASE,TIMER_A);
    TimerDisable(TIMERA2_BASE,TIMER_A);
    TimerDisable(TIMERA1_BASE,TIMER_A);
    TimerDisable(TIMERA0_BASE,TIMER_A);
    //
    // Configure the timer
    //
    TimerConfigure(TIMERA3_BASE, TIMER_CFG_A_PERIODIC);
    TimerConfigure(TIMERA2_BASE, TIMER_CFG_A_PERIODIC);
    TimerConfigure(TIMERA1_BASE, TIMER_CFG_A_ONE_SHOT);
    TimerConfigure(TIMERA0_BASE, TIMER_CFG_A_ONE_SHOT);

    //
    // Set the reload value
    //
    TimerLoadSet(TIMERA3_BASE,TIMER_A,0xffffffff);
    TimerLoadSet(TIMERA2_BASE,TIMER_A,0xffffffff);
    TimerLoadSet(TIMERA1_BASE, TIMER_A, READ_TIMEOUT);
    TimerLoadSet(TIMERA0_BASE, TIMER_A, MULTITAP_TIMEOUT);
    //
    // Enable capture event interrupt
    //
    //TimerIntEnable(TIMERA1_BASE,TIMER_);

    //
    // Enable Timer
    //
    TimerEnable(TIMERA2_BASE,TIMER_A);

}
void Interrupt_Init(void){
    unsigned long ulStatus;
    //
    // Register the interrupt handlers
    // For Sample Collection Only
    //GPIOIntRegister(GPIOA1_BASE, CountIRIntHandler);

    // Main Interrupt Handler to collect IR Signal
    GPIOIntRegister(GPIOA1_BASE, IRIntHandler);


    // Stops reading IR signal if Timeout triggered
    TimerIntRegister(TIMERA1_BASE, TIMER_A, ReadTimeoutIntHandler);

    TimerIntRegister(TIMERA3_BASE, TIMER_A, PlaySliderHandler);
    //
    // Configure rising edge interrupts on SW2 and SW3
    //
    GPIOIntTypeSet(GPIOA1_BASE, 0x10, GPIO_FALLING_EDGE);    // SW3

    ulStatus = GPIOIntStatus (GPIOA1_BASE, false);
    GPIOIntClear(GPIOA1_BASE, ulStatus);            // clear interrupts on GPIOA1

    ulStatus = TimerIntStatus(TIMERA3_BASE, false);
    TimerIntClear(TIMERA3_BASE, ulStatus);

    ulStatus = TimerIntStatus(TIMERA1_BASE, false);
    TimerIntClear(TIMERA1_BASE, ulStatus);

    ulStatus = TimerIntStatus(TIMERA0_BASE, false);
    TimerIntClear(TIMERA0_BASE, ulStatus);
    // clear global variables
    TIMER_intflag = 0;
    TIMER_intcount = 0;


    GPIOIntEnable(GPIOA1_BASE, 0x10);
    TimerIntEnable(TIMERA3_BASE,TIMER_TIMA_TIMEOUT);
    TimerIntEnable(TIMERA1_BASE,TIMER_TIMA_TIMEOUT);
    TimerIntEnable(TIMERA0_BASE,TIMER_TIMA_TIMEOUT);
}








//****************************************************************************
//                      LOCAL FUNCTION PROTOTYPES
//****************************************************************************
static long WlanConnect();


//*****************************************************************************
// SimpleLink Asynchronous Event Handlers -- Start
//*****************************************************************************


//*****************************************************************************
//
//! \brief The Function Handles WLAN Events
//!
//! \param[in]  pWlanEvent - Pointer to WLAN Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent)
{
    switch(pWlanEvent->Event)
    {
        case SL_WLAN_CONNECT_EVENT:
        {
            SET_STATUS_BIT(g_ulStatus, STATUS_BIT_CONNECTION);

            //
            // Information about the connected AP (like name, MAC etc) will be
            // available in 'slWlanConnectAsyncResponse_t'-Applications
            // can use it if required
            //
            //  slWlanConnectAsyncResponse_t *pEventData = NULL;
            // pEventData = &pWlanEvent->EventData.STAandP2PModeWlanConnected;
            //

            // Copy new connection SSID and BSSID to global parameters
            memcpy(g_ucConnectionSSID,pWlanEvent->EventData.
                   STAandP2PModeWlanConnected.ssid_name,
                   pWlanEvent->EventData.STAandP2PModeWlanConnected.ssid_len);
            memcpy(g_ucConnectionBSSID,
                   pWlanEvent->EventData.STAandP2PModeWlanConnected.bssid,
                   SL_BSSID_LENGTH);

            UART_PRINT("[WLAN EVENT] STA Connected to the AP: %s ,"
                            " BSSID: %x:%x:%x:%x:%x:%x\n\r",
                      g_ucConnectionSSID,g_ucConnectionBSSID[0],
                      g_ucConnectionBSSID[1],g_ucConnectionBSSID[2],
                      g_ucConnectionBSSID[3],g_ucConnectionBSSID[4],
                      g_ucConnectionBSSID[5]);
        }
        break;

        case SL_WLAN_DISCONNECT_EVENT:
        {
            slWlanConnectAsyncResponse_t*  pEventData = NULL;

            CLR_STATUS_BIT(g_ulStatus, STATUS_BIT_CONNECTION);
            CLR_STATUS_BIT(g_ulStatus, STATUS_BIT_IP_AQUIRED);

            pEventData = &pWlanEvent->EventData.STAandP2PModeDisconnected;

            // If the user has initiated 'Disconnect' request,
            //'reason_code' is SL_WLAN_DISCONNECT_USER_INITIATED_DISCONNECTION
            if(SL_WLAN_DISCONNECT_USER_INITIATED_DISCONNECTION == pEventData->reason_code)
            {
                UART_PRINT("[WLAN EVENT]Device disconnected from the AP: %s,"
                "BSSID: %x:%x:%x:%x:%x:%x on application's request \n\r",
                           g_ucConnectionSSID,g_ucConnectionBSSID[0],
                           g_ucConnectionBSSID[1],g_ucConnectionBSSID[2],
                           g_ucConnectionBSSID[3],g_ucConnectionBSSID[4],
                           g_ucConnectionBSSID[5]);
            }
            else
            {
                UART_PRINT("[WLAN ERROR]Device disconnected from the AP AP: %s,"
                "BSSID: %x:%x:%x:%x:%x:%x on an ERROR..!! \n\r",
                           g_ucConnectionSSID,g_ucConnectionBSSID[0],
                           g_ucConnectionBSSID[1],g_ucConnectionBSSID[2],
                           g_ucConnectionBSSID[3],g_ucConnectionBSSID[4],
                           g_ucConnectionBSSID[5]);
            }
            memset(g_ucConnectionSSID,0,sizeof(g_ucConnectionSSID));
            memset(g_ucConnectionBSSID,0,sizeof(g_ucConnectionBSSID));
        }
        break;

        default:
        {
            UART_PRINT("[WLAN EVENT] Unexpected event [0x%x]\n\r",
                       pWlanEvent->Event);
        }
        break;
    }
}

//*****************************************************************************
//
//! \brief This function handles network events such as IP acquisition, IP
//!           leased, IP released etc.
//!
//! \param[in]  pNetAppEvent - Pointer to NetApp Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent)
{
    switch(pNetAppEvent->Event)
    {
        case SL_NETAPP_IPV4_IPACQUIRED_EVENT:
        {
            SlIpV4AcquiredAsync_t *pEventData = NULL;

            SET_STATUS_BIT(g_ulStatus, STATUS_BIT_IP_AQUIRED);

            //Ip Acquired Event Data
            pEventData = &pNetAppEvent->EventData.ipAcquiredV4;

            //Gateway IP address
            g_ulGatewayIP = pEventData->gateway;

            UART_PRINT("[NETAPP EVENT] IP Acquired: IP=%d.%d.%d.%d , "
            "Gateway=%d.%d.%d.%d\n\r",
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,3),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,2),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,1),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.ip,0),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,3),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,2),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,1),
            SL_IPV4_BYTE(pNetAppEvent->EventData.ipAcquiredV4.gateway,0));
        }
        break;

        default:
        {
            UART_PRINT("[NETAPP EVENT] Unexpected event [0x%x] \n\r",
                       pNetAppEvent->Event);
        }
        break;
    }
}


//*****************************************************************************
//
//! \brief This function handles HTTP server events
//!
//! \param[in]  pServerEvent - Contains the relevant event information
//! \param[in]    pServerResponse - Should be filled by the user with the
//!                                      relevant response information
//!
//! \return None
//!
//****************************************************************************
void SimpleLinkHttpServerCallback(SlHttpServerEvent_t *pHttpEvent,
                                  SlHttpServerResponse_t *pHttpResponse)
{
    // Unused in this application
}

//*****************************************************************************
//
//! \brief This function handles General Events
//!
//! \param[in]     pDevEvent - Pointer to General Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *pDevEvent)
{
    //
    // Most of the general errors are not FATAL are are to be handled
    // appropriately by the application
    //
    UART_PRINT("[GENERAL EVENT] - ID=[%d] Sender=[%d]\n\n",
               pDevEvent->EventData.deviceEvent.status,
               pDevEvent->EventData.deviceEvent.sender);
}


//*****************************************************************************
//
//! This function handles socket events indication
//!
//! \param[in]      pSock - Pointer to Socket Event Info
//!
//! \return None
//!
//*****************************************************************************
void SimpleLinkSockEventHandler(SlSockEvent_t *pSock)
{
    //
    // This application doesn't work w/ socket - Events are not expected
    //
       switch( pSock->Event )
    {
        case SL_SOCKET_TX_FAILED_EVENT:
            switch( pSock->socketAsyncEvent.SockTxFailData.status )
            {
                case SL_ECLOSE:
                    UART_PRINT("[SOCK ERROR] - close socket (%d) operation "
                    "failed to transmit all queued packets\n\n",
                           pSock->socketAsyncEvent.SockAsyncData.sd);
                    break;
                default:
                    UART_PRINT("[SOCK ERROR] - TX FAILED : socket %d , reason"
                        "(%d) \n\n",
                        pSock->socketAsyncEvent.SockAsyncData.sd,
                        pSock->socketAsyncEvent.SockTxFailData.status);
            }
            break;

        default:
            UART_PRINT("[SOCK EVENT] - Unexpected Event [%x0x]\n\n",pSock->Event);
    }
}


//*****************************************************************************
// SimpleLink Asynchronous Event Handlers -- End
//*****************************************************************************



//*****************************************************************************
//
//! \brief This function initializes the application variables
//!
//! \param    None
//!
//! \return None
//!
//*****************************************************************************
static void InitializeAppVariables()
{
    g_ulStatus = 0;
    g_ulGatewayIP = 0;
    g_Host = SERVER_NAME;
    memset(g_ucConnectionSSID,0,sizeof(g_ucConnectionSSID));
    memset(g_ucConnectionBSSID,0,sizeof(g_ucConnectionBSSID));
}


//*****************************************************************************
//! \brief This function puts the device in its default state. It:
//!           - Set the mode to STATION
//!           - Configures connection policy to Auto and AutoSmartConfig
//!           - Deletes all the stored profiles
//!           - Enables DHCP
//!           - Disables Scan policy
//!           - Sets Tx power to maximum
//!           - Sets power policy to normal
//!           - Unregister mDNS services
//!           - Remove all filters
//!
//! \param   none
//! \return  On success, zero is returned. On error, negative is returned
//*****************************************************************************
static long ConfigureSimpleLinkToDefaultState()
{
    SlVersionFull   ver = {0};
    _WlanRxFilterOperationCommandBuff_t  RxFilterIdMask = {0};

    unsigned char ucVal = 1;
    unsigned char ucConfigOpt = 0;
    unsigned char ucConfigLen = 0;
    unsigned char ucPower = 0;

    long lRetVal = -1;
    long lMode = -1;

    lMode = sl_Start(0, 0, 0);
    ASSERT_ON_ERROR(lMode);

    // If the device is not in station-mode, try configuring it in station-mode
    if (ROLE_STA != lMode)
    {
        if (ROLE_AP == lMode)
        {
            // If the device is in AP mode, we need to wait for this event
            // before doing anything
            while(!IS_IP_ACQUIRED(g_ulStatus))
            {
#ifndef SL_PLATFORM_MULTI_THREADED
              _SlNonOsMainLoopTask();
#endif
            }
        }

        // Switch to STA role and restart
        lRetVal = sl_WlanSetMode(ROLE_STA);
        ASSERT_ON_ERROR(lRetVal);

        lRetVal = sl_Stop(0xFF);
        ASSERT_ON_ERROR(lRetVal);

        lRetVal = sl_Start(0, 0, 0);
        ASSERT_ON_ERROR(lRetVal);

        // Check if the device is in station again
        if (ROLE_STA != lRetVal)
        {
            // We don't want to proceed if the device is not coming up in STA-mode
            return DEVICE_NOT_IN_STATION_MODE;
        }
    }

    // Get the device's version-information
    ucConfigOpt = SL_DEVICE_GENERAL_VERSION;
    ucConfigLen = sizeof(ver);
    lRetVal = sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION, &ucConfigOpt,
                                &ucConfigLen, (unsigned char *)(&ver));
    ASSERT_ON_ERROR(lRetVal);

    UART_PRINT("Host Driver Version: %s\n\r",SL_DRIVER_VERSION);
    UART_PRINT("Build Version %d.%d.%d.%d.31.%d.%d.%d.%d.%d.%d.%d.%d\n\r",
    ver.NwpVersion[0],ver.NwpVersion[1],ver.NwpVersion[2],ver.NwpVersion[3],
    ver.ChipFwAndPhyVersion.FwVersion[0],ver.ChipFwAndPhyVersion.FwVersion[1],
    ver.ChipFwAndPhyVersion.FwVersion[2],ver.ChipFwAndPhyVersion.FwVersion[3],
    ver.ChipFwAndPhyVersion.PhyVersion[0],ver.ChipFwAndPhyVersion.PhyVersion[1],
    ver.ChipFwAndPhyVersion.PhyVersion[2],ver.ChipFwAndPhyVersion.PhyVersion[3]);

    // Set connection policy to Auto + SmartConfig
    //      (Device's default connection policy)
    lRetVal = sl_WlanPolicySet(SL_POLICY_CONNECTION,
                                SL_CONNECTION_POLICY(1, 0, 0, 0, 1), NULL, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Remove all profiles
    lRetVal = sl_WlanProfileDel(0xFF);
    ASSERT_ON_ERROR(lRetVal);

    //
    // Device in station-mode. Disconnect previous connection if any
    // The function returns 0 if 'Disconnected done', negative number if already
    // disconnected Wait for 'disconnection' event if 0 is returned, Ignore
    // other return-codes
    //
    lRetVal = sl_WlanDisconnect();
    if(0 == lRetVal)
    {
        // Wait
        while(IS_CONNECTED(g_ulStatus))
        {
#ifndef SL_PLATFORM_MULTI_THREADED
              _SlNonOsMainLoopTask();
#endif
        }
    }

    // Enable DHCP client
    lRetVal = sl_NetCfgSet(SL_IPV4_STA_P2P_CL_DHCP_ENABLE,1,1,&ucVal);
    ASSERT_ON_ERROR(lRetVal);

    // Disable scan
    ucConfigOpt = SL_SCAN_POLICY(0);
    lRetVal = sl_WlanPolicySet(SL_POLICY_SCAN , ucConfigOpt, NULL, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Set Tx power level for station mode
    // Number between 0-15, as dB offset from max power - 0 will set max power
    ucPower = 0;
    lRetVal = sl_WlanSet(SL_WLAN_CFG_GENERAL_PARAM_ID,
            WLAN_GENERAL_PARAM_OPT_STA_TX_POWER, 1, (unsigned char *)&ucPower);
    ASSERT_ON_ERROR(lRetVal);

    // Set PM policy to normal
    lRetVal = sl_WlanPolicySet(SL_POLICY_PM , SL_NORMAL_POLICY, NULL, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Unregister mDNS services
    lRetVal = sl_NetAppMDNSUnRegisterService(0, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Remove  all 64 filters (8*8)
    memset(RxFilterIdMask.FilterIdMask, 0xFF, 8);
    lRetVal = sl_WlanRxFilterSet(SL_REMOVE_RX_FILTER, (_u8 *)&RxFilterIdMask,
                       sizeof(_WlanRxFilterOperationCommandBuff_t));
    ASSERT_ON_ERROR(lRetVal);


    lRetVal = sl_Stop(SL_STOP_TIMEOUT);
    ASSERT_ON_ERROR(lRetVal);

    InitializeAppVariables();

    return SUCCESS;
}



//****************************************************************************
//
//! \brief Connecting to a WLAN Accesspoint
//!
//!  This function connects to the required AP (SSID_NAME) with Security
//!  parameters specified in te form of macros at the top of this file
//!
//! \param  Status value
//!
//! \return  None
//!
//! \warning    If the WLAN connection fails or we don't aquire an IP
//!            address, It will be stuck in this function forever.
//
//****************************************************************************
static long WlanConnect()
{
    SlSecParams_t secParams = {0};
    long lRetVal = 0;

    secParams.Key = (signed char *)SECURITY_KEY;
    secParams.KeyLen = strlen(SECURITY_KEY);
    secParams.Type = SECURITY_TYPE;

    lRetVal = sl_WlanConnect((signed char *)SSID_NAME,
                           strlen((const char *)SSID_NAME), 0, &secParams, 0);
    ASSERT_ON_ERROR(lRetVal);

    // Wait for WLAN Event
    while((!IS_CONNECTED(g_ulStatus)) || (!IS_IP_ACQUIRED(g_ulStatus)))
    {
        // wait till connects to an AP
        _SlNonOsMainLoopTask();
    }

    return SUCCESS;

}

long printErrConvenience(char * msg, long retVal) {
    UART_PRINT(msg);
    GPIO_IF_LedOn(MCU_RED_LED_GPIO);
    return retVal;
}


//*****************************************************************************
//
//! \brief Flush response body.
//!
//! \param[in]  httpClient - Pointer to HTTP Client instance
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int FlushHTTPResponse(HTTPCli_Handle httpClient)
{
    const char *ids[2] = {
                            HTTPCli_FIELD_NAME_CONNECTION, /* App will get connection header value. all others will skip by lib */
                            NULL
                         };
    char buf[128];
    int id;
    int len = 1;
    bool moreFlag = 0;
    char ** prevRespFilelds = NULL;


    /* Store previosly store array if any */
    prevRespFilelds = HTTPCli_setResponseFields(httpClient, ids);

    /* Read response headers */
    while ((id = HTTPCli_getResponseField(httpClient, buf, sizeof(buf), &moreFlag))
            != HTTPCli_FIELD_ID_END)
    {

        if(id == 0)
        {
            if(!strncmp(buf, "close", sizeof("close")))
            {
                UART_PRINT("Connection terminated by server\n\r");
            }
        }

    }

    /* Restore previosuly store array if any */
    HTTPCli_setResponseFields(httpClient, (const char **)prevRespFilelds);

    while(1)
    {
        /* Read response data/body */
        /* Note:
                moreFlag will be set to 1 by HTTPCli_readResponseBody() call, if more
                data is available Or in other words content length > length of buffer.
                The remaining data will be read in subsequent call to HTTPCli_readResponseBody().
                Please refer HTTP Client Libary API documenation @ref HTTPCli_readResponseBody
                for more information.
        */
        HTTPCli_readResponseBody(httpClient, buf, sizeof(buf) - 1, &moreFlag);
        ASSERT_ON_ERROR(len);

        if ((len - 2) >= 0 && buf[len - 2] == '\r' && buf [len - 1] == '\n'){
            break;
        }

        if(!moreFlag)
        {
            /* There no more data. break the loop. */
            break;
        }
    }
    return 0;
}
//*****************************************************************************
//
//! This function updates the date and time of CC3200.
//!
//! \param None
//!
//! \return
//!     0 for success, negative otherwise
//!
//*****************************************************************************

static int set_time() {
    long retVal;

    g_time.tm_day = DATE;
    g_time.tm_mon = MONTH;
    g_time.tm_year = YEAR;
    g_time.tm_sec = HOUR;
    g_time.tm_hour = MINUTE;
    g_time.tm_min = SECOND;

    retVal = sl_DevSet(SL_DEVICE_GENERAL_CONFIGURATION,
                          SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME,
                          sizeof(SlDateTime),(unsigned char *)(&g_time));

    ASSERT_ON_ERROR(retVal);
    return SUCCESS;
}

static int tls_connect() {
    SlSockAddrIn_t    Addr;
    int    iAddrSize;
    unsigned char    ucMethod = SL_SO_SEC_METHOD_TLSV1_2;
    unsigned int uiIP;
//    unsigned int uiCipher = SL_SEC_MASK_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA;
    unsigned int uiCipher = SL_SEC_MASK_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256;
// SL_SEC_MASK_SSL_RSA_WITH_RC4_128_SHA
// SL_SEC_MASK_SSL_RSA_WITH_RC4_128_MD5
// SL_SEC_MASK_TLS_RSA_WITH_AES_256_CBC_SHA
// SL_SEC_MASK_TLS_DHE_RSA_WITH_AES_256_CBC_SHA
// SL_SEC_MASK_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA
// SL_SEC_MASK_TLS_ECDHE_RSA_WITH_RC4_128_SHA
// SL_SEC_MASK_TLS_RSA_WITH_AES_128_CBC_SHA256
// SL_SEC_MASK_TLS_RSA_WITH_AES_256_CBC_SHA256
// SL_SEC_MASK_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256
// SL_SEC_MASK_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 // does not work (-340, handshake fails)
    long lRetVal = -1;
    int iSockID;

    lRetVal = sl_NetAppDnsGetHostByName(g_Host, strlen((const char *)g_Host),
                                    (unsigned long*)&uiIP, SL_AF_INET);

    if(lRetVal < 0) {
        return printErrConvenience("Device couldn't retrieve the host name \n\r", lRetVal);
    }

    Addr.sin_family = SL_AF_INET;
    Addr.sin_port = sl_Htons(HOST_PORT);
    Addr.sin_addr.s_addr = sl_Htonl(uiIP);
    iAddrSize = sizeof(SlSockAddrIn_t);
    //
    // opens a secure socket
    //
    iSockID = sl_Socket(SL_AF_INET,SL_SOCK_STREAM, SL_SEC_SOCKET);
    if( iSockID < 0 ) {
        return printErrConvenience("Device unable to create secure socket \n\r", lRetVal);
    }

    //
    // configure the socket as TLS1.2
    //
    lRetVal = sl_SetSockOpt(iSockID, SL_SOL_SOCKET, SL_SO_SECMETHOD, &ucMethod,\
                               sizeof(ucMethod));
    if(lRetVal < 0) {
        return printErrConvenience("Device couldn't set socket options \n\r", lRetVal);
    }
    //
    //configure the socket as ECDHE RSA WITH AES256 CBC SHA
    //
    lRetVal = sl_SetSockOpt(iSockID, SL_SOL_SOCKET, SL_SO_SECURE_MASK, &uiCipher,\
                           sizeof(uiCipher));
    if(lRetVal < 0) {
        return printErrConvenience("Device couldn't set socket options \n\r", lRetVal);
    }



/////////////////////////////////
// START: COMMENT THIS OUT IF DISABLING SERVER VERIFICATION
    //
    //configure the socket with CA certificate - for server verification
    //
    lRetVal = sl_SetSockOpt(iSockID, SL_SOL_SOCKET, \
                           SL_SO_SECURE_FILES_CA_FILE_NAME, \
                           SL_SSL_CA_CERT, \
                           strlen(SL_SSL_CA_CERT));

    if(lRetVal < 0) {
        return printErrConvenience("Device couldn't set socket options \n\r", lRetVal);
    }
// END: COMMENT THIS OUT IF DISABLING SERVER VERIFICATION
/////////////////////////////////


    //configure the socket with Client Certificate - for server verification
    //
    lRetVal = sl_SetSockOpt(iSockID, SL_SOL_SOCKET, \
                SL_SO_SECURE_FILES_CERTIFICATE_FILE_NAME, \
                                    SL_SSL_CLIENT, \
                           strlen(SL_SSL_CLIENT));

    if(lRetVal < 0) {
        return printErrConvenience("Device couldn't set socket options \n\r", lRetVal);
    }

    //configure the socket with Private Key - for server verification
    //
    lRetVal = sl_SetSockOpt(iSockID, SL_SOL_SOCKET, \
            SL_SO_SECURE_FILES_PRIVATE_KEY_FILE_NAME, \
            SL_SSL_PRIVATE, \
                           strlen(SL_SSL_PRIVATE));

    if(lRetVal < 0) {
        return printErrConvenience("Device couldn't set socket options \n\r", lRetVal);
    }


    /* connect to the peer device - Google server */
    lRetVal = sl_Connect(iSockID, ( SlSockAddr_t *)&Addr, iAddrSize);

    if(lRetVal >= 0) {
        UART_PRINT("Device has connected to the website:");
        UART_PRINT(SERVER_NAME);
        UART_PRINT("\n\r");
    }
    else if(lRetVal == SL_ESECSNOVERIFY) {
        UART_PRINT("Device has connected to the website (UNVERIFIED):");
        UART_PRINT(SERVER_NAME);
        UART_PRINT("\n\r");
    }
    else if(lRetVal < 0) {
        UART_PRINT("Device couldn't connect to server:");
        UART_PRINT(SERVER_NAME);
        UART_PRINT("\n\r");
        return printErrConvenience("Device couldn't connect to server \n\r", lRetVal);
    }

    GPIO_IF_LedOff(MCU_RED_LED_GPIO);
    GPIO_IF_LedOn(MCU_GREEN_LED_GPIO);
    return iSockID;
}

//*****************************************************************************
//g
//! \brief Handler for parsing JSON data
//!
//! \param[in]  ptr - Pointer to http response body data
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
int ParseJSONData(char *ptr)
{
    long lRetVal = 0;
    int noOfToken;
    jsmn_parser parser;
    jsmntok_t   *tokenList;


    /* Initialize JSON PArser */
    jsmn_init(&parser);

    /* Get number of JSON token in stream as we we dont know how many tokens need to pass */
    noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), NULL, 10);
    if(noOfToken <= 0)
    {
        UART_PRINT("Failed to initialize JSON parser\n\r");
        return -1;

    }

    /* Allocate memory to store token */
    tokenList = (jsmntok_t *) malloc(noOfToken*sizeof(jsmntok_t));
    if(tokenList == NULL)
    {
        UART_PRINT("Failed to allocate memory\n\r");
        return -1;
    }

    /* Initialize JSON Parser again */
    jsmn_init(&parser);
    noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), tokenList, noOfToken);
    if(noOfToken < 0)
    {
        UART_PRINT("Failed to parse JSON tokens\n\r");
        lRetVal = noOfToken;
    }
    else
    {
        UART_PRINT("Successfully parsed %ld JSON tokens\n\r", noOfToken);
    }

    free(tokenList);

    return lRetVal;
}

/*!
    \brief This function read respose from server and dump on console

    \param[in]      httpClient - HTTP Client object

    \return         0 on success else -ve

    \note

    \warning
*/
static int readResponse(HTTPCli_Handle httpClient)
{
    long lRetVal = 0;
    int bytesRead = 0;
    int id = 0;
    unsigned long len = 0;
    int json = 0;
    char *dataBuffer=NULL;
    bool moreFlags = 1;
    const char *ids[4] = {
                            HTTPCli_FIELD_NAME_CONTENT_LENGTH,
                            HTTPCli_FIELD_NAME_CONNECTION,
                            HTTPCli_FIELD_NAME_CONTENT_TYPE,
                            NULL
                         };

    /* Read HTTP POST request status code */
    lRetVal = HTTPCli_getResponseStatus(httpClient);
    UART_PRINT("\r\nHTTP CODE: %i\r\n" , (int)lRetVal);
    if(lRetVal > 0)
    {
        switch(lRetVal)
        {
        case 200:
        {
            UART_PRINT("HTTP Status 200\n\r");
            /*
                 Set response header fields to filter response headers. All
                  other than set by this call we be skipped by library.
             */
            HTTPCli_setResponseFields(httpClient, (const char **)ids);

            /* Read filter response header and take appropriate action. */
            /* Note:
                    1. id will be same as index of fileds in filter array setted
                    in previous HTTPCli_setResponseFields() call.

                    2. moreFlags will be set to 1 by HTTPCli_getResponseField(), if  field
                    value could not be completely read. A subsequent call to
                    HTTPCli_getResponseField() will read remaining field value and will
                    return HTTPCli_FIELD_ID_DUMMY. Please refer HTTP Client Libary API
                    documenation @ref HTTPCli_getResponseField for more information.
             */
            while((id = HTTPCli_getResponseField(httpClient, (char *)g_buff, sizeof(g_buff), &moreFlags))
                    != HTTPCli_FIELD_ID_END)
            {

                switch(id)
                {
                case 0: /* HTTPCli_FIELD_NAME_CONTENT_LENGTH */
                {
                    len = strtoul((char *)g_buff, NULL, 0);
                }
                break;
                case 1: /* HTTPCli_FIELD_NAME_CONNECTION */
                {
                }
                break;
                case 2: /* HTTPCli_FIELD_NAME_CONTENT_TYPE */
                {
                    if(!strncmp((const char *)g_buff, "application/json",
                            sizeof("application/json")))
                    {
                        json = 1;
                    }
                    else
                    {
                        /* Note:
                                Developers are advised to use appropriate
                                content handler. In this example all content
                                type other than json are treated as plain text.
                         */
                        json = 0;
                    }
                    UART_PRINT(HTTPCli_FIELD_NAME_CONTENT_TYPE);
                    UART_PRINT(" : ");
                    UART_PRINT("application/json\n\r");
                }
                break;
                default:
                {
                    UART_PRINT("Wrong filter id\n\r");
                    lRetVal = -1;
                    goto end;
                }
                }
            }
            bytesRead = 0;
            /*
            if(len > sizeof(g_buff))
            {
                dataBuffer = (char *) malloc(len);
                if(dataBuffer)
                {
                    UART_PRINT("Failed to allocate memory\n\r");
                    lRetVal = -1;
                    goto end;
                }
            }
            else
            {
                dataBuffer = (char *)g_buff;
            }
            */
            dataBuffer = (char *)g_buff;
            /* Read response data/body */
            /* Note:
                    moreFlag will be set to 1 by HTTPCli_readResponseBody() call, if more
                    data is available Or in other words content length > length of buffer.
                    The remaining data will be read in subsequent call to HTTPCli_readResponseBody().
                    Please refer HTTP Client Libary API documenation @ref HTTPCli_readResponseBody
                    for more information

             */

            /** heavily modify this section to allow for searching the buffer while its still collecting
             *
             */

            memset(dataBuffer, 0, MAX_BUFF_SIZE + 1);

            char* start = dataBuffer;
            char * end= dataBuffer;

            int bytesWritten = 0;
            char* datacursor = dataBuffer;
            int cur_bytes = 0;
            cur_bytes = HTTPCli_readResponseBody(httpClient, (char *)dataBuffer, MAX_BUFF_SIZE, &moreFlags);
            start = strstr((const char*)dataBuffer, "\"progress_ms\"");
            if(start != NULL){
                end = strchr((const char*) start, ',');

                strncpy(progress_time, start + 16, end - start - 15 );
                progress_time[end - start - 15] = '\0';

                int_progress_time = atol(progress_time);
                UART_PRINT("Progress Time Found: %s Integer:  %i \r\n", progress_time,int_progress_time);
            }
            start = strstr((const char*)end, "\"name\"");
            if(start != NULL){
                end = strstr((const char*) start, ",");
                strncpy(artist_name, start + 10, end - start - 10 );
                artist_name[end - start - 11] = '\0';
                UART_PRINT("Artist Name Found: %s \r\n ", artist_name);
            }

            start = strstr((const char*)end, "\"name\"");
            if(start != NULL){
                end = strstr((const char*) start, ",");
                strncpy(song_name, start + 10, end - start - 10 );
                song_name[end - start - 11] = '\0';
                UART_PRINT("Song Name Found: %s \r\n ", song_name);
            }

            while(moreFlags != 0 ){
                end = NULL;
                memset((char *)dataBuffer, 0, MAX_BUFF_SIZE);
                cur_bytes = HTTPCli_readResponseBody(httpClient, (char *)dataBuffer, MAX_BUFF_SIZE, &moreFlags);
                start = strstr((const char*)dataBuffer, "\"duration_ms\"");
                if(start != NULL){
                    end = strstr((const char*) start, ",");
                    strncpy(duration, start + 16, end - start - 16 );
                    duration[end - start - 16] = '\0';
                    int_duration_time = atol(duration);
                    UART_PRINT("Duration Time Found: %s,Integer: %i \r\n", duration,int_duration_time);
                }
                start = strstr((const char*)end, "\"name\"");
                if(start != NULL){
                    end = strstr((const char*) start, ",");
                    strncpy(song_name, start + 10, end - start - 10 );
                    song_name[end - start - 11] = '\0';
                    UART_PRINT("Song Name Found: %s \r\n ", song_name);
                    if(moreFlags){
                        FlushHTTPResponse(httpClient);
                    }

                    break;
                }
            }


            /*
            start = strstr((const char*)end, "duration_ms");
            if(start != NULL){
                end = strstr((const char*) start, ",");
                strncpy(duration, start + 14, end - start - 14 );
                UART_PRINT("Duration Found: %s \r\n ", duration);
            }*/

            /*
            while(moreFlags != 0 ){
                UART_PRINT("%s\r\n", dataBuffer);
                cur_bytes = HTTPCli_readResponseBody(httpClient, (char *)dataBuffer, MAX_BUFF_SIZE, &moreFlags);
                if(cur_bytes < 0)
                {
                    UART_PRINT("Failed to received response body\n\r");
                    lRetVal = cur_bytes;
                    goto end;
                }


                start = strstr((const char*)end, "artists");
                if(start != NULL){
                    start = strstr((const char*)start, "name");
                    end = strstr((const char*) start, ",");
                    strncpy(artist_name, start + 9, end - start );

                    UART_PRINT("Artist Name Found: %s \r\n ", artist_name);
                }

                start = strstr((const char*)end, "duration_ms");
                if(start != NULL){
                    end = strstr((const char*) start, ",");
                    strncpy(duration, start + 14, end - start - 14 );
                    UART_PRINT("Duration Found: %s \r\n ", duration);
                }
                //dataBuffer[cur_bytes - 1] = '\0';
                UART_PRINT("%s", dataBuffer);
                bytesRead+=cur_bytes;
            }
            */
            //UART_PRINT("%s\r\n", dataBuffer);
            /*
            if(moreFlags){
                FlushHTTPResponse(httpClient);
            }*/


            /****
            if(bytesRead < 0)
            {
                UART_PRINT("Failed to received response body\n\r");
                lRetVal = bytesRead;
                goto end;
            }
            else if( bytesRead < len || moreFlags)
            {
                UART_PRINT("Mismatch in content length and received data length\n\r");
                goto end;
            }
            dataBuffer[bytesRead] = '\0';

            if(json)
            {
                /* Parse JSON data *//*
                lRetVal = ParseJSONData(dataBuffer);
                if(lRetVal < 0)
                {
                    goto end;
                }
            }
            else
            {
                /* treating data as a plain text *//*
            }
            ****/

        }
        break;

        case 204:
            UART_PRINT("COMMAND SENT\r\n");
            FlushHTTPResponse(httpClient);
            break;
        case 400:
            UART_PRINT("BAD REQUEST. REQUEST NOT UNDERSTOOD\r\n");
            FlushHTTPResponse(httpClient);
            break;
        case 401:
            UART_PRINT("REQUEST FAILED. NEED NEW AUTHORIZATION TOKEN\r\n");
            FlushHTTPResponse(httpClient);
            break;
        case 429:
            UART_PRINT("REQUEST FAILED. RATE LIMIT\r\n");
            FlushHTTPResponse(httpClient);
            break;
        case 404:
            UART_PRINT("File not found. \r\n");
            FlushHTTPResponse(httpClient);
            /* Handle response body as per requirement.
                  Note:
                    Developers are advised to take appopriate action for HTTP
                    return status code else flush the response body.
                    In this example we are flushing response body in default
                    case for all other than 200 HTTP Status code.
             */
        default:
            /* Note:
              Need to flush received buffer explicitly as library will not do
              for next request.Apllication is responsible for reading all the
              data.
             */
            //FlushHTTPResponse(httpClient);
            UART_PRINT("UNDEFINED HTTP STATUS CODE: %i \r\n" , lRetVal);
            FlushHTTPResponse(httpClient);
            break;
        }
    }
    else
    {
        UART_PRINT("Failed to receive data from server.\r\n");
        FlushHTTPResponse(httpClient);
        goto end;
    }

    lRetVal = 0;

end:
    if(len > sizeof(g_buff) && (dataBuffer != NULL))
    {
        free(dataBuffer);
    }
    return lRetVal;
}

//*****************************************************************************
//
//! \brief HTTP POST Demonstration
//!
//! \param[in]  httpClient - Pointer to http client
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int HTTPPostMethod(HTTPCli_Handle httpClient, const char* request_uri)
{
    bool moreFlags = 1;
    bool lastFlag = 1;
    char tmpBuf[4];
    long lRetVal = 0;
    char authorization[256] = "Bearer ";

    memcpy(&authorization[7], &authorization_token[0], strlen(authorization_token));
    const char* authorize = &authorization[0];
    HTTPCli_Field fields[5] = {
                               {HTTPCli_FIELD_NAME_CONTENT_TYPE, "application/json"},
                               {HTTPCli_FIELD_NAME_AUTHORIZATION, authorize},
                               {HTTPCli_FIELD_NAME_HOST, HOST_NAME},
                               {HTTPCli_FIELD_NAME_CONTENT_LENGTH, "0"},
                               {NULL, NULL}
                                };


    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send POST method request. */
    /* Here we are setting moreFlags = 1 as there are some more header fields need to send
       other than setted in previous call HTTPCli_setRequestFields() at later stage.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
    */
    moreFlags = 0;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPCli_METHOD_POST, request_uri, moreFlags);
    if(lRetVal < 0)
    {
        UART_PRINT("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }

    //sprintf((char *)tmpBuf, "%d", (sizeof(POST_DATA)-1));

    /* Here we are setting lastFlag = 1 as it is last header field.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
    */
    /*
    lastFlag = 1;
    lRetVal = HTTPCli_sendField(httpClient, HTTPCli_FIELD_NAME_CONTENT_LENGTH, (const char *)tmpBuf, lastFlag);
    if(lRetVal < 0)
    {
        UART_PRINT("Failed to send HTTP POST request header.\n\r");
        return lRetVal;
    }
    */

    /* Send POST data/body */
    /*
    lRetVal = HTTPCli_sendRequestBody(httpClient, POST_DATA, (sizeof(POST_DATA)-1));
    if(lRetVal < 0)
    {
        UART_PRINT("Failed to send HTTP POST request body.\n\r");
        return lRetVal;
    }
    */
    lRetVal = readResponse(httpClient);

    return lRetVal;
}


//*****************************************************************************
//
//! \brief HTTP PUT Demonstration
//!
//! \param[in]  httpClient - Pointer to http client
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int HTTPPutMethod(HTTPCli_Handle httpClient, const char* request_uri)
{
    char authorization[256] = "Bearer ";
    memcpy(&authorization[7], &authorization_token[0], strlen(authorization_token));
    const char* authorize = &authorization[0];
    long lRetVal = 0;
    HTTPCli_Field fields[5] = {
                               {HTTPCli_FIELD_NAME_CONTENT_TYPE, "application/json"},
                               {HTTPCli_FIELD_NAME_AUTHORIZATION, authorize},
                               {HTTPCli_FIELD_NAME_HOST, HOST_NAME},
                               {HTTPCli_FIELD_NAME_CONTENT_LENGTH, "0"},
                               {NULL, NULL}
                            };
    bool        moreFlags = 0;
    bool        lastFlag = 0;
    char        tmpBuf[4];


    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send PUT method request. */
    /* Here we are setting moreFlags = 1 as there are some more header fields need to send
       other than setted in previous call HTTPCli_setRequestFields() at later stage.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
    */
    moreFlags = 0;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPCli_METHOD_PUT, request_uri, moreFlags);
    if(lRetVal < 0)
    {
        UART_PRINT("Failed to send HTTP PUT request header.\n\r");
        return lRetVal;
    }
    //
    //sprintf((char *)tmpBuf, "%d", (sizeof(PUT_DATA)-1));

    /* Here we are setting lastFlag = 1 as it is last header field.
       Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
    */
    /*
    lastFlag = 1;
    lRetVal = HTTPCli_sendField(httpClient, HTTPCli_FIELD_NAME_CONTENT_LENGTH, (char *)tmpBuf, lastFlag);
    if(lRetVal < 0)
    {
        UART_PRINT("Failed to send HTTP PUT request header.\n\r");
        return lRetVal;
    }
    */

    /* Send PUT data/body */
    /*
    lRetVal = HTTPCli_sendRequestBody(httpClient, "", 1);
    if(lRetVal < 0)
    {
        UART_PRINT("Failed to send HTTP PUT request body.\n\r");
        return lRetVal;
    }
    */
    //
    lRetVal = readResponse(httpClient);

    return lRetVal;
}

//*****************************************************************************
//
//! \brief HTTP GET Demonstration
//!
//! \param[in]  httpClient - Pointer to http client
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int HTTPGetMethod(HTTPCli_Handle httpClient, char* request_uri)
{
    char authorization[256] = "Bearer ";

    memcpy(&authorization[7], &authorization_token[0], strlen(authorization_token));
    const char* authorize = &authorization[0];
    long lRetVal = 0;
    HTTPCli_Field fields[4] = {
                                {HTTPCli_FIELD_NAME_CONTENT_TYPE, "application/json"},
                                {HTTPCli_FIELD_NAME_AUTHORIZATION, authorize},
                                {HTTPCli_FIELD_NAME_HOST, HOST_NAME},
                                {NULL, NULL}
                            };
    bool        moreFlags;

    //UART_PRINT("\r\n authorization is :%s with length: %i\r\n",&authorization[0], strlen(authorization) );
    /* Set request header fields to be send for HTTP request. */
    HTTPCli_setRequestFields(httpClient, fields);

    /* Send GET method request. */
    /* Here we are setting moreFlags = 0 as there are no more header fields need to send
       at later stage. Please refer HTTP Library API documentaion @ HTTPCli_sendRequest
       for more information.
    */
    moreFlags = 0;
    lRetVal = HTTPCli_sendRequest(httpClient, HTTPCli_METHOD_GET, request_uri, moreFlags);
    if(lRetVal < 0)
    {
        UART_PRINT("Failed to send HTTP GET request.\n\r");
        return lRetVal;
    }


    lRetVal = readResponse(httpClient);
    UART_PRINT("%s", g_buff);

    return lRetVal;
}

int spotplay(HTTPCli_Handle httpClient){
    int ret = HTTPPutMethod(httpClient, RESUMEHEADER);
    return ret;
}

int spotpause(HTTPCli_Handle httpClient){
    int ret =HTTPPutMethod(httpClient, PAUSEHEADER);
    return ret;
}
int spotnext(HTTPCli_Handle httpClient){
    int ret =HTTPPostMethod(httpClient, SKIPNEXTHEADER);
    return ret;
    //get track/artist name and song duration
}
int spotprev(HTTPCli_Handle httpClient){
    int ret =HTTPPostMethod(httpClient, SKIPPREVHEADER);
    return ret;
    //get track/artist name and song duration
}
int spotinfo(HTTPCli_Handle httpClient){
    int ret = HTTPGetMethod(httpClient, CURRTRACKHEADER);
    while(ret < 0){
        UtilsDelay(80000000);
        ret = HTTPGetMethod(httpClient, CURRTRACKHEADER);
    }
    return ret;
}
int spotvolume(HTTPCli_Handle httpClient, unsigned int percent){
    char *char_percent = malloc(4);

    if(percent   < 10){
        char_percent[0] = percent / 10 + '0';
        char_percent[1] = '\0';
    }else if(percent < 99){
        char_percent[0] = percent / 10 + '0';
        char_percent[1] = percent % 10 + '0';
        char_percent[2] = '\0';
    }
    char* request;
    request = malloc(sizeof(VOLUMEHEADER) + strlen(char_percent));
    strcpy(request, VOLUMEHEADER);
    strcat(request, char_percent);
    UART_PRINT("VOLUME REQUEST: %s\r\n", request);
    int ret =HTTPPutMethod(httpClient, (const char*) request);
    return ret;
}

int spotseekzero(HTTPCli_Handle httpClient){
    int ret =HTTPPutMethod(httpClient, SEEKZEROHEADER);
}

//*****************************************************************************
//
//! Function to connect to AP
//!
//! \param  none
//!
//! \return Error-code or SUCCESS
//!
//*****************************************************************************
static long ConnectToAP()
{
    long lRetVal = -1;

    //
    // Following function configure the device to default state by cleaning
    // the persistent settings stored in NVMEM (viz. connection profiles &
    // policies, power policy etc)
    //
    // Applications may choose to skip this step if the developer is sure
    // that the device is in its desired state at start of applicaton
    //
    // Note that all profiles and persistent settings that were done on the
    // device will be lost
    //

    InitializeAppVariables();


    lRetVal = ConfigureSimpleLinkToDefaultState();
    if(lRetVal < 0)
    {
        if (DEVICE_NOT_IN_STATION_MODE == lRetVal)
        {
            UART_PRINT("Failed to configure the device in its default state, "
                            "Error-code: %d\n\r", DEVICE_NOT_IN_STATION_MODE);
        }

        return -1;
    }

    UART_PRINT("Device is configured in default state \n\r");
    CLR_STATUS_BIT_ALL(g_ulStatus);
    //
    // Assumption is that the device is configured in station mode already
    // and it is in its default state
    //
    lRetVal = sl_Start(0, 0, 0);
    if (lRetVal < 0 || ROLE_STA != lRetVal)
    {
        ASSERT_ON_ERROR(DEVICE_START_FAILED);
    }

    UART_PRINT("Device started as STATION \n\r");
    UART_PRINT("Connecting to AP: %s\r\n", SSID_NAME);
    // Connecting to WLAN AP - Set with static parameters defined at the top
    // After this call we will be connected and have IP address
    lRetVal = WlanConnect();

    UART_PRINT("Connected to the AP: %s\r\n", SSID_NAME);
    return 0;
}

static int ConnectToAuthServer(HTTPCli_Handle httpClient)
{
    UART_PRINT("Retrieving Account Auhorization Token\r\n");
    memset(authorization_token,0,256);
    long lRetVal = -1;
    struct sockaddr_in addr;
    g_ulAuthDestinationIP = 0;
    while(g_ulAuthDestinationIP == 0){
        lRetVal = sl_NetAppDnsGetHostByName((signed char *)HOST_NAME,
                                                 strlen((const char *)AUTH_HOST_NAME),
                                                 &g_ulAuthDestinationIP, SL_AF_INET);
            UART_PRINT("Spotify IP %X\r\n", g_ulAuthDestinationIP);
        UtilsDelay(2 * 80000000);
    }
    SlDateTime_t dt;
       /* Set current date to validate certificate */
       dt.sl_tm_day = DATE;
       dt.sl_tm_mon = MONTH;
       dt.sl_tm_year = YEAR;
       dt.sl_tm_hour = HOUR;
       dt.sl_tm_min = MINUTE;
       dt.sl_tm_sec = SECOND;
       sl_DevSet(SL_DEVICE_GENERAL_CONFIGURATION,
       SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME,
       sizeof(SlDateTime_t), (unsigned char *)(&dt));

       /* Set up the input parameters for HTTP Connection */
      addr.sin_family = AF_INET;
      addr.sin_port = htons(HOST_PORT);
      addr.sin_addr.s_addr = sl_Htonl(g_ulAuthDestinationIP);

       struct HTTPCli_SecureParams sparams;
       /* Set secure TLS connection  */
       /* Security parameters */
       sparams.method.secureMethod = SL_SO_SEC_METHOD_TLSV1;
       sparams.mask.secureMask = SL_SEC_MASK_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256; //SL_SEC_MASK_SSL_RSA_WITH_RC4_128_SHA;;
       //sparams.method.secureMethod =0;
       //sparams.mask.secureMask = 0;
       strncpy(sparams.cafile, SL_SSL_CA_CERT, sizeof(SL_SSL_CA_CERT));
       sparams.privkey[0] = 0;
       sparams.cert[0] = 0;
       sparams.dhkey[0] = 0;
       HTTPCli_setSecureParams(&sparams);

       HTTPCli_construct(httpClient);
       lRetVal = HTTPCli_connect(httpClient, (struct sockaddr *)&addr, HTTPCli_TYPE_TLS, NULL);
       if (lRetVal < 0)
       {
           UART_PRINT("Connection to server failed. error(%d)\n", lRetVal);
       }
       else
       {
           UART_PRINT("Connection to server created successfully\n");
       }

        bool moreFlags = 1;
        bool lastFlag = 1;
        char tmpBuf[4];
        HTTPCli_Field fields[5] = {
                                    {HTTPCli_FIELD_NAME_HOST, AUTH_HOST_NAME},
                                    {HTTPCli_FIELD_NAME_CONTENT_TYPE, "application/x-www-form-urlencoded"},
                                    {HTTPCli_FIELD_NAME_AUTHORIZATION, CLIENT_CREDENTIALS_BASE64},
                                    {HTTPCli_FIELD_NAME_CONTENT_LENGTH, "170"},
                                    {NULL, NULL}
                                };


        /* Set request header fields to be send for HTTP request. */
        HTTPCli_setRequestFields(httpClient, fields);

        /* Send POST method request. */
        /* Here we are setting moreFlags = 1 as there are some more header fields need to send
           other than setted in previous call HTTPCli_setRequestFields() at later stage.
           Please refer HTTP Library API documentaion @ref HTTPCli_sendRequest for more information.
        */
        moreFlags = 0;
        lRetVal = HTTPCli_sendRequest(httpClient, HTTPCli_METHOD_POST, "/api/token", moreFlags);
        if(lRetVal < 0)
        {
            UART_PRINT("Failed to send HTTP POST request header.\n\r");
            return lRetVal;
        }

        //sprintf((char *)tmpBuf, "%d", (sizeof(POST_DATA)-1));

        /* Here we are setting lastFlag = 1 as it is last header field.
           Please refer HTTP Library API documentaion @ref HTTPCli_sendField for more information.
        */
        /*
        lastFlag = 1;
        lRetVal = HTTPCli_sendField(httpClient, HTTPCli_FIELD_NAME_CONTENT_LENGTH, (const char *)tmpBuf, lastFlag);
        if(lRetVal < 0)
        {
            UART_PRINT("Failed to send HTTP POST request header.\n\r");
            return lRetVal;
        }
        */

        /* Send POST data/body */
        lRetVal = HTTPCli_sendRequestBody(httpClient, POST_AUTHORIZATION_DATA, (sizeof(POST_AUTHORIZATION_DATA)-1));
        if(lRetVal < 0)
        {
            UART_PRINT("Failed to send HTTP POST request body.\n\r");
            return lRetVal;
        }

        lRetVal = readResponse(httpClient);

        UART_PRINT("%s", (unsigned char *)g_buff);
        jsmn_parser parser;
        jsmntok_t tokens[10];

        jsmn_init(&parser);
        // js - pointer to JSON string
        // tokens - an array of tokens available
        // 10 - number of tokens available
        const char* buf = (const char *)g_buff;
        jsmn_parse(&parser,buf , strlen(buf), tokens, 10);
        int i = 0;
        for(i=0; i < 10; i++){
            UART_PRINT("\r\nTOKEN %i: type = %X, start = %i, end = %i, size = %i",i, tokens[i].type, tokens[i].start, tokens[i].end, tokens[i].size);
        }

        strncpy(authorization_token, g_buff + tokens[2].start, tokens[2].end - tokens[2].start );
        authorization_token[tokens[2].end - tokens[2].start] = '\0';
        //UART_PRINT("\r\n AUTHORIZATION_TOKEN: %s \r\n", authorization_token);
        return lRetVal;
}

//*****************************************************************************
//
//! Function to connect to HTTP server
//!
//! \param  httpClient - Pointer to HTTP Client instance
//!
//! \return Error-code or SUCCESS
//!
//*****************************************************************************
static int ConnectToHTTPServer(HTTPCli_Handle httpClient)
{
    long lRetVal = -1;
    struct sockaddr_in addr;
    g_ulDestinationIP = 0;
    UART_PRINT("Connecting to SPOTIFY API\r\n");
    #ifdef USE_PROXY
        struct sockaddr_in paddr;
        paddr.sin_family = AF_INET;
        paddr.sin_port = htons(PROXY_PORT);
        paddr.sin_addr.s_addr = sl_Htonl(PROXY_IP);
        HTTPCli_setProxy((struct sockaddr *)&paddr);
    #endif

    /* Resolve HOST NAME/IP */
    while(g_ulDestinationIP == 0){
        lRetVal = sl_NetAppDnsGetHostByName((signed char *)HOST_NAME,
                                                 strlen((const char *)HOST_NAME),
                                                 &g_ulDestinationIP, SL_AF_INET);
        UART_PRINT("Spotify API IP %X\n\r", g_ulDestinationIP);
        UtilsDelay(2 * 80000000);
    }

    //g_ulDestinationIP = 0x23bae019;
    if(lRetVal < 0)
    {
       ASSERT_ON_ERROR(GET_HOST_IP_FAILED);
    }
    SlDateTime_t dt;
    /* Set current date to validate certificate */
    dt.sl_tm_day = DATE;
    dt.sl_tm_mon = MONTH;
    dt.sl_tm_year = YEAR;
    dt.sl_tm_hour = HOUR;
    dt.sl_tm_min = MINUTE;
    dt.sl_tm_sec = SECOND;
    sl_DevSet(SL_DEVICE_GENERAL_CONFIGURATION,
    SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME,
    sizeof(SlDateTime_t), (unsigned char *)(&dt));

    /* Set up the input parameters for HTTP Connection */
   addr.sin_family = AF_INET;
   addr.sin_port = htons(HOST_PORT);
   addr.sin_addr.s_addr = sl_Htonl(g_ulDestinationIP);

    struct HTTPCli_SecureParams sparams;
    /* Set secure TLS connection  */
    /* Security parameters */
    sparams.method.secureMethod = SL_SO_SEC_METHOD_TLSV1;
    sparams.mask.secureMask = SL_SEC_MASK_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256; //SL_SEC_MASK_SSL_RSA_WITH_RC4_128_SHA;;
    //sparams.method.secureMethod =0;
    //sparams.mask.secureMask = 0;
    strncpy(sparams.cafile, SL_SSL_CA_CERT, sizeof(SL_SSL_CA_CERT));
    sparams.privkey[0] = 0;
    sparams.cert[0] = 0;
    sparams.dhkey[0] = 0;
    HTTPCli_setSecureParams(&sparams);

    HTTPCli_construct(httpClient);
    lRetVal = HTTPCli_connect(httpClient, (struct sockaddr *)&addr, HTTPCli_TYPE_TLS, NULL);
    if (lRetVal < 0)
    {
        UART_PRINT("Connection to server failed. error(%d)\n", lRetVal);
    }
    else
    {
        UART_PRINT("Connection to server created successfully\n");
    }




    return 0;
}





//*****************************************************************************
//
//! Board Initialization & Configuration
//!
//! \param  None
//!
//! \return None
//
//*****************************************************************************
void
BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
  //
  // Set vector table base
  //
#if defined(ccs) || defined(gcc)
    IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
#endif
#if defined(ewarm)
    IntVTableBaseSet((unsigned long)&__vector_table);
#endif
#endif
    //
    // Enable Processor
    //
    IntMasterEnable();
    IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}


// Replace with frequency
static void OLEDInit(void){
    //SPI_IF_BIT_RATE
    MAP_SPIReset(GSPI_BASE);
    MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
                     SPI_IF_BIT_RATE,SPI_MODE_MASTER,SPI_SUB_MODE_0,
                     (SPI_SW_CTRL_CS |
                     SPI_4PIN_MODE |
                     SPI_TURBO_OFF |
                     SPI_CS_ACTIVELOW |
                     SPI_WL_8));
    MAP_SPIEnable(GSPI_BASE);
    Adafruit_Init();
    fillScreen(BLACK);

    //Play slider
    drawFastHLine(5, 50, 118, WHITE);
    fillCircle(p, 50, 2, WHITE);

    // Play Button
    fillCircle(64, 90, 20, GREEN);
    fillTriangle(57, 80, 77, 90, 57, 100, BLACK);

    // Forward Button
    fillTriangle(97, 80, 117, 90, 97, 100, GREEN);
    fillRect(115, 81, 3, 20, GREEN);

    // Backwards Button
    fillTriangle(30, 80, 10, 90, 30, 100, GREEN);
    fillRect(8, 81, 3, 20, GREEN);

    // Volume Slider
    drawFastHLine(14, 120, 100, WHITE);
    drawFastHLine(14, 120, v, GREEN);
    fillCircle(v + 14, 120, 1, WHITE);

    int i = 0;
    for(i = 0; i < strlen(songname); i++){
        drawChar(i*12, 10, songname[i], WHITE, BLACK, 2);
    }
    for(i = 0; i < strlen(artist); i++){
        drawChar(i*6, 30, artist[i],WHITE, BLACK, 1);
    }
    // Song Length
    drawChar(100, 56, minutef + '0', WHITE, BLACK, 1);
    drawChar(106, 56, ':', WHITE, BLACK, 1);
    drawChar(112, 56, second1f + '0', WHITE, BLACK, 1);
    drawChar(118, 56, second2f + '0', WHITE, BLACK, 1);
    //incremented time starting from 0:00
    drawChar(6, 56, minute + '0', WHITE, BLACK, 1);
    drawChar(12, 56, ':', WHITE, BLACK, 1);
    drawChar(18, 56, second1 + '0', WHITE, BLACK, 1);
    drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
}

void Report_Codes(int format){

    if(queue_length(data_buffer) < 1){
        return;
    }
    unsigned short int tap_count = 0;
    unsigned int temp_code = 0;
    queue_dequeue(data_buffer, &temp_code, &tap_count);
    translate_code(temp_code, tap_count, &command);

    // Backward
    if(command == 1) {

        ////send backward pressed to player
        spotprev(&httpClient);

        fillTriangle(30, 80, 10, 90, 30, 100, WHITE); //Backward
        fillRect(8, 81, 3, 20, WHITE);
        fillCircle(p, 50, 2, BLACK);
        drawFastHLine(5, 50, 118, WHITE);
        p = 6;
        fillCircle(p, 50, 2, WHITE);
        MAP_UtilsDelay(8000000);
        fillTriangle(30, 80, 10, 90, 30, 100, GREEN); //Backward
        fillRect(8, 81, 3, 20, GREEN);
        drawChar(6, 56, minute + '0', BLACK, BLACK, 1);
        drawChar(18, 56, second1 + '0', BLACK, BLACK, 1);
        drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
        minute = 0;
        second1 = 0;
        second2 = 0;
        drawChar(6, 56, minute + '0', WHITE, BLACK, 1);
        drawChar(18, 56, second1 + '0', WHITE, BLACK, 1);
        drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
        newsong = 1;
    }
    // Play/Pause
    else if(command == 2) {
        //from pause to play
        if (playstate == 0) {

            ////send play to player
            spotplay(&httpClient);
            fillTriangle(57, 80, 77, 90, 57, 100, GREEN);
            fillRect(56, 80, 5, 20, BLACK);
            fillRect(69, 80, 5, 20, BLACK);
            playstate = 1;
            TimerEnable(TIMERA3_BASE,TIMER_A);
        }
        //from play to pause
        else if(playstate == 1) {

            ////send pause to player
            spotpause(&httpClient);
            fillRect(56, 80, 5, 20, GREEN);
            fillRect(69, 80, 5, 20, GREEN);
            fillTriangle(57, 80, 77, 90, 57, 100, BLACK);
            playstate = 0;
            TimerDisable(TIMERA3_BASE,TIMER_A);
        }
    }
    // Forward
    else if(command == 3) {

        ////send to player that forward was pressed here
        spotnext(&httpClient);
        fillTriangle(97, 80, 117, 90, 97, 100, WHITE); //Forward
        fillRect(115, 81, 3, 20, WHITE);
        fillCircle(p, 50, 2, BLACK);
        drawFastHLine(5, 50, 118, WHITE);
        p = 6;
        fillCircle(p, 50, 2, WHITE);
        MAP_UtilsDelay(8000000);
        fillTriangle(97, 80, 117, 90, 97, 100, GREEN); //Forward
        fillRect(115, 81, 3, 20, GREEN);

        playstate = 1;
        newsong = 1;
        TimerEnable(TIMERA3_BASE,TIMER_A);
    }
    // Volume Down
    else if(command == 4) {

        ////send volume down to player

        if(v > 4) {
            fillCircle(v + 14, 120, 1, BLACK);
            drawFastHLine(14, 120, 100, WHITE);
            v -= 5;
            spotvolume(&httpClient, (unsigned int) v);
            drawFastHLine(14, 120, v, GREEN);
            fillCircle(v + 14, 120, 1, WHITE);
        }
        // if we can get state of player
        // just send volume down command to player
        // and call GetVolume(%) in main
        // should be able to remove the if statements
        // in volume up and down
    }
    // Volume Up
    else if(command == 5) {
        ////send volume up to player
        if(v < 96) {
            fillCircle(v + 14, 120, 1, BLACK);
            drawFastHLine(14, 120, 100, WHITE);
            v += 5;
            spotvolume(&httpClient, (unsigned int) v);
            drawFastHLine(14, 120, v, GREEN);
            fillCircle(v + 14, 120, 1, WHITE);
        }
    }
    // same as above but just send volume up to player
}




//*****************************************************************************
//
//! Main  Function
//
//*****************************************************************************
int main()

{
    /*
    char *progress_time = malloc(50);
    char *artist_name = malloc(100);
    char *duration = malloc(50);
    char *song_name = malloc(100);
    */
    memset(g_buff, 0, MAX_BUFF_SIZE+1);
    long lRetVal = -1;


    data_buffer = queue_create();
    memset(recieve_buffer,0x0, RECIEVE_MAX );
    memset(transmit_buffer,0x0, TRANSMIT_MAX );
    memset(transmit_color_buffer,0x0, TRANSMIT_MAX );
    //
    // Initialize Board configurations
    //
    BoardInit();
    //
    // Pinmux for UART
    //
    PinMuxConfig();

    OLEDInit();
    // Configuring UART
    UART_Init();
    InitTerm();
    // Configure Timers
    Timer_Init();

    Interrupt_Init();
    InitializeAppVariables();

    //Testing Zone
    /*
    fillScreen(BLACK);
        while(1){
            //drawBitmap(0, 0, BongoCatPause.data, BongoCatPause.width, BongoCatPause.height, WHITE );
            drawBitmap(0, 0, BongoCatLeftSlap.data, BongoCatLeftSlap.width, BongoCatLeftSlap.height, WHITE );
            drawBitmap(0, 0, BongoCatRightSlap.data, BongoCatRightSlap.width, BongoCatRightSlap.height, WHITE );
        }

    */
    lRetVal = ConnectToAP();
    if(lRetVal < 0)
    {
        LOOP_FOREVER();
    }
    lRetVal = ConnectToAuthServer(&httpAuthClient);
    while(lRetVal < 0){
        UtilsDelay(16000000);
        lRetVal = ConnectToAuthServer(&httpAuthClient);

    }
    //tls_connect();
    lRetVal = ConnectToHTTPServer(&httpClient);
    while(lRetVal < 0)
    {
        UtilsDelay(16000000);
        lRetVal = ConnectToHTTPServer(&httpClient);
    }

    // void drawXBitmap(int x, int y, const unsigned char *bitmap, int w, int h, unsigned int color);

    spotinfo(&httpClient);
    spotpause(&httpClient);
    spotseekzero(&httpClient);
    //// pass name, artist, and songlength into here
    spotinfo(&httpClient);
    GetSongInfo(song_name, artist_name, int_duration_time);
    drawChar(100, 56, minutef + '0', WHITE, BLACK, 1);
    drawChar(112, 56, second1f + '0', WHITE, BLACK, 1);
    drawChar(118, 56, second2f + '0', WHITE, BLACK, 1);
    int i = 0;
    int len = strlen(songname);
    for(i = 0; i < 11; i++){
        if(i < len){
            drawChar(i*12, 10, songname[i],WHITE, BLACK, 2);
        }else{
            drawChar(i*12, 10, 0x20, WHITE, BLACK, 2);
        }
    }
    len = strlen(artist);
    for(i = 0; i < 21; i++){
        if(i < len){
            drawChar(i*6, 30, artist[i],WHITE, BLACK, 1);
        }else{
            drawChar(i*6, 30, 0x20, WHITE, BLACK, 1);
        }

    }

    slider_tick_time =  80000.0 / 123.0 * (unsigned long )int_duration_time / 1.6 ;
    TimerLoadSet(TIMERA3_BASE, TIMER_A, slider_tick_time);
    // Begin
    //writeCommand(SSD1351_CMD_DISPLAYON);
    newsong = 0;;
    UART_PRINT("\r\n\n Spotify Player Connected and Ready to Play!\r\n");
    while(1){`
        Report_Codes(1);
        //PlaySlider();
        //GetVolume(int % 0-100); can use this if player can receive volume percentage
        // if newsong == 1, update song info
        // currently the program starts in this state and when forward/backward is pressed will enter this state
        if(newsong == 1) {
            // wait for GetSongInfo to recieve something
            ResetScreen();
            while(songlength == 0) {

                //// right here is where the device should get info of the new song.
                // Left Timer Reset
                drawChar(6, 56, minute + '0', BLACK, BLACK, 1);
                drawChar(18, 56, second1 + '0', BLACK, BLACK, 1);
                drawChar(24, 56, second2 + '0', BLACK, BLACK, 1);
                minute = 0;
                second1 = 0;
                second2 = 0;
                drawChar(6, 56, minute + '0', WHITE, BLACK, 1);
                drawChar(18, 56, second1 + '0', WHITE, BLACK, 1);
                drawChar(24, 56, second2 + '0', WHITE, BLACK, 1);
                ////send play to player
                spotplay(&httpClient);
                fillTriangle(57, 80, 77, 90, 57, 100, GREEN);
                fillRect(56, 80, 5, 20, BLACK);
                fillRect(69, 80, 5, 20, BLACK);
                //// pass name, artist, and songlength into here
                spotinfo(&httpClient);
                UtilsDelay(80000000)
                GetSongInfo(song_name, artist_name, int_duration_time);
                slider_tick_time =  80000.0 / 123.0 * (unsigned long)int_duration_time / 1.6;

                drawChar(100, 56, minutef + '0', WHITE, BLACK, 1);
                drawChar(112, 56, second1f + '0', WHITE, BLACK, 1);
                drawChar(118, 56, second2f + '0', WHITE, BLACK, 1);
                int i = 0;
                int len = strlen(songname);
                for(i = 0; i < 11; i++){
                    if(i < len){
                        drawChar(i*12, 10, songname[i],WHITE, BLACK, 2);
                    }else{
                        drawChar(i*12, 10, 0x20, WHITE, BLACK, 2);
                    }
                }
                len = strlen(artist);
                for(i = 0; i < 21; i++){
                    if(i < len){
                        drawChar(i*6, 30, artist[i],WHITE, BLACK, 1);
                    }else{
                        drawChar(i*6, 30, 0x20, WHITE, BLACK, 1);
                    }

                }
            }
            songlength = 0;
            newsong = 0;
        }
    }
}

/* */





