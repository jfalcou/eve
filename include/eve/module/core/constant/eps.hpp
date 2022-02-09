//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var eps
  //!
  //! @brief Callable object computing the machine epsilon.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the eps constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < real_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::eps(as<T>())` returns [elementwise](@ref glossary_elementwise), the smallest
  //! positive value `x` of the type such that `1+x !=  x`.
  //!
  //!  * If T is an [integral value](@ref eve::integral_value) the elements returned are equal to one
  //!  * If T is a  [floating real value](@ref eve::floating_real_value) the elements returned are equal to
  //!        - 2.220446049250313e-16 if the [elements type](@ref eve::element_type) is float
  //!        - 1.1920929e-07f        if the [elements type](@ref eve::element_type) is double
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/eps.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(eps_, eps);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto eps_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;

      if constexpr(std::is_integral_v<t_t>) return T(1);
      else if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0X34000000U>();
      else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x3CB0000000000000ULL>();
    }
  }
}
