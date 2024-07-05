# Easy Play 📺

Easy Play is an integrated system designed to help individuals with cerebral palsy (CP) watch movies independently! This repository contains both the embedded and server code, developed in conjunction with a custom button for the ES1050 - Engineering Design course.

## The Issue
Individuals with CP often face challenges using traditional TV remote controls. Our client, Katelynn, loves watching movies but relies on her caretaker to operate the TV. Easy Play empowers her to regain control and independence in her movie-watching experience.

## Our Solution
Easy Play consists of two separate systems: a server and embedded software. The button communicates with the server via Bluetooth Low Energy (BLE) or Wi-Fi (using HTTP packets) and processes requests by sending ADB commands to an Amazon Firestick on the network.

For ease of setup and use, Easy Play includes a user-friendly web UI that allows caretakers to connect, select movies, turn off, and control the software. However, the system is designed so that Katelynn retains full control over the movie-watching experience.

The software intelligently interprets Katelynn's actions based on context. It can:
- Turn the Firestick on and start the requested movie when it's off
- Pause the movie when it is running
- Resume playback when paused
- End playback intelligently after the movie is over

Additionally, safety features are implemented to notify caretakers if the system detects an issue, such as the button being held for an extended period or if a fall is detected.

## Technologies Used
- **Python**: Backend logic and server operations
- **Flask**: Web framework used to host the server
- **HTML/CSS**: Frontend design and styling for the web UI
- **C++ (Arduino)**: Embedded software for the button interface
