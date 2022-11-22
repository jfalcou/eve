//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include "eve/traits/element_type.hpp"
#include <eve/detail/abi.hpp>
#include <eve/detail/function/iota.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/traits/as_logical.hpp>

#include <bitset>

#include <type_traits>

namespace eve::detail
{
//================================================================================================
// Wide to Logical
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
to_logical(wide<T, N> const& v) noexcept
{
  if constexpr( is_aggregated_v<abi_t<T, N>> )
  {
    as_logical_t<wide<T, N>> that;
    that.storage().for_each([](auto& s, auto const& o) { s = to_logical(o); }, v);
    return that;
  }
  else
  {
    return map([](auto e) { return logical<T>(e != 0); }, v);
  }
}

template<value T>
EVE_FORCEINLINE auto
to_logical(logical<T> v) noexcept
{
  return v;
}

template<scalar_value T>
EVE_FORCEINLINE auto
to_logical(T v) noexcept
{
  return logical<std::conditional_t<std::is_same_v<T, bool>, std::uint8_t, T>>(v);
}

template<relative_conditional_expr C, simd_value T>
EVE_FORCEINLINE auto
to_logical(C c, eve::as<T>) noexcept
{
  using l_t = typename as_logical<T>::type;
  using i_t = std::conditional_t< (T::size()>=128 && sizeof(element_type_t<T>) == 1)
                                , as_integer_t<typename as_logical_t<T>::mask_type,unsigned>
                                , as_integer_t<typename as_logical_t<T>::mask_type>
                                >;

  if constexpr( std::same_as<C, ignore_all_> ) return l_t {false};
  else if constexpr( std::same_as<C, ignore_none_> ) return l_t {true};
  else if constexpr( !eve::use_complete_storage<l_t> )
  {
    // Use the most full type to be sure to fill outside values of small wide with false
    using e_t   = eve::element_type_t<i_t>;
    using abi_t = typename i_t::abi_type;
    using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t>>;

    if constexpr( std::same_as<C, keep_first> || std::same_as<C, ignore_last> )
    {
      return bit_cast(to_logical(keep_first(c.count(as<l_t> {})), as<w_t> {}), as<l_t> {});
    }
    else
    {
      std::ptrdiff_t offset = c.offset(as<T> {});
      std::ptrdiff_t count  = c.count(as<T> {});
      keep_between   full_c {offset, offset + count};
      return bit_cast(to_logical(full_c, as<w_t> {}), as<l_t> {});
    }
  }
  else
  {
    auto           i     = detail::linear_ramp(eve::as<i_t>());
    std::ptrdiff_t count = c.count(as<i_t> {});

    if constexpr( std::same_as<C, keep_first> || std::same_as<C, ignore_last> )
    {
      return bit_cast(i < i_t(count), as<l_t> {});
    }
    else if constexpr( std::same_as<C, keep_last> || std::same_as<C, ignore_first> )
    {
      return bit_cast(i >= i_t(l_t::size() - count), as<l_t> {});
    }
    else
    {
      std::ptrdiff_t offset = c.offset(as<i_t> {});
      return bit_cast((i >= i_t {offset}) && (i < i_t {offset + count}), as<l_t> {});
    }
  }
}
}
