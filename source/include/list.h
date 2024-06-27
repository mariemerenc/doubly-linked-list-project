#ifndef _LIST_H_
#define _LIST_H_

#include <iostream> // cout, endl

#include <algorithm> // copy
#include <cassert>   // assert()
#include <cstddef>   // std::ptrdiff_t
#include <iterator>  // bidirectional_iterator_tag
#include <type_traits>

namespace sc { // linear sequence. Better name: sequence container (same as
               // STL).
/*!
 *  A class representing a biderectional iterator defined over a linked list.
 *
 *  \note
 *  This iterator only works for traversing elements inside the same list.
 *
 *  This class is incomplete and it is provided "as is".
 *
 *  \date May, 2nd 2017.
 * \author Selan R. dos Santos
 * 
 *  \modified by: Ana Carolina B. da Silva, Mariana E. Miranda 
 *  \in 2023.1
 * 
 */


 /*!
  *  \class list
  *  \brief Doubly-linked list container class.
  *  \tparam T The type of data stored in the list.
  */
template <typename T> 
class list {

private:
  /*!
   *  \struct Node
   *  \brief Represents a node in the list.
   */
  struct Node {
    T data;       //!< The data stored in the node.
    Node *next;   //!< Pointer to the next node.
    Node *prev;   //!< Pointer to the previous node.


    /*!
     * \brief Constructs a new Node object.
     * \param d The data to be stored in the node.
     * \param n Pointer to the next node.
     * \param p Pointer to the previous node.
     */
    Node(const T &d = T{}, Node *n = nullptr, Node *p = nullptr)
     : data{d}, next{n}, prev{p} { /* empty */ }

  };

public:
  /*!
   *  \class const_iterator
   *  \brief Implements a bidirectional constant iterator for the list<T> class.
   */
  class const_iterator : public std::bidirectional_iterator_tag {
   ///=== Some aliases to help writing a clearer code.
  public:
    using value_type = T;  //!< The type of the value stored in the list.
    using pointer = T *;   //!< Pointer to the value.
    using reference = T &; //!< reference to the value.
    using const_reference = const T &; //!< const reference to the value.
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

  private:
    Node *m_ptr;  //!< The raw pointer.

  public:
    //!  Standard constructor for const_iterator.
    const_iterator(Node *ptr = nullptr) : m_ptr(ptr){ }

    //!  Standard destructor for const_iterator.
    ~const_iterator() {m_ptr ==nullptr;}

    /*!
     *  Copy constructor for const_iterator.
     * \param other The const_iterator to copy from.
     */
    const_iterator(const const_iterator &other) {
      m_ptr=other.m_ptr;
    }

    /*!
     *  Assignment operator for const_iterator.
     * \param other The const_iterator to assign from.
     * \return Reference to the assigned const_iterator.
     */
    const_iterator &operator=(const const_iterator &other) {
      m_ptr = other.m_ptr;
      return *this;
    }

    /*!
     *  Dereference operator.
     * \return Reference to the value pointed by the iterator.
     */
    reference operator*() {
      return m_ptr->data;
    }

    /*!
     *  Dereference operator (const version).
     * \return Const reference to the value pointed by the iterator.
     */
    const_reference operator*() const { 
      return m_ptr->data;
    }

    /*!
     *  Pre-increment operator.
     * \return Reference to the incremented const iterator.
     */
    const_iterator & operator++() {
      assert(m_ptr->next != nullptr);
      m_ptr = m_ptr->next;
      return *this;
    }

    /*!
     *  Post-increment operator.
     * \return Copy of the iterator before increment.
     */
    const_iterator operator++(int) {
      const_iterator temp{*this};
      m_ptr = m_ptr->next;
      return temp;
    }

    /*!
     *  Pre-decrement operator.
     * \return Reference to the decremented iterator.
     */
    const_iterator & operator--() { 
      assert(m_ptr->prev != nullptr);
      m_ptr = m_ptr->prev;
      return *this;
    }

    /*!
     *  Post-decrement operator.
     * \return Reference to the decremented iterator.
     */
    const_iterator operator--(int) { 
      const_iterator temp{*this};
      m_ptr = m_ptr->prev;
      return temp;
    }
    
