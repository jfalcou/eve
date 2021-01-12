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

#include <eve/concept/memory.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/spy.hpp>
#include <type_traits>

#ifdef SPY_COMPILER_IS_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif
namespace eve
{
  template<scalar_value T> struct convert_to_;
}

namespace eve::detail
{
  //================================================================================================
  // SIMD
  //================================================================================================
  template<typename Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr ptr) noexcept
  requires( simd_compatible_ptr<Ptr, as_wide_t<std::remove_cvref_t<decltype(*ptr)>> > )
  {
    return as_wide_t<std::remove_cvref_t<decltype(*ptr)>>(ptr);
  }

  template<typename Ptr, typename Cardinal>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr ptr, Cardinal const &) noexcept
  requires( simd_compatible_ptr < Ptr
                                , as_wide_t < std::remove_cvref_t<decltype(*ptr)>
                                            , typename Cardinal::type
                                            >
                                >
          )
  {
    return as_wide_t<std::remove_cvref_t<decltype(*ptr)>, typename Cardinal::type>(ptr);
  }

  template<relative_conditional_expr C, typename Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr) noexcept
  requires( simd_compatible_ptr<Ptr, as_wide_t<std::remove_cvref_t<decltype(*ptr)>> > )
  {
    using T = std::remove_cvref_t<decltype(*ptr)>;
    return eve::load[cond](ptr, expected_cardinal_t<T>{});
  }

  template<relative_conditional_expr C, typename Ptr, typename Cardinal>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr, Cardinal const&) noexcept
  requires( simd_compatible_ptr<Ptr, as_wide_t< std::remove_cvref_t<decltype(*ptr)>
                                              , typename Cardinal::type>
                                              >
          )
  {
    using e_t = std::remove_cvref_t<decltype(*ptr)>;
    using r_t = as_wide_t< e_t, typename Cardinal::type >;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      return eve::load[cond](ptr.get(), Cardinal{});
    }
    else
    {
      // If the ignore/keep is complete we can jump over if_else
      if constexpr( C::is_complete )
      {
        if constexpr(C::is_inverted)  { return eve::load(ptr, Cardinal{});  }
        else
        {
          if constexpr(C::has_alternative)  return r_t{cond.alternative};
          else                              return r_t{};
        }
      }
      else
      {
        auto offset = cond.offset( as_<r_t>{} );

        if constexpr(C::has_alternative)
        {
          [[maybe_unused]] r_t that(cond.alternative);
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( dst + offset, ptr + offset, sizeof(e_t) * cond.count( as_<r_t>{} ) );
          return that;
        }
        else
        {
          [[maybe_unused]] r_t that;
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( dst + offset, ptr + offset, sizeof(e_t) * cond.count( as_<r_t>{} ) );
          return that;
        }
      }
    }
  }

  //================================================================================================
  // Scalar support
  //================================================================================================
  template<typename Ptr>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Ptr p, scalar_cardinal const&) noexcept
  {
    return *p;
  }

  template<typename Ptr, scalar_value T>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_)
                            , decorated<convert_to_<T>()> const&, Ptr p, scalar_cardinal const&
                            ) noexcept
  {
    return static_cast<T>(*p);
  }
}

#ifdef SPY_COMPILER_IS_GCC
#pragma GCC diagnostic pop
#endif
