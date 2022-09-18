//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/complex/regular/traits.hpp>

namespace eve
{

  namespace detail
  {
    template<unsigned_scalar_value K, typename Z>
    EVE_FORCEINLINE auto complex_binary_dispatch( tag::deta_
                                                , K const & kk, Z const& z) noexcept
    {
      using real_t = decltype(real(z));
      auto k = r_t(kk);
      return z*k;
    }
  }
}