    /*!
     *  Equality operator.
     * \param rhs The iterator to compare with.
     * \return True if the iterators point to the same node, false otherwise.
     */
    bool operator==(const const_iterator &rhs) const { 
      return m_ptr == rhs.m_ptr;
    }

    /*!
     *  Inequality operator.
     * \param rhs The iterator to compare with.
     * \return True if the iterators point to different nodes, false otherwise.
    */
    bool operator!=(const const_iterator &rhs) const {
      return *this != rhs.m_ptr;
    }

      ///=== Additional methods for the const_iterator class. 
   
    /*!
     *  Advances the iterator by a given number of steps.
     * \param step The number of steps to advance.
     * \return Reference to the updated iterator.
     */
    const_iterator operator+=(difference_type step) {
      for (int i = 0; i < step; i++) {
        m_ptr = m_ptr->next;
      }
      return *this;
    }

    /*!
     *  Moves the iterator back by a given number of steps.
     * \param step The number of steps to move back.
     * \return Reference to the updated iterator.
    */
    const_iterator operator-=(difference_type step) { 
      for (int i = 0; i < step; i++) {
        m_ptr = m_ptr->prev;
      }
      return *this;
    }

     /*!
     *  Accesses the data pointed to by the iterator.
     * \return Pointer to the data pointed to by the iterator.
     */
    pointer operator->() const { 
      return m_ptr->data;
    }

    /*!
     *  Calculates the difference between two const_iterators.
     * \param rhs The other const_iterator to calculate the difference with.
     * \return The difference between the two const_iterators.
     */
    difference_type operator-(const const_iterator &rhs) const { 
      return m_ptr - rhs.m_ptr;
    }

    //!  Allows the list<T> class to access the m_ptr field.
    friend class list<T>;

    /*!
     *  Overloads the << operator to print the const_iterator.
     * \param os_ The output stream to write the const_iterator to.
     * \param s_ The const_iterator to be written.
     * \return The modified output stream.
     */
    friend std::ostream &operator<<(std::ostream &os_, const const_iterator &s_) {
      os_ << "[@" << s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
      return os_;
    }
  };


/*!
 * \class iterator
 * \brief Implements a bidirectional iterator for the list<T> class.
*/
  class iterator : public std::bidirectional_iterator_tag {
   ///=== Some aliases to help writing a clearer code.
  public:
    using value_type = T;  //!< The type of the value stored in the list.
    using pointer = T *;   //!< Pointer to the value.
    using reference = T &; //!< reference to the value.
    using const_reference = const T &; //!< const reference to the value.
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

  private:
    Node *m_ptr; //!< The raw pointer.

  public:
    //!  Standard constructor for iterator.
    iterator(Node *ptr = nullptr) : m_ptr(ptr) { }
    
    //!  Standard destructor for iterator.
    ~iterator() {m_ptr == nullptr;}

    /*!
     *  Copy constructor for iterator.
     *  \param other The iterator to copy from.
     */
    iterator(const iterator &other) {
      m_ptr = other.m_ptr;
    }

    /*!
     *  Assignment operator for iterator.
     *  \param other The iterator to assign from.
     *  \return Reference to the assigned iterator.
     */
    iterator &operator=(const iterator &other){
      m_ptr = other.m_ptr;
      return *this;
    }

    /*!
     *  Dereference operator.
     *  \return Reference to the value pointed by the iterator.
     */
    reference operator*() { 
      return m_ptr->data;
    }

    /*!
     *  Dereference operator (const version).
     *  \return Const reference to the value pointed by the iterator.
     */
    const_reference operator*() const { 
      return m_ptr->data;
    }

    /*!
     *  Pre-increment operator.
     *  \return Reference to the incremented iterator.
     */
    iterator operator++() { 
      assert(m_ptr->next != nullptr);
      m_ptr = m_ptr->next;
      return *this;
    }

    /*!
     *  Post-increment operator.
     *  \return Copy of the iterator before increment.
     */
    iterator operator++(int) { 
      iterator temp{*this};
      m_ptr = m_ptr->next;
      return temp;
    }

    /*!
     *  Pre-decrement operator.
     *  \return Reference to the decremented iterator.
     */
    iterator operator--() { 
      assert(m_ptr->prev != nullptr);
      m_ptr = m_ptr->prev;
      return *this;
    }

