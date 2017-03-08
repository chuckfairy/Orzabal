# Future synth plugin

# Install

```sh
## Needs latest versions of these in local
git clone http://git.drobilla.net/serd.git
git clone http://git.drobilla.net/sord.git
git clone http://git.drobilla.net/lilv.git
git clone http://git.drobilla.net/suil.git
git clone http://git.drobilla.net/sratom.git
## Install those /usr/local

cmake .
make -j8

#gui
./src/qt/example
```

# Jack

Starting the app will start jack. I recommnend starting it elsewhere, `./bin/jack_startup.sh` is a sample startup. Midi will need to be enabled.
