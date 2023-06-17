//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/pattern.hpp>

namespace eve
{
  EVE_REGISTER_CALLABLE(canonical_shuffle_adapter_impl_)
  EVE_DECLARE_CALLABLE(canonical_shuffle_adapter_impl_, canonical_shuffle_adapter_impl)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(canonical_shuffle_adapter_impl_, canonical_shuffle_adapter_impl);
  } // namespace detail

  EVE_CALLABLE_API(canonical_shuffle_adapter_impl_, canonical_shuffle_adapter_impl)
}

namespace eve::detail
{
  struct no_matching_shuffle_t
  {};
  constexpr no_matching_shuffle_t no_matching_shuffle;

  template<typename InternalShuffle> struct canocical_shuffle_adapter_bound
  {
    InternalShuffle internalShuffle;

    template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
    EVE_FORCEINLINE auto operator()(T x, eve::fixed<G> g, pattern_t<I...> p) const noexcept ->
        typename T::template rescale<eve::fixed<sizeof...(I) * G>>
    requires(!std::same_as<no_matching_shuffle_t,
                           decltype(canonical_shuffle_adapter_impl(internalShuffle, x, g, p))>)
    {
     return canonical_shuffle_adapter_impl(internalShuffle, x, g, p);
    }

    template<simd_value T, std::ptrdiff_t... I>
    EVE_FORCEINLINE auto operator()(T x, pattern_t<I...> p) const noexcept ->
      decltype(operator()(x, eve::lane<1>, p))
    {
      return operator()(x, eve::lane<1>, p);
    }
  };

  template<typename InternalShuffle>
  constexpr auto as_canonical_shuffle(InternalShuffle internalShuffle)
  {
    return canocical_shuffle_adapter_bound<InternalShuffle> {internalShuffle};
  }
}

#include <eve/detail/function/simd/common/canonical_shuffle_adapter.hpp>
