//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/traits/element_type.hpp>

namespace eve
{
  inline namespace EVE_ABI_NAMESPACE
  {
    template<scalar Type, typename Size> struct wide;
  }

  namespace detail
  {
    template<typename T> struct is_wide { static constexpr bool value = false; };

    template<scalar T, typename N>
    struct is_wide<wide<T,N>> { static constexpr bool value = true; };
  }

  template<typename T>
  concept simd = detail::is_wide<T>::value;

  template<typename T>
  concept plain_simd = simd<T> && plain_scalar<element_type_t<T>>;

  template<typename T>
  concept product_simd  = simd<T> && kumi::product_type<element_type_t<T>>;

  template<typename T>
  concept plain_value = plain_scalar<T> || plain_simd<T>;
}
