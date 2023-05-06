# RBTree Library

RBTree is a C++ template library for working with Red-Black Trees. This README provides information on building and using the library, its dependencies, development, and licensing.

## Build

To build the library, run the following commands:

```
cmake -S . -B ./build
cmake --build ./build
```

## Usage

To use the library, include the header file `RBTree.h` and create an instance of the `RBTree` class.

```cpp
#include <iostream>
#include "RBTree.h"

int main() {
    RBTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    for (auto const& value: tree) {
        std::cout << value << ' ';
    }
    return 0;
}
```

The RBTree class provides an implementation of a red-black tree, a self-balancing binary search tree. The following methods are available for the user to interact with:

- `RBTree()`: Constructor that initializes an empty tree.
- `RBTree(std::initializer_list<T> const &list)`: Constructor that initializes the tree with the values from an initializer list.
- `RBTree(const RBTree &other)`: Copy constructor.
- `RBTree(RBTree &&other) noexcept`: Move constructor.
- `RBTree<T> &operator=(const RBTree<T> &other)`: Copy assignment operator.
- `RBTree<T> &operator=(RBTree<T> &&other)`: Move assignment operator.
- `iterator begin() const`: Returns an iterator to the first element in the tree.
- `iterator end() const`: Returns an iterator to the end of the tree.
- `iterator find(const T &value) const`: Returns an iterator to the node containing the given value, or end() if not found.
- `iterator insert(const T &value)`: Inserts a new node with the given value into the tree, and returns an iterator to the inserted node.
- `size_t size() const`: Returns the number of elements in the tree.
- `size_t max_size() const`: Returns the maximum number of elements the tree can hold.
- `bool empty() const`: Returns true if the tree is empty, false otherwise.
- `size_t count(const T &key)`: Returns the number of nodes containing the given key in the tree.
- `iterator lower_bound(const T &value) const`: Returns an iterator to the first node with a value greater than or equal to the given value.
- `iterator upper_bound(const T &value) const`: Returns an iterator to the first node with a value strictly greater than the given value.
- `std::pair<iterator, iterator> equal_range(const T &key)`: Returns a pair of iterators delimiting the range of nodes containing the given key.
- `bool contains(const T &value) const`: Returns true if the tree contains a node with the given value, false otherwise.
- `void erase(iterator pos)`: Removes the node pointed to by the given iterator from the tree.
- `void erase(const T &value)`: Removes the node with the given value from the tree.
- `void swap(RBTree &other)`: Swaps the contents of this tree with another tree.
- `void clear() noexcept`: Removes all nodes from the tree.
- `void merge(RBTree &other)`: Merges the contents of another tree with this tree.
- `~RBTree()`: Destructor that deallocates all memory used by the tree.

In addition, the RBTree class provides several private helper methods for internal use, such as left_rotate, right_rotate, and insert_fixup.

## Dependencies

The RBTree library depends on CMake 3.10 or later and a C++17 compiler.

## Development

To contribute to the development of the RBTree library, clone the repository and submit a pull request. The library uses CMake for building and testing. You can run the following commands to run the tests:

```
cmake -S . -B ./build
cmake --build ./build
cd build/
make tests
```

## License

The RBTree library is licensed under the MIT License. See [LICENSE](LICENSE) for more information.