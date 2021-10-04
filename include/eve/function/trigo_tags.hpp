//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  struct full_circle_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };
  //================================================================================================
  //! @addtogroup trigonometric
  //! @{
  //! @var quarter_circle
  //!
  //! @brief  Higher-order @callable imbuing a limited range semantic onto other @callable{s}.
  //!
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but gives the correct result
  //! in \f$[-\pi/4, +\pi/4]\f$ only and Nan outside. (respectively \f$[-45, +45]\f$ if
  //! the input in in degrees,  \f$[-0.25, +0.25]\f$ if the input in in \f$\pi\f$ multiples)
  //!
  //! quarter_circle is currently supported only by direct trigonometric object functions
  //! This decorator leads to the fastest algorithm at full precision.
  //!
  //! Generally speaking, beside the call with no decorator, direct trigonometric object functions have
  //! three other decorator flavours eve::small,  eve::medium,  eve::big
  //!
  //! Without any decorator the call to a direct trigonometric object function
  //! tests the input value to choose among the decorated ones the best fit.
  //! Of course, with SIMD parameter the fit is the interval containing all the vector elements.
  //!
  //! The rationale to provide these flavours is that the more costly part of the computation of a
  //! trigonometric function from the radian angle is the reduction of the angle to an angle
  //! in \f$[-\pi/4, +\pi/4]\f$ in radian (resp. \f$[-45, +45]\f$ in degrees or \f$[-0.25, +0.25]\f$ in \pi multiples)
  //! and a quadrant value in\f$[0, 3]\f$.
  //!
  //!  @}
  //================================================================================================
  // range limitation decorator objects for direct trigonometric functions
  struct quarter_circle_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  //================================================================================================
  //! @addtogroup trigonometric
  //! @{
  //! @var small
  //!
  //! @brief  Higher-order @callable imbuing  a limited range standard semantic onto other @callable{s}.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation,
  //! but gives the correct result for \f$[-\pi/2, +\pi/2]\f$ only and Nan outside.
  //! (respectively \f$[-90, +90]\f$ if
  //! the input in in degrees,  \f$[-0.5, +0.5]\f$ if the input in in \f$\pi\f$ multiples)
  //!
  //! small is currently supported only by direct trigonometric object functions
  //!
  //! Beside the call with no decorator, direct trigonometric object functions have
  //! three other decorator flavours eve::quarter_circle,  eve::medium,  eve::big
  //!
  //! Without any decorator the call to a direct trigonometric object function
  //! tests the input value to choose among the decorated ones the best fit.
  //! Of course, with SIMD parameter the fit is the interval containing all the vector elements.
  //!
  //! The rationale to provide these flavours is that the more costly part of the computation of a
  //! trigonometric function from the radian angle is the reduction of the angle to an angle
  //! in \f$[-\pi/4, +\pi/4]\f$ in radian (resp. \f$[-45, +45]\f$ in degrees or \f$[-0.25, +0.25]\f$ in \pi multiples)
  //! and a quadrant value in\f$[0, 3]\f$.
  //!
  //!  @}
  //================================================================================================
  struct small_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  //================================================================================================
  //! @addtogroup trigonometric
  //! @{
  //! @var medium
  //!
  //! @brief  Higher-order @callable imbuing  a limited range semantic onto other @callable{s}.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation,
  //! but  gives the correct result for \f$|x| < 536870912.0f\f$ (float) or  \f$ |x| < 2.0e14 \f$ (double)
  //! (\f$x\f$ in radian) and degrades gently for greater values.
  //! (the bounds are to be converted if the input is  \f$\pi\f$ multiples, and in degrees the call is currently equivalent to big)
  //!
  //! medium is currently supported only by direct trigonometric object functions
  //!
  //! Beside the call with no decorator, direct trigonometric object functions have
  //! three other decorator flavours eve::quarter_circle,  eve::small,  eve::big
  //!
  //! Without any decorator the call to a direct trigonometric object function
  //! tests the input value to choose among the decorated ones the best fit.
  //! Of course, with SIMD parameter the fit is the interval containing all the vector elements.
  //!
  //! The rationale to provide these flavours is that the more costly part of the computation of a
  //! trigonometric function from the radian angle is the reduction of the angle to an angle
  //! in \f$[-\pi/4, +\pi/4]\f$ in radian (resp. \f$[-45, +45]\f$ in degrees or \f$[-0.25, +0.25]\f$ in \pi multiples)
  //! and a quadrant value in\f$[0, 3]\f$.
  //!
  //! medium use a relaxed reduction scheme that can provide degraded precision results for very large inputs
  //!
  //!  @}
  //================================================================================================
   struct medium_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  //================================================================================================
  //! @addtogroup trigonometric
  //! @{
  //! @var big
  //!
  //! @brief  Higher-order @callable imbuing a direct computation semantic onto other @callable{s}.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation,
  //! but  gives the correct result in the whole range,  always using the full reduction algorithm.
  //!
  //! big is currently supported only by direct trigonometric object functions
  //!
  //! Beside the call with no decorator, direct trigonometric object functions have
  //! three other decorator flavours eve::quarter_circle,  eve::small,  eve::medium
  //!
  //! Without any decorator the call to a direct trigonometric object function
  //! tests the input value to choose among the decorated ones the best fit.
  //! Of course, with SIMD parameter the fit is the interval containing all the vector elements.
  //!
  //! The rationale to provide these flavours is that the more costly part of the computation of a
  //! trigonometric function from the radian angle is the reduction of the angle to an angle
  //! in \f$[-\pi/4, +\pi/4]\f$ in radian (resp. \f$[-45, +45]\f$ in degrees or \f$[-0.25, +0.25]\f$ in \pi multiples)
  //! and a quadrant value in\f$[0, 3]\f$.
  //!
  //! big use the heaviest reduction scheme in all situations
  //!
  //!  @}
  struct big_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using full_circle_type     = decorated<full_circle_()>;
  using quarter_circle_type = decorated<quarter_circle_()>;
  using half_circle_type      = decorated<small_()>;
  using medium_type     = decorated<medium_()>;
  using big_type        = decorated<big_()>;

  inline constexpr full_circle_type      const full_circle      = {};
  inline constexpr quarter_circle_type  const quarter_circle  = {};
  inline constexpr half_circle_type       const small       = {};
  inline constexpr medium_type      const medium      = {};
  inline constexpr big_type         const big         = {};
}
