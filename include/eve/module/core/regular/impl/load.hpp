//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/memory.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/spy.hpp>
#include <eve/module/core/regular/unsafe.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/wide.hpp>
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

#if defined(__has_feature)
#  if __has_feature(address_sanitizer) or __has_feature(thread_sanitizer)
#       define EVE_SANITIZERS_ARE_ON
#  endif  // __has_feature
#endif

#if defined(EVE_SANITIZERS_ARE_ON)
  constexpr bool sanitizers_are_on = true;

#undef EVE_SANITIZERS_ARE_ON

#else
  constexpr bool sanitizers_are_on = false;
#endif

  //================================================================================================
  // Load from pointer - Conditional load
  //================================================================================================
  template<relative_conditional_expr C, data_source Ptr, typename Pack>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_)
                            , C const &cond, safe_type const&
                            , eve::as<Pack> tgt, Ptr ptr
                            ) noexcept
  requires simd_compatible_ptr<Ptr,Pack>
  {
    using e_t = typename pointer_traits<Pack>::value_type;
    using r_t = Pack;
    using c_t = cardinal_t<Pack>;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      static constexpr bool is_aligned_enough = c_t() * sizeof(e_t) >= Ptr::alignment();

      if constexpr (!sanitizers_are_on && is_aligned_enough)
      {
        auto that = eve::unsafe(eve::load)(ptr, tgt);
        if constexpr( C::has_alternative )  return replace_ignored(that, cond, cond.alternative);
        else                                return that;
      }
      else
      {
        return eve::load[cond](ptr.get(), tgt);
      }
    }
    else
    {
      // If the ignore/keep is complete we can jump over if_else
      if constexpr( C::is_complete )
      {
        if constexpr(C::is_inverted)  { return eve::load(ptr, tgt);  }
        else
        {
          if constexpr(C::has_alternative)  return r_t{cond.alternative};
          else                              return r_t{};
        }
      }
      else
      {
        auto offset = cond.offset( as<r_t>{} );

        if constexpr(C::has_alternative)
        {
          [[maybe_unused]] r_t that(cond.alternative);
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( (void*)(dst + offset), ptr + offset, sizeof(e_t) * cond.count( as<r_t>{} ) );
          return that;
        }
        else
        {
          [[maybe_unused]] r_t that;
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( (void*)(dst + offset), ptr + offset, sizeof(e_t) * cond.count( as<r_t>{} ) );
          return that;
        }
      }
    }
  }

#if defined(SPY_COMPILER_IS_CLANG) or defined(SPY_COMPILER_IS_GCC)
#define DISABLE_SANITIZERS __attribute__((no_sanitize_address)) __attribute__((no_sanitize_thread))
#elif defined(SPY_COMPILER_IS_MSVC) and !defined(__clang__)
#define DISABLE_SANITIZERS __declspec(no_sanitize_address)
#else
#define DISABLE_SANITIZERS
#endif

  // making unsafe(load) call intrinsics requires a lot of work and is not very portable
  // due to what called functions it will affect.
  // Since the unsafe is mostly used in corner cases, will do it scalar in asan mode.
  template<relative_conditional_expr C, data_source Ptr, typename Pack>
  DISABLE_SANITIZERS Pack load_ ( EVE_SUPPORTS(cpu_)
                                , C const& cond, unsafe_type const&
                                , eve::as<Pack> const& tgt, Ptr ptr
                                ) noexcept
  {
    if constexpr(sanitizers_are_on)
    {
      Pack that;

      auto offset = cond.offset( as<Pack>{} );
      auto count  = cond.count( as<Pack>{} );

      for (std::ptrdiff_t i = offset; i != count + offset; ++i) that.set(i, ptr[i]);

      return that;
    }
    else
    {
      return eve::load(cond,safe,tgt,ptr);
    }
  }
}

#ifdef SPY_COMPILER_IS_GCC
#pragma GCC diagnostic pop
#endif
