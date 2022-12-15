//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/detail/overload.hpp>
#include <array>


namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//! @var faddeeva
//!
//! @brief Callable object computing \f$e^{-z^2}\mathrm{erfc}(-iz)\f$ the scaled complex error func
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
//!      T faddeeva(T z) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `z`:   [floatingl](@ref eve::floating_value) or [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   Returns \f$e^{-z^2}\mathrm{erfc}(-iz)\f$ the scaled complex error func
//!
//!  @groupheader{Example}
//!
//!   **Complex version**
//!
//!  @godbolt{test/doc/complex/faddeeva.cpp}
//!  @}
//================================================================================================
  EVE_MAKE_CALLABLE(faddeeva_, faddeeva);
  namespace detail
  {

    template<floating_ordered_value V>
    EVE_FORCEINLINE auto faddeeva_( EVE_SUPPORTS(cpu_)
                                  , V const & v) noexcept
    {
      using c_t = eve::as_complex_t<V>;
      return faddeeva(c_t{v, 0});
    }

    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::faddeeva_
                                               , Z z) noexcept
    {
      using v_t = eve::as_real_t<Z>;
      using real_t = eve::element_type_t<v_t>;
      auto const   sqrtpi = sqrt_pi(as<real_t>());
      auto const iosqrtpi = i(as<real_t>())/sqrtpi;
      auto fexp =  [iosqrtpi, sqrtpi](auto z){//Fourier expansion approximation

        constexpr real_t tauM = 12;
        constexpr real_t tauM2= 144;
        constexpr size_t  maxN = 23;
        constexpr std::array<real_t, maxN> aN = { //Fourier coefficients
          2.758402332921771e-01, 2.245739552246158e-01, 1.594149382739117e-01, 9.866576641545419e-02, 5.324414078763941e-02
          , 2.505215000539365e-02, 1.027746567053954e-02, 3.676164332844847e-03, 1.146493641242233e-03, 3.117570150461976e-04
          , 7.391433429603010e-05, 1.527949342800837e-05, 2.753956608221073e-06, 4.327858781901246e-07, 5.930030408745884e-08
          , 7.084490307748205e-09, 7.379520635816785e-10, 6.702171606002010e-11, 5.307265163470805e-12, 3.664324113467642e-13
          , 2.205894944941035e-14, 1.157826862628556e-15, 5.298711429467307e-17};
        auto z1 = exp_i(tauM*z);
        auto z2 = tauM2*sqr(z);
        auto FE = sqrtpi/tauM*oneminus(z1)/z2;
        for (size_t n = 1; n <= maxN; ++n)
          FE += (aN[n-1]*dec(sign_alternate(real_t(n))*z1)/(sqr(n*pi(as(tauM))) - z2));
        return  iosqrtpi*tauM2*z*FE;
      };

      auto contfr = [iosqrtpi](auto z){ // the Laplace continued fraction approximation
        constexpr std::array<real_t, 11> bN = {5.5000, 5.0000, 4.5000, 4.0000, 3.5000,
                                               3.0000, 2.5000, 2.0000, 1.5000, 1.0000, 0.5000};
        auto CF = bN[0]/z;
        for (int k = 1; k <= 10; ++k)  CF = bN[k]*rec(z - CF);
        return iosqrtpi*rec(z - CF);
      };

      auto  small_z= [sqrtpi](auto z){
        auto zP2=sqr(z);
        auto  zP4=sqr(zP2);
        auto  zP6=zP2*zP4;
        return (((6 - 6*zP2 + 3*zP4 - zP6)*(15*sqrtpi + i(as<real_t>())*z*(30 + 10*zP2 + 3*zP4)))/(90*sqrtpi));
      };

      auto narr_band = [sqrtpi](auto z, auto aN, auto tauM){ // the narrow band
        real_t tauM2 = sqr(tauM);
        constexpr size_t  maxN = 23;
        auto z1 = cos(tauM*z);
        auto z2 = tauM2*sqr(z);
        auto NB = zero(as(z)); ;
        for (size_t n = 1; n <= maxN; ++n) NB += (aN[n-1]*dec(sign_alternate(real_t(n))*z1)/(sqr(n*eve::pi(as(tauM))) - z2));
        return exp(-sqr(z)) - i(as(z))*(dec(z1)/(tauM*z) - tauM2*z/sqrtpi*NB);
      };


      auto smallim = [narr_band, small_z](auto z){ // approximation at small imag(z)
        constexpr size_t  maxN = 23;
        constexpr std::array<real_t, maxN> aN12 = { //Fourier coefficients
          2.758402332921771e-01, 2.245739552246158e-01, 1.594149382739117e-01, 9.866576641545419e-02, 5.324414078763941e-02
          , 2.505215000539365e-02, 1.027746567053954e-02, 3.676164332844847e-03, 1.146493641242233e-03, 3.117570150461976e-04
          , 7.391433429603010e-05, 1.527949342800837e-05, 2.753956608221073e-06, 4.327858781901246e-07, 5.930030408745884e-08
          , 7.084490307748205e-09, 7.379520635816785e-10, 6.702171606002010e-11, 5.307265163470805e-12, 3.664324113467642e-13
          , 2.205894944941035e-14, 1.157826862628556e-15, 5.298711429467307e-17};
        constexpr std::array<real_t, maxN> aN12_1 = { //Fourier coefficients avoiding poles
          2.738693653257005e-01, 2.237253191645656e-01, 1.597109174949294e-01, 9.963269094255395e-02, 5.431463971403691e-02
          , 2.587496275171680e-02, 1.077185133049561e-02, 3.918760804860615e-03, 1.245818993506881e-03, 3.461058398397597e-04
          , 8.402542038611651e-05, 1.782626047239582e-05, 3.304894416742214e-06, 5.354300211460283e-07, 7.580461285556943e-08
          , 9.378563805151443e-09, 1.013969351293613e-09, 9.579902872635222e-11, 7.909429715194891e-12, 5.706594634502440e-13
          , 3.597962756907448e-14, 1.982367142666383e-15, 9.544634564831883e-17          };

        auto x = real(z);
        auto ind_0 = abs(x)<5e-3;
        auto ind_poles = false_(as(x));
        for(int k = 1; k <= 23; ++k) ind_poles = ind_poles || (abs(x - k*pi(as(x))/12)<1e-4);
        return if_else(!ind_0, if_else(ind_poles
                                      , narr_band(z, aN12_1, real_t(12.1))
                                      , narr_band(z, aN12, real_t(12))
                                      )
                      , small_z(z));
      };

      auto indneg  = is_ltz(imag(z));
      z = if_else(indneg, conj(z), z);
      auto r = Z{nan(as(real(z))), nan(as(real(z)))}; // nan case treated here
      r = if_else(is_infinite(real(z)), zero, r);
      auto notdone = is_finite(z);
      if (eve::any(notdone))
      {
        auto indin  =  sqr_abs(z) <=  real_t(64);
        auto indband =  indin && (imag(z) < real_t(5.0e-3));
        notdone      = next_interval(smallim, notdone, indband, r, z);
        if( eve::any(notdone) )
        {
          notdone = next_interval(fexp, notdone, indin, r, z);
          if( eve::any(notdone) )
          {
            notdone = next_interval(contfr, notdone, notdone, r, z);
          }
        }
      }
      return if_else(indneg, conj(r), r); ;
    }
  }
}
