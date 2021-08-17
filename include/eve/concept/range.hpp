//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <iterator>
#include <type_traits>

namespace eve::detail
{
  template<typename R> concept range = requires(R const& r)
  {
    { std::begin(r) };
    { std::end(r)   };
  };

  template<typename R>
  concept has_random_access = requires(R const& r)
  {
    { r[0] };
  };

  template<typename R>
  concept has_indexed_get = requires(R const& r)
  {
    { r.get(0) };
  };

  template<typename R>
  concept random_access_range = range<R> && has_random_access<R>;
}