    /*!
     *  Post-decrement operator.
     *  \return Reference to the decremented iterator.
     */
    iterator operator--(int) { 
      iterator temp{*this};
      m_ptr = m_ptr->prev;
      return temp;
    }
    
    /*!
     *  Equality operator.
     *  \param rhs The iterator to compare with.
     *  \return True if the iterators point to the same node, false otherwise.
     */
    bool operator==(const iterator &rhs) const { 
      return m_ptr == rhs.m_ptr;
    }
    
    /*!
     *  Inequality operator.
     *  \param rhs The iterator to compare with.
     *  \return True if the iterators point to different nodes, false otherwise.
    */
    bool operator!=(const iterator &rhs) const { 
      return !(m_ptr == rhs.m_ptr);
    }

     ///=== Additional methods for iterating for the iterator class. 
    
    /*!
     *  Advances the iterator by a given number of steps.
     *  \param step The number of steps to advance.
     *  \return Reference to the updated iterator.
     */
    iterator operator+=(difference_type step) { 
      for (int i = 0; i < step; i++) {
        m_ptr = m_ptr->next;
      }
      return *this;
    }

    /*!
     *  Moves the iterator back by a given number of steps.
     *  \param step The number of steps to move back.
     *  \return Reference to the updated iterator.
     */
    iterator operator-=(difference_type step) { 
      for (int i = 0; i < step; i++) {
        m_ptr = m_ptr->prev;
      }
      return *this;
    }

    /*!
     *  Accesses the data pointed to by the iterator.
     *  \return Pointer to the data pointed to by the iterator.
     */
    pointer operator->() const { 
      return m_ptr->data;
    }

    /*!
     *  Calculates the difference between two const_iterators.
     *  \param rhs The other const_iterator to calculate the difference with.
     *  \return The difference between the two const_iterators.
     */
    difference_type operator-(const iterator &rhs) const { 
      return m_ptr - rhs.m_ptr;
    }

    //! \brief Allows the list<T> class to access the m_ptr field.
    friend class list<T>;

    /*!
     *  Overloads the << operator to print the iterator.
     *  \param os_ The output stream to write the terator to.
     *  \param s_ The iterator to be written.
     *  \return The modified output stream.
     */
    friend std::ostream &operator<<(std::ostream &os_, const iterator &s_) {
      os_ << "[@" << s_.m_ptr << ", val = " << s_.m_ptr->data << "]";
      return os_;
    }
  };

  //=== Private members of the class list.
private:
  size_t m_len; 
  Node *m_head; 
  Node *m_tail; 

  //=== Public members of the class list.
public:

  //=== [I] Special members 
  //! \brief Default constructor for list. Constructs an empty list.
  list() : m_len(0), m_head(nullptr), m_tail(nullptr) {
    m_head = new Node();
    m_tail = new Node();
    m_head->next = m_tail;
    m_tail->prev = m_head;
  }

  /*!
   *  Constructs a list with the specified number of elements.
   *  \param count The number of elements to initialize the list with.
   */
  list(size_t count) {
    m_len = 0;
    m_head = new Node();
    m_tail = new Node();
    m_head->next = m_tail;
    m_tail->prev = m_head;
    
    for(auto i{0}; i < count; ++i){
      Node *new_n = new Node(T());
      new_n->prev = m_tail->prev;
      new_n->next = m_tail;
      m_tail->prev->next = new_n;
      m_tail->prev = new_n;
      ++m_len; 
    }
    
  }

  /*!
   *  Constructs a list with elements from the range [first, last).
   *
   *  \tparam InputIt The type of the input iterator.
   *  \param first The beginning of the range.
   *  \param last The end of the range.
   */
  template <typename InputIt> 
  list(InputIt first, InputIt last);
  
  /*!
   *  Copy constructor. Constructs a new list by copying the elements of another list.
   *  \param clone_ The list to be copied.
   */
  list(const list &clone_);

  /*!
   *  Constructs a list with elements from an initializer list.
   *  \param ilist_ The initializer list to initialize the list with.
   */
  list(std::initializer_list<T> ilist_);

  //!  Destructor. Frees the memory occupied by the list.
  ~list();

  /*!
   *  Swaps the contents of two lists.
   *  \param other The other list to swap with.
   */
  void swap(list &other) {
    std::swap(m_len, other.m_len);
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
  }

  /*!
   *  Assignment operator. Replaces the contents of the list with a copy of another list.
   *  \param rhs The list to copy from.
   *  \return Reference to the updated list.
   */
  list &operator=(const list &rhs) { 
    if (this != &rhs) {
      list temp(rhs);
      swap(temp);
    }
    return *this;
  }

  /*!
   *  Assignment operator. Replaces the contents of the list with elements from an initializer list.
   *  \param ilist_ The initializer list to copy from.
   *  \return Reference to the updated list.
   */
  list &operator=(std::initializer_list<T> ilist_) { 
    list temp(ilist_);
    swap(temp);
    return *this;
  }



  //=== [II] ITERATORS
  /*!
   *  Returns an iterator pointing to the first element of the list.
   *  \return An iterator pointing to the first element.
   */
  iterator begin() { 
    return iterator{m_head->next};
  }

  /*!
   * Returns a const iterator pointing to the first element of the list.
   * \return A const iterator pointing to the first element.
   */
  const_iterator cbegin() const { 
    return const_iterator{m_head->next};
  }

  /*!
   *  Returns an iterator pointing to the past-the-end element of the list.
   *  \return An iterator pointing to the past-the-end element.
   */
  iterator end() {
    return iterator{m_tail};
  }

  /**
   * \brief Returns a const iterator pointing to the past-the-end element of the list.
   * \return A const iterator pointing to the past-the-end element.
   */
  const_iterator cend() const { 
    return const_iterator{m_tail};
  }



  //=== [III] Capacity/Status
   /*!
    *  Checks if the list is empty.
    *  \return True if the list is empty, false otherwise.
    */
  [[nodiscard]] bool empty() const {
    return m_len == 0;
  }

  /*!
   *  Returns the number of elements in the list.
   *  \return The number of elements in the list.
   */
  [[nodiscard]] size_t size() const { 
    return m_len;
  }


  //=== [IV] Modifiers
  //!  Removes all elements from the list.
  void clear() {
    while(!empty()){
      pop_back();
    }

    delete m_head;
    delete m_tail;

    m_head = new Node();
    m_tail = new Node();
    m_head->next = m_tail;
    m_tail->prev = m_head;

    m_len = 0;
  }

  /**
   *  Returns the value of the first element in the list.
   *  \return The value of the first element.
   *  \throw std::out_of_range if the list is empty.
   */
  T front() {
    if(empty()) { throw std::out_of_range("A lista está vazia"); }
    return T{m_head->next->data};
  }

  /**
   *  Returns the value of the first element in the list (const version).
   *  \return The value of the first element.
   *  \throw std::out_of_range if the list is empty.
   */
  T front() const {
    if(empty()) { throw std::out_of_range("A lista está vazia"); }
    return T{m_head->next->data};
  }


  /**
   *  Returns the value of the last element in the list.
   *  \return The value of the last element.
   *  \throw std::out_of_range if the list is empty.
   */
  T back() { 
    if(empty()) { throw std::out_of_range("A lista está vazia"); }
    return T{m_tail->prev->data};
  }

  /*!
   *  Returns the value of the last element in the list (const version).
   *  \return The value of the last element.
   *  \throw std::out_of_range if the list is empty.
   */
  T back() const { 
    if(empty()) { throw std::out_of_range("A lista está vazia"); }
    return T{m_tail->prev->data};
  }

  /*!
   *  Inserts a new element at the beginning of the list.
   *  \param value_ The value of the element to insert.
   */
  void push_front(const T &value_);

  /*!
   * \brief Inserts a new element at the end of the list.
   * \param value_ The value of the element to insert.
   */
  void push_back(const T &value_);

  //! \brief Removes the first element of the list.
  void pop_front();

  //! \brief Removes the last element of the list
  void pop_back();


  //=== [IV-a] MODIFIERS W/ ITERATORS

  /*!
   *  \brief Assigns new contents to the list, replacing its current contents.
   *
   *  \tparam InItr The type of the input iterator.
   *  \param first_ The beginning of the range.
   *  \param last_ The end of the range.
   */
  template <class InItr> void assign(InItr first_, InItr last_) {
    clear();
    while(first_ != last_){
      push_back(*first_);
      first_++;
    }
  }

  /*!
   *  \brief Assigns new contents to the list, replacing its current contents.
   *  \param ilist_ The initializer list to copy from.
   */
  void assign(std::initializer_list<T> ilist_) {
    clear();
    for(auto i{ilist_.begin()}; i != ilist_.end(); ++i){
      push_back(*i);
    }
  }

  /*!
   *  Inserts a new value in the list before the iterator 'it'
   *  and returns an iterator to the new node.
   *
   *  \param pos_ An iterator to the position before which we want to insert the new data.
   *  \param value_ The value we want to insert in the list. 
   *  \return An iterator to the new element in the list.
   */
  iterator insert(iterator pos_, const T &value_);

  /*!
   *  Inserts elements from the range [first, last) into the list before 'it'.
   *  and returns an iterator to the last inserted element.
   *
   *  \param InItr The type of the input iterator.
   *  \param pos_ An iterator pointing to the position before which the elements should be inserted.
   *  \param first_ The beginning of the range.
   *  \param last_ The end of the range.
   * 
   *  \return An iterator pointing to the last inserted element.
   */
  template <typename InItr>
  iterator insert(iterator pos_, InItr first_, InItr last_);

  
  /*!
    *  Inserts elements from an initializer list into the list before the specified position.
    *
    *  \param cpos_ An iterator pointing to the position before which the elements should be inserted.
    *  \param ilist_ The initializer list to insert elements from.
    *  \return An iterator pointing to the last inserted element.
    */
  iterator insert(iterator cpos_, std::initializer_list<T> ilist_);

  /*!
   *  Erases the node pointed by 'it_' and returns an iterator
   *  to the node just past the deleted node.
   * 
   *  \param it_ The node we wish to delete.
   *  \return An iterator to the node following the deleted node.
   */
  iterator erase(iterator it_);

  //!  Erase items from [start; end) and return a iterator just past the deleted node.
  iterator erase(iterator start, iterator end);
  
  /*! 
    *   Finds the first occurrence of the specified value in the list.
    *   \param value_ The value to search for.
    *   \return An iterator pointing to the first occurrence of the value, or end() if not found.
    */
    iterator find(const T &value_);
  
  /*! 
   *   Finds the first occurrence of the specified value in the list. (const version)
   *   \param value_ The value to search for.
   *   \return An iterator pointing to the first occurrence of the value, or end() if not found.
   */
  const_iterator find(const T &value_) const;
  
  
  /*!
   *  Partitions the list by rearranging its elements according to a pivot value.
   *
   *  \param start_ An iterator pointing to the beginning of the range to partition.
   *  \param end_ An iterator pointing to the end of the range to partition.
   *  \return An iterator pointing to the partition point.
   */
  iterator partition(iterator start_, iterator end_);
  

  //=== [V] UTILITY METHODS
  
  /*!
   *  Merges another list into this list, maintaining sorted order.
   *  \param other The list to merge into this list.
   */
  void merge(list &other);

  /*!
   *  Splices elements from another list into this list at the specified position.
   *  \param  pos An iterator pointing to the position in this list to insert the spliced elements.
   *  \param  other The list to splice into this list.
   */
  void splice(const_iterator pos, list &other);

  //!  Reverse the order of the elements in the list.
  void reverse();

  //!  Removes all duplicate elements from the list.
  void unique();

  //!  Sorts the list in non-descending order.
  void sort();

