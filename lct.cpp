/*
https://courses.csail.mit.edu/6.851/spring12/scribe/L19.pdf
https://www.cnblogs.com/flashhu/p/9498517.html
https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lct-vertice.cpp
https://codeforces.com/blog/entry/83170
https://github.com/kzvd4729/Tmp/blob/master/lct

represented tree: the actual tree. tree we want to
represent. actual tree are forest of some rooted trees.

preferred child: u is called preferred child of v if
last accessed node in v's subtree is in u's subtree.
preferred child can be null if v is last accessed node
or v has no accessed node.

preferred edge: edge between node and preferred child.

preferred path: continuous path where each edge is
preferred edge. preferred path can be a single node.
a tree will have many preferred path. each preferred
path is node disjoint and every node is in exactly one
preferred path.

auxillary tree/splay tree: splay trees represent
preferred path. one splay tree for each path. splay
trees are balanced binary search tree where nodes are 
keyed by their depth in actual tree.

path-parent pointer: path parent pointer connects two
splay trees. path parent pointer is stored in the root
of splay tree and points to parent of the topmost
(lowest depth) node of preferred path. so a path parent
pointer is an edge of represented tree which is not
preferred.

*/
