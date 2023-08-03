//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/quaternion.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_multipolar
  //!
  //! @brief Callable object computing a quaternion from its multipolar representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a multipolar representation of an \f$\mathbb{R}^4\f$ element.
  //!
  //!  from_multipolar  the two \f$\mathbb{C}\f$ components of the quaternion are given in polar coordinates
  //!
  //! **Defined in header**
  //!
  //!   @code
  //!   #include eve/module/quaternion.hpp>`
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
 //!   {
  //!     auto from_multipolar( auto rho1, auto theta1 auto rho2, auto theta2) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`rho1`, `rho2`:  the moduli
  //! 'theta1', 'theta2': the angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/conversions.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(from_multipolar_, from_multipolar);

  namespace detail
  {
    template<ordered_value V,  ordered_value U,  ordered_value W,  ordered_value T>
    EVE_FORCEINLINE auto from_multipolar_( EVE_SUPPORTS(cpu_)
                                    , V const & rho1
                                    , U const & theta1
                                    , W const & rho2
                                    , T const & theta2) noexcept
    {
      return arithmetic_call(from_multipolar, rho1, theta1, rho2, theta2);
    }

    template<floating_value U>
    EVE_FORCEINLINE auto from_multipolar_(EVE_SUPPORTS(cpu_)
                                    , U const & rho1
                                    , U const & theta1
                                    , U const & rho2
                                    , U const & theta2) noexcept
    {
      return to_quaternion(polar(rho1, theta1), polar(rho2, theta2));
    }
  }
}
