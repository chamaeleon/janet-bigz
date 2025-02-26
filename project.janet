(declare-project
  :name "bigz"
  :description ```bigz wrapper library for Janet```
  :version "0.0.1"
  :author "Lars Nilsson"
  :license "Simplified BSD")

(declare-native
  :name "bigz/bigz"
  :source @["c/module.c" "c/bigz.c" "c/bign.c" "c/bigq.c"])