#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"

struct Node
{
   char *name;
   struct Node *next;
   struct Node *data;
   int dataSize;
};

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

enum erreur_node
{
   OK = 0,                   // Tout ok
   ERR_NB_ARG_INCORRECT = 1, // Le nombre d'arguments est incorrect
   ERR_FILE_NO_EXIST = 2,    // Le fichier n'existe pas
   ERR_OVER_120_CHARS = 3,   // Le nombre de chars d'une ligne depasse 80
   ERR_ALLOCATION_STRING = 4,// L'allocation dynamique echoue
   ERR_ALLOCATION_NODE = 5   // L'allocation dynamique echoue
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
#define NBR_LIGNES_FICHIER "Le nombre de lignes dans le fichier d'entree: "
#define NBR_MOTS_SANS_DOUBLONS "Le nombre de mots sans doublons: "
#define NBR_MOTS_AVEC_DOUBLONS "Le nombre de mots avec doublons: "
#define LETTRE_PLUS_FREQUENTE "La lettre la plus frequente: "
#define NBR_CATEGORIES "Le nombre de categories: "
#define NBR_RECETTES "Le nombre de recettes: "
#define CATEGORIE_PLUS_POPOLAIRE "La categorie la plus populaire: "
#define CATEGORIE_PLUS_DE_RECETTES "La categorie qui a le plus grand nombre de recettes: "
#define RECETTE_PLUS_DE_CHARS "La recette la plus longue: "
#define MSG_ERR_ALLOCATION_DYNAMIQUE_NODE "Erreur: Probleme d'allocation dynamique avec type struct Node.\n"
#define MSG_EMPTY_LIST "La liste est vide.\n"
#define MSG_ERR_NBR_ARG_INCORRECT "Erreur: Le nombre d'arguments doit equivaloir a 2 ou a 4.\n"
#define MSG_ERR_FICHIER_INEXISTANT "Erreur: Le fichier \"%s\" n'existe pas.\n"
#define MSG_ERR_DEPASSEMENT_DE_120_CHARS "Erreur: Il y a un depassament de 120 chars sur une ligne du fichier d'entree.\n"
#define MSG_ERR_ALLOCATION_DYNAMIQUE_STRING "Erreur: Probleme d'allocation dynamique avec type char*.\n"

// Test 1
bool isInputStringLessThan120Chars(char *string)
{
   if (strlen(string) >= MAX_CHARS_PER_LINE)
   {
      fprintf(stderr, "Erreur: Nom de la categorie est trop longue.\n");
      return false;
   }

   return true;
}

void test_isInputStringLessThan120Chars()
{
   char *test = "Bonjour";

   CU_ASSERT_TRUE(isInputStringLessThan120Chars(test));
}

// Test 2
struct Node *createNewNode(char *name)
{
   struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
   
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

void test_createNewNode()
{
   char *name = "Poulet";
   struct Node *node = createNewNode(name);

   CU_ASSERT_EQUAL(node->name, "Poulet");
   CU_ASSERT(node->dataSize == 0);
   CU_ASSERT(node->next == NULL);

   free(node);
}

// Test 3
int getLength(struct Node **head_ref)
{
   int length = 0;
   struct Node *current;
   for(current = *head_ref; current != NULL; current = current->next) {
      length++;
   }
   return length;
}

void test_getLength()
{
   char *name1 = "Poulet";
   char *name2 = "Soupe";
   struct Node *node = createNewNode(name1);
   node->next = createNewNode(name2);
   
   CU_ASSERT_EQUAL(getLength(&node), 2);

   free(node);
}

// Test 4
void deleteList(struct Node** head_ref)
{
   struct Node* current = *head_ref;
   struct Node* next;
 
   while (current != NULL)
   {
      next = current->next;
      free(current);
      current = next;
   }
   
   *head_ref = NULL;
}

void test_deleteList()
{
   char *name = "Poulet";
   struct Node *node = createNewNode(name);

   deleteList(&node);
   CU_ASSERT_TRUE(node == NULL);

   free(node);
}

// Test 5
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

void test_equalsIgnoreCase()
{
   char *str1 = "Poulet";
   char *str2 = "poulet";

   CU_ASSERT_EQUAL(equalsIgnoreCase(str1, str2), 0);
}

int main()
{
   CU_initialize_registry();
   CU_pSuite suite = CU_add_suite("Suite_1", NULL, NULL);

   if (NULL == CU_add_test(suite, "test of isInputStringLessThan120Chars", test_isInputStringLessThan120Chars) ||
       NULL == CU_add_test(suite, "test of createNewNode", test_createNewNode) ||
       NULL == CU_add_test(suite, "test of getLength", test_getLength) ||
       NULL == CU_add_test(suite, "test of deleteList", test_deleteList) ||
       NULL == CU_add_test(suite, "test of equalsIgnoreCase", test_equalsIgnoreCase))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();

   return 0;
} 
