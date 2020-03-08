.. _function-inearest:

########
inearest
########

**Required header:** ``#include <eve/function/inearest.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ inearest = {};
   }

Function object computing the rounding of the  value of a :ref:`Value <concept-value>`.
If a value is an half-integer it is rounded to the nearest even value.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise nearest integral value greater or equal to the :ref:`Value <concept-value>`.

Parameters
**********

* Instance of a  :ref:`Value <concept-ieeevalue>`.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the parameter.


Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_inearest``. This function object
    implements the ``to_inearest_`` version.

  - the  call to ``inearest(a)`` is equivalent to the call ``iround[to_inearest_](a)``

  - half-integral values are rounded to the inearest even integral

.. seealso::  :ref:`nearest <function-ceil>`

Example
*******

.. include:: ../../../../test/doc/core/inearest.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/inearest.txt
  :literal:
