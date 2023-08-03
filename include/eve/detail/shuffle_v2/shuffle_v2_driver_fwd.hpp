//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/pattern.hpp>
#include <eve/detail/shuffle_v2/idxm.hpp>
#include <eve/detail/shuffle_v2/shuffle_v2_helpers.hpp>

namespace eve
{

EVE_REGISTER_CALLABLE(shuffle_v2_driver_impl_)
EVE_DECLARE_CALLABLE(shuffle_v2_driver_impl_, shuffle_v2_driver_impl)

namespace detail
{
  EVE_ALIAS_CALLABLE(shuffle_v2_driver_impl_, shuffle_v2_driver_impl);
} // namespace detail

EVE_CALLABLE_API(shuffle_v2_driver_impl_, shuffle_v2_driver_impl)

template<std::ptrdiff_t G> struct not_positive_group_size
{
  using is_shuffle_user_error = void;
};

template<typename... Ts> struct cant_shuffle_different_types
{
  using is_shuffle_user_error = void;
};

template<typename Pattern, typename G, typename... Ts> struct pattern_failed_validation
{
  using is_shuffle_user_error = void;
};

}

namespace eve::detail
{

template<typename NativeSelector> struct shuffle_v2_driver
{
  NativeSelector selector;

  template<std::ptrdiff_t G, std::ptrdiff_t... I, simd_value T, typename... Ts>
  EVE_FORCEINLINE auto operator()(pattern_t<I...> p, eve::fixed<G> g, T x, Ts... xs) const noexcept
  {
    if constexpr( G <= 0 ) return not_positive_group_size<G> {};
    else if constexpr( !(std::same_as<T, Ts> && ...) )
    {
      return cant_shuffle_different_types<T, Ts...> {};
    }
    else if constexpr( !detail::idxm::validate_pattern(
                           eve::lane<G>, pattern<I...>, eve::as<T> {}, eve::as<Ts> {}...) )
    {
      return pattern_failed_validation<pattern_t<I...>, fixed<G>, T, Ts...> {};
    }
    else { return shuffle_v2_driver_impl(selector, p, g, kumi::reverse(kumi::tuple {x, xs...})); }
  }

  template<pattern_formula Gen, std::ptrdiff_t G, simd_value T, typename... Ts>
  EVE_FORCEINLINE auto operator()(Gen, eve::fixed<G> g, T x, Ts... xs) const noexcept
      -> decltype(operator()(fix_pattern<T::size() / G>(Gen {}), g, x, xs...))
  {
    return operator()(fix_pattern<T::size() / G>(Gen {}), g, x, xs...);
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

template<typename Internal> struct shuffle_reverse_arguments
{
  Internal internal;

  template<typename... Ts> EVE_FORCEINLINE auto impl(Ts... args) const noexcept
  {
    return kumi::apply(internal, kumi::reverse(kumi::tuple {args...}));
  }

  EVE_FORCEINLINE auto operator()(auto... args) const noexcept
  requires(matched_shuffle<decltype(get<0>(impl(args...)))>)
  {
    return impl(args...);
  }

  EVE_FORCEINLINE auto operator()(auto... args) const noexcept
  requires(shuffle_user_error<decltype(impl(args...))>)
  {
    auto error = impl(args...);
    static_assert(!shuffle_user_error<decltype(error)>);
    return kumi::tuple{error, eve::index<0>};
  }
};

template<typename NativeSelector>
shuffle_reverse_arguments(NativeSelector) -> shuffle_reverse_arguments<NativeSelector>;

/*
 * make_shuffle_v2 is a part of shuffle_v2 that converts native shuffle selector into
 * a complete shuffle_v2_core
 *
 * It handles the following:
 * * provide correct api to the caller
 * * emulated abi is handled
 * * bundle are shuffled by field
 * * aggregates are split
 * * multi register shuffles are split into shuffles of up to two registers.
 *   (there is more work for this - at the moment only 2 regitsers per output)
 * * extra inputs are removed (shuffle(a, b) => shuffle(b) if only elements
 *   of b are used.
 * * wide logicals are converted to masks
 * * when shuffling two registers, prefers a lexicographically smaller pattern:
 *   uint32x2 x 2 : {2, 0} and {0, 2} are the same shuffle, just registers swapped.
 *                  will produce {0, 2}
 * * converts all types to std::uint<>_t.
 * * ups the group size if the pattern allows it ({2, 3, 0, 1} => {1, 0})
 * * ups the element size if the group size allows it: uint32x2 => uint64x1
 * * smaller than fundamental cardinals get padded with we_ to fundamental
 * * calls the native selector with (pattern, group_size, wides...);
 */
template<typename NativeSelector>
constexpr auto
make_shuffle_v2(NativeSelector selector)
{
  return shuffle_reverse_arguments {shuffle_v2_driver<NativeSelector> {selector}};
}

}
