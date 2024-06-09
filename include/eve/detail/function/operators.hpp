//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/traits/bit_value.hpp>

namespace eve::detail
{

  //================================================================================================
  // infix bitwise operators
  //================================================================================================
  template<value T, value U, callable_options O>
  EVE_FORCEINLINE constexpr bit_value_t<T, U> bit_and_(EVE_REQUIRES(cpu_),
                                          O const &,
                                          T const &a,
                                          U const &b) noexcept
  {
    using r_t = bit_value_t<T, U>;
    using b_t = as_integer_t<r_t>;

    using ra_t = std::conditional_t<scalar_value<T>,element_type_t<b_t>,b_t>;
    using rb_t = std::conditional_t<scalar_value<U>,element_type_t<b_t>,b_t>;
    auto ba = bit_cast(a, as<ra_t>{});
    auto bb = bit_cast(b, as<rb_t>{});
    return bit_cast( b_t(b_t(ba) & (b_t(bb)) ), as<r_t>());
  }

  template<value T, value U, callable_options O>
  EVE_FORCEINLINE  constexpr auto bit_or_(EVE_REQUIRES(cpu_),
                                          O const &,
                                          T const &a,
                                          U const &b) noexcept
  {
    using r_t = bit_value_t<T, U>;
    using b_t = as_integer_t<r_t>;

    using ra_t = std::conditional_t<scalar_value<T>,element_type_t<b_t>,b_t>;
    using rb_t = std::conditional_t<scalar_value<U>,element_type_t<b_t>,b_t>;
    auto ba = bit_cast(a, as<ra_t>{});
    auto bb = bit_cast(b, as<rb_t>{});
    return bit_cast( b_t(b_t(ba) | (b_t(bb)) ), as<r_t>());
  }

  template<value T, value U, callable_options O>
  EVE_FORCEINLINE constexpr auto bit_xor_(EVE_REQUIRES(cpu_),
                                          O const &,
                                          T const &a,
                                          U const &b) noexcept
  {
    using r_t = bit_value_t<T, U>;
    using b_t = as_integer_t<r_t>;

    using ra_t = std::conditional_t<scalar_value<T>,element_type_t<b_t>,b_t>;
    using rb_t = std::conditional_t<scalar_value<U>,element_type_t<b_t>,b_t>;
    auto ba = bit_cast(a, as<ra_t>{});
    auto bb = bit_cast(b, as<rb_t>{});
    return bit_cast( b_t(b_t(ba) ^ (b_t(bb)) ), as<r_t>());
  }
}
