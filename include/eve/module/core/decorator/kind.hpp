//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
struct p_kind_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using p_kind_type = decorated<p_kind_()>;
//================================================================================================
//! @addtogroup core_decorators
//! @{
//! @var p_kind
//!
//! @brief  Higher-order @callable imbuing p_kind behaviour onto other @callable{s}.
//!
//! #### Synopsis
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A @callable performing the p_kind algorithm choice
//!
//!  @}
//================================================================================================
inline constexpr p_kind_type const p_kind = {};

//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
struct q_kind_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using q_kind_type = decorated<q_kind_()>;
//================================================================================================
//! @addtogroup polynomial
//! @{
//! @var q_kind
//!
//! @brief  Higher-order @callable imbuing q_kind behaviour onto other @callable{s}.
//!
//! #### Synopsis
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A @callable performing the q_kind algorithm choice
//!
//!  @}
//================================================================================================
inline constexpr q_kind_type const q_kind = {};

//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
struct kind_1_
{
  template<auto N> static constexpr auto combine(decorated<diff_<N>()> const&) noexcept
  {
    return decorated<diff_<N>(kind_1_)> {};
  }
};

using kind_1_type = decorated<kind_1_()>;
//================================================================================================
//! @addtogroup polynomial
//! @{
//! @var kind_1
//!
//! @brief  Higher-order @callable imbuing kind_1 behaviour onto other @callable{s}.
//!
//! #### Synopsis
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A @callable performing the kind_1 algorithm choice
//!
//!  @}
//================================================================================================
inline constexpr kind_1_type const kind_1 = {};

//================================================================================================
//================================================================================================
// Function decorators mark-up used in function overloads
struct kind_2_
{
  template<auto N> static constexpr auto combine(decorated<diff_<N>()> const&) noexcept
  {
    return decorated<diff_<N>(kind_2_)> {};
  }
};

using kind_2_type = decorated<kind_2_()>;
//================================================================================================
//! @addtogroup polynomial
//! @{
//! @var kind_2
//!
//! @brief  Higher-order @callable imbuing kind_2 behaviour onto other @callable{s}.
//!
//! #### Synopsis
//!
//! @param f
//! An instance of eve::callable
//!
//! @return
//! A @callable performing the kind_2 algorithm choice
//!
//!  @}
//================================================================================================
inline constexpr kind_2_type const kind_2 = {};

}
