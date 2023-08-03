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

namespace eve
{
  //================================================================================================
  //! @addtogroup quaternion
  //! @{
  //! @var from_semipolar
  //!
  //! @brief Callable object computing a quaternion from its semipolar representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a semipolar representation of an \f$\mathbb{R}^4\f$ element.
  //!
  //!  from_semipolar takes as a first input the magnitude of the quaternion,
  //!  as a second input an angle in the range 0 to \f$\pi/2\f$ such that magnitudes of the first
  //!  two \f$\mathbb{C}\f$ components of the quaternion are the product of the first input and the sine and cosine
  //!  of this angle, respectively, and finally as third and fourth inputs angles in the range \f$-\pi/2\f$ to \f$+\pi/2\f$
  //!  which represent the arguments of the first and second \f$\mathbb{C}\f$ components of the quaternion, respectively.
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
  //!     auto from_semipolar(auto rho, auto alpha auto theta1, auto theta2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `rho`:  the modulus
  //!  * `alpha`, `theta1`, `theta2`: angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value representing the \f$\R^4\f$ element.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/conversions.cpp}
  //!  @}
  //================================================================================================
  namespace tag { struct from_semipolar_; }
  template<> struct supports_conditional<tag::from_semipolar_> : std::false_type {};

  EVE_MAKE_CALLABLE(from_semipolar_, from_semipolar);

  namespace detail
  {
    template<ordered_value V,  ordered_value U,  ordered_value W,  ordered_value T>
    EVE_FORCEINLINE auto from_semipolar_( EVE_SUPPORTS(cpu_)
                               , V const & rho
                               , U const & alpha
                               , W const & theta1
                               , T const & theta2    ) noexcept
    {
      return arithmetic_call(from_semipolar, rho, alpha, theta1, theta2);
    }

    template<floating_value U>
    EVE_FORCEINLINE auto from_semipolar_(EVE_SUPPORTS(cpu_)
                                   , U const & rho
                                   , U const & alpha
                                   , U const & theta1
                                   , U const & theta2) noexcept
    {
      using z_t = eve::as_quaternion_t<U>;
      auto [st1, ct1] = sincos(theta1);
      auto [st2, ct2] = sincos(theta2);
      auto [sa, ca] = sincos(alpha);
      return rho*z_t{ca*ct1, ca*st1, sa*ct2, sa*st2};
    }
  }
}