  /*!  Sorts the elements in the list in non-descending order with the range wich we chose
   *
   *  \param start_ An iterator pointing to the beginning of the range to sort.
   *  \param end_ An iterator pointing to the end of the range to sort.
   */
  void sort_aux(iterator start_, iterator end_);
};



//=== [VI] OPETARORS

/**
 *  Equality comparison operator. Checks if two lists are equal.
 *
 *  \tparam T The type of elements in the lists.
 *  \param l1_ The first list.
 *  \param l2_ The second
 *  \return True if the lists are equal, false otherwise.
 */
template <typename T>
inline bool operator==(const sc::list<T> &l1_, const sc::list<T> &l2_) {
  if (l1_.size() != l2_.size()) { return false; }

  auto it1{l1_.cbegin()};
  auto it2{l2_.cbegin()};
  
  for(auto i=0; i < l1_.size(); it1++, it2++, ++i) {
    if(!(*it1 == *it2) == 1){
      return false;
    }
  }
  return true;
}


/*! 
 *  Inequality comparison operator. Checks if two lists are not equal.
 *
 *  \tparam T The type of elements in the lists.
 *  \param l1_ The first list.
 *  \param l2_ The second list to compare.
 * 
 *  \return true if the lists are not equal, false otherwise.
 */
template <typename T>
inline bool operator!=(const sc::list<T> &l1_, const sc::list<T> &l2_) {
  return !(l1_ == l2_);
}
} // namespace sc
#endif 



  template <typename T>
  template <typename InputIt> 
  sc::list<T>::list(InputIt first, InputIt last){
    m_len = 0;
    m_head = new Node(T(), m_tail, nullptr);
    m_tail = new Node(T(), nullptr, m_head);
    while(first != last){
      push_back(*first);
      first++;
    }
    
  }


  template <typename T>
  sc::list<T>::list(const list &clone_){
    m_head=new Node(T(), m_tail, nullptr);
    m_tail=new Node(T(), nullptr, m_head);
    Node *runo=clone_.m_head->next;
    Node *p=m_head;
    while (runo != clone_.m_tail) {
        Node *nn=new Node(runo->data, m_tail, p);
        p->next=nn;
        m_tail->prev=nn;
        p=nn;
        runo=runo->next;
    }
    m_len=clone_.m_len;
  }

  template <typename T>
  sc::list<T>::list(std::initializer_list<T> ilist_) : list() {
    Node *p=m_head;
    auto runner=ilist_.begin();
    m_len=0;
    while(runner != ilist_.end()) {
        Node *nn=new Node(*runner, m_tail, p);
        p->next=nn;
        m_tail->prev=nn;
        p=nn;
        runner++;
        m_len++;
    }
}

  template <typename T>
  sc::list<T>::~list() {
    clear();
    delete m_head;
    delete m_tail;
  } 



  template <typename T>
  void sc::list<T>::push_front(const T &value_){
    Node *new_node = new Node(value_);
    new_node->next = m_head->next;
    new_node->prev = m_head;
    m_head->next->prev = new_node;
    m_head->next = new_node;
    m_len++;
  }

  template <typename T>
  void sc::list<T>::push_back(const T &value_){
    Node *new_node = new Node(value_, nullptr, nullptr);
    new_node->next = m_tail;
    m_tail->prev->next = new_node;
    new_node->prev = m_tail->prev;
    m_tail->prev = new_node;
    m_len++; 
  }

  template <typename T>
  void sc::list<T>::pop_front(){
    if(m_head->next != m_tail){
      Node *first = m_head->next;
      Node *new_first = first->next;
  

    m_head->next = new_first;
    new_first->prev = m_head;

    delete first;
    --m_len;
    }
  }

  template <typename T>
  void sc::list<T>::pop_back(){
    if(m_len == 0){
      throw std::out_of_range("Lista vazia");
    }

    if(m_tail->prev != m_head){
      Node *last = m_tail->prev;
      Node *new_last = last->prev;

      m_tail->prev = new_last;
      new_last->next = m_tail;

      delete last;
      --m_len;
    }
  }

  template <typename T>
  typename sc::list<T>::iterator sc::list<T>::insert(iterator pos_, const T &value_){
    if (pos_.m_ptr == m_head) {
      push_front(value_);
      return iterator{m_head->next};
    }

    if (pos_.m_ptr == m_tail) {
      push_back(value_);
      return iterator{m_tail->prev};
    }

    Node* newNode = new Node(value_, nullptr, nullptr);

    Node* prevNode = pos_.m_ptr->prev;
    Node* nextNode = pos_.m_ptr;

    newNode->prev = prevNode;
    std::cout << "prevNode: " << prevNode->data << std::endl;
    newNode->next = nextNode;
    std::cout << "nextNode: " << nextNode->data << std::endl;
    prevNode->next = newNode;
    std::cout << "prevNode->next: " << prevNode->next->data << std::endl;
    nextNode->prev = newNode;
    std::cout << "nextNode->prev: " << nextNode->prev->data << std::endl;

    ++m_len;

    return iterator{pos_};

  }

  template <typename T>
  template <typename InputIt>
  typename sc::list<T>::iterator sc::list<T>::insert(iterator pos_, InputIt first_, InputIt last_){
    Node *prevNode = pos_.m_ptr->prev;
    Node *nextNode = pos_.m_ptr;

    for (InputIt it = first_; it != last_; it++) {
      Node *newNode = new Node(*it);
      newNode->prev = prevNode;
      newNode->next = nextNode;
      prevNode->next = newNode;
      nextNode->prev = newNode;
      prevNode = newNode;
      ++m_len;
    }

    return iterator{pos_};
  }

  template <typename T>
  typename sc::list<T>::iterator sc::list<T>::insert(iterator cpos_, std::initializer_list<T> ilist_){
    return insert(cpos_, ilist_.begin(), ilist_.end());
  }

  template <typename T>
  typename sc::list<T>::iterator sc::list<T>::erase(iterator it_){
    if (it_.m_ptr == m_head || it_.m_ptr == m_tail) {
      return it_;
    }

    Node *prevNode = it_.m_ptr->prev;
    Node *nextNode = it_.m_ptr->next;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    delete it_.m_ptr;
    --m_len;

    return iterator{nextNode};
  }

  template <typename T>
  typename sc::list<T>::iterator sc::list<T>::erase(iterator start, iterator end){
    Node *prevNode = start.m_ptr->prev;
    Node *nextNode = end.m_ptr;

    while (start != end) {
      Node *aux = start.m_ptr;
      start++;
      delete aux;
      --m_len;
    }

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    return iterator{nextNode};
  }

  template <typename T>
  typename sc::list<T>::const_iterator sc::list<T>::find(const T &value_) const{
    for (auto it = begin(); it != end(); it++) {
      if (*it == value_) {
        return it;
      }
    }
    return end();
  }

  template <typename T>
  typename sc::list<T>::iterator sc::list<T>::find(const T &value_){
    for (auto it = begin(); it != end(); it++) {
      if (*it == value_) {
        return it;
      }
    }
    return end();
  }

  template <typename T>
  void sc::list<T>::merge(list &other){
    if (this == &other) {
      return;
    }

    Node *aux = m_head->next;
    Node *aux2 = other.m_head->next;

    while (aux != m_tail && aux2 != other.m_tail) {
      if (aux->data < aux2->data) {
        aux = aux->next;
      } else {
        Node *aux3 = aux2->next;
        aux2->prev = aux->prev;
        aux2->next = aux;
        aux->prev->next = aux2;
        aux->prev = aux2;
        aux2 = aux3;
        ++m_len;
      }
    }

    if (aux2 != other.m_tail) {
      aux->prev->next = aux2;
      aux2->prev = aux->prev;
      other.m_tail->prev->next = m_tail;
      m_tail->prev = other.m_tail->prev;
      m_len += other.m_len;
    }

    other.m_head->next = other.m_tail;
    other.m_tail->prev = other.m_head;
    other.m_len = 0;
  }

  template <typename T>
  void sc::list<T>::splice(const_iterator pos, list &other){
    if (this == &other) {
      return;
    }

    Node *aux = pos.m_ptr;
    Node *aux2 = other.m_head->next;

    while (aux2 != other.m_tail) {
      Node *aux3 = aux2->next;
      aux2->prev = aux->prev;
      aux2->next = aux;
      aux->prev->next = aux2;
      aux->prev = aux2;
      aux2 = aux3;
      ++m_len;
    }

    other.m_head->next = other.m_tail;
    other.m_tail->prev = other.m_head;
    other.m_len = 0;
  }

  template <typename T>
  void sc::list<T>::reverse(){
    list aux;
    for (auto it = begin(); it != end(); it++) {
      aux.push_front(*it);
    }
    clear();
    merge(aux);
  }

  template <typename T>
  void sc::list<T>::sort(){
    if (m_len <= 1) {
      return;
    }

    list left(m_len/2 - 1);
    list right(m_len/2 + 1);

    auto it = begin();
    for (int i = 0; i < m_len / 2; i++) {
      left.push_back(*it);
      it++;
    }
    for (int i = m_len / 2; i < m_len; i++) {
      right.push_back(*it);
      it++;
    }

    left.sort();
    right.sort();

    if(left.end() == right.begin()){
      left.pop_back();
    }
    right.merge(left);
    left.merge(right);
  }





  template <typename T>
  void sc::list<T>::unique(){
    auto it = begin();
    while (it != end()) {
      auto it2 = it;
      it2++;
      while (it2 != end() && *it == *it2) {
        it2 = erase(it2);
      }
      it++;
    }
  }
