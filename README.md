# roll-duino

Simple control sketch for motor-shutters (aka "Rollladen" in german). Arduino + Ethernetshield (+ some kind of relay board of course) required.

# usage

This is for 2 shutters (and a 10W LED light). It reacts on GET to http://<IP>:8089/<cmd> where cmd can be: roll1-open roll1-close roll2-open roll2-close led-on led-off

Do not forget to adjust ip+mac as these are mine ;)

# license

(The MIT License)

Copyright (c) 2011 Knut Möller <spam1@knutmoeller.de>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
