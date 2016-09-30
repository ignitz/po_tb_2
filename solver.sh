#/bin/sh

if [[ $# -eq 1 ]]; then
	gen_arg=$1
else
	gen_arg=
fi

echo running generator
./generator $gen_arg > __input
echo running glpsol
glpsol -m sched.mod -d __input -o __temp__
echo running heuristic
./main < __input

