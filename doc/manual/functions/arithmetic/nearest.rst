.. _function-nearest:

#######
nearest
#######

**Required header:** ``#include <eve/function/nearest.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ nearest = {};
   }

Function object computing the rounding of the  value of a :ref:`Value <concept-value>`.
If a value is an half-integer it is rounded to the nearest even value.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise least integral value greater or equal to the  value of the parameter`.

Parameters
**********

* Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``to_nearest_`` version.

  - the  call to ``nearest(x)`` is equivalent to the call ``round(x, to_nearest_)``

  - half-integral values are rounded to the nearest even integral

.. seealso::  :ref:`iceil <function-inearest>`

Example
*******

.. include:: ../../../../test/doc/core/nearest.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/nearest.txt
  :literal:
