//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/pattern.hpp>
#include <eve/detail/idxm.hpp>

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

  template<std::ptrdiff_t G, std::ptrdiff_t... I, simd_value T, typename... Ts>
  EVE_FORCEINLINE auto operator()(pattern_t<I...> p, eve::fixed<G> g, T x, Ts... xs) const noexcept
  {
    static_assert(G <= T::size(),
                  "Group sized passed is bigger than a register, very likely a bug");
    static_assert((std::same_as<T, Ts> && ...), "You can only shuffle the same type");

    static_assert(detail::idxm::validate_pattern(
        eve::lane<G>, pattern<I...>, eve::as<T> {}, eve::as<Ts> {}...));
    return canonical_shuffle_adapter_impl(internalShuffle, p, g, x, xs...);
  }

  template<pattern_formula Gen, std::ptrdiff_t G, simd_value T, typename... Ts>
  EVE_FORCEINLINE auto operator()(Gen, eve::fixed<G> g, T x, Ts... xs) const noexcept
      -> decltype(operator()(fix_pattern<T::size() / G> (Gen {}), g, x, xs...))
  {
    return operator()(fix_pattern<T::size() / G> (Gen {}), g, x, xs...);
  }

  template<std::ptrdiff_t... I>
  EVE_FORCEINLINE auto operator()(pattern_t<I...> p, simd_value auto x, auto... xs) const noexcept
      -> decltype(operator()(p, eve::lane<1>, x, xs...))
  {
    return operator()(p, eve::lane<1>, x, xs...);
  }

  EVE_FORCEINLINE auto
  operator()(pattern_formula auto gen, simd_value auto x, auto... xs) const noexcept
      -> decltype(operator()(gen, eve::lane<1>, x, xs...))
  {
    return operator()(gen, eve::lane<1>, x, xs...);
  }
};

template<typename Internal> struct reverse_arguments
{
  Internal internal;

  template<typename... Ts> EVE_FORCEINLINE auto impl(Ts... args) const noexcept
  {
    return kumi::apply(internal, kumi::reverse(kumi::tuple {args...}));
  }

  template<typename... Ts>
  EVE_FORCEINLINE auto operator()(auto... args) const noexcept
  requires(!std::same_as<no_matching_shuffle_t, decltype(impl(args...))>)
  {
    return impl(args...);
  }
};

template<typename Internal> reverse_arguments(Internal internal) -> reverse_arguments<Internal>;

/*
 * as_canonical_shuffle is an internal function for writing platform specific
 * shuffles.
 *
 * It does the following simplifications
 *
 * * transforms the interfance to (pattern, group_size, wides...);
 * * wide logicals are converted to masks
 * * converts all types to std::uint<>_t.
 * * smaller than fundamental cardinals get padded with we_ to fundamental
 * * ups the group size if the pattern allows it ({2, 3, 0, 1} => {1, 0})
 * * ups the element size if the group size allows it: uint32x2 => uint64x1
 * * when shuffling two registers, if the result uses just one - reduce to shuffling one register
 * * when shuffling two registers, prefers a lexicographically smaller pattern:
 *    uint32x2 x 2 : {2, 0} and {0, 2} are the same shuffle, just registers swapped.
 *                   will produce {0, 2}
 */
template<typename InternalShuffle>
constexpr auto
as_canonical_shuffle(InternalShuffle internalShuffle)
{
  return reverse_arguments {canocical_shuffle_adapter_bound<InternalShuffle> {internalShuffle}};
}

// As an internal helper
template<typename T>
concept matched_shuffle = !std::same_as<no_matching_shuffle_t, T>;

}

#include <eve/detail/function/simd/common/canonical_shuffle_adapter.hpp>
