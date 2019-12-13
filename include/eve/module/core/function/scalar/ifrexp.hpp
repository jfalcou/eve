//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_IFREXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_IFREXP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/tags.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_shr.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_andnot.hpp>   
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/maxexponent.hpp> 
#include <eve/constant/maxexponentm1.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/expobits_mask.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/twotonmb.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/raw.hpp>
#include <eve/detail/meta.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Raw case
  template<typename T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , raw_type const &
                                        , T a0) noexcept
  requires(std::tuple<T, as_integer_t<T, signed>>, floating_point<T>)
  {
    using t_t = value_type_t<T>;
    auto r1   = bitwise_and(Expobits_mask<T>(), a0);
    auto x    = bitwise_notand(Expobits_mask<T>(), a0);
    return  std::make_tuple( bitwise_or(Half<T>(), x),
                             bitwise_shr(r1,Nbmantissabits<t_t>()) - Maxexponentm1<t_t>());
  }
  
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                        , T a0) noexcept
  requires(std::tuple<T, as_integer_t<T, signed>>, floating_point<T>)
  {
    using i_t = as_integer_t<T, signed>;
    if(!a0) return {T(0),i_t(0)};
    else    return raw_(ifrexp)(a0); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // Pedantic case
  template<typename T>
  EVE_FORCEINLINE constexpr auto ifrexp_(EVE_SUPPORTS(cpu_)
                                    , pedantic_type const & 
                                    , T a0) noexcept
  requires(std::tuple<T, as_integer_t<T, signed>>, floating_point<T>)
  {
    using i_t = as_integer_t<T, signed>;
    if (a0 == 0 || is_not_finite(a0))
    {
      return {a0, i_t(0)};
    }
    else
    {
      auto nmb  = Nbmantissabits<T>();
      i_t r1    = bitwise_and(Expobits_mask<T>(), a0);  // extract exp.
      if constexpr(eve::platform::supports_denormals)
      {
        i_t t = i_t(0);
        if(is_eqz(r1)) // denormal
        {
          a0 *= Twotonmb<T>();
          r1  = bitwise_and(Expobits_mask<T>(), a0);  // extract exp. again
          t   = nmb;
        }        
        T x  = bitwise_andnot(a0, Expobits_mask<T>());        // clear exp. in a0
        r1 = bitwise_shr(r1,nmb)- Maxexponentm1<T>();         // compute exp.
        if (r1 > Limitexponent<T>()) return {a0, i_t(0)};       
        r1 -= t;
        return std::make_tuple(bitwise_or(x,Half<T>()), r1);
      }
      else
      {
        T x  = bitwise_andnot(a0, Expobits_mask<T>());        // clear exp. in a0
        r1 = bitwise_shr(r1,nmb)- Maxexponentm1<T>();         // compute exp.
        if (r1 > Limitexponent<T>()) return {a0, i_t(0)};
        return std::make_tuple(bitwise_or(x,Half<T>()), r1);
      }
    }
  }
}

#endif
