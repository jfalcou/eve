//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct almost_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(almost_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //! @var definitely
  //!
  //! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if definitely(eve::fname) is to be called then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/fuzzy/fname.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but while insuring that a small error on the
  //! parameters will not affect the result.
  //!
  //! definitely is currently supported by eve::is_greater, eve::is_less,
  //! eve::is_not_greater_equal, eve::is_not_less_equal and eve::is_not_equal
  //! object functions.
  //!
  //!  @}
  //! @{
  //! @var almost
  //!
  //! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if almost(eve::fname) is to be called then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/fuzzy/fname.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but while insuring that a small error on the
  //! parameters will not affect the result.
  //!
  //! almost is currently supported by eve::is_greater_equal, eve::is_less_equal,
  //! eve::is_not_greater, eve::is_not_less and eve::is_equal
  //! object functions.
  //!  @}
  //! @{
  //! @var tolerant
  //!
  //! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if tolerant(eve::fname) is to be called then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/fuzzy/fname.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but while insuring that a small error on the
  //! parameters will not affect the result.
  //!
  //! tolerant is currently supported by eve::ceil, eve::floor and eve::trunc object functions.
  //!
  //================================================================================================

  //================================================================================================
  // Function decorator - almost mode
  inline constexpr almost_type const almost = {};

  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct definitely_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(definitely_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  //================================================================================================
  // Function decorator - definitely mode
  inline constexpr definitely_type const definitely = {};


  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct tolerant_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(tolerant_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  //================================================================================================
  // Function decorator - tolerant mode
  inline constexpr tolerant_type const tolerant = {};
}
