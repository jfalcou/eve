//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct div_180_t : elementwise_callable<div_180_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(div_180_t, div_180_);
  };

  inline constexpr auto div_180 = functor<div_180_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T div_180_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      auto test = is_nez(a);
      if constexpr( scalar_value<T> )
      {
        if( !test ) return a;
      }
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, double> )
      {
        const T Ch = T(5.5555555555555557675773137304986448725685477256775e-3);
        const T Cl = T(2.12021758174943082362265970771770243087787985109985e-19);
        T c  = Cl * a;
        return fma[test](a, Ch, c);
      }
      else { return convert(div_180(convert(a, as<double>())), as<float>()); }
    }
  }
}
