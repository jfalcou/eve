.. _function-iceil:

#####
iceil
#####

**Required header:** ``#include <eve/function/iceil.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ iceil = {};
   }

Function object computing the least integral value greater or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise least integral value greater or equal to the value of the parameter.

Parameters
**********

* Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``upward_`` version.

  - the call to ``iceil(a)`` is equivalent to the call ``iround(a, upward_)``

.. seealso::  :ref:`ceil <function-ceil>`

Example
*******

.. include:: ../../../../test/doc/core/iceil.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/iceil.txt
  :literal:
