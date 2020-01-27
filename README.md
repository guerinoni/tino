# tino

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Tested environment

| Travis CI (Linux) |  CodeQuality | Github Actions <br> Linux  |
| :---------------: |  :---------: | :------------------------: |
| [![Build Status](https://travis-ci.org/guerinoni/tino.svg?branch=master)](https://travis-ci.org/guerinoni/tino) | [![CodeQuality](https://api.codacy.com/project/badge/Grade/294970b7a9b84d54b9be7c6240fe7ed3)](https://www.codacy.com/manual/guerinoni/tino?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=guerinoni/tino&amp;utm_campaign=Badge_Grade) | ![Ubuntu](https://github.com/guerinoni/tino/workflows/Ubuntu/badge.svg?branch=master) |

## Feature

This is a desktop application useful to simulate communication between the logic board and video board.

* import buffer configuration file from json
* treeview to show protocol of imported file
* settings loaded from file
* widget to edit IO directly using mouse
* communication through:
    - virtual com
    - modbus RS485