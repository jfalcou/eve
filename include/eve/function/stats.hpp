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

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  // Function decorator - cdf mode
  struct cdf_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using cdf_type = decorated<cdf_()>;
  inline constexpr cdf_type const cdf = {};

  //================================================================================================
  // Function decorator - pdf mode
  struct pdf_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using pdf_type = decorated<pdf_()>;
  inline constexpr pdf_type const pdf = {};

  //================================================================================================
  // Function decorator - invcdf mode
  struct invcdf_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using invcdf_type = decorated<invcdf_()>;
  inline constexpr invcdf_type const invcdf = {};

  //================================================================================================
  // Function decorator - mean mode
  struct mean_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using mean_type = decorated<mean_()>;
  inline constexpr mean_type const mean = {};

  //================================================================================================
  // Function decorator - median mode
  struct median_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using median_type = decorated<median_()>;
  inline constexpr median_type const median = {};

  //================================================================================================
  // Function decorator - mode mode
  struct mode_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using mode_type = decorated<mode_()>;
  inline constexpr mode_type const mode = {};

  //================================================================================================
  // Function decorator - scale mode
  struct scale_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using scale_type = decorated<scale_()>;
  inline constexpr scale_type const scale = {};


  //================================================================================================
  // Function decorator - var mode
  struct var_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using var_type = decorated<var_()>;
  inline constexpr var_type const var = {};

  //================================================================================================
  // Function decorator - stdev mode
  struct stdev_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using stdev_type = decorated<stdev_()>;
  inline constexpr stdev_type const stdev = {};

  //================================================================================================
  // Function decorator - entropy mode
  struct entropy_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using entropy_type = decorated<entropy_()>;
  inline constexpr entropy_type const entropy = {};

  //================================================================================================
  // Function decorator - fisher mode
  struct fisher_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using fisher_type = decorated<fisher_()>;
  inline constexpr fisher_type const fisher = {};

  //================================================================================================
  // Function decorator - quantile mode
  struct quantile_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using quantile_type = decorated<quantile_()>;
  inline constexpr quantile_type const quantile = {};

  //================================================================================================
  // Function decorator - skewness mode
  struct skewness_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using skewness_type = decorated<skewness_()>;
  inline constexpr skewness_type const skewness = {};

  //================================================================================================
  // Function decorator - kurtosis mode
  struct kurtosis_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using kurtosis_type = decorated<kurtosis_()>;
  inline constexpr kurtosis_type const kurtosis = {};
}
