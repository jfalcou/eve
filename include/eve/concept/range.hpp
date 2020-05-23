//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_RANGE_HPP_INCLUDED
#define EVE_CONCEPT_RANGE_HPP_INCLUDED

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
  concept random_access_range = range<R> && requires(R const& r)
  {
    { r[0] };
  };
}

#endif
