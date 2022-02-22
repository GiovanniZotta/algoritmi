for x in a b c d e f; do
    echo $x
    ./a.out $1 < in/$x.in > out/$x.out 
done;