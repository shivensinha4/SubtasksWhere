for ((i=1;;i++)); do
  echo $i
  ./random.out
  ./A.out > out1
  exit_code=$?
  if [[ $exit_code -ne 0 ]]; then
      exit 0
  fi
  ./B.out > out2
  diff -w out1 out2 || break;
done