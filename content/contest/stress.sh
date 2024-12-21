for ((i=1;;i++)); do
  echo $i
  ./random.out
  ./A.out > out1
  ./B.out > out2
  diff -w out1 out2 || break;
done