#ifndef RBTREE_INCLUDE_RBTNODE_H_
#define RBTREE_INCLUDE_RBTNODE_H_

enum RBTColor : bool { BLACK, RED };

template <class T>
struct RBTNode {
 private:
  T value_;
  RBTNode<T> *m_parent;
  RBTNode<T> *m_left;
  RBTNode<T> *m_right;
  RBTColor m_color;

 public:
  RBTNode<T>(const T &value, RBTColor color)
      : value_(value),
        m_parent(nullptr),
        m_left(nullptr),
        m_right(nullptr),
        m_color(color) {}

  RBTNode<T>(const RBTNode<T> &other)
      : value_(other.value_),
        m_parent(nullptr),
        m_left(nullptr),
        m_right(nullptr),
        m_color(other.m_color) {}

  RBTNode<T> *get_parent() const { return m_parent; }
  void set_parent(RBTNode<T> *parent) { m_parent = parent; }
  RBTNode<T> *get_left_child() const { return m_left; }
  void set_left_child(RBTNode<T> *left) { m_left = left; }
  RBTNode<T> *get_right_child() const { return m_right; }
  void set_right_child(RBTNode<T> *right) { m_right = right; }
  RBTColor get_color() const { return m_color; }
  void set_color(RBTColor color) { m_color = color; }
  const T &get_value() const { return value_; }

  ~RBTNode<T>() {
    delete m_right;
    delete m_left;
  }
};

#endif  // RBTREE_INCLUDE_RBTNODE_H_
