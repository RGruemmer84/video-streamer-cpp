# C++ Video Filtering Tool
This repo contains the c++ source code for a video capturing and filtering application. It was intended to run in an embedded linux environment and has been tested on x64 Debian and ARM Raspbian (Raspberry Pi). It also contains a filter tuning mechanism for on the fly changes to filter settings, as well as utilities for communicating with an Amazon Web Services cloud account for file storage.

## Code Structure
1. Main:  Main entry point to application.
2. Util:  Various utility classes/functions used by the application.
3. Engine:  A driver that captures, processes, and saves video frames into video files for upload to a remote server.
4. Filter:  An image filtering architecture that processes raw video by passing frames through a set of cascaded filters.
3. GUI:  A simple UI to dynamically adjust filter settings to optimize filter output.

## Getting Started
### Dependencies
1. Qt 5.0 - C++ framework. Used for UI and multi-threading components.
2. OpenCV - Open source computer vision library used by the filtering mechanism.

### Installing
1. Install Qt5.0 binaries.
2. Install opencv binaries. (source code optional)
3. Install QtCreator. (optional but recommended if modifying the UI)
4. Clone this repository.

### Running
To run, launch from the command line or create new project within QtCreator.
