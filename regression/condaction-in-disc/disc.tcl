package require math::special

proc awksplit {text {split default}} {
        set no 0
        if {$split!="default"} {
                set t [split $text $split]
        } else {
                eval set t [list $text]
        }
        uplevel 1 [list set NF [llength $t]]
        foreach i $t {uplevel 1 [list set [incr no] $i]}
        uplevel 1 [list set 0 $t]
} ;# -- RS

proc getopt {_argv name {_var ""} {default ""}} {
    upvar 1 $_argv argv $_var var
    set pos [lsearch -regexp $argv ^$name]
    if {$pos>=0} {
	set to $pos
	if {$_var ne ""} {
	    set var [lindex $argv [incr to]]
	}
	set argv [lreplace $argv $pos $to]
	return 1
    } else {
	if {[llength [info level 0]] == 5} {set var $default}
	return 0
    }
}

# read time 
getopt argv -t time
getopt argv -a alpha
getopt argv -r R
set fd [open "/dev/stdin" "r"]

set beta 2.4048
while {1} {
    set line [gets $fd]
    if {[eof $fd]} {
        close $fd
        break
    }
    awksplit $line
    set rad $1
    if {$rad < $R} {
	set auxJ0 [::math::special::J0 [expr {$beta*$rad/$R}]]
	set T [expr {$auxJ0 * exp(-$alpha * pow($beta/$R, 2) * $time)}]
    } else {
	set T 0.0
    }
    puts "$rad $T"
}

