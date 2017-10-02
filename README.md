# Meta Synth [Jack](http://jackaudio.org/) App

![Main View](https://raw.githubusercontent.com/chuckfairy/Orzabal/master/screenshots/main_view.png)

Currently will load [lv2](http://lv2plug.in/) plugins. Plans for mac and windows vst support soon.

# Install


## Mac

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


## Cmake Install

```shell
# Make sure to have latest lv2 core

# Also in ./bin/build_*
cmake .
make -j8

#gui, only qt rn
./src/qt/orzabal.qt
```


# Pi

```shell
sudo apt-get install x11vncserver wiringPi
```

Tested on usb audio device. Use `./bin/build_pi.sh` for a full screen use. Other build types with default startups.

- `./bin/build_pi_effects.sh` // Effects rack


# Jack

Starting the app will start jack. I recommnend starting it elsewhere, `./bin/jack_startup.sh` is a sample startup. Midi will need to be enabled.
