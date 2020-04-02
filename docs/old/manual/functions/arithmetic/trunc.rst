.. _function-trunc:

#####
trunc
#####

**Required header:** ``#include <eve/function/trunc.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ trunc = {};
   }

Function object computing the greatest integral parte of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise integral value greater or equal to of the parameter`.

Parameter
**********

* ``x``: Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``FE_TONEAREST``, ``FE_DOWNWARD``, ``FE_UPWARD``, ``FE_TOWARDZERO``.
    This function object implements the ``FE_TOWARDZERO`` version.

  - the  call to ``trunc(x)`` is equivalent to the call ``round(x,toward_zero_)``

 - On :ref:`Integral Value <concept-integralvalue>` parameter it returns the input unchanged.

.. seealso::  :ref:`itrunc <function-itrunc>`, :ref:`round <function-round>`


Example
*******

.. include:: ../../../../test/doc/core/trunc.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/trunc.txt
  :literal:
