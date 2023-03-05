#ifndef S21_CONTAINERS_SRC_S21_LIST_H_
#define S21_CONTAINERS_SRC_S21_LIST_H_

namespace s21 {
template <typename Type> class list {
private:
  struct Node;
  struct ListIterator;
  struct ListIteratorConst;

public:
  using value_type = Type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = ListIterator;
  using const_iterator = ListIteratorConst;
  using size_type = size_t;
  using node_type = Node;

  list() : front_(nullptr), back_(nullptr), size_list_(0) { add_fake_node(); };

  list(size_type size_list) : front_(nullptr), back_(nullptr), size_list_(0U) {
    add_fake_node();
    while (size_list > 0) {
      push_back(0);
      --size_list;
    }
  }

  list(std::initializer_list<value_type> const &items)
      : front_(nullptr), back_(nullptr), size_list_(0) {
    add_fake_node();
    for (auto it = items.begin(); it != items.end(); it++) {
      push_back(*it);
    }
  }

  list(const list &other_List)
      : front_(nullptr), back_(nullptr), size_list_(0) {
    add_fake_node();
    for (iterator it = other_List.front_; it != other_List.back_; ++it) {
      push_back(*it);
    }
  }

  list(list &&other_List) { moving(other_List); }

  ~list() {
    clear();
    delete_fake_node();
  }

  list &operator=(const list &other_List) noexcept {
    clear();
    for (iterator it = other_List.front_; it != other_List.back_; ++it) {
      push_back(*it);
    }
    return *this;
  }

  list &operator=(list &&other_List) noexcept {
    if (this != &other_List) {
      clear();
      delete_fake_node();
      moving(other_List);
    }
    return *this;
  }

  const_reference front() const noexcept { return front_->value; }

  const_reference back() const noexcept { return back_->prev->value; }

  iterator begin() noexcept { return front_; };
  const_iterator begin() const noexcept { return front_; };

  iterator end() noexcept { return back_; }
  const_iterator end() const noexcept { return back_; }

  bool empty() const noexcept { return size_list_ == 0; }

  size_type size() const noexcept { return size_list_; }

  size_type max_size() const noexcept {
    return ((std::numeric_limits<size_type>::max() / 2) / sizeof(Node));
  }

  void clear() noexcept {
    while (size_list_ > 0) {
      pop_back();
    }
  }

  iterator insert(iterator pos, const_reference value) noexcept {
    Node *node = new Node(value);
    node->next = pos.node_pointer_;
    if (pos != begin()) {
      pos.node_pointer_->prev->next = node;
      node->prev = pos.node_pointer_->prev;
    } else {
      front_ = node;
      node->prev = back_;
      back_->next = node;
    }
    pos.node_pointer_->prev = node;
    size_list_++;
    return node;
  }

  void erase(iterator pos) noexcept {
    if (pos.node_pointer_ != back_) {
      if (pos != begin() && size_list_ > 1) {
        pos.node_pointer_->prev->next = pos.node_pointer_->next;
        pos.node_pointer_->next->prev = pos.node_pointer_->prev;
        delete pos.node_pointer_;
      } else {
        pos.node_pointer_->next->prev = back_;
        front_ = pos.node_pointer_->next;
        delete pos.node_pointer_;
      }
      size_list_--;
    }
  }

  void push_back(const_reference value) noexcept { insert(back_, value); }

  void pop_back() noexcept {
    iterator it = back_;
    --it;
    erase(it);
  }

  void push_front(const_reference value) noexcept { insert(front_, value); }

  void pop_front() noexcept { erase(front_); }

  void swap(list &other) noexcept {
    std::swap(front_, other.front_);
    std::swap(back_, other.back_);
    std::swap(size_list_, other.size_list_);
  }

  void reverse() noexcept {
    iterator prev_it_back = back_->prev;
    for (iterator it_front = front_, it_back = back_->prev;
         it_front != it_back && it_front != prev_it_back;
         ++it_front, --it_back) {
      std::swap(it_front.node_pointer_->value, it_back.node_pointer_->value);
      prev_it_back = it_back;
    }
  }

  void unique() noexcept {
    for (iterator it = front_; it != back_; ++it) {
      bool flag = true;
      while (flag) {
        iterator tmp = it;
        ++tmp;
        if (*it == *tmp) {
          erase(tmp);
        } else {
          flag = false;
        };
      }
    }
  }

  void sort() noexcept {
    for (iterator it = front_; it != back_; ++it) {
      iterator tmp = it;
      for (iterator check_it = it; check_it != back_; ++check_it) {
        // std::cout << *check_it << " < " << *it << "\n";
        if (*check_it < *tmp) {
          std::swap(*check_it, *it);
          tmp = check_it;
        }
      }
    }
  }

  void merge(list &other) noexcept {
    iterator it = front_;
    while (it != back_ && *it < other.front()) {
      ++it;
    }
    splice(it, other);
  }

  void splice(const_iterator pos, list &other) noexcept {
    iterator it_pos = const_cast<node_type *>(pos.node_pointer_);
    if (it_pos != begin()) {
      it_pos.node_pointer_->prev->next = other.front_;
      other.front_->prev = it_pos.node_pointer_->prev;
    } else {
      front_ = other.front_;
    }
    other.back_->prev->next = it_pos.node_pointer_;
    it_pos.node_pointer_->prev = other.back_->prev;
    size_list_ += other.size_list_;
    other.size_list_ = 0;
    other.back_->prev = nullptr;
    other.front_ = other.back_;
  }

  template <class... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    iterator it_current{const_cast<node_type *>(pos.node_pointer_)};
    for (auto value : {std::forward<Args>(args)...}) {
      it_current = insert(it_current, std::move(value));
      ++it_current;
    }
    return --it_current;
  }

  template <class... Args> void emplace_back(Args &&...args) {
    for (auto value : {std::forward<Args>(args)...}) {
      push_back(std::move(value));
    }
  }

  template <class... Args> void emplace_front(Args &&...args) {
    iterator it_current = begin();
    for (auto value : {std::forward<Args>(args)...}) {
      it_current = insert(it_current, std::move(value));
      ++it_current;
    }
  }

private:
  struct Node {
    value_type value;
    Node *prev;
    Node *next;
    Node(const_reference value) : value(value), prev(nullptr), next(nullptr){};
    Node(const_reference value, Node *ptr_prev, Node *ptr_next)
        : value(value), prev(ptr_prev), next(ptr_next){};
  };

  struct ListIterator {
    ListIterator() = delete;
    ListIterator(Node *node_pointer) : node_pointer_(node_pointer){};
    ListIterator(const ListIterator &other_list_iterator)
        : node_pointer_(other_list_iterator.node_pointer_){};
    ListIterator(ListIterator &&other_list_iterator) noexcept {
      node_pointer_ = other_list_iterator.node_pointer_;
      other_list_iterator.node_pointer_ = nullptr;
    };
    ~ListIterator() noexcept { node_pointer_ = nullptr; };

    iterator operator=(const ListIterator &other) noexcept {
      node_pointer_ = other.node_pointer_;
      return *this;
    };

    iterator operator=(ListIterator &&other) noexcept {
      node_pointer_ = other.node_pointer_;
      other.node_pointer_ = nullptr;
      return *this;
    };

    bool operator!=(const ListIterator &other) noexcept {
      return node_pointer_ != other.node_pointer_;
    };

    bool operator==(const ListIterator &other) noexcept {
      return node_pointer_ == other.node_pointer_;
    };

    iterator &operator++() noexcept {
      node_pointer_ = node_pointer_->next;
      return *this;
    }
    iterator operator++(int) noexcept {
      node_pointer_ = node_pointer_->next;
      return *this;
    }
    iterator operator--(int) noexcept {
      node_pointer_ = node_pointer_->prev;
      return *this;
    }
    iterator &operator--() noexcept {
      node_pointer_ = node_pointer_->prev;
      return *this;
    }
    reference operator*() noexcept { return node_pointer_->value; }

    Node *node_pointer_;
  };

  struct ListIteratorConst {
    ListIteratorConst() = delete;
    ListIteratorConst(Node *node_pointer) : node_pointer_(node_pointer){};
    ListIteratorConst(ListIteratorConst &other_list_iterator)
        : node_pointer_(other_list_iterator.node_pointer_){};
    ListIteratorConst(ListIteratorConst &&other_list_iterator) noexcept {
      node_pointer_ = other_list_iterator.node_pointer_;
      other_list_iterator.node_pointer_ = nullptr;
    };
    ListIteratorConst(const iterator &it) : node_pointer_(it.node_pointer_){};
    ~ListIteratorConst() noexcept { node_pointer_ = nullptr; };

    const_iterator operator=(ListIteratorConst const &node_pointer) noexcept {
      node_pointer_ = node_pointer.node_pointer_;
      return *this;
    };

    const_iterator operator=(ListIteratorConst &&node_pointer) noexcept {
      node_pointer_ = node_pointer.node_pointer_;
      node_pointer.node_pointer_ = nullptr;
      return *this;
    };

    const_iterator operator++(int) noexcept {
      node_pointer_ = node_pointer_->next;
      return *this;
    }

    const_iterator &operator++() noexcept {
      node_pointer_ = node_pointer_->next;
      return *this;
    }
    const_iterator operator--(int) noexcept {
      node_pointer_ = node_pointer_->prev;
      return *this;
    }
    const_iterator &operator--() noexcept {
      node_pointer_ = node_pointer_->prev;
      return *this;
    }
    const_reference operator*() noexcept { return node_pointer_->value; }

    bool operator==(const_iterator node_pointer) const {
      return node_pointer_ == node_pointer.node_pointer_;
    }

    bool operator!=(const_iterator node_pointer) const {
      return node_pointer_ != node_pointer.node_pointer_;
    }

    const Node *node_pointer_;
  };

  void moving(list &other_List) {
    front_ = other_List.front_;
    back_ = other_List.back_;
    size_list_ = other_List.size_list_;
    other_List.front_ = nullptr;
    other_List.back_ = nullptr;
    other_List.size_list_ = 0;
  }

  void output() {
    for (auto it = begin(); it != end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << "\n";
  }

  void add_fake_node() {
    Node *node = new Node(value_type{}, nullptr, nullptr);
    back_ = node;
    front_ = node;
  }

  void delete_fake_node() { delete back_; }

  Node *front_;
  Node *back_;
  size_t size_list_;
};

} // namespace s21

#endif // S21_CONTAINERS_SRC_S21_LIST_H_
