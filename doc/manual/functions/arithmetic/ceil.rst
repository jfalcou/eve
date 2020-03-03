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
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise least integral values greater or equal to the value of the :ref:`wide <type-wide>`.
* [2] Computes the least integral value greater or equal to the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``upward_`` version.

  - the call to ``ceil(a)`` is equivalent to the call ``round(a,upward_)``



Example
*******

.. include:: ../../../../test/doc/core/ceil.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ceil.txt
  :literal:
