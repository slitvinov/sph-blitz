proc compile {program plugin_name} {
    set tmpf "/tmp/__tmp.cpp"
    set ofile "/tmp/__tmp.so"
    
    set outfile [open $tmpf w]
    puts $outfile $program
    close $outfile
    
    set comp_line "{CXX} {CPPFLAGS} {CXXFLAGS} {LDFLAGS} {LIBS} $tmpf -o $ofile -shared"
    eval exec $comp_line
    exec mv $ofile $plugin_name
}