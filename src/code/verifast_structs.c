struct s2 { int x; };
struct s1 { struct s2 inner; };

/*@ predicate s1(struct s1 *p; struct s2 val) =
        p->inner |-> val; @*/

void f(struct s1 *p)
//@ requires s1(p, ?in);
//@ ensures s1(p, ?out);
{
    struct s2 val;
    val.x = 1;
    p->inner;
}

/*@ predicate s1(struct s1 *p; struct s2 val) =
        p->inner |-> val &*& s2_x(&p->inner, _); @*/

/*@ predicate s1(struct s1 *p; struct s2 val) =
        p->inner |-> val &*& s2_x(&p->inner, val.x); @*/
