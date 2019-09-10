//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_CONJ_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_CONJ_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct conj_; }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::conj_), T const&)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::conj] - No support for integral types"
                    );
    }
  }

  EVE_MAKE_CALLABLE(conj_, conj);
}

#endif
