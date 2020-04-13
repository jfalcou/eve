//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SINPICOSPI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SINPICOSPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/detail/generic/trig_finalize.hpp>
#include <eve/module/core/detail/generic/rem2.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/sincos.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/trigo_tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto sinpicospi_(EVE_SUPPORTS(cpu_)
                                        , restricted_type const &
                                        , T a0) noexcept
  Requires(std::tuple<T, T>, Vectorizable<T>)
  {
    return eve::restricted_(sincos)(a0*Pi<T>());
  }


  //////////////////////////////////////////////////////////////////////////////
  /// big, medium, small
  template<typename D, typename T>
  EVE_FORCEINLINE constexpr auto sinpicospi_(EVE_SUPPORTS(cpu_)
                                        , D const &
                                        , T a0) noexcept
  Requires(std::tuple<T, T>, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if (is_not_finite(a0)) return {Nan<T>(), Nan<T>()};
      const T x =  abs(a0);
      if (x > Maxflint<T>()) return {T{0}, T(1)};
      auto [fn, xr, dxr] = rem2(x);
      return sincos_finalize(bitofsign(a0), fn, xr, dxr);
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::sinpicospi scalar ] - type is not an IEEEValue");
      return T();
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto sinpicospi_(EVE_SUPPORTS(cpu_)
                                        , T const &a0) noexcept
  Requires(std::tuple<T, T>, Vectorizable<T>)
  {
    auto x =  eve::abs(a0);
    if (eve::abs(x) <= T(0.25)) return restricted_(sinpicospi)(a0);
    else                        return big_(sinpicospi)(a0);
  }

}

#endif
