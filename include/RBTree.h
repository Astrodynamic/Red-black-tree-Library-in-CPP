#ifndef RBTREE_INCLUDE_RBTREE_H_
#define RBTREE_INCLUDE_RBTREE_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <utility>

#include "RBTNode.h"

template <class T>
class RBTree {
 private:
  RBTNode<T> *m_root = nullptr;
  RBTNode<T> *m_begin = nullptr;
  RBTNode<T> *m_end = nullptr;
  size_t m_size = 0;

 public:
  RBTree() : m_root(nullptr), m_begin(nullptr), m_end(nullptr), m_size(0) {}
  explicit RBTree(std::initializer_list<T> const &list);
  RBTree(const RBTree &other);
  RBTree(RBTree &&other) noexcept;

  RBTree<T> &operator=(const RBTree<T> &other);
  RBTree<T> &operator=(RBTree<T> &&other);

  class iterator;

  virtual iterator begin() const;
  virtual iterator end() const;
  virtual iterator find(const T &value) const;
  iterator insert(const T &value);
  virtual size_t size() const;
  virtual size_t max_size() const;
  virtual bool empty() const;
  virtual size_t count(const T &key);
  virtual iterator lower_bound(const T &value) const;
  virtual iterator upper_bound(const T &value) const;
  virtual std::pair<iterator, iterator> equal_range(const T &key);
  virtual bool contains(const T &value) const;
  virtual void erase(iterator pos);
  virtual void erase(const T &value);
  virtual void swap(RBTree &other);
  virtual void clear() noexcept;
  virtual void merge(RBTree &other);

  virtual ~RBTree();

 private:
  static RBTNode<T> *get_parent(RBTNode<T> *root);
  static void set_parent(RBTNode<T> *root, RBTNode<T> *parent);
  static RBTNode<T> *get_left_child(RBTNode<T> *root);
  static void set_left_child(RBTNode<T> *root, RBTNode<T> *child);
  static RBTNode<T> *get_right_child(RBTNode<T> *root);
  static void set_right_child(RBTNode<T> *root, RBTNode<T> *child);
  static RBTColor get_color(RBTNode<T> *root);
  static void set_color(RBTNode<T> *root, RBTColor color);
  static RBTNode<T> *take_left(RBTNode<T> *root);
  static RBTNode<T> *take_right(RBTNode<T> *root);
  static RBTNode<T> *copy_tree(RBTNode<T> *root);
  static void left_rotate(RBTNode<T> *root);
  static void right_rotate(RBTNode<T> *root);
  static RBTNode<T> *get_tree_min(RBTNode<T> *root);
  static RBTNode<T> *get_tree_max(RBTNode<T> *root);
  static bool is_equal(const T &value_1, const T &value_2);
  static RBTNode<T> *get_next(RBTNode<T> *node);
  static RBTNode<T> *get_prev(RBTNode<T> *node);

  void insert(RBTNode<T> *node);
  void insert_fixup(RBTNode<T> *node);
  void transplant(RBTNode<T> *node_1, RBTNode<T> *node_2);
  void erase(RBTNode<T> *node);
  void erase_fixup(RBTNode<T> *node);
  RBTNode<T> *Find(const T &value) const;
};

#include "RBTIterator.inc"
#include "RBTree.inc"

#endif  // RBTREE_INCLUDE_RBTREE_H_
