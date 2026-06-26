/* Test that btf_type_tag on a non-pointer function return type is dropped:
   it is only meaningful on a pointer type, so no BTF_KIND_TYPE_TAG record is
   emitted and a warning is issued.  PR/125991.  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

int __attribute__((btf_type_tag ("dropped"))) f (int x) { return x; } /* { dg-warning "does not apply to functions" } */

/* The function is emitted, but with no type tag on its return type.  */
/* { dg-final { scan-assembler "BTF_KIND_FUNC 'f'" } } */
/* { dg-final { scan-assembler-not "BTF_KIND_TYPE_TAG" } } */
