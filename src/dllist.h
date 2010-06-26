/// \file dllist.h
/// \author Xiangyu Hu <Xiangyu.Hu@aer.mw.tum.de>
/// \author changes by: Martin Bernreuther <Martin.Bernreuther@ipvs.uni-stuttgart.de>
/// \author changes by: Andreas Mattes
/// \brief Double linked list implementation
///
/// Declares and defines a generic double linked list template

#ifndef DLLIST_H
#define DLLIST_H

///----------------------------------------------------------------------------------------
///      Define a universal template double linked list
///		dllist.h
///----------------------------------------------------------------------------------------
template <class Ldata> class Llist; 
///-----------------------------------------------------------------------
///				a template node on the list
///-----------------------------------------------------------------------
/// \brief A template node in the linked list
///
/// This class represents a node of the generic double linked list Llist
template <class Ldata> class LlistNode {

  ///the list class which manipulates the nodes
  friend class Llist<Ldata>;

private:
  /// The data of this node
  Ldata *data;

  /// The next and the previous nodes
  LlistNode<Ldata> *next, *prev;
	
  ///constructors

  /// An empty node, used for the head node
  LlistNode()                         { data = 0; next = prev = this; }

  /// \brief Creates a new node and inserts it before n
  /// \param d The data for the new node
  /// \param n The node before which the new node is to be inserted
  LlistNode(Ldata *d, LlistNode<Ldata> *n)    { data = d; next = n;
    prev = n->prev; n->prev = this; }
};
///-----------------------------------------------------------------------
///				the template linked list
///-----------------------------------------------------------------------
/// \brief Double linked list implementation
///
/// This class implements a double linked list with generic data.
/// The next pointer of the last node points to the first node and the prev pointer of the first node point to the node itself
template <class Ldata> class Llist {
private:
  ///list length
  int len;

  ///the list head
  LlistNode<Ldata> *node;

public:
  //constructor
  /// creates a list with an empty head node (no data in the head, but the node exists)
  Llist() { node = new LlistNode<Ldata>; len = 0; }

  /// Check if the list is empty (the first node is the last)
  bool empty() const { return (node == node->next); }
	
  /// Check if the node is the last node
  bool isEnd(LlistNode<Ldata> *p) const { return (p->next == node); }
	
  /// Get the first node
  LlistNode<Ldata> *first() const { return node; }

  /// Get the next node
  LlistNode<Ldata> *next(LlistNode<Ldata> *p) const     { return p->next; }
  /// Get the previous node
  LlistNode<Ldata> *prev(LlistNode<Ldata> *p) const     { return p->prev; }
	
  /// Get the node data
  Ldata *retrieve(LlistNode<Ldata> *p) const    { return p->next->data; }
	
  ///set the particle
  void store(LlistNode<Ldata> *p, Ldata *d) const { p->next->data = d; }

  ///get the list length
  int length() const                  { return len; }

  ///insert a node with node data
  inline void insert(LlistNode<Ldata> *p, Ldata *d) { 
    len++;
    p->next = new LlistNode<Ldata>(d, p->next); 
  }

  ///delete a node
  inline void remove(LlistNode<Ldata> *p)	{ 
    LlistNode<Ldata> *t = p->next; p->next = t->next;
    t->next->prev = t->prev; delete t; len--; 
  }
  ///re-initialize to empty list
  inline void clear() {while (!empty()) remove(first());
    len = 0; }
  ///re-initialize to empty list
  //  inline void clear_data()  {while (!empty()) { delete retrieve(first()); remove(first()); }
  //    len = 0; }
	
  ///deconstructor
  inline ~Llist() { while (!empty()) remove(first());
    delete node; }

};

#endif
