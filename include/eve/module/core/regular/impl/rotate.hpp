//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/swap_adjacent_groups.hpp>
#include <eve/module/core/regular/slide_right.hpp>

namespace eve::detail
{

template<std::ptrdiff_t M> struct rotate_lambda
{
  EVE_FORCEINLINE auto operator()(auto x) const { return rotate(x, index<M>); }
};


template<simd_value T, std::ptrdiff_t M>
EVE_FORCEINLINE T rotate_(EVE_SUPPORTS(cpu_), T x, index_t<M>)
  requires (M <= T::size())
{
       if constexpr ( M == T::size() || M == 0 ) return x;
  else if constexpr ( M == T::size() / 2       ) return swap_adjacent_groups(x, eve::lane<T::size() / 2>);
  else if constexpr ( is_bundle_v<typename T::abi_type> )
  {
    return T(kumi::map(rotate_lambda<M>{}, x));
  }
  else return slide_right(x, x, index<T::size() - M>);
}

}
