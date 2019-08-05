#!/bin/bash

mv ../src/json ~/.
cat $(find ../ -name '*pp') | sed '/^\s*$/d' | wc -l
mv ~/json ../src/
