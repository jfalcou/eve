//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/is_logical.hpp>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
{
  return apply_over(logical_xor, a, b);
}

template<scalar_value T, scalar_value U>
EVE_FORCEINLINE as_logical_t<T>
                logical_xor_(EVE_SUPPORTS(cpu_), logical<T> const                &a, logical<U> const                &b) noexcept
{
  return as_logical_t<T> {a.value() != b.value()};
}

template<simd_value T, simd_value U>
EVE_FORCEINLINE as_logical_t<T>
logical_xor_(EVE_SUPPORTS(cpu_), logical<T> const& a, logical<U> const& b) noexcept requires
    has_native_abi_v<T> && has_native_abi_v<U> &&(cardinal_v<T> == cardinal_v<U>)
{
  using abi_t = typename T::abi_type;
  if constexpr( std::is_same_v<U, T> )
  {
    if constexpr( !abi_t::is_wide_logical )
    {
      using s_t = typename logical<T>::storage_type;
      using m_t = typename s_t::type;
      m_t r     = a.storage().value ^ b.storage().value;
      return s_t {r};
    }
    else { return bit_cast(bit_xor(a.bits(), b.bits()), as<as_logical_t<T>>()); }
  }
  else { return logical_xor(a, convert(b, as<logical<element_type_t<T>>>())); }
}

template<simd_value T, scalar_value U>
EVE_FORCEINLINE as_logical_t<T>
                logical_xor_(EVE_SUPPORTS(cpu_),
                             logical<T> const                &a,
                             logical<U> const                &b) noexcept requires has_native_abi_v<T> && has_native_abi_v<U>
{
  using elt_t = element_type_t<T>;
  using abi_t = typename T::abi_type;

  if constexpr( !abi_t::is_wide_logical ) { return eve::logical_xor(a, b.value()); }
  else if constexpr( sizeof(elt_t) == sizeof(U) )
  {
    auto bb = is_nez(T(bit_cast(b, as<logical<elt_t>>())));
    return bit_cast(bit_xor(a.bits(), bb.bits()), as<as_logical_t<T>>());
  }
}

template<scalar_value T, simd_value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_),
             logical<T> const& a,
             logical<U> const& b) noexcept requires has_native_abi_v<T> && has_native_abi_v<U>
{
  using elt_t = element_type_t<U>;
  using r_t   = as_wide_t<logical<T>, cardinal_t<U>>;
  using abi_t = typename logical<U>::abi_type;

  if constexpr( !abi_t::is_wide_logical )
  {
    r_t a_cast {a};
    r_t b_cast {b.storage()};
    return eve::logical_xor(a_cast, b_cast);
  }
  else if constexpr( sizeof(elt_t) == sizeof(T) )
  {
    auto aa = r_t(a);
    return bit_cast(bit_xor(aa.bits(), b.bits()), as<r_t>());
  }
}

template<logical_value T>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
{
  return T {b} != a;
}

template<logical_value U>
EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
{
  return U {a} != b;
}

EVE_FORCEINLINE auto
logical_xor_(EVE_SUPPORTS(cpu_), bool a, bool b) noexcept
{
  return a != b;
}
}
