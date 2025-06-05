//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/conditional.hpp>
#include <eve/memory/pointer.hpp>

namespace eve
{
  template<typename Options>
  struct load_t : relative_conditional_callable<load_t, Options, unsafe_option>
  {
    template<detail::data_source Ptr>
    EVE_FORCEINLINE wide_value_type_t<Ptr> operator()(Ptr ptr) const noexcept
    {
      return EVE_DISPATCH_CALL(ptr, as<wide_value_type_t<Ptr>>{});
    }

    template<detail::data_source Ptr, std::ptrdiff_t N>
    EVE_FORCEINLINE as_wide_t<value_type_t<Ptr>, fixed<N>> operator()(Ptr ptr, fixed<N>) const noexcept
    {
      return EVE_DISPATCH_CALL(ptr, as<as_wide_t<value_type_t<Ptr>, fixed<N>>>{});
    }

    template<detail::data_source Ptr, simd_value Wide>
    EVE_FORCEINLINE Wide operator()(Ptr ptr, as<Wide> tgt) const noexcept
    {
      return EVE_DISPATCH_CALL(ptr, tgt);
    }

    template<std::input_iterator Iterator>
    EVE_FORCEINLINE as_wide_t<typename std::iterator_traits<Iterator>::value_type> operator()(Iterator b, Iterator e) const noexcept
      requires (!Options::contains(condition_key) && !Options::contains(unsafe2))
    {
      using base = typename std::iterator_traits<Iterator>::value_type;
      return EVE_DISPATCH_CALL(b, e, as<as_wide_t<base>>{});
    }

    template<std::input_iterator Iterator, simd_value Wide>
    EVE_FORCEINLINE Wide operator()(Iterator b, Iterator e, as<Wide> tgt) const noexcept
      requires (!Options::contains(condition_key) && !Options::contains(unsafe2))
    {
      return EVE_DISPATCH_CALL(b, e, tgt);
    }

    EVE_CALLABLE_OBJECT(load_t, load_);
  };

  //================================================================================================
  //! @addtogroup simd
  //! @{
  //!   @var load
  //!   @brief Loads data from a pointer or a pair of iterators into a [SIMD value](@ref eve::simd_value)
  //!
  //!   @groupheader{Header file}
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
  //!     // Regular overloads
  //!     template<detail::data_source Ptr>
  //!     wide_value_type_t<Ptr> load(Ptr ptr) const noexcept;                                                           // 1
  //!
  //!     template<detail::data_source Ptr, std::ptrdiff_t N>
  //!     as_wide_t<value_type_t<Ptr>, fixed<N>> load(Ptr ptr, fixed<N>) const noexcept;                                 // 1
  //!
  //!     template<detail::data_source Ptr, simd_value Wide>
  //!     Wide load(Ptr ptr, as<Wide> tgt) const noexcept;                                                               // 1
  //!
  //!     template<std::input_iterator Iterator>
  //!     as_wide_t<typename std::iterator_traits<Iterator>::value_type>
  //!     load(Iterator b, Iterator e) const noexcept;                                                                   // 1
  //!
  //!     template<std::input_iterator Iterator, simd_value Wide>
  //!     Wide load(Iterator b, Iterator e, as<Wide> tgt) const noexcept;                                                // 1
  //!
  //!     // Conditional overloads
  //!     auto load[relative_conditional_expr c](/* any non-iterator version of the above overloads */) const noexcept;  // 2
  //!
  //!     // Semantic options
  //!     auto load[unsafe](/* any non-iterator version of the above overloads */) const noexcept;                       // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `ptr`: A data source referencing the data to load.
  //!   * `b`, `e`: A pair of iterators over the data to load.
  //!   * `c`: A [relative conditional expression](@ref eve::relative_conditional_expr) that determines which elements to load.
  //!
  //!  **Return value**
  //!
  //!   1. A [SIMD value](@ref eve::simd_value) containing the element referenced by the data source or the iterators.
  //!   2. Same as 1., but elements whose corresponding condition mask lane evaluates to `false` are left undefined.
  //!   3. Same as 1., but uses as scalar version of the operation if a sanitizer is enabled.
  //!
  //!   @note
  //!      2. and 3. are not available for iterators.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{example/tutorial/load_ignore.cpp}
  //================================================================================================
  inline constexpr auto load = functor<load_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/detail/function/simd/common/load.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/load.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/load.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/detail/function/simd/arm/neon/load.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/load.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/detail/function/simd/riscv/load.hpp>
#endif
