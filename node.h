/**
 * Cette bibliotheque contient des constantes et des methodes implementes
 * permettant a l'utlisation de listes chaines.
 *
 * @author Fang, Xin Ran
 * @version 2021-11-14
 */

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "recherche.h"

struct Node
{
   char *name;
   struct Node *next;
   struct Node *data;
   int dataSize;
};

enum erreur_node
{
   ERR_ALLOCATION_NODE = 5 // L'allocation dynamique echoue
};

#define MSG_ERR_ALLOCATION_DYNAMIQUE_NODE "Erreur: Probleme d'allocation dynamique avec type struct Node.\n"
#define MSG_EMPTY_LIST "La liste est vide.\n"

struct Node *createNewNode(char *name);
void sortedInsert(struct Node **head_ref, struct Node *new_node);
struct Node *findElement(struct Node **head_ref, char *element);
void printList(struct Node *head);
void printSubList(struct Node *head);
void addRecipeToCategory(struct Node **head_ref, char *category, char *recipe);
void deleteNode(struct Node **head_ref, int position);
void deleteList(struct Node **head_ref);
int equalsIgnoreCase(char *str1, char *str2);
int getLength(struct Node **head_ref);

struct Node *createNewNode(char *name)
{
   struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

   if (new_node == NULL)
   {
      fprintf(stderr, MSG_ERR_ALLOCATION_DYNAMIQUE_NODE);
      exit(ERR_ALLOCATION_NODE);
   }

   new_node->name = name;
   new_node->dataSize = 0;
   new_node->next = NULL;

   return new_node;
}

int getLength(struct Node **head_ref)
{
   int length = 0;
   struct Node *current;

   for (current = *head_ref; current != NULL; current = current->next)
   {
      length++;
   }

   return length;
}

void sortedInsert(struct Node **head_ref, struct Node *new_node)
{
   struct Node *current;

   if (*head_ref == NULL || equalsIgnoreCase((*head_ref)->name, new_node->name) >= 0)
   {
      new_node->next = *head_ref;
      *head_ref = new_node;
      current = *head_ref;
   }
   else
   {
      current = *head_ref;

      while (current->next != NULL && equalsIgnoreCase(new_node->name, current->next->name) > 0)
      {
         current = current->next;
      }

      new_node->next = current->next;
      current->next = new_node;
   }
}

void deleteNode(struct Node **head_ref, int position)
{
   if (*head_ref == NULL)
      return;

   struct Node *temp = *head_ref;

   if (position == 0)
   {
      *head_ref = temp->next;
      free(temp);
      return;
   }

   for (int i = 0; temp != NULL && i < position - 1; i++)
      temp = temp->next;

   if (temp == NULL || temp->next == NULL)
      return;

   struct Node *next = temp->next->next;

   free(temp->next);

   temp->next = next;
}

void deleteList(struct Node **head_ref)
{
   struct Node *current = *head_ref;
   struct Node *next;

   while (current != NULL)
   {
      next = current->next;
      free(current);
      current = next;
   }

   *head_ref = NULL;
}

struct Node *findElement(struct Node **head_ref, char *element)
{
   struct Node *temp = *head_ref;

   while (temp != NULL)
   {
      if (equalsIgnoreCase(temp->name, element) == 0)
         return temp;

      temp = temp->next;
   }
   return NULL;
}

void printList(struct Node *head)
{
   if (head == NULL)
   {
      printf(MSG_EMPTY_LIST);
      return;
   }

   struct Node *temp = head;

   while (temp != NULL)
   {
      if (temp->data != NULL)
         printSubList(temp->data);

      temp = temp->next;
   }
}

void printSubList(struct Node *head)
{
   struct Node *temp = head;

   while (temp != NULL)
   {
      printf("%s\n", temp->name);
      temp = temp->next;
   }
}

int equalsIgnoreCase(char *str1, char *str2)
{
   while (*str1 != '\0' && tolower((unsigned char)*str1) == tolower((unsigned char)*str2))
   {
      ++str1;
      ++str2;
   }

   int diff = (tolower((unsigned char)*str1) - tolower((unsigned char)*str2));

   return diff;
}

#endif
