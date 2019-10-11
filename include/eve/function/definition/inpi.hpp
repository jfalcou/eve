//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_INPI_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_INPI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve
{
 namespace tag { struct inpi_; }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::inpi_), T const&)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::inpi] - No support for integral types"
                    );
    }
  }

  EVE_MAKE_CALLABLE(inpi_, inpi);
}

#endif
