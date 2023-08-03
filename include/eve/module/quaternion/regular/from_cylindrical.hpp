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
  //! @var from_cylindrical
  //!
  //! @brief Callable object computing a quaternion from its cylindrical representation.
  //!
  //!  This function build quaternions in a way similar to the way polar builds complex numbers
  //!  from a cylindrical representation of an \f$\mathbb{R}^2\f$ element.
  //!
  //! from_cylindrical first two inputs are the polar coordinates of the first \f$\mathbb{C}\f$
  //! component of the quaternion.
  //! The third and fourth inputs are placed into the third and fourth \f$\mathbb{R}\f$
  //! components of the quaternion, respectively.
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
  //!     auto from_cylindrical(auto r, auto angle, auto h1, auto h2) const noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!  * `r`, angle`, `h1`, `h2`
  //!
  //! **Return value**
  //!
  //! the quaternion value.
  //!
  //!  @groupheader{Example}
  //!
  //! @godbolt{doc/quaternion/regular/conversions.cpp}
  //!  @}
  //================================================================================================

  namespace tag { struct from_cylindrical_; }
  template<> struct supports_conditional<tag::from_cylindrical_> : std::false_type {};

  EVE_MAKE_CALLABLE(from_cylindrical_, from_cylindrical);

  namespace detail
  {
    template<ordered_value V,  ordered_value U,  ordered_value W,  ordered_value T>
    EVE_FORCEINLINE auto from_cylindrical_( EVE_SUPPORTS(cpu_)
                               , V const & r
                               , U const & angle
                               , W const & h1
                               , T const & h2) noexcept
    {
      return arithmetic_call(from_cylindrical, r, angle, h1, h2);
    }

    template<floating_value T>
    EVE_FORCEINLINE auto from_cylindrical_(EVE_SUPPORTS(cpu_)
                                           , T const & r
                                           , T const & angle
                                           , T const & h1
                                           , T const & h2) noexcept
    {
      using z_t = eve::as_quaternion_t<T>;
      auto [sa, ca] = sincos(angle);
      return z_t{r*ca, r*sa, h1, h2};
    }
  }
}
