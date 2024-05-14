//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/count_true.hpp>

namespace eve::detail
{

template<callable_options O, typename L, typename F>
EVE_FORCEINLINE bool
iterate_selected_(EVE_REQUIRES(sve_), O const& opts, top_bits<L> l, F&& f)
requires(L::size() > 1 && !top_bits<L>::is_aggregated)
{
  auto ignore = opts[condition_key];
  if constexpr( !std::same_as<decltype(ignore), ignore_none_> )
  {
    return iterate_selected[ignore_none](l & top_bits<L>{ignore}, f);
  }
  else
  {
    auto m = l.storage;
    while( any(m) )
    {
      L ignored_before = svbrka_z(sve_true<element_type_t<L>>(), m);
      m = svbic_z(sve_true<element_type_t<L>>(), m, ignored_before);
      if (f(count_true(ignored_before) - 1)) {
        return true;
      }
    }
    return false;
  }
}

}
