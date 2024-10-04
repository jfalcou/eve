//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/overload.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <iterator>

namespace eve
{
  template<typename Options>
  struct unalign_t : callable<unalign_t, Options>
  {
    template<std::contiguous_iterator I>
    constexpr EVE_FORCEINLINE I operator()(I ptr) const noexcept
    {
      return EVE_DISPATCH_CALL_PT(I, ptr);
    }

    template<typename Ptr>
    EVE_FORCEINLINE auto operator()(Ptr p) const noexcept -> decltype(p.unalign())
    {
      return EVE_DISPATCH_CALL_PT(decltype(p.unalign()), p);
    }

    template<typename T, typename N>
    constexpr EVE_FORCEINLINE T* operator()(aligned_ptr<T, N> p) const noexcept
    {
      return EVE_DISPATCH_CALL_PT(T*, p);
    }

    template<typename... Ptrs>
    constexpr EVE_FORCEINLINE auto operator()(soa_ptr<Ptrs...> ptr) const noexcept
              -> soa_ptr<decltype(std::declval<unalign_t>()(std::declval<Ptrs>()))...>
    {
      return EVE_DISPATCH_CALL_PT((soa_ptr<decltype(std::declval<unalign_t>()(std::declval<Ptrs>()))...>), ptr);
    }

    EVE_CALLABLE_OBJECT(unalign_t, unalign_);
  };

  // TODO DOC is this to be there : there is no simd parameter involved. Perhaps better in algo ?
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //!   @var unalign
  //!   @brief Callable object for computing an unaligned version of a relaxed iterator.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     template<std::contiguous_iterator I>
  //!     constexpr I unalign(I p) noexcept;                      // 1
  //!
  //!     template<eve::relaxed_iterator Ptr>
  //!     constexpr auto unalign(Ptr p) noexcept;                 // 2
  //!
  //!     template<typename T, typename N>
  //!     constexpr T* unalign(aligned_ptr<T, N> p) noexcept;     // 3
  //!
  //!     template<typename... Ptrs>
  //!     constexpr auto unalign(soa_ptr<Ptrs...> p) noexcept;    // 4
  //!   }
  //!   @endcode
  //!
  //!   Convert the pointer or iterator passed as a parameter to a pointer without
  //!   qny information about its alignment.
  //!
  //!   **Parameters**
  //!     * `p`: A pointer or relaxed iterator to convert.
  //!
  //!    **Return value**
  //!     1. Return `p` as it is as `std::iterator` does not provide alignment information.
  //!     2. Return the iterator-specific value as computed by the iterator `unalign` member.
  //!     3. Return the raw pointer contained in `p`.
  //!     4. Return a `soa_ptr` made of all unaligned pointers of `p`.
  //================================================================================================
  inline constexpr auto unalign = functor<unalign_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @addtogroup memory
  //! @{
  //!   @typedef unaligned_t
  //!   @brief  Compute the unaligned pointer type associated to a given type.
  //!   @tparam T Type to process
  //!
  //!   **Required header:** `#include <eve/module/core.hpp>`
  //!
  //!   @code{.cpp}
  //!   template <typename T>
  //!   using unaligned_t = decltype(unalign(std::declval<T>()));
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename T> using unaligned_t = decltype(unalign(std::declval<T>()));
}
namespace eve::detail
{
  template<std::contiguous_iterator I, callable_options O>
  constexpr EVE_FORCEINLINE I unalign_(EVE_REQUIRES(cpu_), O const&, I i) noexcept
  {
    return i;
  }

  template<typename Ptr, callable_options O>
  constexpr EVE_FORCEINLINE auto unalign_(EVE_REQUIRES(cpu_), O const&, Ptr p) noexcept
  -> decltype(p.unalign())
  {
    return p.unalign();
  }

  template<typename T, typename N, callable_options O>
  constexpr EVE_FORCEINLINE T* unalign_(EVE_REQUIRES(cpu_), O const&, aligned_ptr<T, N> p) noexcept
  {
    return p.get();
  }

  template<typename... Ptrs, callable_options O>
  constexpr EVE_FORCEINLINE auto unalign_(EVE_REQUIRES(cpu_), O const&, soa_ptr<Ptrs...> p) noexcept
  {
    return soa_ptr<unaligned_t<Ptrs>...> {kumi::map(unalign, p)};
  }
}
