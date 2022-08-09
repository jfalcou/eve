//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/is_native.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // +=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto)
  self_add(wide<T, N> &self,
           U const &        other) requires(scalar_value<U> || std::same_as<wide<T, N>, U>)
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
    {
      return self_add(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        apply<N::value>([&](auto... I) { (self.set(I, self.get(I) + other.get(I)), ...); });
        return self;
      }
      else if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s += o; }, other );
        return self;
      }
    }
  }

  //================================================================================================
  // -=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto)
  self_sub(wide<T, N> &self,
           U const &        other) requires(scalar_value<U> || std::same_as<wide<T, N>, U>)
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
      return self_sub(self, type {other});
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        apply<N::value>([&](auto... I) { (self.set(I, self.get(I) - other.get(I)), ...); });
        return self;
      }
      else if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s -= o; }, other );
        return self;
      }
    }
  }

  //================================================================================================
  // *=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto)
  self_mul(wide<T, N> &self,
           U const &        other) requires(scalar_value<U> || std::same_as<wide<T, N>, U>)
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
      return self_mul(self, type {other});
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        apply<N::value>([&](auto... I) { (self.set(I, self.get(I) * other.get(I)), ...); });
        return self;
      }
      else if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s *= o; }, other );
        return self;
      }
    }
  }

  //================================================================================================
  // /=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto)
  self_div(wide<T, N> &self,
           U const &        other) requires(scalar_value<U> || std::same_as<wide<T, N>, U>)
  {
    using type = wide<T, N>;

    if constexpr( scalar_value<U> )
      return self_div(self, type {other});
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        apply<N::value>([&](auto... I) { (self.set(I, self.get(I) / other.get(I)), ...); });
        return self;
      }
      else if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s /= o; }, other );
        return self;
      }
    }
  }

  //================================================================================================
  // %=
  //================================================================================================
  template<integral_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto)
  self_rem(wide<T, N> &self,
           U const &        other) requires(integral_scalar_value<U> || std::same_as<wide<T, N>, U>)
  {
    using type = wide<T, N>;

    if constexpr( integral_scalar_value<U> )
    {
      return self_rem(self, type {other});
    }
    else if constexpr( std::same_as<type, U> )
    {
      if constexpr( is_aggregated_v<abi_t<T, N>> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s %= o; }, other );
        return self;
      }
      else
      {
        wide<T, N> that;
        apply<N::value>([&](auto... I) { (that.set(I, self.get(I) % other.get(I)), ...); });
        return self = that;
      }
    }
  }
}
