/**
 * Cette bibliotheque contient des constantes et des methodes implementes
 * qui permet de faire des recherches a travers des listes chainees ou les
 * categories et les recettes recuperees a partir du fichier d'entree.
 *
 * @author Fang, Xin Ran
 * @version 2021-11-14
 */

#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "node.h"

// ---------- //
// Constantes //
// ---------- //

enum erreur
{
   OK = 0,                   // Tout ok
   ERR_NB_ARG_INCORRECT = 1, // Le nombre d'arguments est incorrect
   ERR_FILE_NO_EXIST = 2,    // Le fichier n'existe pas
   ERR_OVER_120_CHARS = 3,   // Le nombre de chars d'une ligne depasse 80
   ERR_ALLOCATION_STRING = 4 // L'allocation dynamique echoue
};

#define MAX_CHARS_PER_LINE 120
#define OPTION_S "-S"

#define USAGE "Usage: ./recherche [liste.txt] [-S] [stats.txt]\n       Si aucun argument est fourni, le programme affiche cette instruction et se termine.\n\
Recherche option:\n\
   -S [stats.txt]    Enregistrer les statistiques du fichier d'entree au fichier de sorite.\n"
#define MSG_ACCUEIL "Entrez votre critere de recherche : "
#define MSG_CATEGORIE_INEXISTANTE "Categorie inexistante.\n"
#define MSG_RECHERCHE_INVALIDE "Recherche invalide.\n" // Si rechercher trois mots
#define MSG_AUCUN_RESULTAT_TROUVE "Aucun resultat trouve.\n"

// Messages d'erreur
#define MSG_ERR_NBR_ARG_INCORRECT "Erreur: Le nombre d'arguments doit equivaloir a 2 ou a 4.\n"
#define MSG_ERR_FICHIER_INEXISTANT "Erreur: Le fichier \"%s\" n'existe pas.\n"
#define MSG_ERR_DEPASSEMENT_DE_120_CHARS "Erreur: Il y a un depassament de 120 chars sur une ligne du fichier d'entree.\n"
#define MSG_ERR_ALLOCATION_DYNAMIQUE_STRING "Erreur: Probleme d'allocation dynamique avec type char*.\n"

void validateNbArguments(int argc);
void validateFile(char *file_name);
void verifyNbCharEachLine(char *file_name);
void verifyStringAllocation(char *string);
char *getStringUntilBracket(char *string);
void addRecipeToCategory(struct Node **head_ref, char *category, char *recipe);
bool isInputStringLessThan120Chars(char *string);
void readUserInput(char input_saved[], int *nb_words_saved);
struct Node *findRecipesFromCategory(struct Node *head, char *category);
struct Node *findRecipeByKeyWord(struct Node *head_ref, char *category, char *keyWord);

void validateNbArguments(int argc)
{
   if (argc != 2 && argc != 4)
   {
      fprintf(stderr, MSG_ERR_NBR_ARG_INCORRECT);
      printf(USAGE);
      exit(ERR_NB_ARG_INCORRECT);
   }
}

void validateFile(char *file_name)
{
   FILE *fp = fopen(file_name, "r");

   if (fp == NULL)
   {
      fprintf(stderr, MSG_ERR_FICHIER_INEXISTANT, file_name);
      printf(USAGE);
      exit(ERR_FILE_NO_EXIST);
   }

   fclose(fp);
}

void verifyNbCharEachLine(char *file_name)
{
   FILE *fp = fopen(file_name, "r");
   char line[MAX_CHARS_PER_LINE + 1];

   while (fgets(line, MAX_CHARS_PER_LINE, fp) != NULL)
   {
      if (strlen(line) > MAX_CHARS_PER_LINE)
      {
         fprintf(stderr, MSG_ERR_DEPASSEMENT_DE_120_CHARS);
         printf(USAGE);
         fclose(fp);
         exit(ERR_OVER_120_CHARS);
      }
   }

   fclose(fp);
}

void verifyStringAllocation(char *str)
{
   if (str == NULL)
   {
      fprintf(stderr, MSG_ERR_ALLOCATION_DYNAMIQUE_STRING);
      exit(ERR_ALLOCATION_STRING);
   }
}

void addRecipeToCategory(struct Node **head_ref, char *category, char *recipe)
{
   struct Node *position = findElement(head_ref, category);
   struct Node *category_node;

   if (position == NULL)
   {
      struct Node *new_category_node = createNewNode(category);
      sortedInsert(head_ref, new_category_node);
      category_node = new_category_node;
   }
   else
   {
      category_node = position;
   }

   struct Node *new_recipe_node = createNewNode(recipe);
   sortedInsert(&category_node->data, new_recipe_node);
   category_node->dataSize++;
}

char *getStringUntilBracket(char *string)
{
   char *target = NULL;
   char *end = strstr(string, "]");

   if (end)
   {
      target = (char *)malloc(end - string + 1);
      verifyStringAllocation(target);
      memcpy(target, string, end - string);
      target[end - string] = '\0';
   }

   return target;
}

bool isInputStringLessThan120Chars(char *string)
{
   if (strlen(string) >= MAX_CHARS_PER_LINE)
   {
      fprintf(stderr, "Erreur: Entree invalide.\n");
      return false;
   }

   return true;
}

void readUserInput(char input_saved[], int *nb_words_saved)
{
   char input[120];
   int nb_words = 1;
   int is_input_length_correct = false;
   int result;

   while (nb_words > 2 || !is_input_length_correct)
   {
      if (nb_words > 2)
         printf(MSG_RECHERCHE_INVALIDE);

      printf(MSG_ACCUEIL);

      nb_words = 1;
      result = scanf(" %119[^\n]", input);
      int i;

      if (result > 0)
      {
         for (i = 0; input[i] != '\0'; i++)
         {
            if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
               nb_words++;
         }
      }

      if (nb_words < 3 || nb_words > 0)
         is_input_length_correct = true;
   }

   strcpy(input_saved, input);
   *nb_words_saved = nb_words;
}

struct Node *findRecipesFromCategory(struct Node *head, char *category)
{
   if (!isInputStringLessThan120Chars(category))
      return NULL;
   struct Node *category_found = findElement(&head, category);

   if (category_found == NULL)
   {
      printf(MSG_CATEGORIE_INEXISTANTE);
      return NULL;
   }

   return category_found;
}

struct Node *findRecipeByKeyWord(struct Node *head, char *category, char *keyWord)
{
   struct Node *recipes;
   recipes = findRecipesFromCategory(head, category);

   if (recipes != NULL)
   {
      while (recipes->data != NULL)
      {
         if (strstr(recipes->data->name, keyWord) != NULL)
            return recipes->data;

         recipes->data = recipes->data->next;
      }

      printf(MSG_AUCUN_RESULTAT_TROUVE);

      return NULL;
   }

   return NULL;
}

#endif
