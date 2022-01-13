//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/memory/soa_ptr.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //! @var read
  //!
  //! @brief Callable object reading single value from memory
  //!
  //! **Required header:** `#include <eve/function/read.hpp>`
  //!
  //! `operator*` based interface used in the standard has notorious issues with proxy references.
  //! To prevent those issues when dealing with complex, potentially SIMD-aware iterators, `eve::read`
  //! is to be used.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Performs a single read from memory                         |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<typename Ptr> auto operator()(Ptr p) const noexcept
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `ptr`: Memory to read from.
  //!
  //! **Return value**
  //!
  //! Returns a signle value read at the memory location specified by `ptr`. If `ptr` is
  //! equivalent to `nullptr`, the behavior is undefined.
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(read_, read);

  namespace detail
  {
    template<typename Ptr> EVE_FORCEINLINE auto read_(EVE_SUPPORTS(cpu_), Ptr ptr) noexcept
    requires requires(Ptr p) { *p; }
    {
      return *ptr;
    }

    template<typename ...Ptrs>
    EVE_FORCEINLINE auto read_(EVE_SUPPORTS(cpu_), soa_ptr<Ptrs...> ptr) noexcept
    {
      return kumi::map(read, ptr);
    }
  }
}
