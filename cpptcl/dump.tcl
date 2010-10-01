proc interp'dump {filename} {
    set res "\# sph-blitz tcl configuration dump\n"
    # catch {package require "a non-existing one"}
    # foreach package [lsort [package names]] {
    # 	if {![catch {package present $package} version]} {
    # 	    append res "package require $package $version" \n
    # 	}
    # }
    foreach i [lsort [info globals]] {
	if {$i == "env"} continue  ;# don't dump environment..
	if {[string match tcl_* $i]} continue ;# ..or Tcl system vars
	if {[string match auto_index $i]} continue ;# ..or Tcl system vars
	if {[array exists ::$i]} {
	    append res [list array set $i [array get ::$i]]\n
	} else {
	    append res [list set $i [set ::$i]]\n
	}
    }

    foreach alias [lsort [interp aliases {}]] {
	append res "interp alias {} $alias {} [interp alias {} $alias]\n"
    }
    set fp [open $filename w]
    puts $fp $res
    close $fp
}