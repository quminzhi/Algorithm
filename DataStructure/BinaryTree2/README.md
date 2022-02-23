# Binary Tree

## Introduction

A tree is a frequently-used data structure to simulate a hierarchical tree structure.

Each node of the tree will have a root value and a list of references to other nodes which are called child nodes. From graph view, a tree can also be defined as a directed acyclic graph which has `N` nodes and `N-1` edges.

A Binary Tree is one of the most typical tree structure. As the name suggests, a binary tree is a tree data structure in which each node has at most two children, which are referred to as the left child and the right child.

## Traverse a Tree

In this chapter, we will focus on the traversal methods used in a binary tree. Understanding these traversal methods will definitely help you have a better understanding of the tree structure and have a solid foundation for the further study.

The goal of this chapter is to:

- Understand the difference between different tree traversal methods.
- Be able to solve preorder, inorder and postorder traversal recursively.
- Be able to solve preorder, inorder and postorder traversal iteratively.
- Be able to do level traversal using BFS.

### Preorder Traverse

Pre-order traversal is to visit the root first. Then traverse the left subtree. Finally, traverse the right subtree.

