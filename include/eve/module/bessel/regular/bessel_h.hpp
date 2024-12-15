//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include "eve/traits/as_logical.hpp"
#include <kyosu/details/callable.hpp>
#include <kyosu/bessel.hpp>


namespace kyosu
{

  template<typename Options>
  struct bessel_h_t : eve::strict_elementwise_callable<bessel_h_t, Options, eve::spherical_option, eve::cylindrical_option, kind_1_option, kind_2_option>
  {
    template<eve::scalar_value N, typename Z>
    requires(concepts::real<Z> || concepts::cayley_dickson<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z) const noexcept
    {
      constexpr int Kind = Options::contains(kind_2) ? 2 : 1;
      if constexpr(concepts::complex<Z> )
      {
        if constexpr(eve::integral_scalar_value<N>)
        {
          if constexpr(Options::contains(eve::spherical))
          {
            if (eve::is_ltz(n))
            {
              using u_t = eve::underlying_type_t<Z>;
              return _::sb_hr<Kind>(u_t(n), z);
            }
            else
              return _::sb_hn<Kind>(n, z);
          }
          else
            return _::cb_hn<Kind>(n, z);
        }
        else if constexpr( eve::floating_scalar_value<N>)
        {
          if constexpr(Options::contains(eve::spherical))
            return _::sb_hr<Kind>(n, z);
          else
            return _::cb_hr<Kind>(n, z);
        }
      }
      else
        return _::cayley_extend_rev(*this, n, z);
    }

    template<eve::scalar_value N, typename Z, std::size_t S>
    requires(concepts::real<Z> || concepts::complex<Z>)
      KYOSU_FORCEINLINE constexpr auto  operator()(N const& n, Z const & z, std::span<Z, S> hs) const noexcept
    {
      constexpr int Kind = Options::contains(kind_2) ? 2 : 1;
      if constexpr(eve::integral_scalar_value<N>)
      {
        if constexpr(Options::contains(eve::spherical))
       {
          if (eve::is_ltz(n))
          {
            using u_t = eve::underlying_type_t<Z>;
            return _::sb_hr(u_t(n), z, hs);
          }
          else
            return _::sb_hn<Kind>(n, z, hs);
        }
        else
          return _::cb_hn<Kind>(n, z, hs);
      }
      else
      {
        if constexpr(Options::contains(eve::spherical))
          return _::sb_hr<Kind>(n, z, hs);
        else
          return _::cb_hr<Kind>(n, z, hs);
      }
    }

    KYOSU_CALLABLE_OBJECT(bessel_h_t, bessel_h_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  bessel_h
//!   @brief Computes the spherical or cylindrical Hankel functions,
//!   extended to the complex plane and cayley_dickson  algebras.
//!
//!   @code
//!   #include <kyosu/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace kyosu
//!   {
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson T>    constexpr auto bessel_h(N n, T z)                                       noexcept; //1
//!      template<eve;scalar_value N, kyosu::concepts::real T>              constexpr T    bessel_h(N n, T z)                                       noexcept; //1
//!      template<eve;scalar_value N, kyosu::concepts::complex T, size_t S> constexpr auto bessel_h(N n, T z, std::span<Z, S> chs)                  noexcept; //2
//!      template<eve;scalar_value N, kyosu::concepts::real T, size_t S>    constexpr T    bessel_h(N n, T z, std::span<Z, S> chs)                  noexcept; //2
//!
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson T>    constexpr auto bessel_h[spherical](N n, T z)                            noexcept; //3
//!      template<eve;scalar_value N, kyosu::concepts::real T>              constexpr T    bessel_h[spherical](N n, T z)                            noexcept; //3
//!      template<eve;scalar_value N, kyosu::concepts::complex T, size_t S> constexpr auto bessel_h[spherical](N n, T z, std::span<Z, S> shs)       noexcept; //4
//!      template<eve;scalar_value N, kyosu::concepts::real T, size_t S>    constexpr T    bessel_h[spherical](N n, T z, std::span<Z, S> shs)       noexcept; //4
//!
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson T>    constexpr auto bessel_h[kind_2](/*any previous overloads*/)             noexcept; //5
//!      template<eve;scalar_value N, kyosu::concepts::cayley_dickson T>    constexpr auto bessel_h[kind_2][spherical](/*any previous overloads*/)  noexcept; //6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`: scalar  order (integral or floating)
//!     * `z`: Value to process.
//!     * `shs`, `chs`  : std::span of T
//!
//!   **Return value**
//!
//!     1. returns \f$H_n\f$(z) (cylindrical first kind).
//!     2. Same as 1,  but chs is filled by the lesser orders.
//!     3. returns \f$h_n\f$(z) (spherical).
//!     4. Same as 3,  but shs is filled by the lesser orders.
//!     5. Same as 1., 2., 3., 4. but returns second kind Hankel functions values.
//!     6. Same as 1., 2., 3., 4. but returns second kind spherical Hankel functions values.
//!
//!  @note
//!    * Let \f$ i =  \lfloor |n| \rfloor \f$ and \f$ j=|n|-i\f$. If \f$n\f$ is
//!        positive the lesser order are \f$(\pm j, \pm(j+1), \dots,  \pm(j+i)) \f$
//!        with \f$+\f$ sign if \f$n\f$ is positive and  \f$-\f$ sign if \f$n\f$ is negative.
//!    * The span parameters are filled according the minimum of their allocated size and \f$i\f$.
//!    * `cylindical` and `kind_1` options can be used and their results are identical to the regular call (no option).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Hankel Function](https://mathworld.wolfram.com/HankelFunction.html)
//!   *  [Wikipedia: Bessel function](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Bessel functions](https://dlmf.nist.gov/10.2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/bessel_h.cpp}
//======================================================================================================================
  inline constexpr auto bessel_h = eve::functor<bessel_h_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
