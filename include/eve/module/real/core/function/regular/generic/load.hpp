//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/memory.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/spy.hpp>
#include <eve/function/unsafe.hpp>
#include <eve/function/replace.hpp>
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
  // Bundle load
  //================================================================================================
  template<typename... Pointers>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_), kumi::tuple<Pointers...> ptr) noexcept
  {
    auto card = expected_cardinal_t< kumi::tuple<std::remove_cvref_t<decltype(*std::declval<Pointers>())>...> >{};
    return eve::load(ptr, card);
  }

/*  template<typename... Pointers,typename Cardinal>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_), kumi::tuple<Pointers...> ptr
                            , Cardinal
                            ) noexcept
  {
    return bundle { kumi::map ( [](auto p) { return eve::load(p, Cardinal{}); }, ptr) };
  }
*/
  template<relative_conditional_expr C, typename... Pointers>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_), C cond, kumi::tuple<Pointers...> ptr ) noexcept
  {
    auto card = expected_cardinal_t< kumi::tuple<std::remove_cvref_t<decltype(*std::declval<Pointers>())>...> >{};
    return eve::load[cond](ptr, card);
  }

/*  template<relative_conditional_expr C, typename... Pointers,typename Cardinal>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_)
                            , C cond, kumi::tuple<Pointers...> ptr, Cardinal
                            ) noexcept
  {
    return bundle { kumi::map ( [&](auto p) { return eve::load[cond](p, Cardinal{}); }, ptr) };
  }

  template<typename... Pointers>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_), unsafe_type, kumi::tuple<Pointers...> ptr) noexcept
  {
    return bundle { kumi::map ( [](auto p) { return eve::unsafe(eve::load)(p); }, ptr) };
  }

  template<typename... Pointers,typename Cardinal>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_), unsafe_type, kumi::tuple<Pointers...> ptr
                            , Cardinal
                            ) noexcept
  {
    return bundle { kumi::map ( [](auto p) { return eve::unsafe(eve::load)(p, Cardinal{}); }, ptr) };
  }

  template<relative_conditional_expr C, typename... Pointers>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_), unsafe_type, C cond, kumi::tuple<Pointers...> ptr ) noexcept
  {
    return bundle { kumi::map ( [&](auto p) { return eve::unsafe(eve::load)[cond](p); }, ptr) };
  }

  template<relative_conditional_expr C, typename... Pointers,typename Cardinal>
  EVE_FORCEINLINE auto load_( EVE_SUPPORTS(cpu_), unsafe_type
                            , C cond, kumi::tuple<Pointers...> ptr, Cardinal
                            ) noexcept
  {
    return bundle { kumi::map ( [&](auto p) { return eve::unsafe(eve::load)[cond](p, Cardinal{}); }, ptr) };
  }
*/

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
      static constexpr bool is_aligned_enough = Cardinal() * sizeof(e_t) >= Ptr::alignment();

      if constexpr (!sanitizers_are_on && is_aligned_enough)
      {
        auto that = eve::unsafe(eve::load)(ptr, Cardinal{});
        if constexpr( C::has_alternative )  return replace_ignored(that, cond, cond.alternative);
        else                                return that;
      }
      else
      {
        return eve::load[cond](ptr.get(), Cardinal{});
      }
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
          std::memcpy( (void*)(dst + offset), ptr + offset, sizeof(e_t) * cond.count( as_<r_t>{} ) );
          return that;
        }
        else
        {
          [[maybe_unused]] r_t that;
          auto* dst   = (e_t*)(&that.storage());
          std::memcpy( (void*)(dst + offset), ptr + offset, sizeof(e_t) * cond.count( as_<r_t>{} ) );
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

#if defined(SPY_COMPILER_IS_CLANG) or defined(SPY_COMPILER_IS_GCC)
#define DISABLE_SANITIZERS __attribute__((no_sanitize_address)) __attribute__((no_sanitize_thread))
#elif defined(SPY_COMPILER_IS_MSVC)
#define DISABLE_SANITIZERS __declspec(no_sanitize_address)
#else
#define DISABLE_SANITIZERS
#endif

  // making unsafe(load) call intinsics requires a lot of work and is not very portable
  // due to what called functions it will affect.
  // Since the unsafe is mostly used in corner cases, will do it scalar in asan mode.
  template<relative_conditional_expr C, typename Ptr, typename Cardinal>
  requires(sanitizers_are_on)
  DISABLE_SANITIZERS auto load_(EVE_SUPPORTS(cpu_), C const &cond, unsafe_type, Ptr ptr, Cardinal const&) noexcept
                  -> decltype( eve::load[cond](ptr, Cardinal{}))
  {
    using e_t = std::remove_cvref_t<decltype(*ptr)>;
    using r_t = as_wide_t< e_t, typename Cardinal::type >;

    r_t that;

    auto offset = cond.offset( as_<r_t>{} );
    auto count  = cond.count( as_<r_t>{} );

    for (std::ptrdiff_t i = offset; i != count + offset; ++i) that.set(i, ptr[i]);

    return that;
  }

  template<relative_conditional_expr C,typename Ptr>
  requires(sanitizers_are_on)
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C const &cond, unsafe_type, Ptr ptr) noexcept
              ->  decltype(eve::load[cond](ptr))
  {
    using T = std::remove_cvref_t<decltype(*ptr)>;
    return eve::unsafe(eve::load[cond])(ptr, expected_cardinal_t<T>{});
  }

  template<typename Ptr, typename Cardinal>
  requires(sanitizers_are_on)
  DISABLE_SANITIZERS auto load_(EVE_SUPPORTS(cpu_), unsafe_type, Ptr ptr, Cardinal const& N) noexcept
                  -> decltype(eve::load(ptr, N))
  {
    return eve::unsafe(eve::load[eve::ignore_none])(ptr, N);
  }

  template<typename Ptr>
  requires(!sanitizers_are_on)
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), unsafe_type, Ptr ptr) noexcept
              ->  decltype(eve::load(ptr))
  {
    return eve::unsafe(eve::load[eve::ignore_none])(ptr);
  }

  template<typename ...Args>
  requires (!sanitizers_are_on)
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), unsafe_type, Args ... args) noexcept
              ->  decltype( eve::load(args...) )
  {
    return eve::load(args...);
  }

  template<relative_conditional_expr C, typename ... Args>
  requires (!sanitizers_are_on)
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C const &cond, unsafe_type, Args ... args) noexcept
              ->  decltype( eve::load[cond](args...) )
  {
    return eve::load[cond](args...);
  }

}
#ifdef SPY_COMPILER_IS_GCC
#pragma GCC diagnostic pop
#endif
