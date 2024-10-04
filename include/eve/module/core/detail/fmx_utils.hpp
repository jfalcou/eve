//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits.hpp>

namespace eve::detail
{
  //todo: simplify
  template <typename W, typename... Ts>
  using fmx_erw_t = as_wide_as_t<common_type_t<element_type_t<Ts>...>, W>;

  template <typename T, typename U, typename V>
  using fmx_promote_rt = common_value_t<fmx_erw_t<T, T, U, V>, fmx_erw_t<U, T, U, V>, fmx_erw_t<V, T, U, V>>;
}
