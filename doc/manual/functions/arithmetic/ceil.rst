.. _function-ceil:

####
ceil
####

**Required header:** ``#include <eve/function/ceil.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ceil = {};
   }

Function object computing the least integral value greater or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise least integral value greater or equal to the  value of the parameter.

Parameter
**********

* ``x``: Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``FE_TONEAREST``, ``FE_DOWNWARD``, ``FE_UPWARD``, ``FE_TOWARDZERO``.
    This function object implements the ``FE_UPWARD`` version.

  - the call to ``ceil(a)`` is equivalent to the call ``round(a, upward_)``

  - On :ref:`Integral Value <concept-integralvalue>` parameter it returns the input unchanged.

.. seealso::  :ref:`iceil <function-iceil>`, :ref:`round <function-round>`

Example
*******

.. include:: ../../../../test/doc/core/ceil.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ceil.txt
  :literal:
