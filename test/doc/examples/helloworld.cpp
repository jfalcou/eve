//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
//! [hello]
#include <iostream>
#include <list>
#include <numeric>
#include <vector>
//! [hello-include-wide]
#include <eve/wide.hpp>
//! [hello-include-wide]

#include <eve/function/mul.hpp>
#include <eve/function/add.hpp>
#include <eve/function/store.hpp>

int main()
{
  //! [hello-namespace]
  namespace bs = eve;
  //! [hello-namespace]
  //! [hello-wide]
  using wide_t = eve::wide<float, eve::fixed<8>>;
  //! [hello-wide]

  //! [hello-def-ctor]
  wide_t res;
  //! [hello-def-ctor]

  //! [hello-splat-ctor]
  wide_t tens{10};
  //! [hello-splat-ctor]

  wide_t elevens{11};

  //! [hello-ptr-iota]
  std::vector<float> values(1000);
  std::iota(values.begin(), values.end(), float(0));
  wide_t ptr_wide(values.data());
  //! [hello-ptr-iota]

  //! [hello-iter-con]
  std::vector<float> data(wide_t::static_size);
  std::iota(data.begin(), data.begin() + wide_t::static_size, float(0));
  wide_t iter_wide(data.begin(), data.end());
  //! [hello-iter-con]

  //! [hello-enum-con]
  wide_t enum_wide{10, 11, 12, 13, 14, 15, 16, 17};
  //! [hello-enum-con]

  //! [hello-ops]
  res = (tens + elevens) * 2;
  //! [hello-ops]

  //! [hello-store]
  std::vector<float> output(wide_t::static_size);
  eve::store(res, &output[0]);
  //! [hello-store]

  //! [hello-io]
  std::cout << res << std::endl;
  //! [hello-io]

  return 0;
}
//! [hello]
