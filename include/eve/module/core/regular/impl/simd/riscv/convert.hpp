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
#include <eve/detail/category.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(rvv_), wide<T, N> const                &v, as<U> const                &tgt) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) == sizeof(U))
{
  constexpr auto in_c  = categorize<wide<T, N>>();
  constexpr auto out_c = categorize<wide<U, N>>();
  if constexpr( match(in_c, category::float_) )
  {
    if constexpr( match(out_c, category::int_) ) return __riscv_vfcvt_rtz_x(v, N::value);
    else if constexpr( match(out_c, category::uint_) ) return __riscv_vfcvt_rtz_xu(v, N::value);
  }
  else if constexpr( match(out_c, category::float_) ) { return __riscv_vfcvt_f(v, N::value); }
  else return bit_cast(v, as<wide<U, N>> {});
}

// Narrow
template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(rvv_), wide<T, N> const                &v, as<U> const                &tgt) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) > sizeof(U))
{
  constexpr auto in_c  = categorize<wide<T, N>>();
  constexpr auto out_c = categorize<wide<U, N>>();

  constexpr int Scale = sizeof(T) / sizeof(U);
  if constexpr( Scale == 2 )
  {
    // we can perform operation.
    if constexpr( match(in_c, category::float_) )
    {
      if constexpr( match(out_c, category::int_) ) return __riscv_vfncvt_rtz_x(v, N::value);
      else if constexpr( match(out_c, category::uint_) ) return __riscv_vfncvt_rtz_xu(v, N::value);
      else if constexpr( match(out_c, category::float_) ) return __riscv_vfncvt_f(v, N::value);
    }
    if constexpr( match(in_c, category::int_) )
    {
      if constexpr( match(out_c, category::int_) ) return __riscv_vncvt_x(v, N::value);
      else if constexpr( match(out_c, category::uint_) )
      {
        auto part_done = convert(v, as<downgrade_t<T>> {});
        return convert(part_done, tgt);
      }
      else if constexpr( match(out_c, category::float_) ) return __riscv_vfncvt_f(v, N::value);
    }
    if constexpr( match(in_c, category::uint_) )
    {
      if constexpr( match(out_c, category::uint_) ) return __riscv_vncvt_x(v, N::value);
      else if constexpr( match(out_c, category::int_) )
      {
        auto part_done = convert(v, as<downgrade_t<T>> {});
        return convert(part_done, tgt);
      }
      else if constexpr( match(out_c, category::float_) ) return __riscv_vfncvt_f(v, N::value);
    }
  }
  else
  {
    // we need to cast to the lower type. Then call convert again.
    using down_ty = downgrade_t<T>;
    if constexpr( sizeof(T) == sizeof(down_ty) )
    {
      // this means downgrade_t reached limit (for fp for example).
      using int_ty   = as_integer_t<T>;
      auto part_done = convert(v, as<int_ty> {});
      return convert(part_done, tgt);
    }
    else
    {
      auto part_done = convert(v, as<down_ty> {});
      return convert(part_done, tgt);
    }
  }
}
// Widen
template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(rvv_), wide<T, N> const                &v, as<U> const                &tgt) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) < sizeof(U))
         && (riscv_rvv_dyn_::getLMUL<U>(N::value) <= 8)
{
  constexpr auto in_c  = categorize<wide<T, N>>();
  constexpr auto out_c = categorize<wide<U, N>>();
  constexpr int  Scale = sizeof(U) / sizeof(T);
  if constexpr( Scale == 2 )
  {
    if constexpr( match(in_c, category::int_) )
    {
      if constexpr( match(out_c, category::int_) ) return __riscv_vwcvt_x(v, N::value);
      else if constexpr( match(out_c, category::uint_) )
      {
        using cast_ty = as_integer_t<T, U>;
        auto casted   = bit_cast(v, as<wide<cast_ty, N>> {});
        return convert(casted, tgt);
      }
      else if constexpr( match(out_c, category::float_) ) return __riscv_vfwcvt_f(v, N::value);
    }
    else if constexpr( match(in_c, category::uint_) )
    {
      if constexpr( match(out_c, category::uint_) ) return __riscv_vwcvtu_x(v, N::value);
      else if constexpr( match(out_c, category::int_) )
      {
        using cast_ty = as_integer_t<T, U>;
        auto casted   = bit_cast(v, as<wide<cast_ty, N>> {});
        return convert(casted, tgt);
      }
      else if constexpr( match(out_c, category::float_) ) return __riscv_vfwcvt_f(v, N::value);
    }
    else if constexpr( match(in_c, category::float_) )
    {
      if constexpr( match(out_c, category::int_) ) return __riscv_vfwcvt_rtz_x(v, N::value);
      else if constexpr( match(out_c, category::uint_) ) return __riscv_vfwcvt_rtz_xu(v, N::value);
      else if constexpr( match(out_c, category::float_) ) return __riscv_vfwcvt_f(v, N::value);
    }
  }
  else
  {
    // we need to have widen operation before.
    using bigger_t = upgrade_t<T>;
    auto part_done = convert(v, as<bigger_t> {});
    return convert(part_done, tgt);
  }
}

template<scalar_value T, scalar_value U, typename N>
EVE_FORCEINLINE logical<wide<U, N>>
convert_impl(EVE_SUPPORTS(rvv_), logical<wide<T, N>> const& v, as<logical<U>> const& tgt) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return convert(v.bits(), as<U> {}) != 0;
}

}
