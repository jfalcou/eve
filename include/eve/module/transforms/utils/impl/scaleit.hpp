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
  template<range R, scalar_value T>
  EVE_FORCEINLINE void scaleit_(EVE_SUPPORTS(cpu_)
                            , R & f
                            , T const & norm) noexcept
  {
    if (norm != one(as(norm)))
    {
      using t_t = typename R::value_type;
      using e_t = underlying_type_t<t_t>;
      e_t fac(norm);
      auto mul = [fac](auto &c) noexcept{return c *= fac;};
      if constexpr(eve::algo::is_soa_vector_v<R>)
      {
        eve::algo::transform_inplace[eve::algo::unroll<2>](f,  mul);
      }
      else
      {
        if constexpr(std::is_floating_point_v<t_t>)
        {
          eve::algo::transform_inplace[eve::algo::unroll<2>](f, mul);
        }
        else
        {  //TODO make eve::transform_inplace work here
           std::transform(f.data(), f.data()+std::size(f), f.data(), mul);
        }
      }
    }
  }

  template<range R, scalar_value T>
  EVE_FORCEINLINE void scaleit_(EVE_SUPPORTS(cpu_)
                            , R & fr
                            , R & fi
                            , T const & norm) noexcept
  requires (std::is_floating_point_v<typename R::value_type>)
  {
   if (norm != one(as(norm)))
    {
      using t_t = typename R::value_type;
      using e_t = underlying_type_t<t_t>;
      e_t fac(norm);
      auto  mul = [fac]<typename C>(C x) noexcept{return x*fac;};
      eve::algo::transform_inplace(fr, mul);
      eve::algo::transform_inplace(fi, mul);
    }
  }
}
