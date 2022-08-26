//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex/regular/detail/special.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <array>

namespace eve
{
//================================================================================================
//! @addtogroup complex
//! @{
//! @var deta
//!
//! @brief Callable object computing \f$ \sum_0^\infty \frac{(-1)^n}{(kn+1)^z}\f$
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/complex.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< like<complex> T >
//!      T deta(T z) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `z`:   [floatingl](@ref eve::floating_real_value) or [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   Returns the Dirichlet sum \f$ \sum_0^\infty \frac{(-1)^n}{(kn+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/deta.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/deta.cpp}
//!  @}
//================================================================================================
  EVE_MAKE_CALLABLE(deta_, deta);
  namespace detail
  {
    template<unsigned_scalar_value N, floating_real_value V>
    EVE_FORCEINLINE auto deta_( EVE_SUPPORTS(cpu_)
                              , N const & n
                              , V const & v) noexcept
    {
      return real(deta(n, as_complex_t<V>(v, 0)));
    }

    template<unsigned_scalar_value K, typename Z>
    EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::deta_
                                                , K const & kk, Z z) noexcept
    {
      using v_t = eve::as_real_t<Z>;
      using real_t = eve::element_type_t<v_t>;
      auto k = real_t(kk);
      auto [rz, iz] = z;
      auto iszero = is_eqz(z);
      auto isreal = is_eqz(iz);
      auto isneg  = is_lez(rz);
      auto isnegreal = isreal && isneg;
      auto isodd  = isnegreal && is_odd(rz);
      auto iseven = isnegreal && is_even(rz);

      auto r=half(as(rz)); // reflection point
      auto reflect = rz < r;
      z =  if_else(reflect, oneminus(z), z);

      std::array<real_t, 64> cm = {
        .27105054312137610850e-19
        -.17889335846010823161e-17,
        .58167446553847312884e-16,
        -.12421162189080181548e-14,
        .19593322190397666205e-13,
        -.24347803504257137241e-12,
        .24823251635643084345e-11,
        -.21352608103961806529e-10,
        .15816215942184366772e-9,
        -.10246226511017621219e-8,
        .58768014045093054654e-8,
        -.30137695171547022183e-7,
        .13931171712321674741e-6,
        -.58440580661848562719e-6,
        .22376124247437700378e-5,
        -.78585149263697370338e-5,
        .25423835243950883896e-4,
        -.76053287924037718971e-4,
        .21106516173760261250e-3,
        -.54504190222378945440e-3,
        .13131884053420191908e-2,
        -.29592166263096543401e-2,
        .62512730682449246388e-2,
        -.12405987285776082154e-1,
        .23176737166455607805e-1,
        -.40840766970770029873e-1,
        .68016197438946063823e-1,
        -.10726959700408922397,
        .16054206784249779846,
        -.22851039270529494523,
        .31007238254065152134,
        -.40215850009669926857,
        .50000000000000000000,
        -.59784149990330073143,
        .68992761745934847866,
        -.77148960729470505477,
        .83945793215750220154,
        -.89273040299591077603,
        .93198380256105393618,
        -.95915923302922997013,
        .97682326283354439220,
        -.98759401271422391785,
        .99374872693175507536,
        -.99704078337369034566,
        .99868681159465798081,
        -.99945495809777621055,
        .99978893483826239739,
        -.99992394671207596228,
        .99997457616475604912,
        -.99999214148507363026,
        .99999776238757525623,
        -.99999941559419338151,
        .99999986068828287678,
        -.99999996986230482845,
        .99999999412319859549,
        -.99999999897537734890,
        .99999999984183784058,
        -.99999999997864739190,
        .99999999999751767484,
        -.99999999999975652196,
        .99999999999998040668,
        -.99999999999999875788,
        .99999999999999994183,
        -.99999999999999999821,
        .99999999999999999997
      };

      auto f = zero(as(z));
      auto n = eve::algo::views::reverse(eve::algo::views::iota_with_step(one(as<real_t>()), k, cm.size()));
      auto cur =  n.begin();
      for(size_t i=0; i < cm.size(); ++i, ++cur)
      {
        auto j = read(cur);
        f += cm[i]*pow(j, -z);
      }
      if (none(reflect)) return f;

      auto reflection = [&](auto f){
        if (k == 1){
          auto u = dec(exp2(z));
          auto t = -2*u/dec(u)/pow(pi(as(real(f))), z);;
          f = if_else(reflect, t*cospi(half(as(real(f)))*z)*tgamma(z)*f, f);
          f = if_else(iszero, half(as(f)), f);
          f = if_else(iseven, zero, f);
        }
        else if (k == 2){
          f=if_else(reflect, pow(two_o_pi(as(f)), z)*sinpi(z)*tgamma(z)*f, f);
          f=if_else(isodd, zero, f);
        }
        else
        {
          f=if_else(reflect, allbits, f);
        }
        return f;
      };
      return reflection(f);
    }
  }
}
