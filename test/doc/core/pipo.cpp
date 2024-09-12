// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cfenv>

int main()
{
  auto sml = eve::smallestposval(eve::as(1.0f));
  {
    eve::wide wf0{1.0f, 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};
    eve::wide wf1{sml, -sml, 1.0f, -1.0f, 2.0f, -2.0f, 3.0f, -3.0f};

    std::cout << std::setprecision(15)<< "-> add          (wf0, wf1)       = " << eve::add               (wf0, wf1) << "\n";
    std::cout << std::setprecision(15)<< "-> add[downward](wf0, wf1)       = " << eve::add[eve::downward](wf0, wf1) << "\n";
    std::cout << std::setprecision(15)<< "-> add[upward](wf0, wf1)         = " << eve::add[eve::upward](wf0, wf1) << "\n";
//    std::cout << std::setprecision(15)<< "-  diff                            = " << eve::add[eve::upward](wf0, wf1) - eve::add[eve::downward](wf0, wf1) << "\n";
  }
  {
    static eve::wide wf0{1.0f, 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};
    static eve::wide wf1{eve::smallestposval(eve::as(1.0f)), -eve::smallestposval(eve::as(1.0f)), 1.0f, -1.0f, 2.0f, -2.0f, 3.0f, -3.0f};

    std::cout << std::setprecision(15)<< "-> add          (wf0, wf1)       = " << eve::add               (wf0, wf1) << "\n";
    std::cout << std::setprecision(15)<< "-> add[downward](wf0, wf1)       = " << eve::add[eve::downward](wf0, wf1) << "\n";
    std::cout << std::setprecision(15)<< "-> add[upward](wf0, wf1)         = " << eve::add[eve::upward](wf0, wf1) << "\n";
//    std::cout << std::setprecision(15)<< "-  diff                            = " << eve::add[eve::upward](wf0, wf1) - eve::add[eve::downward](wf0, wf1) << "\n";
  }
}
