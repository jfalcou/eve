//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CONVERT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CONVERT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/max.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/saturate.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

namespace eve::detail
{
  // Don't do anything if we idem-cast
  template<typename IN>
  EVE_FORCEINLINE auto convert_ ( EVE_SUPPORTS(cpu_),
                                    IN const & v0, as_<IN> const&
                                  ) noexcept
  requires(IN, vectorizable<IN>)
  {
    return v0;
  }

  template<typename IN, typename OUT>
  EVE_FORCEINLINE auto convert_( EVE_SUPPORTS(cpu_),
                                 IN const & v0, as_<OUT> const& tgt
                               ) noexcept
  requires(OUT, vectorizable<IN>, vectorizable<OUT>)
  {
//     std::cout <<  "scalar " << std::endl;
//     std::cout <<  "Valmin<IN>()                   " << Valmin<IN>() << std::endl;
//     std::cout <<  "v0                             " << v0 << std::endl; 
//     std::cout <<  "is_eqz(Valmin<IN>()-v0)        "<< is_eqz(Valmin<IN>()-v0) << std::endl;
//     std::cout <<  "static_cast<OUT>(Valmin<IN>()) " << static_cast<OUT>(Valmin<IN>())<< std::endl;
//     std::cout <<  std::hexfloat <<  "v0 hex                            " << v0 << std::endl;
//     std::cout <<  std::hexfloat <<  "Valmin<IN>() hex                  " << Valmin<IN>() <<  std::dec << std::endl;
    return static_cast<OUT>(v0);
  }
    
  //////////////////////////////////////////////////////////////////////////////////////
  // saturated case
  //////////////////////////////////////////////////////////////////////////////////////

  template<typename IN, typename OUT>
  EVE_FORCEINLINE auto convert_( EVE_SUPPORTS(cpu_)
                                 , saturated_type const &
                                 , IN const & v0, as_<OUT> const& tgt
                                 ) noexcept
  requires(OUT, vectorizable<IN>, vectorizable<OUT>)
  {
    if constexpr(std::is_same_v<IN, OUT>)
    {
      return v0; 
    }
    else if constexpr(std::is_integral_v<OUT>)
    {
      if constexpr(std::is_floating_point_v<IN>) // input is floating point
      {
        if constexpr(sizeof(OUT) != sizeof(IN))
        {
          return convert(saturate(as<OUT>(), v0), as<OUT>()); 
        }
        else if constexpr(std::is_signed_v<OUT>) //float -> int32 or double -> int64
        {
          if constexpr(eve::platform::supports_nans)
          {
            if (is_nan(v0)) return Zero<OUT>();
          }
          if (v0 >= Valmax<OUT>()) return Valmax<OUT>();
          if (v0 <= Valmin<OUT>()) return Valmin<OUT>();
          return static_cast<OUT>(v0);
        }
        else //float -> uint32 or double -> uint64
        {
          if (is_ngez(v0)) return Zero<OUT>();
          if (v0 >= Valmax<OUT>()) return Valmax<OUT>();
          return static_cast<OUT>(v0);
        }
      }
      else // input is integral
      {
        if constexpr(sizeof(OUT) > sizeof(IN))
        {
          return convert(v0, tgt);
        }
        else
        {
          IN Vax = Valmax<OUT>();
          IN Vim = Valmin<OUT>();
          return static_cast<OUT>(clamp(v0, Vim, Vax));
        }        
      }
    }
    else // OUTPUT is floating point   
    {
      return convert(v0, tgt);  
    } 
  } 
}

#endif
