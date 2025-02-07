#!/bin/bash

npm i
bare-make generate
bare-make build
bare-make install
npm pack
mv a-1.2.3.tgz ./b/
cd ./b

npm i
bare-make generate
bare-make build
bare-make install
cd ..

bare test.js
