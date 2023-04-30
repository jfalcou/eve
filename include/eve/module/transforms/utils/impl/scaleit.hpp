//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/transforms/utils/aos_soa.hpp>
#include <type_traits>
#include <execution>

namespace eve::detail
{
  template<decorator D, range R, scalar_value T>
  EVE_FORCEINLINE void scaleit_(EVE_SUPPORTS(cpu_)
                            , D const &
                            , R & f
                            , T const & fac) noexcept
  requires(is_one_of<D>(types<aos_type, soa_type> {}))
  {
    if (fac != one(as(fac)))
    {
      using e_t = typename R::value_type;
      auto mul = [fac](auto &c) noexcept{
        return c *= fac;
      };
      if constexpr(std::same_as<D, aos_type>)
      {
        if constexpr(std::is_floating_point_v<e_t>)
        {
          eve::algo::transform_inplace(f, mul);
        }
        else
        {  //TODO make eve::transform_inplace work here
           std::transform(f.data(), f.data()+std::size(f), f.data(), mul);
        }
      }
      else if constexpr(std::same_as<D, soa_type>)
      {
        eve::algo::transform_inplace(f,  mul);
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
      auto  mul = [fac]<typename C>(C x) noexcept{
        return x*fac;
      };
      eve::algo::transform_inplace(fr, mul);
      eve::algo::transform_inplace(fi, mul);
    }
  }
}
