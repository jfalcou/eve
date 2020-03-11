//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_TOFLOAT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_TOFLOAT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/convert.hpp>
#include <eve/detail/meta.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto tofloat_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    using vt_t = value_type_t<T>;
    if constexpr( std::is_floating_point_v<value_type_t<T>> )
    {
      return a;
    }
    else if constexpr(sizeof(vt_t) < 4)
    {
      //     auto aa = convert(a, as<int32_t>());
      return convert(a, single_);
    }
    else
    {
      return convert(a, as_<as_floating_point_t<value_type_t<T>>>());
    }
  }

  template<typename T, typename Tag>
  EVE_FORCEINLINE constexpr auto tofloat_(EVE_SUPPORTS(cpu_), Tag const& tag_, T const &a) noexcept
  {
    if constexpr( std::is_integral_v< value_type_t<T> > )
    {
      return a;
    }
    else
    {
      return Tag()(convert)(a, as_<as_floating_point_t<value_type_t<T>>>());
    }
  }
}

#endif
