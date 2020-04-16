# Movie Reviews Analysis Using Binary Search Trees
## About
This program utilizes an implementation of the Binary Search Tree data structure to allow retrieval/storeage of data efficiently. 
All search and insert algorithms are O(log N).

## How it works 
The user is prompted to input a .txt file consisting of movie data and a .txt file consisting of review data. The data is then parsed and stored in the BST data structure. After storage is completed, the user is allowed and prompted to search the data.
The program accepts two .txt files:
 * Movies file
   - Each line consists: movie_id, year, title
 * Reviews file
   - Each line consists: review_id, movie_id, rating

## How to run(from command line)
From the project directory execute:
```console
./program.exe
```
and you will be prompted to enter movie filename:
```console
movies file?> movies1.txt
``` 

you will then be prompted to enter reviews filename:
```console
reviews file?> reviews1.txt
``` 

Output:
```console
Num movies: 252
Num reviews: 204826

Tree by movie id: size=252, height=16
Tree by movie name: size=252, height=16 
```

now you can search by id or name:
```console
Enter a movie id or name (or # to quit)> 175
``` 

Output:
```gch
Movie ID: 175
Movie Name: Network
Avg rating: 3.68107
5 stars: 172
4 stars: 311
3 stars: 211
2 stars: 67
1 star: 26
``` 

