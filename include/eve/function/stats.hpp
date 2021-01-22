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


}
