//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/detail/convert.hpp>
#include <eve/algo/preprocess_range.hpp>

namespace eve::algo
{
  template <is_range_ref<range_ref> R, typename T>
  struct converting_range
  {
    R rng;

    EVE_FORCEINLINE explicit converting_range(R r) : r(r) {}

    EVE_FORCEINLINE auto begin() const
    {
      return convert(r.begin(), eve::as<T>);
    }

    EVE_FORCEINLINE auto end() const
    {
      return convert(r.end(), eve::as<T>);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(preprocess_range_, converting_range self)
    {
      return convert(preprocess_range(self.r), eve::as<T>{});
    }
  };
}
