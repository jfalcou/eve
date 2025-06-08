//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/comparisons.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/nb_values.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve::detail
{
  template<value T, callable_options O>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_equal_(EVE_REQUIRES(cpu_), O const&, logical<T> a, logical<T> b) noexcept
  {
    if constexpr( scalar_value<T> ) return as_logical_t<T>(a == b);
    else                            return bit_cast( is_equal(a.bits(), b.bits()), as(a));
  }

  template<value T, callable_options O>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_equal_(EVE_REQUIRES(cpu_), O const & o, T const& a, T const& b) noexcept
  {
    if constexpr( kumi::product_type<element_type_t<T>> )
    {
      if constexpr( has_comparison_support<T> ) return comparisons<T>::equal(o, a,b);
      else                                      return a.storage() == b.storage();
    }
    else if constexpr(O::contains(almost))
    {
      using l_t = as_logical_t<T>;
      auto tol = o[almost].value(T{});
      using t_t = decltype(tol);

      if constexpr(integral_value<t_t>) return if_else(nb_values(a, b) <= tol, true_(as<l_t>()), false_(as<l_t>())) ;
      else                              return dist[pedantic](a, b) <= tol * max(eve::abs(a), eve::abs(b));
    }
    else if constexpr(O::contains(numeric))
    {
      auto tmp  = is_equal(a, b);
      if constexpr( floating_value<T> ) tmp = tmp || (is_nan(a) && is_nan(b));
      return tmp;
    }
    else
    {
      if constexpr(scalar_value<T>) return as_logical_t<T>(a == b);
      else                          return apply_over ( []<typename E>(E const& e, E const& f)
                                                        { return as_logical_t<E>(e == f); }
                                                      , a, b
                                                      );
    }
  }
}
