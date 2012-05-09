#! /bin/bash

awk '/INITIAL_CONDITION/{$2=0} 1' lock-exchange.cfg | \
awk '/TIMING/{$3=1e-4; $4=1e-4} 1' > lock-exchange_init.cfg
../src/sph  lock-exchange_init
awk -f ../scripts/lock-exchange.awk  lock-exchange_init.rst > lock-exchange.rst

rm outdata/*.dat
../src/sph  lock-exchange