#ifndef SRC_INCLUDE_SOURCE_RBTITERATOR_TPP_
#define SRC_INCLUDE_SOURCE_RBTITERATOR_TPP_

template <class T>
class RBTree<T>::iterator {
  friend class RBTree;

 private:
  RBTNode<T> *node_ = nullptr;
  RBTNode<T> *m_root = nullptr;
  bool is_end_ = false;

 protected:
  iterator(bool is_end, RBTNode<T> *root) : m_root(root), is_end_(is_end) {}
  iterator(RBTNode<T> *node, RBTNode<T> *root)
      : node_(node), m_root(root), is_end_(false) {}

 public:
  iterator() = default;
  iterator(const iterator &other) = default;
  iterator &operator=(const iterator &other) = default;

  iterator operator++() {
    auto next = get_next(node_);
    node_ = next;
    if (next == nullptr) {
      is_end_ = true;
    }
    return *this;
  }

  iterator operator++(int) {
    auto state = *this;
    auto next = get_next(node_);
    node_ = next;
    if (next == nullptr) {
      is_end_ = true;
    }
    return state;
  }

  iterator operator--() {
    if (is_end_) {
      node_ = get_tree_max(m_root);
      is_end_ = false;
    } else {
      node_ = get_prev(node_);
    }
    return *this;
  }

  iterator operator--(int) {
    auto state = *this;
    if (is_end_) {
      node_ = get_tree_max(m_root);
      is_end_ = false;
    } else {
      node_ = get_prev(node_);
    }
    return state;
  }

  const T *operator->() const { return &node_->get_value(); }

  const T &operator*() const { return node_->get_value(); }

  bool operator==(const iterator &other) const {
    return other.m_root == m_root && other.node_ == node_ &&
           other.is_end_ == is_end_;
  }

  bool operator!=(const iterator &other) const { return !(other == *this); }
};

#endif  // SRC_INCLUDE_SOURCE_RBTITERATOR_TPP_
