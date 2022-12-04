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
template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shl(wide<T,N>& self, wide<U,N> shift) noexcept
requires (sve_abi<abi_t<T, N>> && sizeof(T) == sizeof(U))
{
  using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
  auto const si = bit_cast(shift,as<i_t>());

  self = svlsl_x(sve_true<T>(), self, si);
  return self;
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shl(wide<T,N>& self, U shift) noexcept
requires sve_abi<abi_t<T, N>>
{
  using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
  self = svlsl_x(sve_true<T>(), self, i_t(shift));
  return self;
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shr(wide<T,N>& self, wide<U,N> shift) noexcept
requires (sve_abi<abi_t<T, N>> && sizeof(T) == sizeof(U))
{
  using u_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;

  if constexpr( std::is_signed_v<T> )
  {
    self = svasr_x(sve_true<T>(), self, bit_cast(shift,as<u_t>()));
    return self;
  }
  else
  {
    self = svlsr_x(sve_true<T>(), self, bit_cast(shift,as<u_t>()));
    return self;
  }
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shr(wide<T,N>& self, U shift) noexcept
requires sve_abi<abi_t<T, N>>
{
  using u_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;

  if constexpr( std::is_signed_v<T> )
  {
    self = svasr_x(sve_true<T>(), self, u_t(shift));
    return self;
  }
  else
  {
    self = svlsr_x(sve_true<T>(), self, u_t(shift));
    return self;
  }
}

template<scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
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
EVE_FORCEINLINE auto&
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
EVE_FORCEINLINE auto&
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
}
