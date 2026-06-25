/* Test generation of BTF type tags applied to typedefs of non-pointer types.

   Unlike btf-type-tag-3.c, where the type tags reach the typedef via a pointer,
   here the tags annotate the underlying (non-pointer) type directly, or are
   applied to a use of an existing typedef.  In both cases a BTF_KIND_TYPE_TAG
   record is inserted into the chain between the typedef and its underlying
   type.  */

/* { dg-do compile } */
/* { dg-options "-O0 -gbtf -dA" } */

#define __tag1 __attribute__((btf_type_tag("1")))
#define __tag2 __attribute__((btf_type_tag("2")))

/* Single type tag in the typedef definition.
   var("a") -> typedef("td1") -> type_tag("1") -> int  */
typedef int __tag1 td1;
td1 a;

/* Multiple type tags in the typedef definition.
   var("b") -> typedef("td2") -> type_tag("2") -> type_tag("1") -> int  */
typedef int __tag1 __tag2 td2;
td2 b;

/* Type tag applied to a use of an existing (untagged) typedef.
   var("c") -> typedef("base") -> type_tag("1") -> int  */
typedef int base;
base __tag1 c;

/* { dg-final { scan-assembler-times " BTF_KIND_VAR 'a'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPEDEF 'td1'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'td1'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG '1'\\)" 1 } } */

/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'td2'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG '2'\\)" 1 } } */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG '2'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG '1'\\)" 1 } } */

/* { dg-final { scan-assembler-times " BTF_KIND_TYPEDEF 'base'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_TYPE_TAG '1'\\)" 1 } } */

/* In total there should be three TYPE_TAG '1' chains feeding an int.  */
/* { dg-final { scan-assembler-times " BTF_KIND_TYPE_TAG '1'(\[\\r\\n\]+\[^\\r\\n\]*){2}\\(BTF_KIND_INT 'int'\\)" 3 } } */
