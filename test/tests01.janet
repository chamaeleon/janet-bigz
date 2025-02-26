(import bigz/bigz :as bz)

(defn bz [n] (bz/from-integer n))
(defn bz-str [s] (bz/from-string s 10))

(let [a (bz 20)
      b (bz 10)
      c (bz 30)
      d (bz 20)]
  (assert (= (bz/compare a b) 1))
  (assert (= (bz/compare a c) -1))
  (assert (= (bz/compare a d) 0))
  (assert (< b a))
  (assert (= a d))
  (assert (> c b))
  (assert (<= a d))
  (assert (>= a d))
  (assert (not= a b)))

(let [a (bz 123)
      b (bz-str "123")
      c (bz 456)
      d (bz-str "456")]
  (assert (= a b))
  (assert (= (string a) "123"))
  (assert (= (string b) "123"))
  (assert (= c d))
  (assert (not= a c))
  (assert (not= b d)))

(let [a (bz 10)
      b (bz 20)
      c (bz/add a b)
      d (bz/subtract a b)
      e (bz/multiply a b)
      f (bz/div b a)
      g (bz/negate a)]
  (assert (= c (bz 30)))
  (assert (= d (bz -10)))
  (assert (= e (bz 200)))
  (assert (= f (bz 2)))
  (assert (= g (bz -10))))

(let [a (bz 10)]
  (assert (= (bz/test-bit 0 a) 0))
  (assert (= (bz/test-bit 1 a) 1))
  (assert (= (bz/test-bit 2 a) 0))
  (assert (= (bz/test-bit 3 a) 1))
  (assert (= (bz/bit-count a) 2)))

(let [a (bz 123456)
      b (bz 10)
      c (bz 20)]
  (assert (= (bz/truncate a b) (bz 12345)))
  (assert (= (bz/truncate a c) (bz 6172)))
  (assert (= (bz/floor a b) (bz 12345)))
  (assert (= (bz/floor a c) (bz 6172)))
  (assert (= (bz/ceiling a b) (bz 12346)))
  (assert (= (bz/ceiling a c) (bz 6173))))

(let [a (bz 14)
      b (bz 16)
      c (bz 25)
      d (bz 35)
      ten (bz 10)]
  (assert (= (bz/round a ten) (bz 1)))
  (assert (= (bz/round b ten) (bz 2)))
  (assert (= (bz/round c ten) (bz 2)))
  (assert (= (bz/round d ten) (bz 4))))

(let [a (bz 10)
      b (bz -10)
      c (bz 4)]
  (assert (= (bz/mod a c) (bz 2)))
  (assert (= (bz/rem a c) (bz 2)))
  (assert (= (bz/mod b c) (bz 2)))
  (assert (= (bz/rem b c) (bz -2))))

(let [a (bz 3)
      b (bz -3)]
  (assert (= (bz/pow a 5) (bz 243)))
  (assert (= (bz/pow b 5) (bz -243)))
  (assert (= (bz/pow b 4) (bz 81))))

(let [a (bz 4)
      b (bz 5)
      c (bz -4)
      d (bz -5)]
  (assert (bz/even? a))
  (assert (not (bz/even? b)))
  (assert (bz/even? c))
  (assert (not (bz/even? d)))
  (assert (not (bz/odd? a)))
  (assert (bz/odd? b))
  (assert (not (bz/odd? c)))
  (assert (bz/odd? d)))

(let [a (bz-str "100000000000000000000")
      b (bz/multiply a a)
      c (bz 31)]
  (assert (= (bz/to-string b 10 false) "10000000000000000000000000000000000000000"))
  (assert (= (bz/to-string c 2 false) "11111")))

(let [a (bz 10)
      b (bz 7)]
  (assert (= (bz/not a) (bz -11)))
  (assert (= (bz/and a b) (bz 2)))
  (assert (= (bz/or a b) (bz 15))))

(let [a (bz 3)]
  (assert (= (bz/ash a 3) (bz 24)))
  (assert (= (bz/ash a 4) (bz 48)))
  (assert (= (bz/ash a -1) (bz 1)))
  (assert (= (bz/ash a -2) (bz 0)))
  (assert (= (bz/ash a -3) (bz 0))))

(let [a (bz 256)]
  (assert (= (bz/sqrt a) (bz 16))))

(let [a (bz 24)
      b (bz 5)
      c (bz 120)
      d (bz 48)]
  (assert (= (bz/lcm a b) (bz 120)))
  (assert (= (bz/gcd c d) (bz 24))))

(let [a (bz 3)
      b (bz 5)
      c (bz 7)
      d (bz 13)]
  (assert (= (bz/mod-exp a b c) (bz 5)))
  (assert (= (bz/mod-exp b a d) (bz 8))))