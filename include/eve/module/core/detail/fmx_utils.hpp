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
  template <typename W, typename... Ts>
  using fmx_rpart_t = as_wide_as_t<common_type_t<element_type_t<Ts>...>, W>;

  template <typename T, typename U, typename V>
  using fmx_common_promote_t = common_value_t<fmx_rpart_t<T, T, U, V>, fmx_rpart_t<U, T, U, V>, fmx_rpart_t<V, T, U, V>>;
}
