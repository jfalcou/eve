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
#include <eve/module/core/regular/rotl.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve
{
  template<typename Options>
  struct rotr_t : strict_elementwise_callable<rotr_t, Options>
  {
    template<eve::unsigned_value T, eve::integral_value S>
    requires(eve::same_lanes_or_scalar<T, S>)
    constexpr EVE_FORCEINLINE as_wide_as_t<T,S> operator()(T v, S s) const
    {
      constexpr int l [[maybe_unused]] = sizeof(element_type_t<T>) * 8;
      EVE_ASSERT( detail::assert_good_shift<T>(eve::abs(s))
                , "[eve::rotr] Rotating by "  << s << " is out of the range ]" << -l << ", " << l << "[."
                );

      return EVE_DISPATCH_CALL(v,s);
    }

    template<eve::unsigned_value T, auto S>
    constexpr EVE_FORCEINLINE T operator()(T v, index_t<S> s) const
    {
      constexpr int l = sizeof(element_type_t<T>) * 8;
      static_assert(eve::abs(S) < l, "[eve::rotr] Rotation is out of range.");

      return EVE_DISPATCH_CALL(v,s);
    }

    EVE_CALLABLE_OBJECT(rotr_t, rotr_);
  };

  inline constexpr auto rotr = functor<rotr_t>;
}


namespace eve::detail
{
  template<typename T, typename S, callable_options O>
  constexpr EVE_FORCEINLINE as_wide_as_t<T,S> rotr_(EVE_REQUIRES(cpu_), O const& o, T v, S s)
  {
    using s_t = as_wide_as_t<as_integer_t<S,signed>, S>;
    return rotl_(EVE_TARGETS(cpu_),o,v,bit_cast(eve::minus(s),as<s_t>{}));
  }

  template<typename T, auto S, callable_options O>
  constexpr EVE_FORCEINLINE T rotr_(EVE_REQUIRES(cpu_), O const& o, T v, index_t<S>)
  {
    return rotl_(EVE_TARGETS(cpu_),o,v,index<-S>);
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rotr.hpp>
#endif
