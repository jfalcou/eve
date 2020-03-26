.. _function-ifloor:

######
ifloor
######

**Required header:** ``#include <eve/function/ifloor.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ifloor = {};
   }

Function object computing the greatest integral value less or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise least integral value greater or equal to the value of the parameter.

Parameter
**********

* ``x``: Instance of a  :ref:`IEEEValue <concept-ieeevalue>`.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the parameter.

Notes
******

   - the standard proposes 4 rounding modes namely: ``FE_TONEAREST``, ``FE_DOWNWARD``, ``FE_UPWARD``, ``FE_TOWARDZERO``.
     This function object implements the ``FE_DOWNWARD``` version.

  - the  call to ``ifloor(x)`` is equivalent to the call ``iround(x, downward_)``

.. seealso::  :ref:`floor <function-floor>`,   :ref:`iround <function-iround>`

Example
*******

.. include:: ../../../../test/doc/core/ifloor.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ifloor.txt
  :literal:
