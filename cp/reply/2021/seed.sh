# for x in {1..5}; do
#     echo $x
#     ./a.out $x < in/e.in > out/e/e$x.out
# done;

for ((i=1; i<100; i++)); do
    echo $i
    ./a.out $i < in/f.in > out/f/f$i.out
done