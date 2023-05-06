#ifndef RBTREE_INCLUDE_RBTITERATOR_INC_
#define RBTREE_INCLUDE_RBTITERATOR_INC_

template <class T>
class RBTree<T>::iterator {
  friend class RBTree;

 private:
  RBTNode<T> *node_ = nullptr;
  RBTNode<T> *m_root = nullptr;
  bool m_is_end = false;

 protected:
  iterator(bool is_end, RBTNode<T> *root) : m_root(root), m_is_end(is_end) {}
  iterator(RBTNode<T> *node, RBTNode<T> *root)
      : node_(node), m_root(root), m_is_end(false) {}

 public:
  iterator() = default;
  iterator(const iterator &other) = default;
  iterator &operator=(const iterator &other) = default;

  iterator operator++() {
    auto next = get_next(node_);
    node_ = next;
    if (next == nullptr) {
      m_is_end = true;
    }
    return *this;
  }

  iterator operator++(int) {
    auto state = *this;
    auto next = get_next(node_);
    node_ = next;
    if (next == nullptr) {
      m_is_end = true;
    }
    return state;
  }

  iterator operator--() {
    if (m_is_end) {
      node_ = get_tree_max(m_root);
      m_is_end = false;
    } else {
      node_ = get_prev(node_);
    }
    return *this;
  }

  iterator operator--(int) {
    auto state = *this;
    if (m_is_end) {
      node_ = get_tree_max(m_root);
      m_is_end = false;
    } else {
      node_ = get_prev(node_);
    }
    return state;
  }

  const T *operator->() const { return &node_->get_value(); }

  const T &operator*() const { return node_->get_value(); }

  bool operator==(const iterator &other) const {
    return other.m_root == m_root && other.node_ == node_ &&
           other.m_is_end == m_is_end;
  }

  bool operator!=(const iterator &other) const { return !(other == *this); }
};

#endif  // RBTREE_INCLUDE_RBTITERATOR_INC_
