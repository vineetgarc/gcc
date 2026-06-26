/* Test btf_type_tag attribute on function return types.

   Following clang, btf_type_tag is only meaningful on a pointer type.  On a
   function it applies to the return type only when that return type is a
   pointer; a non-pointer return type still warns and the tag is dropped.  */
/* { dg-do compile } */

/* Non-pointer return: tag does not apply, warning expected.  */
int __attribute__((btf_type_tag ("A"))) a (int x); /* { dg-warning "does not apply to functions" } */

/* Pointer return: tag applies to the return type, accepted.  */
__attribute__((btf_type_tag ("B"))) int *b (int y); /* { dg-bogus "does not apply to functions" } */

int *c (int z) __attribute__((btf_type_tag ("C"))); /* { dg-bogus "does not apply to functions" } */
