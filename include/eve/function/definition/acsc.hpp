//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_ACSC_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_ACSC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct acsc_; }
  
  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::acsc_), T const&)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::acsc] - No support for integral types"
                    );
    }
  }
  
  EVE_MAKE_CALLABLE(acsc_, acsc);
}

#endif
