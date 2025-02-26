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

(print "version = " (bz/version))
(print)
(print "fac(10) = " (fac 10))
(print "fac(20) = " (fac 20))
(print "fac(30) = " (fac 50))
(print)

(defn fib1 [n]
  (if (< n 2)
    (bz/from-integer 1)
    (bz/add (fib1 (- n 1))
            (fib1 (- n 2)))))

(defn fib2 [n]
  (defn recur [n a b]
    (if (< n 1)
      a
      (recur (- n 1) b (bz/add a b))))
  (recur n (bz/from-integer 1) (bz/from-integer 1)))

(print "fib1(10) = " (fib1 10))
(print "fib1(20) = " (fib1 20))
(print "fib1(40) = " (fib1 40) " (slow recursion)")

(print)

(print "fib2(10) = " (fib2 10))
(print "fib2(20) = " (fib2 20))
(print "fib2(40) = " (fib2 40) " (fast iteration)")

(print)

(print "fib2(100) = " (fib2 100))
(print "fib2(200) = " (fib2 200))
(print "fib2(300) = " (fib2 400))

(print)

(def zero (bz/from-integer 0))
(def two (bz/from-integer 2))
(def three (bz/from-integer 3))

(defn factors [n]
  (defn recur [factors n factor]
    (if (< n (bz/multiply factor factor))
      (if (>= n two)
        (array/push factors n)
        factors)
      (if (= zero (bz/mod n factor))
        (recur (array/push factors factor)
               (bz/div n factor)
               factor)
        (recur factors n
               (if (= factor two)
                 three
                 (bz/add factor two))))))
  (recur @[] n two))

(let [n (bz/from-string "3761287643876417876" 10)]
  (prin "factors(" n ") = [ ")
  (each f (factors n) (prin f " "))
  (print "]"))
```
```
version = 2.1.0

fac(10) = 3628800
fac(20) = 2432902008176640000
fac(30) = 30414093201713378043612608166064768844377641568960512000000000000

fib1(10) = 89
fib1(20) = 10946
fib1(40) = 165580141 (slow recursion)

fib2(10) = 89
fib2(20) = 10946
fib2(40) = 165580141 (fast iteration)

fib2(100) = 573147844013817084101
fib2(200) = 453973694165307953197296969697410619233826
fib2(300) = 284812298108489611757988937681460995615380088782304890986477195645969271404032323901

factors(3761287643876417876) = [ 2 2 13 23 281 2411 4641964741 ]
```
