It should work with most compilers and I don't think it has any endianness issues.

It's optimized solely for being lightweight, i.e. having a small program size.  On a 32 bit micro, it should be about 1.7KB optimized.

Initially pulled from my [U2F Zero](https://github.com/conorpp/u2f-zero) project and 
realized I'll probably re-use this accross different projects.

## How to install

Just put platform dependent code in `putf` for sending one character through your interface.

## How to use

You can probably figure it out from reading the [header file](https://github.com/conorpp/small-printing/blob/master/small_printing.h).

But for example, to print a string:

```
s_prints("this is a string\r\n");
```

To print uint type in decimal format:

```
s_printd("here are 3 integers: ", 3, 11, 22, 33);

# or with no string
putd(1234);
```

In hexadecimal:


```
s_printx("here are 3 integers: ", 3, 11, 22, 33);

# or with no string
putx(0x1234);
```

And similar for bytes, long ints.
