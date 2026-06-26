/* Test generation for btf_type_tag attribute when applied to struct/union
   types after definition.  PR/125888.

   btf_type_tag does not affect type identity, layout or fields, so it is now
   accepted on already-defined aggregate types (and on typedefs of them) and a
   DW_TAG_GNU_annotation DIE is generated for each.  */
/* { dg-do compile } */
/* { dg-options "-gdwarf -dA" } */

struct foo
{
  int a;
  char c;
};

struct foo __attribute__((btf_type_tag ("tag1"))) x;  /* { dg-bogus "ignoring attribute" } */
typedef const struct foo c_foo;
c_foo __attribute__((btf_type_tag ("tag2"))) y; /* { dg-bogus "ignoring attribute" } */

union bar
{
  int s;
  unsigned int u;
};

typedef union bar __attribute__((btf_type_tag("tag3"))) tag_bar; /* { dg-bogus "ignoring attribute" } */
const tag_bar z;

/* Each tag generates a DW_TAG_GNU_annotation DIE.  The DW_AT_const_value
   patterns accept either the strp form ("DW_AT_const_value: \"tag\"") or the
   inline-string form (".ascii \"tag\\0\" ... DW_AT_const_value") so the test
   works on targets that do not pool debug strings (e.g. bpf).  */
/* { dg-final { scan-assembler-times {(?n)DIE \(.*\) DW_TAG_GNU_annotation} 3 } } */
/* { dg-final { scan-assembler-times {(?n)( DW_AT_const_value: "tag1"|"tag1..".* DW_AT_const_value)} 1 } } */
/* { dg-final { scan-assembler-times {(?n)( DW_AT_const_value: "tag2"|"tag2..".* DW_AT_const_value)} 1 } } */
/* { dg-final { scan-assembler-times {(?n)( DW_AT_const_value: "tag3"|"tag3..".* DW_AT_const_value)} 1 } } */
