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
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise integral part values of the :ref:`wide <type-wide>`.
* [2] Computes the integral part of the value of the scalar.

Parameters
**********

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

Return value
**************

* [1,2] A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``toward_zero_`` version.

  - the  call to ``trunc(a)`` is equivalent to the call ``round(a,toward_zero_)``

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/trunc.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/trunc.txt
  :literal:
