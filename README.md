# Meta Synth [Jack](http://jackaudio.org/) App

![Main View](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/main_view.png)

Currently will load [lv2](http://lv2plug.in/) plugins. Plans for mac and windows vst support soon.


# Install

## Requires
- Latest [LV2](https://lv2plug.in/) installed, usually not what package manager will grab you
- `qtdeclarative5-dev`
- `libiw-dev iw`
- `jack libjack-dev`
- `cmake`
- `libboost-all-dev`
- Some LV2/Audio plugins (calf, guitarix)


If creating a linux / pi device
- [WiringPi](https://github.com/WiringPi/WiringPi)
- `node` # for VNC client


## Mac Specific

```shell
# Install Qt from https://qt.io

# Following installs

# building
brew install cmake

# brew install jack # From http://www.jackosx.com
brew install boost lv2

# lv2 plugins
# brew install mda-lv2
# brew tap david0/homebrew-audio
# brew install --HEAD calf
```


## Cmake Install and Building

```shell
# Make sure to have latest lv2 core

git submodule update --init

# Also in ./bin/build_*
cd build
cmake .. # Or ../bin/build_* see different types
make -j4 # -j<NumberofCores>

# gui, only qt rn
./src/qt/orzabal.qt

# Tools
./src/qt/orzabal.qt --help
  -l, --list          List of plugins
  -p, --plugin-types  Plugin Types Installed
  -h, --help          Display this message
      --run arg       Run raw midi instrument from CLI
      --load arg      Load JSON setting
```


# Pi

```shell
sudo apt-get install wiringPi
#sudo apt-get install x11vncserver #will also be installed during cmake
#you can configure the server and ill write instructions later
#./src/pi/CMakeLists.txt
```

Tested on usb audio device. Use `./bin/build_pi.sh` for a full screen use. Other build types with default startups.

- `./bin/build_pi_effects.sh` // Effects rack


# Jack

Starting the app will start jack. I recommnend starting it elsewhere, `./bin/jack_startup.sh` is a sample startup. Midi will need to be enabled.


# Features


## Midi Instrument From a Plugin

![Main View](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/main_view.png)


## Effects Rack

![Effects Rack](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/orzabal-effect-rack.png)

Control individual inputs and outputs allowing to setup a vocoder or anysidechained plugin inside your rack.


## Control Effect Values From External Midi

![Midi Control UI](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/orzabal-midi-control.png)

![OrzaPad Demo](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/orzapad-control-demo.gif)

Set a midi control port as an input and set multiple values to be controlled within the app. This gif example uses the [OrzaPad](https://github.com/chuckfairy/OrzaPad) as the input


## Control and Save it all

![Settings](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/orzabal-settings-tab.png)

- Save your effect rack and instrument setup as a preset to load again.
- Within this screen you can also see some setup for output and input.


## Tools for Musical Device

![Device Screen](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/orzabal-sbc-tab.png)

- Run in startup at full screen
- Connect to wifi
- Control from another computer (and in the browser [noVNC](https://github.com/novnc/noVNC))


# Thanks

- [drobilla](https://github.com/drobilla)
