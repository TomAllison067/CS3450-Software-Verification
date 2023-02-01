mkdir build
for cfile in example-programs/*.c; 
do 
  gcc $cfile -o build/`basename $cfile .c`;
done

