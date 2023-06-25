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
  //! @var spherical
  //!
  //! @brief Callable object computing a quaternion from its spherical representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a spherical representation of an \f$\mathbb{R}^4\f$ element.
  //!
  //!  spherical takes as inputs a (positive) magnitude and a point on the hypersphere, given by three angles.
  //!  The first of these, theta has a natural range of \f$-\pi\f$ to \f$+\pi\f$, and the other two have natural
  //!  ranges of \f$-\pi/2\f$ to \f$+\pi/2\f$ (as is the case with the usual spherical coordinates in \f$\mathbb{R}^3\f$).
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
  //!     auto spherical(auto rho, auto theta, auto phi1, auto phi2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!   * `rho`:  the modulus
  //!   * `theta`, 'phi1`, 'phi2`: angles in radian
  //!
  //! **Return value**
  //!
  //! the quaternion value
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/quaternion/regular/spherical.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(spherical_, spherical);

  namespace detail
  {
    template<ordered_value V,  ordered_value U,  ordered_value W,  ordered_value T>
    EVE_FORCEINLINE auto spherical_( EVE_SUPPORTS(cpu_)
                               , V const & rho
                               , U const & theta
                               , W const & phi1
                               , T const & phi2    ) noexcept
    {
      return arithmetic_call(spherical, rho, theta, phi1, phi2);
    }

    template<floating_value U>
    EVE_FORCEINLINE auto spherical_(EVE_SUPPORTS(cpu_)
                                   , U const & rho
                                   , U const & theta
                                   , U const & phi1
                                   , U const & phi2) noexcept
    {
      using z_t = eve::as_quaternion_t<U>;
      auto [st, ct] = sincos(theta);
      auto [sp1, cp1] = sincos(phi1);
      auto [sp2, cp2] = sincos(phi2);
      auto d = sp2;
      auto f = cp1*cp2;
      return rho*z_t{ct*f, st*f, sp1*d, d};
    }
  }
}
