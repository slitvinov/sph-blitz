set s 30

set val 42.0

set aux(1) 1.0
set aux(2) 2.0

set mat(1,1) 18.0

set aux_no  1
proc getmatNo {x y} {
    set no [expr {$aux_no + 1}]
}