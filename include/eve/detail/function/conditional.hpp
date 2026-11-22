//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/as.hpp>
#include <eve/as_element.hpp>
#include <eve/conditional.hpp>
#include <eve/concept/generator.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/if_else.hpp>

EVE_NAMESPACE::_
{
  //================================================================================================
  // What's the alternative for this case ?
  //================================================================================================
  template<conditional_expr C, typename Target, typename Arg>
   Target alternative(C const& c, Arg a0, as<Target> const&)
  {
    if constexpr( C::has_alternative )
    {
      if constexpr( generator<typename C::alternative_type> )
        return Target{ c.alternative(as_element<Target>{}) };
      else
        return Target{ convert(c.alternative, as_element<Target>{}) };
    }
    else
    {
      if      constexpr(logical_value<Target>)    return false_(as<Target>());
      else if constexpr(std::same_as<Arg,Target>) return a0;
      else if constexpr(scalar_value<Arg>)        return Target(a0);
      else                                        return convert(a0, eve::as_element<Target>());
    }
  }

  //================================================================================================
  // Turn a conditional into a mask
  //================================================================================================
  template<conditional_expr C, typename Target>
   auto expand_mask(C const& c, as<Target> const&)
  {
    auto msk = c.mask( as<Target>{} );
    // clang-cl -march=skylake-avx512: unit.core.bit_and/bit_or/..., frexp, next failed to compile: a
    // logical<wide<float16_t>> mask with an emulated _Float16 doesn't share the storage of
    // logical<wide<uint16_t>> as it does natively, so there is no direct conversion: convert it.
    if constexpr( std::constructible_from<as_logical_t<Target>, decltype(msk)> )
      return as_logical_t<Target>(msk);
    else
      return convert(msk, as_element<as_logical_t<Target>>());
  }

  //================================================================================================
  // Handle the basic if/if_else cases
  //================================================================================================
  template<conditional_expr C, typename Op, typename Arg0, typename... Args>
   auto mask_op( C const& c
                              , [[maybe_unused]] Op f
                              , [[maybe_unused]] Arg0 const& a0
                              , [[maybe_unused]] Args const&... as
                              )
  {
    using r_t = decltype(f(a0,as...));

          if constexpr( C::is_complete && !C::is_inverted ) return alternative(c,a0,eve::as<r_t>{});
    else  if constexpr( C::is_complete &&  C::is_inverted ) return f(a0,as...);
    else                                                    return if_else( c.mask(eve::as<r_t>())
                                                                          , f(a0,as...)
                                                                          , alternative(c,a0,eve::as<r_t>{})
                                                                          );
  }
}
