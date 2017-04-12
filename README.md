# Meta Synth [Jack](http://jackaudio.org/) App

![Main View](https://github.com/chuckfairy/Orzabal/tree/master/screenshots/main_view.png)

Currently will load [lv2](http://lv2plug.in/) plugins. Plans for mac and windows vst support soon.

# Install

```shell
# Make sure to have latest lv2 core

# Also in ./bin/build_*
cmake .
make -j8

#gui, only qt rn
./src/qt/orzabal.qt
```

# Jack

Starting the app will start jack. I recommnend starting it elsewhere, `./bin/jack_startup.sh` is a sample startup. Midi will need to be enabled.

# Pi

Tested on usb device. Use `./bin/build_pi.sh` for a full screen use.
