//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_ARG_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_ARG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/pedantic.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct arg_; }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::arg_), T const&)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::arg] - No support for integral types"
                    );
    }

    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(pedantic_type, eve::tag::arg_), T const&)
    {
      static_assert ( std::is_floating_point_v<value_type_t<T>>,
                      "[eve::pedantic_(eve::arg)] - No support for integral types"
                    );
    }
  }

  EVE_MAKE_CALLABLE(arg_, arg);
}

#endif
