.. _function-iround:

######
iround
######

**Required header:** ``#include <eve/function/iround.hpp>``

.. code-block:: c++
  :linenos:

   template<typename T             > constexpr T operator()( T const & x ) noexcept;
   template<typename T,typename TAG> constexpr T operator()( T const & x, TAG const & ) noexcept;

* [1]  Computes the element-wise nearest integral value of the parameter.
* [2] Computes the element-wise rounding according ``TAG`` direction.


Parameters
**********

* **x**: Instance of a  :ref:`Value <concept-value>`.
* TAG parameter type (if present) can be ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``, fixing the 
  rounding mode. It defaults to ``to_nearest_``.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the parameter.

Notes
******

  - This object function can be called with an optional tag parameter that changes its meaning:
  - ``iround(a, to_nearest_ )`` is equivalent to the call ``inearest(a)``
  - ``iround(a, toward_zero_)`` is equivalent to the call ``itrunc(a)``
  - ``iround(a, upward_ )`` is equivalent to the call ``iceil(a)``
  - ``iround(a, downward_)`` is equivalent to the call ``ifloor(a)``

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``. 
  - the  call to ``iround(x)`` is equivalent to the call ``iround(x, to_nearest_)``

Example
*******

.. include:: ../../../../test/doc/core/iround.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/iround.txt
  :literal:
