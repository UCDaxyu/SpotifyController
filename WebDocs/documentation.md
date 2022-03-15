
***
**Connecting to the Internet**

Text here

**Spotify Authentication**
Before using any other parts of their api, Spotify requires authentication from the user and application through the following authorizaiton flow.
![Authorization Code](Media/AuthG_AuthoriztionCode.png)

1. The app requests authorization to access api and/or user data
2. Spotify responds by requesting a user login at a developer specified redireciton URI
3. The user logs in to authorize access.
4. The app requests an access token and refresh token tied to the user
5. The app is now free to make API calls if they provide the access token.
6. The app can get new access tokens by re-requesting authorization providing the refresh token in place of user login.

Refresh tokens last as long as the user permits the application to access the the data. In light of this, we decided to <a href="https://developer.spotify.com/documentation/web-api/quick-start/" target="_blank">follow their guide</a> and create a tempory http server to host a one time user login. This provided us with a refresh token that will last as long as we want. 

**Spotify API**

Spotify provides full documentation of their web api on their developer website. 
<a href="https://developer.spotify.com/documentation/web-api/reference/#/" target="_blank">Full Spotify API Documentation Here!</a>


The API calls we chose to implement are provided as macro definitions below. 

``` c
#define PLAYSTATEHEADER      "/v1/me/player"
#define TRANSFERPLAYHEADER   "/v1/me/player"
#define CURRTRACKHEADER      "/v1/me/player/currently-playing"
#define GETDEVICESHEADER     "/v1/me/player/devices"
#define RESUMEHEADER         "/v1/me/player/play"
#define PAUSEHEADER          "/v1/me/player/pause"
#define SKIPNEXTHEADER       "/v1/me/player/next"
#define SKIPPREVHEADER       "/v1/me/player/previous"
#define SEEKZEROHEADER       "/v1/me/player/seek?position_ms=0"
#define VOLUMEHEADER         "/v1/me/player/volume?volume_percent="
```


****

To send data from Spotify about what task the user wants done, user input is collected through an IR remote control. Each button of the remote sends a different waveform to the IR receiver connected to our CC3200 LaunchPad. Using an onboard timer and GPIO pin interrupt the board can interpret these waveforms to determine what button on the remote the user pressed. Each waveform can be interpreted as a 32 bit integer which is unique for each button of the remote. This incoming value is then examined to determine which button was pressed by the user. Each button is mapped to a command to send to spotify . //adding more rn

**Displaying Data on the OLED**
![Authorization Code](Media/IMG_1608.JPG)

The OLED display utilizes a modified version of Adafruit's [open source graphics library](http://www.adafruit.com/product/1431) made for Arduino. The modified library ports this code to a version that can be recognized by the CC3200. The OLED displays the track name, artist, track length, volume level, and a media player interface for the user. The track name and artist are pulled directly from spotify, the track length is pulled from spotify in milliseconds and converted to minutes:seconds format for the display, and the rest of the display consists of controls the user can send to spotify.
