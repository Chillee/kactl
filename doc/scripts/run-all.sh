#!/usr/bin/env bash
DIR=${1:-.}
tests="$(find $DIR/stress-tests -name '*Polygon*.cpp')"
declare -i pass=0
declare -i fail=0
failTests=""
ulimit -s 524288 # For 2-sat test
for test in $tests; do
    echo "$(basename $test): "
    start=`date +%s.%N`
    g++ -std=c++14 -O2 $test
    retCode1=$?
    ./a.out
    end=`date +%s.%N`
    retCode2=$?
    if (($retCode1 != 0 || $retCode2 != 0)); then
        echo "Failed with $retCode"
        fail+=1
        failTests="$failTests$test\n"
    else
        pass+=1
    fi
    runtime=$( echo "$end - $start" | bc -l )
    echo "Took $runtime seconds"
    rm -f a.out
    echo
done
echo "$pass/$(($pass+$fail)) tests passed"
if (($fail == 0)); then
    echo "No tests failed"
    exit 0
else
    echo -e "These tests failed: \n $failTests"
    exit 1
fi
