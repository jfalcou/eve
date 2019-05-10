//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_ARM_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_ARM_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/arm/predef.hpp>
#include <eve/ext/as_register.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

#if EVE_HW_ARM >= EVE_NEON_VERSION
namespace eve
{
  template<typename T>
  struct logical;

  namespace ext
  {
    // ---------------------------------------------------------------------------------------------
    // AARCH 64
#  if defined(__aarch64__)
    template<typename Size>
    struct as_register<double, Size, eve::neon128_, std::enable_if_t<(Size::value == 2)>>
    {
      using type = float64x2_t;
    };

    template<typename Size>
    struct as_register<double, Size, eve::neon64_, std::enable_if_t<(Size::value == 1)>>
    {
      using type = float64x1_t;
    };
#  endif

    // ---------------------------------------------------------------------------------------------
    // NEON 128
    template<typename Size>
    struct as_register<float, Size, eve::neon128_, std::enable_if_t<(Size::value == 4)>>
    {
      using type = float32x4_t;
    };

    template<typename Size>
    struct as_register<std::int64_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 2)>>
    {
      using type = int64x2_t;
    };

    template<typename Size>
    struct as_register<std::int32_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 4)>>
    {
      using type = int32x4_t;
    };

    template<typename Size>
    struct as_register<std::int16_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 8)>>
    {
      using type = int16x8_t;
    };

    template<typename Size>
    struct as_register<std::int8_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 16)>>
    {
      using type = int8x16_t;
    };

    template<typename Size>
    struct as_register<std::uint64_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 2)>>
    {
      using type = uint64x2_t;
    };

    template<typename Size>
    struct as_register<std::uint32_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 4)>>
    {
      using type = uint32x4_t;
    };

    template<typename Size>
    struct as_register<std::uint16_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 8)>>
    {
      using type = uint16x8_t;
    };

    template<typename Size>
    struct as_register<std::uint8_t, Size, eve::neon128_, std::enable_if_t<(Size::value == 16)>>
    {
      using type = uint8x16_t;
    };

    // ---------------------------------------------------------------------------------------------
    // NEON 64
    template<typename Size>
    struct as_register<float, Size, eve::neon64_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = float32x2_t;
    };

    template<typename Size>
    struct as_register<std::int64_t, Size, eve::neon64_, std::enable_if_t<(Size::value == 1)>>
    {
      using type = int64x1_t;
    };

    template<typename Size>
    struct as_register<std::int32_t, Size, eve::neon64_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = int32x2_t;
    };

    template<typename Size>
    struct as_register<std::int16_t, Size, eve::neon64_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = int16x4_t;
    };

    template<typename Size>
    struct as_register<std::int8_t, Size, eve::neon64_, std::enable_if_t<(Size::value <= 8)>>
    {
      using type = int8x8_t;
    };

    template<typename Size>
    struct as_register<std::uint64_t, Size, eve::neon64_, std::enable_if_t<(Size::value == 1)>>
    {
      using type = uint64x1_t;
    };

    template<typename Size>
    struct as_register<std::uint32_t, Size, eve::neon64_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = uint32x2_t;
    };

    template<typename Size>
    struct as_register<std::uint16_t, Size, eve::neon64_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = uint16x4_t;
    };

    template<typename Size>
    struct as_register<std::uint8_t, Size, eve::neon64_, std::enable_if_t<(Size::value <= 8)>>
    {
      using type = uint8x8_t;
    };

    // logical cases
    template<typename T, typename Size>
    struct as_register<logical<T>, Size, eve::neon128_>
        : as_register<detail::as_integer_t<T, unsigned>, Size, eve::neon128_>
    {
    };

    template<typename T, typename Size>
    struct as_register<logical<T>, Size, eve::neon64_>
        : as_register<detail::as_integer_t<T, unsigned>, Size, eve::neon64_>
    {
    };
  }
}

#endif

#endif
