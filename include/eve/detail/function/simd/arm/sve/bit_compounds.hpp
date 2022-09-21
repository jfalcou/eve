//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
template<scalar_value T, value U, typename N>
EVE_FORCEINLINE decltype(auto)
self_bitand(wide<T, N>& self, U const& other) noexcept
requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U))) && sve_abi<abi_t<T, N>>
{
  using type = wide<T, N>;
  if constexpr( element_bit_compatible_to<U, type> )
  {
    auto bit_other = eve::bit_cast(other, as<T> {});
    self           = self_bitand(self, type {bit_other});
  }
  else
  {
    using i_t = typename type::template rebind <as_integer_t<T, signed>,N>;
    constexpr auto tgt = as<i_t>();
    self = bit_cast ( i_t(svand_x(sve_true<T>(), bit_cast(self,tgt), bit_cast(other,tgt)))
                    , as(self)
                    );
  }

  return self;
}

template<scalar_value T, value U, typename N>
EVE_FORCEINLINE decltype(auto)
self_bitor(wide<T, N>& self, U const& other) noexcept
requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U))) && sve_abi<abi_t<T, N>>
{
  using type = wide<T, N>;
  if constexpr( element_bit_compatible_to<U, type> )
  {
    auto bit_other = eve::bit_cast(other, as<T> {});
    self           = self_bitor(self, type {bit_other});
  }
  else
  {
    using i_t = typename type::template rebind <as_integer_t<T, signed>,N>;
    constexpr auto tgt = as<i_t>();
    self = bit_cast ( i_t(svorr_x(sve_true<T>(), bit_cast(self,tgt), bit_cast(other,tgt)))
                    , as(self)
                    );
  }

  return self;
}
template<scalar_value T, value U, typename N>
EVE_FORCEINLINE decltype(auto)
self_bitxor(wide<T, N>& self, U const& other) noexcept
requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U))) && sve_abi<abi_t<T, N>>
{
  using type = wide<T, N>;
  if constexpr( element_bit_compatible_to<U, type> )
  {
    auto bit_other = eve::bit_cast(other, as<T> {});
    self           = self_bitxor(self, type {bit_other});
  }
  else
  {
    using i_t = typename type::template rebind <as_integer_t<T, signed>,N>;
    constexpr auto tgt = as<i_t>();
    self = bit_cast ( i_t(sveor_x(sve_true<T>(), bit_cast(self,tgt), bit_cast(other,tgt)))
                    , as(self)
                    );
  }

  return self;
}

/*
self_shl
self_shr
*/

}
