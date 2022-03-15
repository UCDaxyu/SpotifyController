# About

## What is it?
***

This project is a spotify controller implemented using a CC3200 LaunchPad with peripherals connected to the internet. Using Spotify’s API the device can push instructions (such as pause/play, skip track, volume control) to spotify and display metadata of the currently playing track in a user-friendly interface.
This project is a spotify controller implemented entirely using a CC3200 LaunchPad. Using Spotify’s API, the device can push instructions (such as pause/play, skip track, volume control) to spotify and display metadata of the currently playing track in a user-friendly interface.

We made this project as our final project for our Embedded System Design Class (ECS172) at UC Davis. We were tasked to create a stand-alone, interactive system that controls something over the internet using the REST API and tools we used from previous labs in the class.

//also move to documentation probably
## Materials
***

Text Here


//Move this to documentation
## How it works
***
**Connecting to the Internet**

Text here

**Sending/Receiving data to/from Spotify**

Text here about receiving data

To send data to Spotify about what task the user wants done, user input is collected through an IR remote control. Each button of the remote sends a different waveform to the IR receiver connected to our CC3200 LaunchPad. Using an onboard timer and GPIO pin interrupt the board can interpret these waveforms to determine what button on the remote the user pressed. Each waveform can be interpreted as a 32 bit integer which is unique for each button of the remote. This incoming value is then examined to determine which button was pressed by the user. Each button is mapped to a command to send to spotify and the board will upload this command to spotify which will recognize the format of the command sent and execute it.

**Displaying Data on the OLED**

Text here

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```
