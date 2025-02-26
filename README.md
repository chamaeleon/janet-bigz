# bigz

This is a wrapper for the [bigz](https://sourceforge.net/projects/bigz/) bignum library for the [Janet](https://www.janet-lang.org/) programming language.

# Examples

```lisp
(import bigz/bigz :as bz)

(defn fac [n]
  (if (< n 2)
    (bz/from-integer 1)
    (bz/multiply (bz/from-integer n)
                 (fac (- n 1)))))

(print "fac(50) = " (fac 50))
```
```
30414093201713378043612608166064768844377641568960512000000000000
```
