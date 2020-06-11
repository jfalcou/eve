//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/all.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct exp2_; }

  template<>
  struct supports_optimized_conversion<tag::exp2_> : std::true_type {};

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp2_), T const& ,  [[maybe_unused]] S const& s)
    {
      using vt_t = value_type_t<T>;
      if constexpr(std::is_integral_v<vt_t>)
      {
        EVE_ASSERT( all(is_gez(s)),
                    "[eve::exp2] - with integral entries the parameter element(s) must be greater then 0"
                  );
        EVE_ASSERT( all(is_less(s, sizeof(vt_t)*8-std::is_signed_v<vt_t>)),
                    "[eve::exp2]  - overflow caused by too large integral entry"
                  );
      }
    }
  }

  EVE_MAKE_CALLABLE(exp2_, exp2);
}
