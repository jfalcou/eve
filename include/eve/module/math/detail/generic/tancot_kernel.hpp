//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  tancot_eval(const T& z) noexcept
  {
    // here T is float or double and z positive
    static_assert(std::is_floating_point_v<element_type_t<T>>,
                  "[detail;:tan_kernel] - entry type is not IEEEValue");
    if constexpr( std::is_same_v<element_type_t<T>, float> )
    {
      T zz = eve::sqr(z);
      return fma(eve::reverse_horner(zz, T(0x1.5554dep-2f), T(0x1.112dbap-3f), T(0x1.b58b92p-5f)
                                    , T(0x1.90436ap-6f), T(0x1.98ef38p-9f), T(0x1.338a76p-7f)) , zz*z, z);
    }
    else if constexpr( std::is_same_v<element_type_t<T>, double> )
    {
      T       zz  = sqr(z);
      const T num =
        eve::reverse_horner(zz, T(-0x1.11fead3299176p+24), T(0x1.199eca5fc9dddp+20), T(-0x1.992d8d24f3f38p+13))
        ;
    T       den =
    eve::reverse_horner(zz, T(-0x1.9afe03cbe5a31p+25), T(0x1.7d98fc2ead8efp+24)
                       , T(-0x1.427bc582abc96p+20), T(0x1.ab8a5eeb36572p+13), T(0x1.0p0));
    return fma(z, (zz * (num / den)), z);
    }
  }
}
