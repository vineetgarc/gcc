/* Test btf_type_tag on a typedef of an already-defined struct, union or enum.
   PR/125888.

   Unlike a typedef that defines the aggregate inline (btf-type-tag-6.c), here
   the aggregate is defined first and a separate typedef adds the tag.  The tag
   is recorded as a BTF_KIND_TYPE_TAG inserted between the typedef and the
   aggregate:
     S_t -> type_tag("st") -> struct S
     U_t -> type_tag("un") -> union  U
     E_t -> type_tag("en") -> enum   E  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

#define __t(x) __attribute__((btf_type_tag (x)))

struct S { int x; };
union  U { int a; long b; };
enum   E { E0, E1 };

typedef struct S __t ("st") S_t;
typedef union  U __t ("un") U_t;
typedef enum   E __t ("en") E_t;

S_t s;
U_t u;
E_t e;

/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'S_t'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'st'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'st'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_STRUCT 'S'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'U_t'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'un'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'un'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_UNION 'U'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'E_t'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG 'en'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG 'en'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_ENUM 'E'\\)" 1 } } */
