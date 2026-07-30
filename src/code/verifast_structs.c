struct s2 { int x; };
struct s1 { struct s2 inner; };

/*@ predicate s1(struct s1 *p; struct s2 val) =
        s1_inner(p, val); @*/

void f(struct s1 *p)
//@ requires s1(p, ?in);
//@ ensures s1(p, ?out);
{
    p->inner.x =1 ;
}

/*@ predicate s1_A(struct s1 *p; struct s2 val) =
        s1_inner(p,val) &*& s2_x(&p->inner, _);
@*/

/*@ predicate s1_B(struct s1 *p; struct s2 val) =
       s1_inner(p,val) &*& s2_x(&p->inner, val.x);
@*/
