.. _function-indeg:

#######
indeg
#######

**Required header:** ``#include <eve/function/indeg.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ indeg = {};
   }

Function object  converts :ref:`IEEEValue <concept-ieeevalue>` radian to degree.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Converts element-wise the :ref:`wide <type-wide>`.
* [2] Converts the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/indeg.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/indeg.txt
  :literal:
