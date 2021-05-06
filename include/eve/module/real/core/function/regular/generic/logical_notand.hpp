//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<value T, value U>
  EVE_FORCEINLINE  auto logical_notand_(EVE_SUPPORTS(cpu_)
                                       , T const &a
                                       , U const &b) noexcept
  {
    return apply_over(logical_notand, a, b);
  }

  template<scalar_value T, scalar_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_notand_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires (has_native_abi_v<T> && has_native_abi_v<U>)
  {
    if constexpr(is_logical_v<T>) {
      return logical_notand(a.value(), b);
    }
    else if  constexpr(is_logical_v<U>) {
      return logical_notand(a, b.value());
    }
    else
    {
      return as_logical_t<T>(!a && b);
    }
  }

  template<simd_value T, simd_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_notand_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U> && (cardinal_v<T> == cardinal_v<U>)
  {
    using abi_t = typename T::abi_type;

         if constexpr ( !abi_t::is_wide_logical )  { return logical_notand(to_logical(a), to_logical(b)); }
    else if constexpr(sizeof(T) == sizeof(U)) { return bit_cast(bit_notand(bit_mask(a), bit_mask(b)), as_<as_logical_t<T>>());}
    else                                 { return apply_over(logical_notand, a, b); }
  }

  template<simd_value T, scalar_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_notand_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires (has_native_abi_v<T> && has_native_abi_v<U>)
  {
    return logical_notand(is_nez(a), is_nez(b));
  }

  template<scalar_value T, simd_value U>
  EVE_FORCEINLINE  auto logical_notand_(EVE_SUPPORTS(cpu_)
                                    , T const &a
                                    , U const &b) noexcept
  requires (has_native_abi_v<T> && has_native_abi_v<U>)
  {
    return logical_notand(is_nez(a), is_nez(b));
  }

  template<simd_value T, simd_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_notand_(EVE_SUPPORTS(cpu_)
                                               , logical<T> const &a
                                               , logical<U> const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U> && (cardinal_v<T> == cardinal_v<U>)
  {
    using abi_t = typename T::abi_type;

         if constexpr ( !abi_t::is_wide_logical ) { return !a && b; }
    else if constexpr(sizeof(T) == sizeof(U)) { return bit_cast(bit_notand(a.bits(), b.bits()), as_<as_logical_t<T>>());}
    else                                 { return apply_over(logical_notand, a, b); }
  }

  template<simd_value T, scalar_value U>
  EVE_FORCEINLINE  as_logical_t<T> logical_notand_(EVE_SUPPORTS(cpu_)
                                               , logical<T> const &a
                                               , logical<U> const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U>
  {
    using elt_t = element_type_t<T>;
    using abi_t = typename T::abi_type;

    if constexpr ( !abi_t::is_wide_logical )
    {
      auto bb = b ? logical<T>(true) : logical<T>(false);

      return eve::logical_notand(a, bb);
    }
    else if constexpr(sizeof(elt_t) == sizeof(U))
    {
      auto bb = is_nez(T(bit_cast(b, as<logical<elt_t>>())));

      return bit_cast(bit_notand(a.bits(), bb.bits()), as_<as_logical_t<T>>());
    }
    else           { return apply_over(logical_notand, a, b); }
  }

  template<scalar_value T, simd_value U>
  EVE_FORCEINLINE auto logical_notand_(EVE_SUPPORTS(cpu_)
                                   , logical<T> const &a
                                   , logical<U> const &b) noexcept
  requires has_native_abi_v<T> && has_native_abi_v<U>
  {
    using elt_t = element_type_t<U>;
    using r_t = as_wide_t<logical<T>, cardinal_t<U>>;
    using abi_t = typename logical<U>::abi_type;

    if constexpr ( !abi_t::is_wide_logical )
    {
      r_t a_cast{a};
      r_t b_cast {b.storage()};
      return eve::logical_notand(a_cast, b_cast);
    }
    else if constexpr(sizeof(elt_t) == sizeof(T))
    {
      auto aa = r_t(a);

      return bit_cast(bit_notand(aa.bits(), b.bits()), as<r_t>());
    }
    else        { return apply_over(logical_notand, a, b); }
  }

  template<logical_value T>
  EVE_FORCEINLINE auto logical_notand_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
  {
    return b ? T{!a} : false_(as<T>());
  }

  template<logical_value U>
  EVE_FORCEINLINE auto logical_notand_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
  {
    return a ? false_(as<U>()): U{b};
  }

  EVE_FORCEINLINE  auto logical_notand_(EVE_SUPPORTS(cpu_)
                                       , bool a
                                       , bool b) noexcept
  {
    return  !a && b;
  }


}
