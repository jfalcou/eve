//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<real_scalar_value T, typename N, conditional_expr C>
  auto count_mask(logical<wide<T,N>> mask, C c)
  {
    if constexpr ( sizeof(T) == 2 && abi_t<T, N>::is_wide_logical )
    {
      auto shrink_bytes = eve::convert(mask, eve::as<eve::logical<std::uint8_t>>{});
      return top_bits{shrink_bytes, c}.as_int();
    }
    else
    {
      return top_bits{mask, c}.as_int();
    }
  }
}
