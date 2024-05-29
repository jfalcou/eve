//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/assert.hpp>
#include <eve/traits/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/abs.hpp>

namespace eve
{
  template<typename Options>
  struct rotl_t : strict_elementwise_callable<rotl_t, Options>
  {
    template<eve::unsigned_value T, eve::integral_value S>
    requires(eve::same_lanes_or_scalar<T, S>)
    constexpr EVE_FORCEINLINE as_wide_as_t<T,S> operator()(T v, S s) const
    {
      constexpr int l [[maybe_unused]] = sizeof(element_type_t<T>) * 8;
      EVE_ASSERT( detail::assert_good_shift<T>(eve::abs(s))
                , "[eve::rotl] Rotating by "  << s << " is out of the range ]" << -l << ", " << l << "[."
                );

      return EVE_DISPATCH_CALL(v, s);
    }

    template<eve::unsigned_value T, auto S>
    constexpr EVE_FORCEINLINE T operator()(T v, index_t<S> s) const
    {
      constexpr int l = sizeof(element_type_t<T>) * 8;
      static_assert(eve::abs(S) < l, "[eve::rotl] Rotation is out of range.");

      return EVE_DISPATCH_CALL(v, s);
    }

    EVE_CALLABLE_OBJECT(rotl_t, rotl_);
  };

  inline constexpr auto rotl = functor<rotl_t>;
}

#include <eve/module/core/regular/impl/rotl.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rotl.hpp>
#endif
