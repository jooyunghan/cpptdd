Build and run
========

    gcc driver.c normalizer.c bstree.c -o bstree
    time ./bstree < encyclopedia.txt

    gcc driver.c normalizer.c trie.c -o trie
    time ./trie < encyclopedia.txt

    awk -f freq.awk encyclopedia.txt

Sample Run
========

    $ time ./trie < encyclopedia.txt 
		1654759

		real	0m1.311s
		user	0m1.171s
		sys	0m0.089s

		$ time ./bstree < encyclopedia.txt 
		1654759

		real	0m1.996s
		user	0m1.948s
		sys	0m0.027s


