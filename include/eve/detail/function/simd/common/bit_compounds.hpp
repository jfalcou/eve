//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_real_scalar_value T, typename N, typename ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N,ABI>& v, wide<U,N,ABI> s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a << b); };

    if constexpr(has_aggregated_abi_v<T> || has_aggregated_abi_v<U>)  v = aggregate(ss, v, s);
    else                                                              v = map(ss, v, s);

    return v;
  }

  template<integral_real_scalar_value T, typename N, typename ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N,ABI>& v, U s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a << b); };

    if constexpr(has_aggregated_abi_v<T>) v = aggregate(ss, v, s);
    else                                  v = map(ss, v, s);

    return v;
  }

  //================================================================================================
  // >>=
  //================================================================================================
  template<integral_real_scalar_value T, typename N, typename ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N,ABI>& v, wide<U,N,ABI> s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a >> b); };

    if constexpr(has_aggregated_abi_v<T> || has_aggregated_abi_v<U>)  v = aggregate(ss, v, s);
    else                                                              v = map(ss, v, s);

    return v;
  }

  template<integral_real_scalar_value T, typename N, typename ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N,ABI>& v, U s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a >> b); };

    if constexpr(has_aggregated_abi_v<T>) v = aggregate(ss, v, s);
    else                                  v = map(ss, v, s);

    return v;
  }

  //================================================================================================
  // &=
  //================================================================================================
  template<scalar_value T, value U, typename N, non_native_abi ABI>
  EVE_FORCEINLINE decltype(auto) self_bitand(wide<T, N, ABI> &self, U const &other) noexcept
  requires((sizeof(wide<T, N, ABI>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitand(self, type {bit_other});
    }
    else
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        auto& data = self.storage();

        apply<N::value>([&](auto... I) {
          ((data[I] = bit_and_(EVE_RETARGET(cpu_), self.get(I), other.get(I))), ...);
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
  template<scalar_value T, value U, typename N, non_native_abi ABI>
  EVE_FORCEINLINE decltype(auto)
  self_bitor(wide<T, N, ABI> &self, U const &other) requires((sizeof(wide<T, N, ABI>) == sizeof(U))
                                                             || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitor(self, type {bit_other});
    }
    else
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        auto& data = self.storage();

        apply<N::value>([&](auto... I) {
          ((data[I] = bit_or_(EVE_RETARGET(cpu_), self.get(I), other.get(I))), ...);
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
  template<scalar_value T, value U, typename N, non_native_abi ABI>
  EVE_FORCEINLINE decltype(auto)
  self_bitxor(wide<T, N, ABI> &self, U const &other) requires((sizeof(wide<T, N, ABI>) == sizeof(U))
                                                              || (sizeof(T) == sizeof(U)))
  {
    using type = wide<T, N, ABI>;

    if constexpr( scalar_value<U> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other, as_<T> {});
      return self_bitxor(self, type {bit_other});
    }
    else
    {
      if constexpr( is_emulated_v<abi_t<T, N>> )
      {
        auto& data = self.storage();

        apply<N::value>([&](auto... I) {
          ((data[I] = bit_xor_(EVE_RETARGET(cpu_), self.get(I), other.get(I))), ...);
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
