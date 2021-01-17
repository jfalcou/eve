//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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
      if constexpr( is_emulated_v<ABI> )
      {
        auto& data = self.storage();

        apply<N::value>([&](auto... I) {
          ((data[I] = bit_and_(EVE_RETARGET(cpu_), self[I], other[I])), ...);
        });

        return self;
      }
      else if constexpr( is_aggregated_v<ABI> )
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
      if constexpr( is_emulated_v<ABI> )
      {
        auto& data = self.storage();

        apply<N::value>([&](auto... I) {
          ((data[I] = bit_or_(EVE_RETARGET(cpu_), self[I], other[I])), ...);
        });

        return self;
      }
      else if constexpr( is_aggregated_v<ABI> )
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
      if constexpr( is_emulated_v<ABI> )
      {
        auto& data = self.storage();

        apply<N::value>([&](auto... I) {
          ((data[I] = bit_xor_(EVE_RETARGET(cpu_), self[I], other[I])), ...);
        });

        return self;
      }
      else if constexpr( is_aggregated_v<ABI> )
      {
        self.storage().for_each( [&](auto& s, auto const& o)  { s ^= o; }, other );
        return self;
      }
    }
  }
}
