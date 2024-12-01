#! /bin/sh
for f in mame zexall emuz80 sbc8080
do  MF=./build/projects/sdl/${f}/gmake-linux/${f}.make
    if test -f $MF; then
        cat  $MF |
        sed 's/-lshared //g
            s/-lportmidi //g
            s/-lfrontend //g
            s/-lbgfx/ /g' > tmp.$$
        mv tmp.$$ $MF
    fi
done
