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
  //! @var from_cylindrospherical
  //!
  //! @brief Callable object computing a quaternion from its cylindrospherical representation.
  //!
  //!  cylindrospherical is specific to quaternions. It is often interesting to consider
  //!  \f$\mathbb{H}\f$ as the cartesian product of \f$\mathbb{R}\f$ by \f$\mathbb{R3}\f$
  //!  (the quaternionic multiplication has then a special form, as given here).
  //!  This function therefore builds a quaternion from this representation, with the \f$\mathbb{R3}\f$ component given
  //!  in usual \f$\mathbb{R3}\f$ spherical coordinates.
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
  //!     auto from_cylindrospherical(auto t, auto radius, auto longitude, auto latitude) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `t`, `radius`:  the moduli
  //!  * `longitude`, `latitude`: angles in radian
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
  namespace tag { struct from_cylindrospherical_; }
  template<> struct supports_conditional<tag::from_cylindrospherical_> : std::false_type {};

  EVE_MAKE_CALLABLE(from_cylindrospherical_, from_cylindrospherical);

  namespace detail
  {
    template<ordered_value V,  ordered_value U,  ordered_value W,  ordered_value T>
    EVE_FORCEINLINE auto from_cylindrospherical_( EVE_SUPPORTS(cpu_)
                               , V const & t
                               , U const & radius
                               , W const & longitude
                               , T const & latitude    ) noexcept
    {
      return arithmetic_call(from_cylindrospherical, t, radius, longitude, latitude);
    }

    template<floating_value T>
    EVE_FORCEINLINE auto from_cylindrospherical_(EVE_SUPPORTS(cpu_)
                                           , T const & t
                                           , T const &  r
                                           , T const & longitude
                                           , T const & latitude    ) noexcept
    {
      using z_t = eve::as_quaternion_t<T>;
      auto [slat, clat] = sincos(latitude);
      auto [slon, clon] = sincos(longitude);
      auto f = r*clat;
      return z_t{t, f*clon, f*slon, r*slat};
    }
  }
}
