//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/fft/utils/soac2ri.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/fft/utils/aos_soa.hpp>
#include <type_traits>
#include <execution>

namespace eve::detail
{
  template<decorator D, range R, scalar_value T>
  EVE_FORCEINLINE void scaleit_(EVE_SUPPORTS(cpu_)
                            , D const &
                            , R & f
                            , T const & fac) noexcept
  requires(eve::is_complex_v<typename R::value_type> && is_one_of<D>(types<aos_type, soa_type> {}))
  {
    if (fac != one(as(fac)))
    {
      using e_t = typename R::value_type;
      auto  mul = [fac]<typename C>(C x){
        return x*fac;
      };
      if constexpr(std::same_as<D, aos_type>)
      {
        if constexpr(std::is_floating_point_v<e_t>)
        {
          eve::algo::transform_inplace(f, mul);
        }
        else
        {
          std::transform(f.data(), f.data()+f.size(), f.data(), mul);
        }
      }
      else if constexpr(std::same_as<D, soa_type>)
      {
        auto [fr, fi] = soac2ri(f);
        eve::algo::transform_inplace(fr, mul);
        eve::algo::transform_inplace(fi, mul);
      }
    }
  }

  template<range R, scalar_value T>
  EVE_FORCEINLINE void scaleit_(EVE_SUPPORTS(cpu_)
                            , R & fr
                            , R & fi
                            , T const & fac) noexcept
  {
    if (fac != one(as(fac)))
    {
      auto  mul = [fac]<typename C>(C x){
        return x*fac;
      };
      eve::algo::transform_inplace(fr, mul);
      eve::algo::transform_inplace(fi, mul);
    }
  }
}
