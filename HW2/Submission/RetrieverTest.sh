#!/bin/bash
# Retriever test. Will call the server and print out the content
# Important, set up the server first

./Retriever $1 /testFile.txt $2 # Access a file on server
cat content.txt

./Retriever $1 /SecretFile.html $2 # Access an unauthorized file
cat content.txt

./Retriever $1 ../testFile.txt $2 # Access a forbidden file
cat content.txt

./Retriever $1 testFile.txt $2 # Access a file that does not exist
cat content.txt

./BadRetriever $1 /testFile.txt $2 # Access using a bad request
