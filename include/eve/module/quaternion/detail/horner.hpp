#pragma once

#include <eve/concept/range.hpp>
#include <eve/module/core.hpp>
#include <eve/traits/common_value.hpp>

#include <concepts>
#include <iterator>

#include <initializer_list>
#include <iostream>

namespace eve::detail
{
  //================================================================================================
  //== Horner right variadic
  //================================================================================================

  // This commented implementation will be used later to implement right quaternion or octonion polynomial evaluation
  // when multiple decorators will be allowed
  //
  template<value T0, value... Cs>
  EVE_FORCEINLINE constexpr auto
  horner_impl(right_type const &, T0 const& xx, Cs... cs) noexcept
  -> common_value_t<T0, Cs...>
  {
    using r_t          = common_value_t<T0, Cs...>;
    constexpr size_t N = sizeof...(Cs);
    if constexpr( N == 0 ) return r_t(0);
    else if constexpr( N == 1 ) return (r_t(cs), ...);
    else if constexpr( N == 2 ) return fma(r_t(xx), r_t(cs)...);
    else
    {
      auto x    = r_t(xx);
      r_t  that(zero(as<r_t>()));
      auto next = [&](auto that, auto arg) { return fma(x, that, arg); };
      ((that = next(that, cs)), ...);
      return that;
    }
  }


  // This  implementation is use for left-polynomial evalution (even for quaternion or octonion)
  // it calls the default
  template<value T0, value... Cs>
  EVE_FORCEINLINE constexpr auto
  horner_impl(left_type const &, T0 const& xx, Cs... cs) noexcept
  -> common_value_t<T0, Cs...>
  {
    return horner_impl(xx, cs...);
  }
}
