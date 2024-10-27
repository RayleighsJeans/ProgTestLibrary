#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CAPACITY 50000 // Size of the HashTable.


// Defines the table item.
template <typename Key, typename Value>
struct HashTableItem
{
  Key* key;
  Value* value;
};


unsigned long hash_function(char* str)
{
  unsigned long i = 0;

  for (int j = 0; str[j]; j++)
    i += str[j];

  return i % CAPACITY;
}


template <typename K, typename V>
struct LinkedList
{
 public:
  HashTableItem<K, V>* item;
  LinkedList* next;
};


template <typename K, typename V>
struct DoubleLinkedList
{
 public:
  HashTableItem<K, V>* item;
  LinkedList<K, V>* next;
  LinkedList<K, V>* previous;
};


namespace hash_tables
{
template <typename Key, typename Value>
class HashedTable
{
 private:
  // Defines the table.
  struct Table
  {
    // Contains an array of pointers to items.
    HashTableItem<Key, Value>** items;
    LinkedList<Key, Value>** overflow_buckets;
    int size;
    int count;
  };


 private:
  Table* m_table;


 private:
  void free_table(Table* table)
  {
    // Frees the table.
    for (int i = 0; i < table->size; i++) {
      HashTableItem<Key, Value>* item = table->items[i];

      if (item != NULL)
        free_item(item);
    }

    // Free the overflow bucket lists and its items.
    // free_overflow_buckets(table);
    free(table->items);
    free(table);
  };


  void free_item(HashTableItem<Key, Value>* item)
  {
    // Frees an item.
    free(item->key);
    free(item->value);
    free(item);
  };


