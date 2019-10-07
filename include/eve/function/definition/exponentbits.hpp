//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_EXPONENTBITS_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_EXPONENTBITS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/pedantic.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct exponentbits_; }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::exponentbits_), T const&)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::exponentbits] - No support for integral types"
                    );
    }

    template<typename T>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::exponentbits_), pedantic_type const&, T const&)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::pedantic_(eve::exponentbits)] - No support for integral types"
                    );
    }
  }

  EVE_MAKE_CALLABLE(exponentbits_, exponentbits);
}

#endif
