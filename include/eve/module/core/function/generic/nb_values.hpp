//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_NB_VALUES_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_NB_VALUES_HPP_INCLUDED

#include <eve/detail/meta.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/module/core/detail/generic/next_kernel.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_unordered.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/signnz.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/tags.hpp>
#include <cmath>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto nb_values_(EVE_SUPPORTS(cpu_)
                                 , T const &a
                                 , U const &b) noexcept
  requires(as_integer_t<std::conditional_t<is_vectorized_v<T>, T, U>, unsigned>
          , either<std::is_same_v<U, T>
          , std::is_same_v<value_type_t<U>, T>
          , std::is_same_v<value_type_t<T>, U>>)
  {
    using v_t =  value_type_t<T>; 
    using ui_t = as_integer_t<std::conditional_t<is_vectorized_v<T>, T, U>, unsigned>; 
    if constexpr(std::is_floating_point_v<v_t>)
    {
      auto aa = eve::detail::bitinteger(a);
      auto bb = eve::detail::bitinteger(b);
      auto z = if_else (is_unordered(a, b)
                     , eve::Valmax<ui_t>()
                     , bit_cast(dist(bb, aa), as<ui_t>())
                     );
      return inc[is_ltz(signnz(a)*signnz(b))](z); 
    }
    else
      return bit_cast(dist(a, b), as<ui_t>()); 
  }
}

#endif
