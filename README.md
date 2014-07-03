# lightem - light 'em up! a library to control RGB LED's

## Overview

lightem is a C++ library that implements a subset of the "Serial Addressable
RGB PWM LED Driver" protocol defined by
[picprojects](http://picprojects.org.uk/projects/zcode/sadpktformat.htm).

It is targeted to implement a way to control addressable LED's, like e.g.
the [Adafruit Neopixels](http://www.adafruit.com/categories/168), over some
communication medium.


## C API

The C API consists only of one function, to create a frame from all necessary
parameters.

        #include <lightem.h>

        size_t sz;
        /* create a broadcast message and set all colors to full intensity */
        void* p = lightem_c(0xff, 255, 255, 255, &sz);


## C++ API

The C++ API provides a more advanced interface, e.g. by the possibility of
"translation" of group addresses to an array of single addresses that lie
within that group.

        #include <lightem.h>

        lightem l;
        uint8_t b[l.sz_frame];

        read(fd, b, sizeof(b));


        if (l.setFrame(f) && l.isPixelValue())
          {
           size_t sz;
            uint8_t* p = l.getAddr(&sz);
            if (p)
              {
                printf("plain address %d", l.getAddr());
                for (size_t i = 0; i < sz; ++i) {
                  printf("%d = 0x%08X", p[i], l.getColor());
                }
                free(p);
                return;
              }
          }


## Installation
- Clone the repository to your Arduino/libraries folder:

        git clone https://github.com/sjaeckel/lightem.git

- Add the library to your Arduino project, add the include directive to your sketch and you're ready to use it:

        #include <lightem.h>

## Meta
- [Bugs](https://github.com/sjaeckel/lightem/issues)

## Contribute
If you want to contribute:

- Fork the project.
- Make your feature addition or bug fix based on develop.
- Add tests for it. This is important so I don't break it in a future version
  unintentionally.
- Commit, do not mess with version
- Send me a pull request. Bonus points for topic branches.

