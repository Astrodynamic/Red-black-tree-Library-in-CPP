#ifndef SRC_INCLUDE_SOURCE_RBTREE_TPP_
#define SRC_INCLUDE_SOURCE_RBTREE_TPP_

template <class T>
RBTNode<T> *RBTree<T>::get_parent(RBTNode<T> *root) {
  return root ? root->get_parent() : nullptr;
}

template <class T>
void RBTree<T>::set_parent(RBTNode<T> *root, RBTNode<T> *parent) {
  if (root) {
    root->set_parent(parent);
  }
}

template <class T>
RBTNode<T> *RBTree<T>::get_left_child(RBTNode<T> *root) {
  return root ? root->get_left_child() : nullptr;
}

template <class T>
void RBTree<T>::set_left_child(RBTNode<T> *root, RBTNode<T> *child) {
  if (root) {
    root->set_left_child(child);
    set_parent(get_left_child(root), root);
  }
}

template <class T>
RBTNode<T> *RBTree<T>::get_right_child(RBTNode<T> *root) {
  return root ? root->get_right_child() : nullptr;
}

template <class T>
void RBTree<T>::set_right_child(RBTNode<T> *root, RBTNode<T> *child) {
  if (root) {
    root->set_right_child(child);
    set_parent(get_right_child(root), root);
  }
}

template <class T>
RBTColor RBTree<T>::get_color(RBTNode<T> *root) {
  return root ? root->get_color() : BLACK;
}

template <class T>
void RBTree<T>::set_color(RBTNode<T> *root, RBTColor color) {
  if (root) {
    root->set_color(color);
  }
}

template <class T>
RBTNode<T> *RBTree<T>::take_left(RBTNode<T> *root) {
  RBTNode<T> *temp = nullptr;
  if (root) {
    temp = get_left_child(root);
    set_parent(temp, nullptr);
    set_left_child(root, nullptr);
  }
  return temp;
}

template <class T>
RBTNode<T> *RBTree<T>::take_right(RBTNode<T> *root) {
  RBTNode<T> *temp = nullptr;
  if (root) {
    temp = get_right_child(root);
    set_parent(temp, nullptr);
    set_right_child(root, nullptr);
  }
  return temp;
}

template <class T>
RBTNode<T> *RBTree<T>::copy_tree(RBTNode<T> *root) {
  RBTNode<T> *temp = nullptr;
  if (root) {
    temp = new RBTNode<T>(*root);
    set_left_child(temp, copy_tree(get_left_child(root)));
    set_right_child(temp, copy_tree(get_right_child(root)));
  }
  return temp;
}

template <class T>
void RBTree<T>::left_rotate(RBTNode<T> *root) {
  auto parent = get_parent(root);
  auto right = take_right(root);
  auto right_left = take_left(right);
  set_right_child(root, right_left);
  set_left_child(right, root);
  if (get_left_child(parent) == root) {
    set_left_child(parent, right);
  } else {
    set_right_child(parent, right);
  }
}

template <class T>
void RBTree<T>::right_rotate(RBTNode<T> *root) {
  auto parent = get_parent(root);
  auto left = take_left(root);
  auto left_right = take_right(left);
  set_left_child(root, left_right);
  set_right_child(left, root);
  if (get_left_child(parent) == root) {
    set_left_child(parent, left);
  } else {
    set_right_child(parent, left);
  }
}

template <class T>
void RBTree<T>::insert(RBTNode<T> *node) {
  RBTNode<T> *prev = nullptr;
  RBTNode<T> *curr = m_root;
  while (curr != nullptr) {
    prev = curr;
    if (node->get_value() < curr->get_value()) {
      curr = get_left_child(curr);
    } else {
      curr = get_right_child(curr);
    }
  }
  if (prev == nullptr) {
    m_root = node;
  } else {
    if (node->get_value() < prev->get_value()) {
      set_left_child(prev, node);
    } else {
      set_right_child(prev, node);
    }
  }
  insert_fixup(node);
}

template <class T>
void RBTree<T>::insert_fixup(RBTNode<T> *node) {
  while (get_color(get_parent(node)) == RED) {
    if (get_parent(node) == get_left_child(get_parent(get_parent(node)))) {
      auto uncle = get_right_child(get_parent(get_parent(node)));
      if (get_color(uncle) == RED) {
        set_color(get_parent(node), BLACK);
        set_color(uncle, BLACK);
        set_color(get_parent(get_parent(node)), RED);
        node = get_parent(get_parent(node));
      } else if (node == get_right_child(get_parent(node))) {
        node = get_parent(node);
        left_rotate(node);
      } else {
        set_color(get_parent(node), BLACK);
        set_color(get_parent(get_parent(node)), RED);
        right_rotate(get_parent(get_parent(node)));
      }
    } else {
      auto uncle = get_left_child(get_parent(get_parent(node)));
      if (get_color(uncle) == RED) {
        set_color(get_parent(node), BLACK);
        set_color(uncle, BLACK);
        set_color(get_parent(get_parent(node)), RED);
        node = get_parent(get_parent(node));
      } else if (node == get_left_child(get_parent(node))) {
        node = get_parent(node);
        right_rotate(node);
      } else {
        set_color(get_parent(node), BLACK);
        set_color(get_parent(get_parent(node)), RED);
        left_rotate(get_parent(get_parent(node)));
      }
    }
  }
  while (get_parent(node) != nullptr) {
    node = get_parent(node);
  }
  m_root = node;
  set_color(m_root, BLACK);
}

template <class T>
void RBTree<T>::transplant(RBTNode<T> *node_1, RBTNode<T> *node_2) {
  if (get_parent(node_1) == nullptr) {
    m_root = node_2;
    set_parent(node_2, nullptr);
  } else if (node_1 == get_left_child(get_parent(node_1))) {
    set_left_child(get_parent(node_1), node_2);
  } else {
    set_right_child(get_parent(node_1), node_2);
  }
}

template <class T>
RBTNode<T> *RBTree<T>::get_tree_min(RBTNode<T> *root) {
  while (get_left_child(root)) {
    root = get_left_child(root);
  }
  return root;
}

template <class T>
RBTNode<T> *RBTree<T>::get_tree_max(RBTNode<T> *root) {
  while (get_right_child(root)) {
    root = get_right_child(root);
  }
  return root;
}

template <class T>
void RBTree<T>::erase(RBTNode<T> *node) {
  auto next = node;
  auto color = get_color(next);
  RBTNode<T> *child = nullptr;
  if (get_left_child(node) == nullptr) {
    child = get_right_child(node);
    transplant(node, get_right_child(node));
  } else if (get_right_child(node) == nullptr) {
    child = get_left_child(node);
    transplant(node, get_left_child(node));
  } else {
    next = get_tree_min(get_right_child(node));
    color = get_color(next);
    child = get_right_child(next);
    if (get_parent(next) == node) {
      set_parent(child, next);
    } else {
      transplant(next, get_right_child(next));
      set_right_child(next, get_right_child(node));
    }
    transplant(node, next);
    set_left_child(next, get_left_child(node));
    set_color(next, get_color(node));
  }
  if (color == BLACK) {
    erase_fixup(child);
  }
}

template <class T>
void RBTree<T>::erase_fixup(RBTNode<T> *node) {
  while (get_parent(node) != nullptr && get_color(node) == BLACK) {
    if (node == get_left_child(get_parent(node))) {
      auto brother = get_right_child(get_parent(node));
      if (get_color(brother) == RED) {
        set_color(brother, BLACK);
        set_color(get_parent(node), RED);
        left_rotate(get_parent(node));
        brother = get_right_child(get_parent(node));
      }
      if (get_color(get_left_child(brother)) == BLACK &&
          get_color(get_right_child(brother)) == BLACK) {
        set_color(brother, RED);
        node = get_parent(node);
      } else if (get_color(get_right_child(brother)) == BLACK) {
        set_color(get_left_child(brother), BLACK);
        set_color(brother, RED);
        right_rotate(brother);
        brother = get_right_child(get_parent(node));
      } else {
        set_color(brother, get_color(get_parent(node)));
        set_color(get_parent(node), BLACK);
        set_color(get_right_child(brother), BLACK);
        left_rotate(get_parent(node));
        node = m_root;
      }
    } else {
      auto brother = get_left_child(get_parent(node));
      if (get_color(brother) == RED) {
        set_color(brother, BLACK);
        set_color(get_parent(node), RED);
        right_rotate(get_parent(node));
        brother = get_left_child(get_parent(node));
      }
      if (get_color(get_right_child(brother)) == BLACK &&
          get_color(get_left_child(brother)) == BLACK) {
        set_color(brother, RED);
        node = get_parent(node);
      } else if (get_color(get_left_child(brother)) == BLACK) {
        set_color(get_right_child(brother), BLACK);
        set_color(brother, RED);
        left_rotate(brother);
        brother = get_left_child(get_parent(node));
      } else {
        set_color(brother, get_color(get_parent(node)));
        set_color(get_parent(node), BLACK);
        set_color(get_left_child(brother), BLACK);
        right_rotate(get_parent(node));
        node = m_root;
      }
    }
  }
  set_color(node, BLACK);
}

template <class T>
bool RBTree<T>::is_equal(const T &value_1, const T &value_2) {
  return (value_1 == value_2);
}

template <class T>
RBTNode<T> *RBTree<T>::Find(const T &value) const {
  auto curr = m_root;
  while (curr != nullptr && !is_equal(value, curr->get_value())) {
    if (value < curr->get_value()) {
      curr = get_left_child(curr);
    } else {
      curr = get_right_child(curr);
    }
  }
  return curr;
}

template <class T>
RBTNode<T> *RBTree<T>::get_next(RBTNode<T> *node) {
  RBTNode<T> *next = get_parent(node);
  if (get_right_child(node)) {
    next = get_tree_min(get_right_child(node));
  } else {
    while (next && node == get_right_child(next)) {
      node = next;
      next = get_parent(next);
    }
  }
  return next;
}

