//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload/supports.hpp>
#include <eve/traits/overload/default_behaviors.hpp>

#include <eve/detail/function/simd/common/bit_cast.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/bit_cast.hpp>
#endif

namespace eve::detail
{
  template<typename T, typename Target>
  requires (sizeof(T) == sizeof(Target))
  EVE_FORCEINLINE constexpr Target bit_cast(T const& a, as<Target> tgt) noexcept
  {
    return detail::bit_cast_impl(current_api, a, tgt);
  }
}
