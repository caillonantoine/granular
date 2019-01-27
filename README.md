# Granular
A C++ based granular pd external.

Compile it this way

```bash
mkdir build && cd build && cmake .. && make
```

And then run it with

```bash
pd -nogui granular.pd
```

By default, it loads `kalimba.wav` and takes input 48 - 51 from a MIDI controller to modify
* Play hop size
* Read hop size
* Grain size
* Volume
