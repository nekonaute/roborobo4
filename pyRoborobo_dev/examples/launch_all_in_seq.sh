for file in *.py
do
  run=false
  echo "running $file"
	python "$file"
	echo "--------- END ---------"
	read -p "Continue? (y/n) " -r
	if [[ $REPLY =~ ^[Yy]$ ]]
	then
	    run=true
	fi
	if [[ ! $run == true ]]
	then
	  break
	fi
done

