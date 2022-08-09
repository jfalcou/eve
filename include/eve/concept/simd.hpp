//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/concept/scalar.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/element_type.hpp>

namespace eve
{
  inline namespace EVE_ABI_NAMESPACE
  {
    template<arithmetic_scalar_value Type, typename Size> struct wide;
  }

  template<typename T>
  concept arithmetic_simd_value = detail::instance_of<T,wide>;

  template<typename T>
  concept plain_simd_value =  arithmetic_simd_value<T> && plain_scalar_value<element_type_t<T>>;

  template<typename T>
  concept product_simd_value = arithmetic_simd_value<T> && kumi::product_type<element_type_t<T>>;
}
