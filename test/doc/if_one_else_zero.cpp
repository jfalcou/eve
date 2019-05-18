#include <eve/function/if_else.hpp>
#include <eve/wide.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <iostream>

using iT = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;
using wide_ft  = eve::wide<float, eve::fixed<4>>;
using wide_lt = eve::as_logical_t<wide_it>;
using eve::as_;

int main() {
  wide_it si = {2, -3, 0, 4};
  wide_lt lsi= {true, false, false, true};

  std::cout << "---- simd" << '\n'
            << " <- si =                              " << si << '\n'
            << " <- lsi =                             " << lsi << '\n'
            << " -> eve::if_else[as_<wide_t>](si, eve::zero_, eve::one_) =   "
            <<eve::if_else[as_<wide_ft>()](si, eve::zero_, eve::one_) << '\n'
            << " -> if_else[as_<wide_ft>()](lsi, eve::zero_, eve::one_) =       "
            << eve::if_else[as_<wide_ft>()](lsi, eve::zero_, eve::one_) << '\n';

  iT ssi = 3;
  eve::logical<iT>  lssi = false;

  std::cout << "---- scalar" << '\n'
            << " ssi =                                " << ssi << '\n'
            << " lssi =                               " << lssi << '\n'
            << " -> eve::if_else[as_<double>()](ssi, eve::zero_,eve::one_) =       "
            << eve::if_else[as_<double>()](ssi, eve::zero_, eve::one_) << '\n'
            << " -> eve::if_else[as_<double>()](lssi, eve::zero_, eve::one_) =      "
            << eve::if_else[as_<double>()](lssi, eve::zero_, eve::one_) << '\n';
  return 0;
}
