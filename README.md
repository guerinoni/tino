# tino

required dependencies:
* lcov to run metrics/runCoverage.sh (see how much code is covered by tests)
* socat to run startVSP.sh (open a virtual serial port) and use the auto connection feature

to open a virtual comunication:

~~~
./starVSP.sh
~~~

this generates an output like this:

~~~
2019/08/02 08:27:18 socat[4776] N PTY is /dev/pts/2
2019/08/02 08:27:18 socat[4776] N PTY is /dev/pts/3
2019/08/02 08:27:18 socat[4776] N starting data transfer loop with FDs [6,6] and [8,8]
~~~

connect tino to /dev/pts/2 and your client to /dev/pts/3

