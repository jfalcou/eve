//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(signmask_, signmask);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto signmask_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = detail::value_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)
      {
        return Constant<T, 0x80000000U>();
      }
      else if constexpr(std::is_same_v<t_t, double>)
      {
        return Constant<T, 0x8000000000000000ULL>();
      }
      else if constexpr(std::is_same_v<t_t, uint8_t>)
      {
        return Constant<T, 0x80U>();
      }
      else if constexpr(std::is_same_v<t_t, uint16_t>)
      {
        return Constant<T, 0x8000U>();
      }
      else if constexpr(std::is_same_v<t_t, uint32_t>)
      {
        return Constant<T, 0x80000000U>();
      }
      else if constexpr(std::is_same_v<t_t, uint64_t>)
      {
        return Constant<T, 0x8000000000000000ULL>();
      }
      else if constexpr(std::is_same_v<t_t, int8_t>)
      {
        return Constant<T, -128>();
      }
      else if constexpr(std::is_same_v<t_t, int16_t>)
      {
        return Constant<T, -32768>();
      }
      else if constexpr(std::is_same_v<t_t, int32_t>)
      {
        return Constant<T, -2147483648LL>();
      }
      else if constexpr(std::is_same_v<t_t, int64_t>)
      {
        return Constant<T, -9223372036854775807LL - 1>();
      }
    }
  }
}
