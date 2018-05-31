//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_ABI_HPP_INCLUDED
#define EVE_ARCH_X86_ABI_HPP_INCLUDED

#include <cstddef>
#include <climits>
#include <type_traits>

//==================================================================================================
/**
  As MSVC doesn't have /ARCH: option for each extension in the SSE family, the EVE_ASSUME_* macros
  helps user to specify which sub-SSE* ABI is desirable
**/
//==================================================================================================
#if defined(_MSC_VER)
  #if defined(EVE_ASSUME_SSE3)
    #define __SSE3__
  #endif
  #if defined(EVE_ASSUME_SSSE3)
    #define __SSSE3__
  #endif
  #if defined(EVE_ASSUME_SSE4_1)
    #define __SSE4_1__
  #endif
  #if defined(EVE_ASSUME_SSE4_2)
    #define __SSE4_2__
  #endif
  #if defined(EVE_ASSUME_SSE4A)
    #define __SSE4A__
  #endif
  #if defined(EVE_ASSUME_XOP)
    #define __XOP__
  #endif
  #if defined(EVE_ASSUME_FMA4)
    #define __FMA4__
  #endif
  #if defined(EVE_ASSUME_FMA3)
    #define __FMA3__
  #endif
#endif

namespace eve
{
  //================================================================================================
  // X86 SIMD Extension ABI Detection
  //================================================================================================
  enum class abi_ { scalar_ = -1
                  , mmx_    =  10
                  , sse1_   = 100, sse2_    = 200
                  , sse3_   = 300, ssse3_   = 310
                  , sse4_1_ = 410, sse4_2_  = 420
                  , avx_    = 500, avx2_    = 600
                  , avx512_ = 700
                  };

  template<abi_ ABI, std::size_t Bits> struct abi_info
  {
    static constexpr abi_         abi           = ABI;
    static constexpr std::size_t  register_size = Bits;
    static constexpr std::size_t  size          = Bits/CHAR_BIT;

    template<typename Type>
    using cardinal = std::integral_constant<std::size_t, size/sizeof(Type)>;
   };

#if defined(__AVX512F__)
  using current_abi = abi_info<abi::avx512_,512> ;
#elif defined(__AVX2__)
  using current_abi = abi_info<abi::avx2_,256>;
#elif defined(__AVX__)
  using current_abi = abi_info<abi::avx_,256>;
#elif defined(__SSE4_2__)
  using current_abi = abi_info<abi::sse4_2_,128>;
#elif defined(__SSE4_1__)
  using current_abi = abi_info<abi::sse4_1_,128>;
#elif defined(__SSSE3__)
  using current_abi = abi_info<abi::ssse3_,128>;
#elif defined(__SSE3__)
  using current_abi = abi_info<abi::sse3_,128>;
#elif (defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2))
  using current_abi = abi_info<abi::sse2_,128>;
#elif(defined(__SSE__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 1))
  using current_abi = abi_info<abi::sse1_,128>;
#elif defined(__MMX__)
  using current_abi = abi_info<abi::mmx_,64>;
#else
  using current_abi = abi_info<abi::scalar_,128>;
#endif

  //================================================================================================
  // X86 SIMD Extension Options Detection
  //================================================================================================
#if defined(__SSE4A__)
  inline constexpr bool supports_sse4a = true;
#else
  inline constexpr bool supports_sse4a = false;
#endif

#if defined(__XOP__)
  inline constexpr bool supports_xop = true;
#else
  inline constexpr bool supports_xop = false;
#endif

#if defined(__FMA__)
  inline constexpr bool supports_fma3 = true;
#else
  inline constexpr bool supports_fma3 = false;
#endif

#if defined(__FMA4__)
  inline constexpr bool supports_fma4 = true;
#else
  inline constexpr bool supports_fma4 = false;
#endif
}

#endif
