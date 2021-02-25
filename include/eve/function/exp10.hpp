//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/assert.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/maxlog10.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct exp10_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp10_), T const&, [[maybe_unused]] S const& s)
    {
      using vt_t = value_type_t<T>;
      if constexpr(std::is_integral_v<vt_t>)
      {
        EVE_ASSERT( eve::all(is_gez(s)),
                    "[eve::exp10] - with integral entries the parameter element(s) must be greater then 0"
                  );
        EVE_ASSERT( eve::all(is_less(s, maxlog10(eve::as<T>()))),
                    "[eve::exp10]  - overflow caused by too large integral entry"
                  );
      }
    }
  }

  EVE_MAKE_CALLABLE(exp10_, exp10);
}

#include <eve/module/real/math/function/regular/generic/exp10.hpp>
