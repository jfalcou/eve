//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_ENFORCE_PRECISION_HPP_INCLUDED
#define EVE_DETAIL_ENFORCE_PRECISION_HPP_INCLUDED

namespace eve::detail
{
  
#ifdef EVE_HW_X86
  namespace x86
  {
    template<class T>
    struct x87_precision_flag;

    template<>
    struct x87_precision_flag<float>
    {
      static const unsigned short value = 0;
    };

    template<>
    struct x87_precision_flag<double>
    {
      static const unsigned short value = 2;
    };

    template<>
    struct x87_precision_flag<long double>
    {
      static const unsigned short value = 1;
    };

    EVE_FORCEINLINE unsigned short x87_get_control_word()
    {
    #ifdef _MSC_VER
      #ifndef EVE_HW_X86
      unsigned short cw;
      __asm {
        fnstcw cw
      }
      return cw;
      #else
      // FIXME: MSVC x64 doesn't support inline ASM
      return 0;
      #endif
    #elif defined(__GNUC__)
      unsigned short cw;
      __asm__ __volatile__ ("fnstcw %w0" : "=m" (cw));
      return cw;
    #else
      #error unsupported compiler to manage x87 floating-point control word
    #endif
    }

    EVE_FORCEINLINE void x87_set_control_word(unsigned short cw)
    {
    #ifdef _MSC_VER
      #ifndef EVE_HW_X86
      __asm {
        fldcw cw
      }
      #else
      // FIXME: MSVC x64 doesn't support inline ASM
      boost::ignore_unused(cw);
      #endif
    #elif defined(__GNUC__)
      __asm__ __volatile__ ("fldcw %0" : : "m" (cw));
    #else
      #error unsupported compiler to manage x87 floating-point control word
    #endif
    }
  }
  #endif

  template<class T, class Enable = void>
  struct enforce_precision
  {
    EVE_FORCEINLINE enforce_precision()
    {
    }
  };

  #if !defined(FLT_EVAL_METHOD) && defined(__FLT_EVAL_METHOD__)
  #define FLT_EVAL_METHOD __FLT_EVAL_METHOD__
  #endif

  #ifdef FLT_EVAL_METHOD
    #if FLT_EVAL_METHOD != 0
      #ifndef EVE_HAS_X87
        #define EVE_HAS_X87
      #endif
    #endif

  // default without FLT_EVAL_METHOD is to have x87 in 32-bit and no x87 in 64-bit
  // can force otherwise with EVE_NO_X87
  #elif defined(BOOST_ARCH_X86_AVAILABLE) && !defined(BOOST_ARCH_X86_64_AVAILABLE) && !defined(EVE_NO_X87)
    #ifndef EVE_HAS_X87
      #define EVE_HAS_X87
    #endif
  #endif

  #ifdef EVE_HAS_X87
  template<class T>
  struct enforce_precision<T, typename boost::enable_if< boost::is_floating_point<T> >::type>
  {
    EVE_FORCEINLINE enforce_precision() : cw(x86::x87_get_control_word())
    {
      unsigned short new_cw = (cw & 0xFCFF) | (x86::x87_precision_flag<T>::value << 8);
      x86::x87_set_control_word(new_cw);
    }

    EVE_FORCEINLINE ~enforce_precision()
    {
      x86::x87_set_control_word(cw);
    }

    unsigned short cw;
  };
#endif
}

#endif
