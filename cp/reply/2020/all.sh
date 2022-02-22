for x in a b c d e f; do
    echo $x
    ./a.out < in/$x.txt > out/$x.txt
done