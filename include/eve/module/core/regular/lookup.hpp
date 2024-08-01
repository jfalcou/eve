/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/same_lanes.hpp>

//DOC TODO
namespace eve
{
  template<typename Options>
  struct lookup_t : callable<lookup_t, Options>
  {
    template<simd_value V, integral_simd_value I>
    requires( same_lanes<V,I> )
    constexpr EVE_FORCEINLINE V operator()(V v, I i) const noexcept { return EVE_DISPATCH_CALL(v,i); }

    EVE_CALLABLE_OBJECT(lookup_t, lookup_);
//================================================================================================
  inline constexpr auto lookup = functor<lookup_t>;
//================================================================================================
  };

}

#include <eve/module/core/regular/impl/lookup.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/lookup.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/lookup.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/lookup.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/lookup.hpp>
#endif
