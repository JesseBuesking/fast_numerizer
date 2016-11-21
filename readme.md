#  fast_numerizer

https://github.com/jduff/numerizer in c using re2c and lemon

## Prereqs

- Get [googletest](https://github.com/google/googletest)
- Get [yaml-cpp](https://github.com/jbeder/yaml-cpp)
    - $ cmake -G "Unix Makefiles"
    - $ make
    - $ sudo make install

## Building

1. Install lemon to ~/repositories/lemon. If you install elsewhere, update the Makefile.
2. Install re2c
3. make

## TODOS:

- [x] Test for thread safety & make thread safe
    - not needed for ruby since it has the global lock
- [ ] Back-to-back numbers
- [ ] Reuse sds, but "grow" to max size between, if over DEFAULT_SIZE
- [ ] Negatives
- [ ] Fractions

Performance related:
- [ ] For faster parsing of strings with lots of numbers, sdscatprinf (sdscatprintf -> vsnprintf -> vfprintf -> \_\_printf_fp -> hack_digit)
- [ ] For faster parsing of strings with fewer numbers numerizer_start and Parse (probably grammar)
