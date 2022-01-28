/**
 * Cette bibliotheque contient des constantes et des methodes implementes
 * permettant de calculer les statistiques du fichier d'entree.
 *
 * @author Fang, Xin Ran
 * @version 2021-11-14
 */

#ifndef STATS_H
#define STATS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "node.h"

#define NBR_LIGNES_FICHIER "Le nombre de lignes dans le fichier d'entree: "
#define NBR_MOTS_SANS_DOUBLONS "Le nombre de mots sans doublons: "
#define NBR_MOTS_AVEC_DOUBLONS "Le nombre de mots avec doublons: "
#define LETTRE_PLUS_FREQUENTE "La lettre la plus frequente: "
#define NBR_CATEGORIES "Le nombre de categories: "
#define NBR_RECETTES "Le nombre de recettes: "
#define CATEGORIE_PLUS_POPOLAIRE "La categorie la plus populaire: "
#define CATEGORIE_PLUS_DE_RECETTES "La categorie qui a le plus grand nombre de recettes: "
#define RECETTE_PLUS_DE_CHARS "La recette la plus longue: "

struct Stats
{
   int nbLines;
   int nbCategories;
   int nbRecipes;
   char *categoryWithMostRecipes;
   char *longestRecipeName;
   struct Node *word_counter_head;
   struct Node *letter_counter_hear;
};

void removeAllChars(char *str, char c);
void addItemToLinkedList(struct Node **head_ref, char *item);
void addWord(struct Node **head_ref, char *line);
char *getMostFrequentLetterIgnoreDuplicate(struct Node **head_ref);
char *getNodeWithMaxDataSize(struct Node *node);
int getNbUniqueNode(struct Node *node);
void saveStatsInFile(char *file_name, struct Stats stats, struct Node *word_counter_head);

void removeAllChars(char *str, char c)
{
   char *pr = str, *pw = str;
   while (*pr)
   {
      *pw = *pr++;
      pw += (*pw != c);
   }
   *pw = '\0';
}

void addItemToLinkedList(struct Node **head_ref, char *item)
{
   struct Node *position = findElement(head_ref, item);

   char *node = malloc(strlen(item) * sizeof(char));
   strncpy(node, item, strlen(item));

   if (position == NULL)
   {
      struct Node *new_node = createNewNode(node);
      sortedInsert(head_ref, new_node);
   }
   else
   {
      position->dataSize++;
   }
};

void addWord(struct Node **head_ref, char *line)
{
   char *str = malloc(120 * sizeof(char));
   strcpy(str, line);

   removeAllChars(str, '[');
   removeAllChars(str, ']');
   removeAllChars(str, '\n');
   char *word = strtok(str, " ");
   while (word != NULL)
   {
      addItemToLinkedList(head_ref, word);
      word = strtok(NULL, " ");
   }
   free(str);
};

char *getNodeWithMaxDataSize(struct Node *node)
{
   struct Node *current;
   int maxDataSize = node->dataSize;
   char *maxDataSizeCategory = node->name;

   for (current = node; current != NULL; current = current->next)
   {
      if (current->dataSize > maxDataSize)
      {
         maxDataSize = current->dataSize;
         maxDataSizeCategory = current->name;
      }
   }
   return maxDataSizeCategory;
};

int getNbUniqueNode(struct Node *node)
{
   int count = 0;
   struct Node *current;

   for (current = node; current != NULL; current = current->next)
   {
      if (current->dataSize == 0)
      {
         count++;
      }
   }
   return count;
}

char *getMostFrequentLetterIgnoreDuplicate(struct Node **head_ref)
{
   struct Node *current;
   struct Node *letter_head = NULL;

   for (current = *head_ref; current != NULL; current = current->next)
   {
      while (*current->name != '\0')
      {
         char *str = malloc(1 * sizeof(char));
         strncpy(str, current->name, 1);
         addItemToLinkedList(&letter_head, str);
         free(str);
         current->name++;
      }
   }

   char *letter = getNodeWithMaxDataSize(letter_head);
   deleteList(&letter_head);
   return letter;
}

void saveStatsInFile(char *file_name, struct Stats stats, struct Node *word_counter_head)
{
   FILE *fp = fopen(file_name, "w");
   fputs("Statistiques\n\n", fp);
   fputs(NBR_LIGNES_FICHIER, fp);

   fprintf(fp, "%d", stats.nbLines);
   fputs("\n", fp);
   fputs(NBR_MOTS_SANS_DOUBLONS, fp);
   fprintf(fp, "%d", getNbUniqueNode(word_counter_head));
   fputs("\n", fp);

   fputs(NBR_MOTS_AVEC_DOUBLONS, fp);
   fprintf(fp, "%d", getLength(&word_counter_head));
   fputs("\n", fp);

   fputs(LETTRE_PLUS_FREQUENTE, fp);
   fputs(getMostFrequentLetterIgnoreDuplicate(&word_counter_head), fp);
   fputs("\n", fp);

   fputs(NBR_CATEGORIES, fp);
   fprintf(fp, "%d", stats.nbCategories);
   fputs("\n", fp);

   fputs(NBR_RECETTES, fp);
   fprintf(fp, "%d", stats.nbLines);
   fputs("\n", fp);

   fputs(CATEGORIE_PLUS_POPOLAIRE, fp);
   fputs(stats.categoryWithMostRecipes, fp);
   fputs("\n", fp);

   fputs(CATEGORIE_PLUS_DE_RECETTES, fp);
   fputs(stats.categoryWithMostRecipes, fp);
   fputs("\n", fp);
   fputs(RECETTE_PLUS_DE_CHARS, fp);
   fputs(stats.longestRecipeName, fp);
}

#endif
