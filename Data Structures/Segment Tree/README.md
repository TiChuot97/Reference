[//]: # (Below are links to math symbols)

[//]: # (Numbers)
[0]: https://latex.codecogs.com/gif.latex?0
[1]: https://latex.codecogs.com/gif.latex?1
[2]: https://latex.codecogs.com/gif.latex?2
[3]: https://latex.codecogs.com/gif.latex?3
[4]: https://latex.codecogs.com/gif.latex?4
[5]: https://latex.codecogs.com/gif.latex?5
[6]: https://latex.codecogs.com/gif.latex?6
[7]: https://latex.codecogs.com/gif.latex?7
[8]: https://latex.codecogs.com/gif.latex?8
[9]: https://latex.codecogs.com/gif.latex?9

[n]: https://latex.codecogs.com/gif.latex?n
[arr]: https://latex.codecogs.com/gif.latex?a_1%2C%20a_2%2C%20a_3%2C%20...%2C%20a_%7Bn%20-%201%7D%2C%20a_n
[q]: https://latex.codecogs.com/gif.latex?q
[ai]: https://latex.codecogs.com/gif.latex?a_i
[o1]: https://latex.codecogs.com/gif.latex?O%281%29
[on]: https://latex.codecogs.com/gif.latex?O%28n%29

# Segment Tree

## Introduction

Segment Tree (also called Interval Tree) is one of the most widely used data
structures (along Binary Indexed Tree) in competitive programming. Segment Tree
can be combined with a variety of other techniques to create problems ranging
from medium to extremely difficult. Hence, Segment Tree is a must-know data
structure if you want to proceed further on the competitive programming journey.

Besides from being ubiquitous in competitions, Segment Tree is also popular for
its understandability. Compared with Binary Indexed Tree (one other popular
tree-like data structure), Segment Tree has the advantage of being more flexible
(i.e any problem that can be solved with Binary Indexed Tree can be solved with
Segment Tree) and a lot simpler to comprehend.

In the following sections, we will go over how Segment Tree works and its
implementation, starting with the most basic problem that it solves.

## Problem

This section will describe the example problem which we will use throughout this
tutorial to see Segment Tree in action:


> Given an array of ![n] integers ![arr] and ![q] queries, each of which is of
the two following types:
>   * ![type1](https://latex.codecogs.com/gif.latex?C%20%5Ctextit%7B%20%7D%20i%20%5Ctextit%7B%20%7D%20x%3A)
  Change the value of *a_i* to *x*
>   * ![type2](https://latex.codecogs.com/gif.latex?S%20%5Ctextit%7B%20%7D%20l%20%5Ctextit%7B%20%7D%20r%3A)
  Compute the sum ![sum](https://latex.codecogs.com/gif.latex?%5Csum_%7Bi%20%3D%20l%7D%5Er%20a_i%20%3D%20a_l%20&plus;%20a_%7Bl%20&plus;%201%7D%20&plus;%20...%20&plus;%20a_%7Br%20-%201%7D%20&plus;%20a_r)

## Naive solution

It is easy to see that we can solve the problem above by simply follow
instructions. Then, for the first type of query, we can update the value of
![ai] in ![o1]:
```cpp
  void update(int i, int x) {
    a[i] = x;
  }
```
On the other hand, for each query of then second type, the sum can be computed
in ![on] by:
```cpp
  int query(int l, int r) {
    int sum = 0;
    for (int i = l; i <= r; ++i) {
      sum += a[i];
    }
    return sum;
  }
```
With this approach, update queries can be executed very quickly while sum
queries, on the other hand, takes a lot of time. This can be an issue if we
receive an overwhelming amount of type two queries and very few type one
queries. This is where Segment Tree comes to the rescue!

## Basic Segment Tree

### Structure

So, what exactly is Segment Tree? To keep things simple, let us denote ![Sij](https://latex.codecogs.com/gif.latex?S_%7Bi%2C%20j%7D%20%3D%20%5Csum_%7Bt%20%3D%20i%7D%5Ej%20a_t). To solve the above problem, the idea is that we compute and store the following sums of subarrays in a binary-tree-like structure:
  - The whole array: ![S1n](https://latex.codecogs.com/gif.latex?S_%7B1%2C%20n%7D)
  - The left and right halves of the array: ![S1](https://latex.codecogs.com/gif.latex?S_%7B1%2C%20%5Clfloor%7B%5Cfrac%7Bn%7D%7B2%7D%5Crfloor%7D%7D%2C%20S_%7B%5Clfloor%7B%5Cfrac%7Bn%7D%7B2%7D%5Crfloor%20&plus;%201%2C%20n%7D%7D).
  - The left and right halves of each of the above subarrays:
  ![subarrs](https://latex.codecogs.com/gif.latex?a_%7B1..%5Clfloor%5Cfrac%7Bn%7D%7B4%7D%5Crfloor%7D%2C%20a_%7B%5Clfloor%5Cfrac%7Bn%7D%7B4%7D%5Crfloor%20&plus;%201..%5Clfloor%5Cfrac%7Bn%7D%7B2%7D%5Crfloor%7D%2C%20a_%7B%5Clfloor%5Cfrac%7Bn%7D%7B2%7D%5Crfloor%20&plus;%201..%5Clfloor%5Cfrac%7B3n%7D%7B4%7D%5Crfloor%7D%2C%20a_%7B%5Clfloor%5Cfrac%7B3n%7D%7B4%7D%5Crfloor%20&plus;%201..n%7D)
  - ...
  - So on until the subarrays are of size ![1]

These sums are then stored in the following tree-like structure:

![figure1](./img/1.png)