  HashTableItem<Key, Value>* create_item(Key* key, Value* value)
  {
    // Creates a pointer to a new HashTable item.
    HashTableItem<Key, Value>* item =
      (HashTableItem<Key, Value>*)malloc(sizeof(HashTableItem<Key, Value>));
    item->key = (Key*)malloc(strlen(key) + 1);
    item->value = (Value*)malloc(strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item;
  };


  LinkedList<Key, Value>* allocate_list()
  {
    // Allocates memory for a LinkedList pointer.
    LinkedList<Key, Value>* list =
      (LinkedList<Key, Value>*)malloc(sizeof(LinkedList<Key, Value>));
    return list;
  }


  LinkedList<Key, Value>* linkedlist_insert(LinkedList<Key, Value>* list,
                                            HashTableItem<Key, Value>* item)
  {
    // Inserts the item onto the LinkedList.
    if (!list) {
      LinkedList<Key, Value>* head = allocate_list();
      head->item = item;
      head->next = NULL;
      list = head;
      return list;
    }
    else if (list->next == NULL) {
      LinkedList<Key, Value>* node = allocate_list();
      node->item = item;
      node->next = NULL;
      list->next = node;
      return list;
    }

    LinkedList<Key, Value>* temp = list;
    while (temp->next->next) {
      temp = temp->next;
    }

    LinkedList<Key, Value>* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
  }


  HashTableItem<Key, Value>* linkedlist_remove(LinkedList<Key, Value>* list)
  {
    // Removes the head from the LinkedList.
    // Returns the item of the popped element.
    if (!list)
      return NULL;
    if (!list->next)
      return NULL;

    LinkedList<Key, Value>* node = list->next;
    LinkedList<Key, Value>* temp = list;
    temp->next = NULL;
    list = node;
    HashTableItem<Key, Value>* it = NULL;
    memcpy(temp->item, it, sizeof(HashTableItem<Key, Value>));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
  }

  void free_linkedlist(LinkedList<Key, Value>* list)
  {
    LinkedList<Key, Value>* temp = list;

    while (list) {
      temp = list;
      list = list->next;
      free(temp->item->key);
      free(temp->item->value);
      free(temp->item);
      free(temp);
    }
  }


  LinkedList<Key, Value>** create_overflow_buckets()
  {
    // Create the overflow buckets; an array of LinkedLists.
    LinkedList<Key, Value>** buckets = (LinkedList<Key, Value>**)calloc(
      m_table->size, sizeof(LinkedList<Key, Value>*));

    for (int i = 0; i < m_table->size; i++)
      buckets[i] = NULL;
    return buckets;
  }

  void free_overflow_buckets()
  {
    // Free all the overflow bucket lists.
    LinkedList<Key, Value>** buckets = m_table->overflow_buckets;

    for (int i = 0; i < m_table->size; i++)
      free_linkedlist(buckets[i]);
    free(buckets);
  }


 public:
  HashedTable(int size)
  {
    // Creates a new HashTable.
    m_table = (Table*)malloc(sizeof(Table));
    m_table->size = size;
    m_table->count = 0;
    m_table->items = (HashTableItem<Key, Value>**)calloc(
      m_table->size, sizeof(HashTableItem<Key, Value>*));

    for (int i = 0; i < m_table->size; i++)
      m_table->items[i] = NULL;

    m_table->overflow_buckets = create_overflow_buckets();
  };

  ~HashedTable() { free_table(m_table); };


 public:
  void insert(Key* key, Value* value)
  {
    // Creates the item.
    HashTableItem<Key, Value>* item = create_item(key, value);

    // Computes the index.
    int index = hash_function(key);

    HashTableItem<Key, Value>* current_item = m_table->items[index];

    if (current_item == NULL) {
      // Key does not exist.
      if (m_table->count == m_table->size) {
        // HashTable is full.
        printf("Insert Error: Hash Table is full\n");
        free_item(item);
        return;
      }

      // Insert directly.
      m_table->items[index] = item;
      m_table->count++;
    }
    else {
      // Scenario 1: Update the value.
      if (strcmp(current_item->key, key) == 0) {
        strcpy(m_table->items[index]->value, value);
      }
      else {
        // Scenario 2: Handle the collision.
        handle_collision(index, item);
      }
    }
  }


  Value* search(Key* key)
  {
    // Searches for the key in the HashTable.
    // Returns NULL if it doesn't exist.
    int index = hash_function(key);
    HashTableItem<Key, Value>* item = m_table->items[index];
    LinkedList<Key, Value>* head = m_table->overflow_buckets[index];

    // Provide only non-NULL values.
    if (item != NULL) {
      if (strcmp(item->key, key) == 0)
        return item->value;

      if (head == NULL)
        return NULL;

      item = head->item;
      head = head->next;
    }

    return NULL;
  }


  void remove(Key* key)
  {
    // Deletes an item from the table.
    int index = hash_function(key);
    HashTableItem<Key, Value>* item = m_table->items[index];
    LinkedList<Key, Value>* head = m_table->overflow_buckets[index];

    if (item == NULL) {
      // Does not exist.
      return;
    }
    else {
      if (head == NULL && strcmp(item->key, key) == 0) {
        // Collision chain does not exist.
        // Remove the item.
        // Set table index to NULL.
        m_table->items[index] = NULL;
        free_item(item);
        m_table->count--;
        return;
      }
      else if (head != NULL) {
        // Collision chain exists.
        if (strcmp(item->key, key) == 0) {
          // Remove this item.
          // Set the head of the list as the new item.
          free_item(item);
          LinkedList<Key, Value>* node = head;
          head = head->next;
          node->next = NULL;
          m_table->items[index] =
            create_item(node->item->key, node->item->value);
          free_linkedlist(node);
          m_table->overflow_buckets[index] = head;
          return;
        }

        LinkedList<Key, Value>* curr = head;
        LinkedList<Key, Value>* prev = NULL;

        while (curr) {
          if (strcmp(curr->item->key, key) == 0) {
            if (prev == NULL) {
              // First element of the chain.
              // Remove the chain.
              free_linkedlist(head);
              m_table->overflow_buckets[index] = NULL;
              return;
            }
            else {
              // This is somewhere in the chain.
              prev->next = curr->next;
              curr->next = NULL;
              free_linkedlist(curr);
              m_table->overflow_buckets[index] = head;
              return;
            }
          }

          curr = curr->next;
          prev = curr;
        }
      }
    }
  }


  void handle_collision(unsigned long index, HashTableItem<Key, Value>* item)
  {
    LinkedList<Key, Value>* head = m_table->overflow_buckets[index];

    if (head == NULL) {
      // Creates the list.
      head = allocate_list();
      head->item = item;
      m_table->overflow_buckets[index] = head;
      return;
    }
    else {
      // Insert to the list.
      m_table->overflow_buckets[index] = linkedlist_insert(head, item);
      return;
    }
  }


  void find(Key* key)
  {
    Key* val;
    if ((val = search(key)) == NULL) {
      printf("Key:%s does not exist\n", key);
      return;
    }
    else {
      printf("Key:%s, Value:%s\n", key, val);
    }
  }

  void show()
  {
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < m_table->size; i++) {
      if (m_table->items[i]) {
        printf("Index:%d, Key:%s, Value:%s\n", i, m_table->items[i]->key,
               m_table->items[i]->value);
      }
    }
    printf("-------------------\n\n");
  }
}; // class HashedTable
} // namespace hash_tables