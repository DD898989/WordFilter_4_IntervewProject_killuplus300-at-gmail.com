# WordFilter_4_IntervewProject_killuplus300-at-gmail.com
## Purpose ##
The purpose of this project is making a word filter system for dialogs that have length around 100. And the total filter cases more than 200K with arbitrary lengthes in any language.  


## Complexity Evaluation ##
### The following three Tries were evaluated ###
#### 1. Normal Trie ####
![](https://i.imgur.com/BQ6VJ03.png) <br/>
*from http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Text/trie01.html*
<br/>
<br/>
<br/>
#### 2. Redis Trie ####
![](https://i.imgur.com/8LKCr0t.png) <br/>
*from Wikipedia*
<br/>
<br/>
<br/>
#### 3. Tenary Trie ####
![](https://i.imgur.com/Ky4ItGl.png) <br/>
*from https://www.geeksforgeeks.org/ternary-search-tree/*
<br/>
<br/>
<br/>
Age           | Time  | Food | Gold | Requirement
------------  | ----  | ---  | ---  | ---
Feudal Age    | 02:10 |  500 |    0 | Dark Age building x 2
Castle Age    | 02:40 |  800 |  200 | Feudal Age building x 2
Imperial Age  | 03:30 | 1000 |  800 | Castle Age building x 
<br/>
|           	  |Time             |Space       |
| ------------- |:---------------:|-----------:|
| Normal        | `O(K*L)`        | `O(N*L*R)` |
| Redis         | `O(L)`          | `O(N*L*L)` |
| Tenary        | `O(K*(L+log N))`| `O(N*L)`   |
<br/>
N: number of words<br/>
L: average length of words<br/>
K: number of matches<br/>
R: size of alphabet<br/>
<br/>
**Tenary Trie** is greatly infected by the order of the words that we insert, and it's not easy to implement an balanced-mechanism, so Tenary Trie is **out**<br/>
<br/>
**Reids Trie** have space complexity `O(N*L*L)`, since we want the system to adapt arbitrary word length, so we consider `L` to be large, so Reids Trie is **out**<br/>
<br/>
**Normal Trie** ,although with time complexity `O(N*L)`, but K is depending on the dialog length( ~100), and the size of alphabet `R` can be set by us, so this project **is implemented by Normal Trie**
<br/>


## Implementation ##
If we have only 26 english alphabet to be considered, the space complexity is `O(N*L*26)`, like the following picture showed:<br/>
<br/>
![](https://i.imgur.com/HKZjU9d.png) <br/>
*https://www.quora.com/What-is-the-best-way-to-implement-a-Trie-in-Java*
<br/>
<br/>
But our system is for any languages, so the Unicode result R to be 65536, sure that would be hell huge space that is needed, so instead an Unicode Trie, we reduce the complexity to Binary Trie(R=2) and Byte Trie(R=256) to see which is better.<br/>


## Analysis ##

![](https://i.imgur.com/yR8B93O.png) <br/>
x: filter cases<br/>
y: memory used(kb)<br/>
dialog length:500<br/>
<br/>
<br/>
![](https://i.imgur.com/HcpftLz.png) <br/>
x: filter cases<br/>
y: average finished time<br/>
dialog length:500<br/>
<br/>
<br/>
![](https://i.imgur.com/5EofnaC.png) <br/>
x: dialog length<br/>
y: average finished time<br/>
filter cases:216000<br/>
<br/>
<br/>

## Conclusion ##
Both the Binary Trie and Bity Trie are match the complexity evaluation we done before, but Bity Trie only a litter faster than Binary Trie and takes too much space, so the Binary Trie is consider to be the most efficient for the original purpose.
<br/>
<br/>
<br/>
