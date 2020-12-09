//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/x86/predef.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
  struct x86_128_;
  struct x86_256_;
}

#if defined(EVE_HW_X86)

namespace eve
{
  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::x86_128_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width <= 16)
      {
              if constexpr(std::is_same_v<Type,double> ) return  __m128d{};
        else  if constexpr(std::is_same_v<Type,float > ) return  __m128{};
        else  if constexpr(std::is_integral_v<Type>    ) return  __m128i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::x86_256_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 32)
      {
              if constexpr(std::is_same_v<Type,double> ) return __m256d{};
        else  if constexpr(std::is_same_v<Type,float > ) return __m256{};
        else  if constexpr(std::is_integral_v<Type>    ) return __m256i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  template<typename Type, typename Size>
  struct as_register<Type, Size, eve::x86_512_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 64)
      {
              if constexpr(std::is_same_v<Type,double> ) return __m512d{};
        else  if constexpr(std::is_same_v<Type,float > ) return __m512{};
        else  if constexpr(std::is_integral_v<Type>    ) return __m512i{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  namespace detail
  {
    template<int N> struct as_mask;

    struct mask8  { __mmask8  value; };
    struct mask16 { __mmask16 value; };
    struct mask32 { __mmask32 value; };
    struct mask64 { __mmask64 value; };

    template<> struct as_mask<8>  { using type = mask8; };
    template<> struct as_mask<16> { using type = mask16; };
    template<> struct as_mask<32> { using type = mask32; };
    template<> struct as_mask<64> { using type = mask64; };

    template<int N> using as_mask_t = typename as_mask<std::max(8,N)>::type;
  }

  // logical uses different registers in AVX512
  template<typename Type, typename Size>
  struct as_register<logical<Type>, Size, eve::x86_512_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 64) return detail::as_mask_t<64/sizeof(Type)>{};
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

# if defined(SPY_SIMD_IS_X86_AVX512)
  template<typename Type, typename Size>
  struct as_register<logical<Type>, Size, eve::x86_128_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width <= 16)
      {
        if constexpr(Size::value <= 8 )  return detail::mask8{};
        if constexpr(Size::value == 16)  return detail::mask16{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

  template<typename Type, typename Size>
  struct as_register<logical<Type>, Size, eve::x86_256_>
  {
    static constexpr auto find()
    {
      constexpr auto width = sizeof(Type)*Size::value;
      if constexpr(width == 32)
      {
        if constexpr(Size::value <= 8 )  return detail::mask8{};
        if constexpr(Size::value == 16)  return detail::mask16{};
        if constexpr(Size::value == 32)  return detail::mask32{};
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve x86] - Type is not usable in a SIMD register");
  };

# else
  // logical uses same registers
  template<typename T, typename Size>
  struct as_register<logical<T>, Size, eve::x86_128_> : as_register<T, Size, eve::x86_128_>
  {
  };

  template<typename T, typename Size>
  struct as_register<logical<T>, Size, eve::x86_256_> : as_register<T, Size, eve::x86_256_>
  {
  };

# endif
}
#endif