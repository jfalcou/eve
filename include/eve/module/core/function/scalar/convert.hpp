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
#include <eve/function/pedantic.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/saturate.hpp>
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
    return static_cast<OUT>(v0); 
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  // pedantic case
  //////////////////////////////////////////////////////////////////////////////////////

  template<typename IN, typename OUT>
  EVE_FORCEINLINE auto convert_( EVE_SUPPORTS(cpu_)
                                 , pedantic_type const &
                                 , IN const & v0, as_<OUT> const& tgt
                                 ) noexcept
  requires(OUT, vectorizable<IN>, vectorizable<OUT>)
  {
    return convert(v0, tgt);  
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
      if constexpr(std::is_floating_point_v<IN> || (sizeof(OUT) <= sizeof(IN)))
      {
        return convert(saturate(as<OUT>(v0)), as<OUT>()); 
      }
    }
    else        
    {
      return convert(v0, tgt);  
    } 
  } 
}

#endif
