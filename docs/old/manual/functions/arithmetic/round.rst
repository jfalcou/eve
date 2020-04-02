.. _function-round:

#####
round
#####

**Required header:** ``#include <eve/function/round.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ round = {};
   }

Function object computing the least integral value greater or equal to the  value of a :ref:`Value <concept-value>`.

.. code-block:: c++
  :linenos:

   template<typename T             > constexpr T operator()( T const & x ) noexcept;
   template<typename T,typename TAG> constexpr T operator()( T const & x, TAG const & tag ) noexcept;

* [1]  Computes the element-wise nearest integral value of the parameter.
* [2] Computes the element-wise rounding according ``TAG`` direction.


Parameters
**********


* ``x``: Instance of a  :ref:`Value <concept-value>`.
* ``tag`` parameter (if present) can be ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest_``, fixing the 
  rounding mode. It defaults to ``to_nearest_``.

Return value
**************

*  A value with the same type as the first parameter.

Notes
******

  - This object function can be called with an optional tag parameter that change its meaning:

  - ``round(x, to_nearest_ )`` is equivalent to the call ``nearest(x)``
  - ``round(x, toward_zero_)`` is equivalent to the call ``trunc(x)``
  - ``round(x, upward_ )`` is equivalent to the call ``ceil(x)``
  - ``round(x, downward_)`` is equivalent to the call ``floor(x)``

  - the standard proposes 4 rounding modes namely: ``FE_TONEAREST``, ``FE_DOWNWARD``, ``FE_UPWARD``, ``FE_TOWARDZERO``.
    **EVE** proposes four corresponding parameter values of different types:  ``upward_``, ``downward_``,
    ``toward_zero_`` and ``to_nearest_``. 

  - the  call to ``round(x)`` is equivalent to the call ``nearest(x)``


Example
*******

.. include:: ../../../../test/doc/core/round.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/round.txt
  :literal:
