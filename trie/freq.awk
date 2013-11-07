 { count++ 
   for (i=1; i<NF; i++)
     words[$i]++
 }
 
 END { 
   #for (i in words)
   #  print words.length
   print count
 }
