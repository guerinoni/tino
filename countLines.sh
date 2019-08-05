#!/bin/bash

mv src/json ~/
find . -name '*pp' | xargs wc -l
mv ~/json src/
