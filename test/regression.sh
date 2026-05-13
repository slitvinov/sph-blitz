#!/bin/sh
# Build and run reference cases; diff against checked-in goldens.
set -eu

ROOT=$(cd -- "$(dirname -- "$0")/.." && pwd)
cd "$ROOT"
make -s all

WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT
fail=0

run() {
    name=$1 cfg=$2 stamp=$3
    rm -rf outdata
    cp "$cfg.cfg" "$WORK/$name.cfg"
    if [ -f "$cfg.txt" ]; then cp "$cfg.txt" "$WORK/$name.txt"; fi
    if ! example/sdpd "$WORK/$name" > "$WORK/$name.log" 2>&1; then
        echo "FAIL $name: sdpd exited non-zero"
        tail -20 "$WORK/$name.log"
        fail=1; return
    fi
    if ! diff -q "outdata/p.$stamp.dat" "test_data/p.ref.$name.dat" > /dev/null; then
        echo "FAIL $name: output differs from test_data/p.ref.$name.dat"
        diff "outdata/p.$stamp.dat" "test_data/p.ref.$name.dat" | head -10
        fail=1; return
    fi
    echo "ok   $name"
}

run ellipse    cases/ellipse    0001171350
run poiseuille cases/poiseuille 0000050347

exit "$fail"
