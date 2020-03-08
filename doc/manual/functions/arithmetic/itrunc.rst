.. _function-itrunc:

######
itrunc
######

**Required header:** ``#include <eve/function/itrunc.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ itrunc = {};
   }

Function object computing the greatest integral part of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise integral part of the parameter`.

Parameters
**********

* Instance of a  :ref:`IEEEValue <concept-ieeevalue>`.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``upward_`` version.

  - the call to ``iceil(a)`` is equivalent to the call ``iround[upward_](a)``

.. seealso::  :ref:`trunc <function-trunc>`

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``toward_zero_`` version.

  - the  call to ``itrunc(a)`` is equivalent to the call ``iround(a, toward_zero_)``

Example
*******

.. include:: ../../../../test/doc/core/itrunc.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/itrunc.txt
  :literal:
