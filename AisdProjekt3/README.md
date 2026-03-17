Dynamic sparse table

To store values indexed by sparse keys from a certain universe N, hash tables seem to be a good solution. A downside of using them may be poor access time in the pessimistic case. Another way to handle this task is to use a trie tree, which offers a better pessimistic time estimate.

In our task, the trie is described by two parameters: n and k. It is built in the following way: the root has n child nodes, and each of those has k more child nodes. To insert a key x, we start from the root. If the root is free (each node holds at most one key and possibly a value — in our case only the key), we store the value and finish the operation. If the root is already occupied, we search for a place by selecting the next child node using div = x mod n, and then div = div mod k, repeating until we find a free spot. Searching is done similarly — starting from the root and following nodes with indices mod n and then mod k until we find the value x or reach an empty child node (meaning the key is not in the tree). Deleting is a bit harder and requires finding the node p with the given key. If it's an internal node, a deletion candidate must be selected. The candidate q can be searched for in different ways but must always be a leaf node (one with no children). We use a simple strategy of always searching to the left. If a candidate is found, its value is copied to the node p (where key x was stored), and then node q is deleted.

#################################################################################
Input
The first line contains the number n, specifying the number of test cases (commands I, L, D, and P – insert, lookup, delete, and print), each on a new line. The next line contains two numbers: minimum and maximum, defining the possible range of input values. The following line contains two more numbers: n and k, the parameters of our trie. Then, after a blank line, there are n test cases as mentioned earlier. Command:
I x – inserts key x into the trie. If it already exists, it prints x exist; otherwise, it prints nothing.
L x – prints x exist if the key is found, otherwise x not exist.
D x – deletes key x from the trie. If deletion fails (key not found), it prints x not exist. If deletion is successful, it prints nothing. The deleted node is either the leftmost external child of the node containing x, or the node itself if it has no children.
P – prints the contents of the tree in preorder order. If during deletion (D x) the leftmost external node is not chosen, the tree structure will differ, affecting preorder traversal and final output.
Output
Each line contains the result of the commands (I, L, D, P), or no line in case no output is expected (e.g., successful insertion or deletion x).

#################################################################################
Example
Input
29
0 511
8 4

I 3
I 31
I 150
I 190
I 130
I 174
I 81
I 30
I 203
P
L 32
L 30
L 150
D 150
L 150
I 150
L 150
D 3
L 3
I 3
L 3
D 3
L 3
D 30
L 30
I 30
L 30
D 30
L 30

Output
3 81 130 203 150 174 190 30 31 
32 not exist
30 exist
150 exist
150 not exist
150 exist
3 not exist
3 exist
3 not exist
30 not exist
30 exist
30 not exist
