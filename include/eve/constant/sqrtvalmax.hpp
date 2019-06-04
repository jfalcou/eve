//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_SQRTVALMAX_HPP_INCLUDED
#define EVE_CONSTANT_SQRTVALMAX_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/constant/constant.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(sqrtvalmax_, sqrtvalmax_);

  template<typename T>
  EVE_FORCEINLINE auto Sqrtvalmax(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;
    if constexpr(std::is_same_v<t_t, float>) return Constant<T,0x5f7FFFFEU>(); 
    if constexpr(std::is_same_v<t_t, double>)return Constant<T,0X5FEFFFFFFFFFFFFFULL>();
    if constexpr(std::is_same_v<t_t, std::uint8_t>) return T(15); 
    if constexpr(std::is_same_v<t_t, std::uint16_t>) return T(255); 
    if constexpr(std::is_same_v<t_t, std::uint32_t>) return T(65535); 
    if constexpr(std::is_same_v<t_t, std::uint64_t>) return T(4294967296ULL); 
    if constexpr(std::is_same_v<t_t, std::int8_t>) return T(11); 
    if constexpr(std::is_same_v<t_t, std::int16_t>) return T(181); 
    if constexpr(std::is_same_v<t_t, std::int32_t>) return T(46340); 
    if constexpr(std::is_same_v<t_t, std::int64_t>) return T(3037000499LL); 
  }

  EVE_MAKE_NAMED_CONSTANT(sqrtvalmax_, Sqrtvalmax);
}

#endif
