/* Test generation of BTF type tags applied to a typedef of a struct type.

   When a btf_type_tag is supplied in the definition of a typedef whose
   underlying type is a struct, the attribute is recorded on the struct type,
   i.e. on the DW_AT_type target of the typedef DIE.  A BTF_KIND_TYPE_TAG
   record is therefore inserted into the chain between the typedef and the
   struct:
     var("s") -> typedef("S_t") -> type_tag("t1") -> struct("S")  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

#define __tag1 __attribute__((btf_type_tag("t1")))

typedef struct S { int x; } __tag1 S_t;
S_t s;

/* { dg-final { scan-assembler-times " BTF_KIND_VAR 's'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPEDEF 'S_t'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'S_t'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 't1'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 't1'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_STRUCT 'S'\\)" 1 } } */
