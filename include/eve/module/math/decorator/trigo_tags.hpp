//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  // range limitation decorators objects for direct trigonometric functions
  struct full_circle_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };
  //================================================================================================
  //! @addtogroup math_trig
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
  //!  @}
  //================================================================================================
  struct quarter_circle_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  //================================================================================================
  //! @addtogroup math_trig
  //! @{
  //! @var half_circle
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
  //!  @}
  //================================================================================================
  struct half_circle_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  namespace detail
  {
    // medium and big decorators are internal so in detail
    //================================================================================================
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
    //! but  gives the correct result for \f$|x| < 1.76858e+15f\f$ (float) or  \f$ |x| < 2.0e14 \f$ (double)
    //! (\f$x\f$ in radian) and degrades gently for greater values.
    //! (the bounds are to be converted if the input is  \f$\pi\f$ multiples, and in degrees the call is currently equivalent to big)
    //! medium use a relaxed reduction scheme
    //!
    //================================================================================================
    struct medium_
    {
      template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
    };

    //================================================================================================
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
    struct big_
    {
      template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
    };

    using medium_type     = decorated<medium_()>;
    using big_type        = decorated<big_()>;
    inline constexpr medium_type      const medium      = {};
    inline constexpr big_type         const big         = {};
  }
  using full_circle_type      = decorated<full_circle_()>;
  using quarter_circle_type   = decorated<quarter_circle_()>;
  using half_circle_type      = decorated<half_circle_()>;

  inline constexpr full_circle_type     const full_circle      = {};
  inline constexpr quarter_circle_type  const quarter_circle   = {};
  inline constexpr half_circle_type     const half_circle      = {};
}
