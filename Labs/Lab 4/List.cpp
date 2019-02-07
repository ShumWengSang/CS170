/*!*****************************************************************************
\file   List.cpp
\author Roland Shum
\par    email: roland.shum\@digipen.edu
\par    DigiPen Login: roland.shum
\par    Course: CS170
\par    Section: A
\par    Lab 4
\date   02/07/2019

\brief
    This file contains the implementation of the following functions for the
    singly linked-list node in lab 4.

    Functions include:

       + AddToEnd
       + AddToFront
       + Count
       + FindItem
       + FreeList
       + PrintList
       + Insert

  Hours spent on this assignment: 1

  Specific portions that gave you the most trouble:
    No debugger to tell me what went wrong with the program when it fails.

*******************************************************************************/
#include <iostream> // cout, endl
#include "List.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

namespace CS170 //! namespace CS170
{
  namespace ListLab //! namespace ListLab
  {
    namespace
    {
    /*!*************************************************************************
      \brief
        Uses new to allocate memory for a new Node and assigns the number of the
        node with the given value.

      \param value
        The number the node is to hold.

      \return
        Returns a pointer to the new node.
    ***************************************************************************/
      struct Node* MakeNode(int value)
      {
        struct Node *pNode = new Node; // Allocate memory
        pNode->number = value;         // Set number
        pNode->next = 0;               // Set next (no next yet)

        return pNode;
      }

    /*!*************************************************************************
      \brief
        Given a node and the two nodes in the linked list to place the node in
        between, places the node between the front and back nodes.

      \param value
        The node to insert into the linked list.

      \param front
        The node that will be in front of the inserted node.

      \param back
        The node that will be behind the inserted node.

    ***************************************************************************/
      void Insert_Between(Node *value, Node *front, Node *back)
      {
        value->next = back;
        front->next = value;
      }
    }

    /*!*************************************************************************
      \brief
        Given the head of a linked list, prints the entire linked list out.

      \param list
        Pointer to the head of the linked list.

    ***************************************************************************/
    void PrintList(struct Node *list)
    {
      while (list)
      {
        std::cout << list->number << "   ";
        list = list->next;
      }
      std::cout << std::endl;
    }

    /*!*************************************************************************
      \brief
        Given the head of a linked list, counts the number of nodes in said
        list.

      \param list
        Pointer to the head of the linked list.

      \return
        The number of nodes in the given linked list.

    ***************************************************************************/
    int Count(struct Node *list)
    {
      int count = 0; // Number of nodes in the list

      while (list)
      {
        count++;
        list = list->next;
      }

      return count;
    }

    /*!*************************************************************************
      \brief
        Given a linked list, adds a new node to the end of it. Will create a new
        node if passed in NULL.

      \param pList
        Pointer to the head of the linked list.

      \param value
        The value the new node will hold.

    ***************************************************************************/
    void AddToEnd(Node **pList, int value)
    {
      // If the list is NULL, create a node there.
      if (*pList == NULL)
      {
        *pList = MakeNode(value);
        return;
      }

      // Traverse to end of list.
      while((*pList)->next != NULL)
      {
        pList = &((*pList)->next);
      }

      // Now we create a node and add it to the end.
      (*pList)->next = MakeNode(value);
    }

    /*!*************************************************************************
      \brief
        Given a linked list, adds a new node to front of it and sets the head
        to that new node.

      \param pList
        Pointer to the head of the linked list.

      \param value
        The value the new node will hold.

    ***************************************************************************/
    void AddToFront(Node **pList, int value)
    {
      // Make a new node.
      Node *newNode = MakeNode(value);

      // Set this new node to the head of the linked list..
      newNode->next = *pList;

      *pList = newNode;
    }

    /*!*************************************************************************
      \brief
        Given a linked list, searches through the linked list for the given
        value and returns the first node found with that value. If no nodes are
        found with that value, returns NULL.

      \param list
        Pointer to a node that is the head of the linked list.

      \param value
        The value of the node to find.

      \return
        A pointer to the node containing the given value. Returns NULL if none
        are found.

    ***************************************************************************/
    Node *FindItem(Node *list, int value)
    {
      // Traverse to the end of list.
      while(list != NULL)
      {
        // If the currunt node is the value.
        if(value == list->number)
        {
          // Return the node.
          return list;
        }
        // Else continue looking through the list.
        list = list->next;
      }
      // We have not found it. Return NULL.
      return NULL;
    }

    /*!*************************************************************************
      \brief
        Given the head of the linked list, frees all the nodes in the linked
        list.

      \param pList
        Pointer to the head of the linked list.

    ***************************************************************************/
    void FreeList(Node *pList)
    {
      // Keep a pointer to the next node.
      Node *nextNode = pList->next;

      // Keep a pointer to the next node, free the current one.
      while(pList != NULL)
      {
        // Set the new pointer.
        nextNode = pList->next;

        // free the current one.
        delete pList;

        // Point to next in list.
        pList = nextNode;
      }
    }

    /*!*************************************************************************
      \brief
        Given a linked list, adds a new node with the given value in the
        position specified. Valid placements range from 0 to the size of the
        linked list. If the position given is invalid, the function will not
        add a new node.

        Ie. In the list of [2, 3, 5], 5 will have position 2. Adding a node at
        position 2 with value of 10 will make [2, 3, 10, 5].

      \param pList
        Pointer to the head of the linked list.

      \param value
        The value the new node will hold.

      \param position
        The index position the new node will have.

    ***************************************************************************/
    void Insert(Node **pList, int value, int position)
    {
      // Check if position is a valid value in the linked list.
      if(position > Count(*pList) || position < 0)
      {
        // There is none of that position around here.
        return;
      }

      // If we are just placing at position 0, which is head, we add to front.
      if(position == 0)
      {
        AddToFront(pList, value);

        // End function
        return;
      }
      else if(position == Count(*pList)) // Adding to back of array?
      {
        AddToEnd(pList, value);

        // End functions.
        return;
      }

      // Else we add in the middle of list.
      int traverse_count = 0 ;     // How many times do we really need to move?
      Node *curr_node = *pList;

      // Traverse the list until we the next one is where we need to insert.
      while(++traverse_count < position)
      {
        curr_node = curr_node->next;
      }

      // Now we insert between the current node and its next node.
      Insert_Between(MakeNode(value), curr_node, curr_node->next);
    }
  } // namespace ListLab
} // namespace CS170
