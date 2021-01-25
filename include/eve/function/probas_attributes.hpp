//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/implementation.hpp>

namespace eve
{

  template<typename D>
  concept distribution = requires(D)
  {
    typename D::is_distribution_t;
  };

  EVE_MAKE_CALLABLE(cdf_, cdf);              // cumulative distribution function
  EVE_MAKE_CALLABLE(pdf_, pdf);              // density function
  EVE_MAKE_CALLABLE(invcdf_, invcdf);        // inverse of cumulative distribution function (quantile)
  EVE_MAKE_CALLABLE(mgf_, mgf);              // moment generating function
  EVE_MAKE_CALLABLE(cf_, cf);                // characteristic function
  EVE_MAKE_CALLABLE(parameters_, parameters);//parameters stored in struct
  EVE_MAKE_CALLABLE(kullback_, kullback);    // kullback-leiber divergence
  EVE_MAKE_CALLABLE(mean_, mean);            // mean
  EVE_MAKE_CALLABLE(median_, median);        // median
  EVE_MAKE_CALLABLE(mode_, mode);            // mode
  EVE_MAKE_CALLABLE(mad_, mad);              // mean absolute deviation
  EVE_MAKE_CALLABLE(stdev_, stdev);          // standard deviation
  EVE_MAKE_CALLABLE(var_, var);              // variance
  EVE_MAKE_CALLABLE(entropy_, entropy);      // entropy
  EVE_MAKE_CALLABLE(fisher_, fisher);        // fisher information
  EVE_MAKE_CALLABLE(skewness_, skewness);    // skewness
  EVE_MAKE_CALLABLE(kurtosis_, kurtosis);    // kurtosis
  EVE_MAKE_CALLABLE(scale_, scale);          // scale

  namespace detail
  {
    template < distribution D,  floating_real_value U>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_), D const &d, U const &x ) noexcept  = delete;
    template < distribution D,  floating_real_value U>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_), D const &d, U const &x ) noexcept  = delete;
    template < distribution D,  floating_real_value U>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_), D const &d, U const &x ) noexcept  = delete;
    template < distribution D,  floating_real_value U>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_), D const &d, U const &x ) noexcept  = delete;
    template < distribution D,  floating_real_value U>
    EVE_FORCEINLINE  auto  cf_(EVE_SUPPORTS(cpu_), D const &d, U const &x ) noexcept  = delete;

    template < distribution D>
    EVE_FORCEINLINE  auto scale_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto mad_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto kullback_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto fisher_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
    template < distribution D>
    EVE_FORCEINLINE  auto parameters_(EVE_SUPPORTS(cpu_), D const &d ) noexcept  = delete;
  }
}
