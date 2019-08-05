#!/bin/bash
cppcheck ../src -ijson --enable=style --output-file=checkout.xml --inconclusive --xml --xml-version=2 -v && firefox checkout.xml 
