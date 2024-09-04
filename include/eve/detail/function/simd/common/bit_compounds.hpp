//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, wide<U,N> s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a << b); };

    if constexpr(   is_aggregated_v<abi_t<T, N>>
                &&  is_aggregated_v<abi_t<U, N>>
                )                                     v = aggregate(ss, v, s);
    else                                              v = map(ss, v, s);

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, U s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a << b); };

    if constexpr(is_aggregated_v<abi_t<T, N>>) v = aggregate(ss, v, s);
    else                                          v = map(ss, v, s);

    return v;
  }

  template<integral_scalar_value T, typename N, std::ptrdiff_t V>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, index_t<V> const&) noexcept
  {
    return self_shl(v,V);
  }

  //================================================================================================
  // >>=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE bit_value_t<wide<T, N>, U>& self_shr(wide<T,N>& v, wide<U,N> s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a >> b); };

    if constexpr(   is_aggregated_v<abi_t<T, N>>
                &&  is_aggregated_v<abi_t<U, N>>
                )                                     v = aggregate(ss, v, s);
    else                                              v = map(ss, v, s);

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, U s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a >> b); };

    if constexpr(is_aggregated_v<abi_t<T, N>>) v = aggregate(ss, v, s);
    else                                          v = map(ss, v, s);

    return v;
  }

  template<integral_scalar_value T, typename N, std::ptrdiff_t V>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, index_t<V> const&) noexcept
  {
    return self_shr(v,V);
  }

  //================================================================================================
  // &=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE bit_value_t<wide<T, N>, U>& self_bitand(wide<T, N> &self, U const &other) noexcept
  requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U))) && non_native_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = bit_cast(other, as<T> {});
      return self_bitand(self, type {bit_other});
    }
    else
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        auto& data = self.storage();
        apply<N::value>([&](auto... I)
        {
          using i_t = as_integer_t<T>;
          using t_t = as<i_t>;
          ((data[I] = bit_cast( i_t(bit_cast(self.get(I),t_t{}) & bit_cast(other.get(I),t_t{})), as<T>{})), ...);
        });
        return self;
      }
      else if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s &= o; }, other );
        return self;
      }
    }
  }

  //================================================================================================
  // |=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE bit_value_t<wide<T, N>, U>&
  self_bitor(wide<T, N> &self, U const &other) requires((sizeof(wide<T, N>) == sizeof(U))
                                                             || (sizeof(T) == sizeof(U))) && non_native_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = bit_cast(other, as<T> {});
      return self_bitor(self, type {bit_other});
    }
    else
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        auto& data = self.storage();
        apply<N::value>([&](auto... I)
        {
          using i_t = as_integer_t<T>;
          using t_t = as<i_t>;
          ((data[I] = bit_cast( i_t(bit_cast(self.get(I),t_t{}) | bit_cast(other.get(I),t_t{})), as<T>{})), ...);
        });
        return self;
      }
      else if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s |= o; }, other );
        return self;
      }
    }
  }

  //================================================================================================
  // ^=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE bit_value_t<wide<T, N>, U>&
  self_bitxor(wide<T, N> &self, U const &other) requires((sizeof(wide<T, N>) == sizeof(U))
                                                              || (sizeof(T) == sizeof(U))) && non_native_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = bit_cast(other, as<T> {});
      return self_bitxor(self, type {bit_other});
    }
    else
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        auto& data = self.storage();
        apply<N::value>([&](auto... I)
        {
          using i_t = as_integer_t<T>;
          using t_t = as<i_t>;
          ((data[I] = bit_cast( i_t(bit_cast(self.get(I),t_t{}) ^ bit_cast(other.get(I),t_t{})), as<T>{})), ...);
        });
        return self;
      }
      else if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s ^= o; }, other );
        return self;
      }
    }
  }
}
