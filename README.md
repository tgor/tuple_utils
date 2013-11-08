C++11 tuple utils
===========

Author: Tomasz Stepniak

- Tuple utils is still under active development.
- This library is created mostly for learning purposes, yet it is targeted for production code usability. Internally it uses CMake, Doxygen and CppUnit. Compiled with GCC 4.8.1 and Clang 3.3
- Please note that this library is using template metaprogramming so readability is not its primary goal. Bear in mind that Doxygen does not support TMP techniques, this limitation is circumvented as much as it can be.
- Tuple utils is designed to be header-only library, so for not raising additional dependencies it is not using BOOST nor any other external libraries.
- Despite of being header-only library it is well tested, so it should not contain any major bugs. However please use it cautiously, I do not bear responsibility for any faults and errors caused by using tuple utils.  
- Lack of OOP design is intentional because I wanted to focus on generic and functional programming (in my opinion it is more suitable for a library code)
- Some parts of tuple utils will be updated with advent of the C++14 standard (e.g. use of std::integer_sequence instead of a hand-written indices trick)
