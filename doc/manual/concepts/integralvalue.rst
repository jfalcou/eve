.. _concept-integralvalue:

IntegralValue
=============

An :ref:`concept-integralvalue` type is a type which satisfies either :ref:`concept-vectorizable` or
 :ref:`concept-vectorized` and which underlying scalar type behaves like an integral value.

Requirements
------------

A type ``T`` satisfies :ref:`concept-integralvalue` if:

  - ``T``  satisfies :ref:`concept-vectorizable` or :ref:`concept-vectorized`
  - ``std::is_integral_v<eve::scalar_of_t<T>>`` evaluates to ``true``

Example
---------

  - ``int``
  - ``short``
  - ``eve::wide<std::int64_t>``
