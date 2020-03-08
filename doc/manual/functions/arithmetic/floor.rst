.. _function-floor:

#####
floor
#####

**Required header:** ``#include <eve/function/floor.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ floor = {};
   }

Function object computing the greatest integral value less or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise greatest integral value less or equal to the  value of the parameter`.

Parameters
**********

* Instance of a  :ref:`IEEEValue <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``downward_`` version.

  - the  call to ``floor(a)`` is equivalent to the call ``round(a,downward_)``

.. seealso::  :ref:`ifloor <function-ifloor>`

Example
*******

.. include:: ../../../../test/doc/core/floor.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/floor.txt
  :literal:
