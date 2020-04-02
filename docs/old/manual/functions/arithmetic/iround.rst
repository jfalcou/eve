.. _function-iround:

######
iround
######

**Required header:** ``#include <eve/function/iround.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ iround = {};
   }

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T             > constexpr T operator()( T const & x ) noexcept;
   template<typename T,typename TAG> constexpr T operator()( T const & x, TAG const & tag = to_nearest_) noexcept;

* [1]  Computes the element-wise nearest integral value of the parameter.
* [2]  Computes the element-wise rounding according ``TAG`` rounding mode.


Parameters
**********

* ``x``: Instance of a  :ref:`Value <concept-value>`.
* ``tag`` parameter (if present) can be ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``, fixing the 
  rounding mode. It defaults to ``to_nearest_``.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the first parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``FE_TONEAREST``, ``FE_DOWNWARD``, ``FE_UPWARD``, ``FE_TOWARDZERO``.
    **EVE** proposes four corresponding parameter values of different types:  ``upward_``, ``downward_``,
    ``toward_zero_`` and ``to_nearest_``. 
  - ``iround(x, to_nearest_ )`` is equivalent to the call ``inearest(x)`` and implements standard ``FE_TONEAREST``.
  - ``iround(x, toward_zero_)`` is equivalent to the call ``itrunc(x)`` and implements standard ``FE_TOWARDZERO``.
  - ``iround(x, upward_ )`` is equivalent to the call ``iceil(x)`` and implements standard ``FE_UPWARD``.
  - ``iround(x, downward_)`` is equivalent to the call ``ifloor(x)`` and implements standard ``FE_DOWNWARD``.
  - the  call to ``iround(x)`` is equivalent to the call ``iround(x, to_nearest_)``.

Example
*******

.. include:: ../../../../test/doc/core/iround.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/iround.txt
  :literal:
