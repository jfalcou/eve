//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/combine.hpp>
#include <eve/module/core/regular/interleave.hpp>
#include <eve/module/core/regular/shuffle.hpp>

#include <eve/traits/product_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/as_element.hpp>

#include <bit>

namespace eve::detail
{

template<value In, scalar_value Out>
EVE_FORCEINLINE auto convert_saturated(EVE_REQUIRES(cpu_), In v0, as<Out> tgt) noexcept
{
  return convert(saturate(v0, tgt), tgt);
}

//================================================================================================
// tuple<->tuple convert
template <callable_options Options>
struct convert_lambda
{
  Options const& opts;

  template <typename T, typename M>
  EVE_FORCEINLINE constexpr void operator()(T const& in, M *res_m) const noexcept
  {
    *res_m = eve::convert[opts](in, eve::as_element<M>{});
  }
};

template <callable_options O, typename Tgt>
struct maybe_saturated
{
  template <typename T>
  EVE_FORCEINLINE constexpr auto operator()(T const& v) const noexcept
  {
    if constexpr (O::contains(saturated2)) return saturate(v, as<Tgt>{});
    else                                   return v;
  }
};

//================================================================================================
// logical<->logical default convert implementation
template<value In, scalar_value Out>
EVE_FORCEINLINE auto convert_impl(EVE_REQUIRES(cpu_), logical<In> v0, [[maybe_unused]] as<logical<Out>> tgt) noexcept
{
  using out_t = as_wide_t<logical<Out>, cardinal_t<In>>;

  if constexpr( has_aggregated_abi_v<In> )
  {
    // If input is aggregated, we can slice and combine without lose of performance
    return out_t {eve::convert(v0.slice(lower_), tgt), eve::convert(v0.slice(upper_), tgt)};
  }
  else
  {
    using s_in_t  = std::make_signed_t<typename logical<In>::bits_type::value_type>;
    using v_int_t = typename logical<In>::bits_type::template rebind<s_in_t, cardinal_t<out_t>>;
    using s_out_t = std::make_signed_t<typename logical<Out>::bits_type>;

    // Just convert the bit and bitcast back to the proper output
    return bit_cast(convert(bit_cast(v0.bits(), as<v_int_t> {}), as<s_out_t> {}), as<out_t> {});
  }
}

//================================================================================================
// wide<->wide convert

//================================================================================================
// wide<->wide default convert implementation
template<typename In, typename Out>
EVE_FORCEINLINE auto convert_impl(EVE_REQUIRES(cpu_), In v0, as<Out> tgt) noexcept
{
  using out_t = as_wide_t<Out, cardinal_t<In>>;

  if constexpr( has_aggregated_abi_v<In> )
  {
    // If input is aggregated, we can slice and combine without lose of performance
    return out_t {eve::convert(v0.slice(lower_), tgt), eve::convert(v0.slice(upper_), tgt)};
  }
  else { return map(convert, v0, tgt); }
}

//================================================================================================
// Convert helpers
// large<->small integers via chain
template<integral_simd_value In, integral_scalar_value Out>
EVE_FORCEINLINE auto convert_integers_chain(In v0, as<Out> tgt) noexcept
{
  using in_t  = element_type_t<In>;
  using out_t = element_type_t<Out>;

  // Convert from large to very small is a chain of downward convert
  if constexpr( sizeof(in_t) / sizeof(out_t) > 2 )
  {
    using s_t    = std::conditional_t<std::is_signed_v<in_t>, signed, unsigned>;
    using next_t = make_integer_t<sizeof(in_t) / 2, s_t>;
    return convert(convert(v0, as<next_t> {}), tgt);
  }
  // Convert from small to very large is a chain of upward convert
  else if constexpr( sizeof(out_t) / sizeof(in_t) > 2 )
  {
    using s_t    = std::conditional_t<std::is_signed_v<in_t>, signed, unsigned>;
    using next_t = make_integer_t<sizeof(in_t) * 2, s_t>;
    return convert(convert(v0, as<next_t> {}), tgt);
  }
  else { return bit_cast(v0, as<wide<Out, typename In::cardinal_type>> {}); }
}

// Convert helpers : large->small integers via a single shuffle
template<integral_scalar_value T, integral_scalar_value U, typename N>
EVE_FORCEINLINE auto convert_integers_shuffle(wide<T, N> v, as<U>) noexcept
{
  static_assert((sizeof(T) / sizeof(U) >= 2),
                "[eve::convert] - Shuffle conversion requires ration of 1:2^n between types");

  constexpr auto shuffler = as_pattern {
      [](auto i, auto c)
      {
        // Take one element out of every sizing step + endian support
        constexpr auto factor = sizeof(T) / sizeof(U);
        constexpr auto shift  = (std::endian::native == std::endian::little) ? 0 : (factor - 1);
        std::ptrdiff_t idx    = (i * factor) + shift;
        return (idx < c) ? idx : i;
      }};

  using c_t = fixed<N::value * sizeof(T) / sizeof(U)>;
  return bit_cast(shuffle(bit_cast(v, as<wide<U, c_t>> {}), shuffler), as<wide<U, N>> {});
}

template<typename T, typename N, typename U>
EVE_FORCEINLINE auto convert_slice(wide<T, N> v, as<U> tgt)
{
  if constexpr( N::value > 1 )
  {
    auto [l, h] = v.slice();
    return wide<U, N>(convert(l, tgt), convert(h, tgt));
  }
  else return map(convert, v, tgt);
}

// Convert integer from 2^n -> 2^n+1
template<typename T, typename N, typename U>
EVE_FORCEINLINE auto convert_integers_interleave(wide<T, N> v, as<U>)
{
  static_assert((sizeof(U) / sizeof(T) == 2),
                "[eve::convert] - Interleave conversion requires ration of 2:1 between types");

  if constexpr( N::value == 1 ) { return wide<U, N> {static_cast<U>(v.get(0))}; }
  else
  {
    auto pieces = [](auto w)
    {
      if constexpr( std::endian::native == std::endian::little )
      {
        if constexpr( std::is_signed_v<T> ) return eve::interleave(w, (w < 0).mask());
        else return eve::interleave(w, zero(as(w)));
      }
      else
      {
        if constexpr( std::is_signed_v<T> ) return eve::interleave((w < 0).mask(), w);
        else return eve::interleave(zero(as(w)), w);
      }
    };

    auto [l, h] = pieces(v);
    eve::wide<U, N> that {eve::bit_cast(l, eve::as<eve::wide<U, typename N::split_type>> {}),
                          eve::bit_cast(h, eve::as<eve::wide<U, typename N::split_type>> {})};
    return that;
  }
}
}
