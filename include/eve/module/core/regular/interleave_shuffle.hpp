//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/function/interleave.hpp>
#include <eve/traits/overload.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>

//TODO doc
namespace eve
{
  template<typename Options>
  struct interleave_shuffle_t : callable<interleave_shuffle_t, Options>
  {
    template<typename T, typename U>
    static constexpr auto r_t() noexcept {
      if constexpr (simd_value<T>) return typename T::combined_type{};
      else                         return typename U::combined_type{};
    }

    template<value T, value U>
    EVE_FORCEINLINE decltype(r_t<T, U>()) operator()(T v, U w) const noexcept
      requires (same_lanes_or_scalar<T, U> && (simd_value<T> || simd_value<U>))
    {
      return EVE_DISPATCH_CALL_PT((decltype(r_t<T, U>())), v, w);
    }

    EVE_CALLABLE_OBJECT(interleave_shuffle_t, interleave_shuffle_);
  };

  inline constexpr auto interleave_shuffle = functor<interleave_shuffle_t>;

  namespace detail
  {
    template<callable_options O, typename T, typename U>
    EVE_FORCEINLINE auto interleave_shuffle_(EVE_REQUIRES(cpu_), O const&, T a, U b) noexcept
    {
      if constexpr (scalar_value<T>)      return interleave_shuffle(U{a}, b);
      else if constexpr (scalar_value<U>) return interleave_shuffle(a, T{b});
      else
      {
        auto [ l, h ] = interleave(a, b);
        return typename T::combined_type { l, h };
      }
    }
  }
}
