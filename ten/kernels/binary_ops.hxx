#ifndef TA_KERNELS_STD_SIMD_BINARY_OPS_HXX
#define TA_KERNELS_STD_SIMD_BINARY_OPS_HXX

#include <experimental/bits/simd.h>
#include <experimental/simd>

#include <ten/config.hxx>
#include <ten/types.hxx>

namespace ten::kernels {

template <::ten::binary_operation kind, class A, class B, class C>
static void binary_ops(const A &a, const B &b, C &c) {
   size_t n = a.size();
   constexpr size_t vlen = ::ten::simd_vecLen;
   using ::ten::binary_operation;
   using T = typename A::value_type;
   using vector_type = std::experimental::fixed_size_simd<float, vlen>;
   using alignment = std::experimental::element_aligned_tag;

   for (size_t i = 0; i < n / vlen; i++) {
      // Load a and b
      size_t offset = i * vlen;
      vector_type a_vec;
      a_vec.copy_from(a.data() + offset, alignment{});
      vector_type b_vec;
      b_vec.copy_from(b.data() + offset, alignment{});
      // c_vec = a_vec ops b_vec
      vector_type c_vec;
      switch (kind) {
      case binary_operation::add:
         c_vec = a_vec + b_vec;
         break;
      case binary_operation::sub:
         c_vec = a_vec - b_vec;
         break;
      case binary_operation::div:
         c_vec = a_vec / b_vec;
         break;
      case binary_operation::mul:
         c_vec = a_vec * b_vec;
         break;
      }
      // Copy back
      c_vec.copy_to(c.data() + offset, alignment{});
   }
   for (size_t i = vlen * (n / vlen); i < n; i++) {
      switch (kind) {
      case binary_operation::add:
         c[i] = a[i] + b[i];
         break;
      case binary_operation::sub:
         c[i] = a[i] - b[i];
         break;
      case binary_operation::div:
         c[i] = a[i] / b[i];
         break;
      case binary_operation::mul:
         c[i] = a[i] * b[i];
         break;
      }
   }
}
} // namespace ten::kernels

#endif
