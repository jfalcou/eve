//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MAXLOG10_HPP_INCLUDED
#define EVE_CONSTANT_MAXLOG10_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
/*
   if T is double
      r = 308.2547155599167;
    else if T is float
      r = 38.23080825805664;
*/
namespace eve
{
  EVE_MAKE_CALLABLE(maxlog10_, maxlog10_);

  template<typename T>
  constexpr EVE_FORCEINLINE auto Maxlog10(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x4218ec59U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x40734413509f79feULL>();
    if constexpr(std::is_same_v<t_t, int8_t>) return T(2);
    if constexpr(std::is_same_v<t_t, int16_t>) return T(4);
    if constexpr(std::is_same_v<t_t, int32_t>) return T(9);
    if constexpr(std::is_same_v<t_t, int64_t>) return T(18); 
    if constexpr(std::is_same_v<t_t, uint8_t>) return T(2);
    if constexpr(std::is_same_v<t_t, uint16_t>) return T(4);
    if constexpr(std::is_same_v<t_t, uint32_t>) return T(9);
    if constexpr(std::is_same_v<t_t, uint64_t>) return T(19); 
  }

  EVE_MAKE_NAMED_CONSTANT(maxlog10_, Maxlog10);
}

#endif
