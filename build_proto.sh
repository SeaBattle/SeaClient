#!/bin/bash
echo "Generating packets";
cd deps/SeaPackets;
protoc-c --c_out=. *.*;

echo "Removing old packets";
rm -r ../../API/include/packet/gen;
rm -r ../../API/src/packet/gen;

echo "Creating dirs";
mkdir ../../API/include/packet/gen;
mkdir ../../API/src/packet/gen;

echo "Copying new packets";
mv *.h ../../API/include/packet/gen;
mv *.c ../../API/src/packet/gen;

cd ../../;
