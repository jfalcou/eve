//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core
//! @{
//! @var ieee_cts
//!
//! @brief Callable object computing a floating constant from its scalar hexadecimal integral
//! representations |
//!
//! **Required header:** `#include <eve/module/core.hpp>`
//!
//! | Member       | Effect                                                     |
//! |:-------------|:-----------------------------------------------------------|
//! | `operator()` | generates a floating constant                              |
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  template <auto f, auto d, floating_ordered_value T> T operator()(as<T> target) const
//!  noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **template Parameters**
//!
//! `f':  float scalar constant
//!
//!`'d': double scalar constant
//!
//!   ** Parameters**
//!
//!  'target': as<T>() where T is the chosen return type
//!
//! **Return value**
//!
//! the call `eve::ieee_cts<f, d>(as<T>())`
//! is semantically equivalent to :
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  using t_t = element_type_t<T>;
//!  if constexpr(std::same_as<t_t, float>) return T(f)
//!  else if constexpr(std::same_as<t_t, double>)  return T(d);
//!  else the result is UB
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//! ---
//!
//! #### Example
//!
//! godbolt{doc/core/constant/ieee_constant.cpp}
//!
//! @}
//================================================================================================
  template<floating_value T>
  EVE_FORCEINLINE auto ieee_constant(float vf,  double vd, eve::as<T> const& = {}) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr( std::same_as<elt_t, float> )
    {
      return T(vf);
    }
    else if constexpr(std::same_as<elt_t, double>)
    {
       return T(vd);
    }
  }

  namespace _
  {
    struct real32 { constexpr real32(auto v) : value(v) {} float  value; };
    struct real64 { constexpr real64(auto v) : value(v) {} double value; };
  }

  template<eve::_::real32 BF, eve::_::real64 BD,typename T>
  auto ieee_cts(eve::as<T>)
  {
    using e_t = eve::element_type_t<T>;
    if      constexpr(std::same_as<float,e_t>) return T(BF.value);
    else if constexpr(std::same_as<double,e_t>) return T(BD.value);
  }
}
