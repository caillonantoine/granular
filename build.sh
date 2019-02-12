mkdir -p build
cd build
cmake ..
make
echo "#N canvas 641 288 450 300 10;
#X obj 67 195 granular~;
#X msg 45 108 load kalimba.wav;
#X msg 73 131 2000 500 8192;
#X obj 73 154 unpack f f f;
#X obj 67 259 tabwrite~ viewer;
#N canvas 1120 496 450 250 (subpatch) 0;
#X array viewer 1000 float 3;
#X coords 0 1 1000 -1 200 140 1;
#X restore 215 136 graph;
#X obj 42 27 loadbang;
#X msg 64 58 \; pd dsp 1;
#X text 190 27 The granular~ object takes 3 parameters;
#X text 190 40 - Write hop size;
#X text 190 52 - Read hop size;
#X text 190 64 - Grain size;
#X obj 12 220 metro 100;
#X connect 0 0 4 0;
#X connect 1 0 0 0;
#X connect 1 0 2 0;
#X connect 2 0 3 0;
#X connect 3 0 0 1;
#X connect 3 1 0 2;
#X connect 3 2 0 3;
#X connect 6 0 1 0;
#X connect 6 0 7 0;
#X connect 6 0 12 0;
#X connect 12 0 4 0;" >> granular~-help.pd
