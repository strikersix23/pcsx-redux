/*

MIT License

Copyright (c) 2023 PCSX-Redux authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#pragma once

#include <bit>
#include <concepts>
#include <version>

#ifdef _MSC_VER
#define POLYFILL_NO_UNIQUE_ADDRESS [[msvc::no_unique_address]]
#else
#define POLYFILL_NO_UNIQUE_ADDRESS [[no_unique_address]]
#endif

namespace PCSX {

namespace PolyFill {

// MacOS / AppleClang is bad.
template <class T>
concept IntegralConcept = std::is_integral<T>::value;

template <IntegralConcept T>
static constexpr T byteSwap(T val) {
#if defined(__cpp_lib_byteswap) && (__cpp_lib_byteswap >= 202110L)
    return std::byteswap<T>(val);
#else
    if constexpr (sizeof(T) == 1) {
        return val;
    } else {
        T ret = 0;
        for (size_t i = 0; i < sizeof(T); i++) {
            ret |= static_cast<T>(static_cast<uint8_t>(val >> (i * 8)) << ((sizeof(T) - i - 1) * 8));
        }
        return ret;
    }
#endif
}

}  // namespace PolyFill

}  // namespace PCSX
