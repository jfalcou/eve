//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/constant.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(sqrtvalmax_, sqrtvalmax);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr  auto sqrtvalmax_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = detail::value_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)              {
        return Constant<T, 0x5f7FFFFEU>(); }
      else if constexpr(std::is_same_v<t_t, double>)        {
        return Constant<T, 0X5FEFFFFFFFFFFFFFULL>(); }
      else if constexpr(std::is_same_v<t_t, std::uint8_t>)  {
        return T(15); }
      else if constexpr(std::is_same_v<t_t, std::uint16_t>) {
        return T(255); }
      else if constexpr(std::is_same_v<t_t, std::uint32_t>) {
        return T(65535); }
      else if constexpr(std::is_same_v<t_t, std::uint64_t>) {
        return T(4294967296ULL); }
      else if constexpr(std::is_same_v<t_t, std::int8_t>)   {
        return T(11); }
      else if constexpr(std::is_same_v<t_t, std::int16_t>)  {
        return T(181); }
      else if constexpr(std::is_same_v<t_t, std::int32_t>)  {
        return T(46340); }
      else if constexpr(std::is_same_v<t_t, std::int64_t>)  {
        return T(3037000499LL); }
    }
  }
}
