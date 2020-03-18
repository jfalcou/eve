.. _function-signnz:

######
signnz
######

**Required header:** ``#include <eve/function/signnz.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ signnz = {};
   }

Function object computing the signnz (-1 or 1) of a :ref:`Value <concept-value>`, the signnz of zero being one.

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise non-zero sign (-1 or 1) of the :ref:`Value <concept-value>`.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.


Options
*******

  - With the regular call the ``signnz`` of Nan is undefined
  - With the :ref:`pedantic_ <feature-decorator>` decorator the ``signnz`` of a Nan is a Nan
  - With a :ref:`Value <concept-ieeevalue>` the ``signnz`` of negative zero is ``-1``

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/signnz.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/signnz.txt
  :literal:
