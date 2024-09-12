// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cfenv>

int main()
{
  auto sml = eve::smallestposval(eve::as(1.0));
  {
    eve::wide wf0{1.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
    eve::wide wf1{sml, -sml, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};

    std::cout << std::setprecision(20)<< "<- wf0                           = " <<wf0 << "\n";
    std::cout << std::setprecision(20)<< "<- wf1                           = " <<wf1 << "\n";
    std::cout << std::setprecision(20)<< "-> add          (wf0, wf1)       = " << eve::add               (wf0, wf1) << "\n";
    std::cout << std::setprecision(20)<< "-> add[downward](wf0, wf1)       = " << eve::add[eve::downward](wf0, wf1) << "\n";
    std::cout << std::setprecision(20)<< "-> add[upward](wf0, wf1)         = " << eve::add[eve::upward](wf0, wf1) << "\n";
//    std::cout << std::setprecision(20)<< "-  diff                            = " << eve::add[eve::upward](wf0, wf1) - eve::add[eve::downward](wf0, wf1) << "\n";
  }
  {
    static eve::wide wf0{1.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
    static eve::wide wf1{eve::smallestposval(eve::as(1.0)), -eve::smallestposval(eve::as(1.0)), 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};

    std::cout << std::setprecision(20)<< "-> add          (wf0, wf1)       = " << eve::add               (wf0, wf1) << "\n";
    std::cout << std::setprecision(20)<< "-> add[downward](wf0, wf1)       = " << eve::add[eve::downward](wf0, wf1) << "\n";
    std::cout << std::setprecision(20)<< "-> add[upward](wf0, wf1)         = " << eve::add[eve::upward](wf0, wf1) << "\n";
//    std::cout << std::setprecision(20)<< "-  diff                            = " << eve::add[eve::upward](wf0, wf1) - eve::add[eve::downward](wf0, wf1) << "\n";
  }

  {
    static eve::wide wf0{1.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
    static eve::wide wf1{eve::smallestposval(eve::as(1.0)), -eve::smallestposval(eve::as(1.0)), 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
    auto [r, e] = eve::two_add(wf0, wf1);
    std::cout << std::setprecision(20)<< "r = " << r << std::endl;
    std::cout << std::setprecision(20)<< "e = " << e << std::endl;
    r = eve::if_else(eve::is_gtz(e), eve::next(r), r);
    std::cout << std::setprecision(20)<< "-  r = " << r << std::endl;
  }

  {
    static eve::wide wf0{1.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
    static eve::wide wf1{eve::smallestposval(eve::as(1.0)), -eve::smallestposval(eve::as(1.0)), 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
    auto [r, e] = eve::two_add(wf0, wf1);
    std::cout << std::setprecision(20)<< "r = " << r << std::endl;
    std::cout << std::setprecision(20)<< "e = " << e << std::endl;
    r = eve::if_else(eve::is_ltz(e), eve::prev(r), r);
    std::cout << std::setprecision(20)<< "-  r = " << r << std::endl;
  }
}