template <class T>
RBTNode<T> *RBTree<T>::get_prev(RBTNode<T> *node) {
  RBTNode<T> *prev = get_parent(node);
  if (get_left_child(node)) {
    prev = get_tree_max(get_left_child(node));
  } else {
    while (prev && node == get_left_child(prev)) {
      node = prev;
      prev = get_parent(prev);
    }
  }
  return prev;
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::begin() const {
  iterator it_temp_1(true, m_root);
  iterator it_temp_2(m_begin, m_root);
  return empty() ? it_temp_1 : it_temp_2;
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::end() const {
  return {true, m_root};
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::find(const T &value) const {
  auto node = Find(value);
  return node ? iterator(node, m_root) : end();
}

template <class T>
size_t RBTree<T>::size() const {
  return m_size;
}

template <class T>
size_t RBTree<T>::max_size() const {
  return std::numeric_limits<size_t>::max() / sizeof(RBTree<T>) / 2;
}

template <class T>
bool RBTree<T>::empty() const {
  return m_size == 0;
}

template <class T>
bool RBTree<T>::contains(const T &value) const {
  return !empty() && find(value) != end();
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::insert(const T &value) {
  ++m_size;
  RBTNode<T> *node = new RBTNode<T>(value, RED);
  insert(node);
  m_begin = get_tree_min(m_root);
  m_end = get_tree_max(m_root);
  return {node, m_root};
}

template <class T>
void RBTree<T>::clear() noexcept {
  delete m_root;
  m_begin = nullptr;
  m_root = nullptr;
  m_end = nullptr;
  m_size = 0;
}

template <class T>
void RBTree<T>::erase(const T &value) {
  auto node = Find(value);
  if (node) {
    if (m_size == 1) {
      clear();
    } else {
      erase(node);
      set_left_child(node, nullptr);
      set_right_child(node, nullptr);
      delete node;
      m_begin = get_tree_min(m_root);
      m_end = get_tree_max(m_root);
      --m_size;
    }
  }
}

template <class T>
void RBTree<T>::erase(typename RBTree<T>::iterator pos) {
  erase(*pos);
}

template <class T>
void RBTree<T>::swap(RBTree &other) {
  std::swap(m_root, other.m_root);
  std::swap(m_begin, other.m_begin);
  std::swap(m_end, other.m_end);
  std::swap(m_size, other.m_size);
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::lower_bound(const T &value) const {
  auto it = begin();
  for (; it != end(); ++it) {
    if (*it >= value) {
      break;
    }
  }
  return it;
}

template <class T>
typename RBTree<T>::iterator RBTree<T>::upper_bound(const T &value) const {
  auto it = begin();
  for (; it != end(); ++it) {
    if (*it > value) {
      break;
    }
  }
  return it;
}

template <class T>
std::pair<typename RBTree<T>::iterator, typename RBTree<T>::iterator>
RBTree<T>::equal_range(const T &value) {
  return {lower_bound(value), upper_bound(value)};
}

template <class T>
size_t RBTree<T>::count(const T &value) {
  std::pair<iterator, iterator> pair = equal_range(value);
  size_t count = 0;
  for (auto it = pair.first; it != pair.second; ++it) {
    ++count;
  }
  return count;
}

template <class T>
void RBTree<T>::merge(RBTree &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

template <class T>
RBTree<T>::RBTree(std::initializer_list<T> const &list) {
  if (m_size != 0) {
    clear();
  }
  for (const auto &value : list) {
    insert(value);
  }
}

template <class T>
RBTree<T>::RBTree(const RBTree &other) {
  if (m_root != other.m_root) {
    if (m_size != 0) {
      clear();
    }
    if (other.m_size > 0) {
      m_root = copy_tree(other.m_root);
      m_begin = get_tree_min(m_root);
      m_end = get_tree_max(m_root);
      m_size = other.m_size;
    }
  }
}

template <class T>
RBTree<T>::RBTree(RBTree &&other) noexcept {
  if (m_root != other.m_root) {
    if (m_size != 0) {
      clear();
    }
    if (other.m_size > 0) {
      swap((other));
    }
  }
}

template <class T>
RBTree<T> &RBTree<T>::operator=(const RBTree &other) {
  if (m_root != other.m_root) {
    if (m_size != 0) {
      clear();
    }
    if (other.m_size > 0) {
      m_root = copy_tree(other.m_root);
      m_begin = get_tree_min(m_root);
      m_end = get_tree_max(m_root);
      m_size = other.m_size;
    }
  }
  return *this;
}

template <class T>
RBTree<T> &RBTree<T>::operator=(RBTree &&other) {
  if (m_root != other.m_root) {
    if (m_size != 0) {
      clear();
    }
    if (other.m_size > 0) {
      swap((other));
    }
  }
  return *this;
}

template <class T>
RBTree<T>::~RBTree() {
  if (m_size != 0) {
    clear();
  }
}
#endif  // SRC_INCLUDE_SOURCE_RBTREE_TPP_
