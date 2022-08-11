//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/combine.hpp>
#include <eve/module/core/regular/shuffle.hpp>
#include <eve/module/core/regular/interleave.hpp>
#include <eve/product_type.hpp>
#include <eve/traits/as_wide.hpp>

#include <bit>

namespace eve::detail
{
//================================================================================================
//  scalar<->scalar convert
template<scalar_value In, scalar_value Out>
requires(!product_type<In> && !product_type<Out>) EVE_FORCEINLINE
    auto convert_(EVE_SUPPORTS(cpu_), In v0, as<Out> const&) noexcept
{
  if constexpr( std::same_as<In, Out> ) return v0;
  else return static_cast<Out>(v0);
}

//================================================================================================
// tuple<->tuple convert
struct convert_lambda
{
  template<typename T, typename M>
  EVE_FORCEINLINE constexpr void operator()(T const& in, M *res_m) const noexcept
  {
    *res_m = eve::convert(in, eve::as<element_type_t<M>> {});
  }
};

template<product_type T, product_type U>
requires(kumi::result::flatten_all_t<T>::size()
         == kumi::result::flatten_all_t<U>::size()) EVE_FORCEINLINE
    auto convert_(EVE_SUPPORTS(cpu_), T const& v0, eve::as<U>)
{
  if constexpr( std::same_as<element_type_t<T>, U> ) { return v0; }
  else
  {
    using out_t = std::conditional_t<scalar_value<T>, U, as_wide_t<U, cardinal_t<T>>>;
    out_t res;

    auto outs = kumi::flatten_all(res, [](auto& m) { return &m; });
    auto ins  = kumi::flatten_all(v0);

    kumi::for_each(convert_lambda {}, ins, outs);

    return res;
  }
}

//================================================================================================
// logical<->logical convert
template<value In, scalar_value Out>
EVE_FORCEINLINE auto
convert_(EVE_SUPPORTS(cpu_),
         logical<In> const                      & v,
         [[maybe_unused]] as<logical<Out>> const& tgt) noexcept
{
  constexpr auto is_wide_logical = In::abi_type::is_wide_logical;
  using out_t                    = as_wide_t<logical<Out>, cardinal_t<logical<In>>>;

  if constexpr( std::same_as<element_type_t<In>, Out> ) return v;
  else if constexpr( scalar_value<In> ) return static_cast<logical<Out>>(v.bits());
  else if constexpr( is_wide_logical )
  {
    using in_t = element_type_t<In>;

    if constexpr( sizeof(Out) == sizeof(in_t) ) return bit_cast(v, as<out_t> {});
    else if constexpr( std::is_unsigned_v<in_t> || std::is_floating_point_v<in_t> )
    {
      using i_t = as<logical<wide<as_integer_t<in_t, signed>, cardinal_t<logical<In>>>>>;
      return convert(bit_cast(v, i_t {}), tgt);
    }
    else if constexpr( std::is_unsigned_v<Out> || std::is_floating_point_v<Out> )
    {
      using i_t = as<logical<as_integer_t<Out, signed>>>;
      return bit_cast(convert(v, i_t {}), as<out_t> {});
    }
    else return convert_impl(EVE_RETARGET(current_api_type), v, tgt);
  }
  else if constexpr( has_aggregated_abi_v<In> || has_aggregated_abi_v<out_t> )
  {
    // If input or output are aggregated, we slice and combine without lose of performance
    return out_t {eve::convert(v.slice(lower_), tgt), eve::convert(v.slice(upper_), tgt)};
  }
  else
  {
    //  For non-wide logical, we only have to convert kmask
    using s_t = typename out_t::storage_type;
    return out_t(s_t {static_cast<typename s_t::type>(v.storage().value)});
  }
}

//================================================================================================
// logical<->logical default convert implementation
template<value In, scalar_value Out>
EVE_FORCEINLINE auto
convert_impl(EVE_SUPPORTS(cpu_),
             logical<In> const                      & v0,
             [[maybe_unused]] as<logical<Out>> const& tgt) noexcept
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
EVE_FORCEINLINE auto
convert_impl(EVE_SUPPORTS(cpu_), In const& v0, as<Out> const& tgt) noexcept
{
  using out_t = as_wide_t<Out, cardinal_t<In>>;

  if constexpr( has_aggregated_abi_v<In> )
  {
    // If input is aggregated, we can slice and combine without lose of performance
    return out_t {eve::convert(v0.slice(lower_), tgt), eve::convert(v0.slice(upper_), tgt)};
  }
  else { return map(convert, v0, tgt); }
}

template<simd_value In, scalar_value Out>
requires(!product_type<In> && !product_type<Out>) EVE_FORCEINLINE
    auto convert_(EVE_SUPPORTS(cpu_), In const& v0, as<Out> const& tgt) noexcept
{
  using in_t  = element_type_t<In>;
  using out_t = element_type_t<Out>;

  // Converting T to T is identity
  if constexpr( std::same_as<in_t, Out> ) { return v0; }
  else
  {
    // Converting between integral of different signs is just a bit_cast away
    if constexpr( std::signed_integral<in_t> && std::unsigned_integral<out_t> )
    {
      auto s_res = convert(v0, eve::as<std::make_signed_t<out_t>> {});
      return bit_cast(s_res, eve::as<wide<Out, cardinal_t<In>>> {});
    }
    else if constexpr( std::unsigned_integral<in_t> && std::signed_integral<out_t> )
    {
      auto u_res = convert(v0, eve::as<std::make_unsigned_t<out_t>> {});
      return bit_cast(u_res, eve::as<wide<Out, cardinal_t<In>>> {});
    }
    else
    {
      // Fallbacks to architecture-specific cases
      return convert_impl(EVE_RETARGET(current_api_type), v0, tgt);
    }
  }
}

// Convert helpers : large<->small integers via chain
template<integral_simd_value In, integral_scalar_value Out>
EVE_FORCEINLINE auto
convert_integers_chain(In const& v0, as<Out> const& tgt) noexcept
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
EVE_FORCEINLINE auto
convert_integers_shuffle(wide<T, N> v, as<U> const&) noexcept
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

// Convert helper : sign extension
template<typename T>
EVE_FORCEINLINE auto
sign_extend(T v) noexcept
{
  if constexpr( std::is_signed_v<element_type_t<T>> ) return (v < 0).mask();
  else return zero(as(v));
}

template<typename T, typename N, typename U>
EVE_FORCEINLINE auto
convert_slice(wide<T, N> v, as<U> const& tgt)
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
EVE_FORCEINLINE auto
convert_integers_interleave(wide<T, N> v, as<U> const&)
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
