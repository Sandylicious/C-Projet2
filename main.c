/**
* Ce programme permet d'effectuer des recherches dans une banque de recettes
* d'un fichier et d'enregistrer une serie de statistiques dans un fichier de
* sortie. Il doit donc recevoir en paramètre un fichier ```liste.txt```
* contenant a chaque ligne le nom d'une recette suivi par le nom des categies
* qu'elle appartienne (entre crochet). Une recette peut etre retrouvee dans
* une a plusieurs categories et une categorie peut contenir plusieurs recettes.
* L'utilisateur peut rechercher soit par categorie, soit par categorie avec un
* mot-cle. Si le categorie ou le categorie avec mot-cle est trouve, le nom de
* la(des) recette(s) sera affiche, si rien n'est trouve, un message d'erreur
* sera affiche. Toute autre combinaison sera consideree invalide et sera
* rejete par l'application. D'ailleurs, il est important qu'aucune ligne du
* fichier depasse 120 caracteres et l'utilisateur peut faire autant de 
* recherches qu'il desire a chaque execution du programme. 
* 
* Pour arreter le programme, il faut taper sur ```Ctrl + C```.
*
* @author Fang, Xin Ran
* @version 2021-12-21
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "recherche.h"
#include "node.h"
#include "stats.h"

int main(int argc, char *argv[])
{
   validateNbArguments(argc);
   validateFile(argv[1]);
   verifyNbCharEachLine(argv[1]);
   printf("\n");

   FILE *fp = fopen(argv[1], "r");

   struct Node *category_head = NULL;
   char line[MAX_CHARS_PER_LINE + 1];

   //Initialize Stats
   struct Stats stats;
   stats.nbLines = 0;
   stats.longestRecipeName = "";
   struct Node *word_counter_head = NULL;

   char *str_line = malloc(MAX_CHARS_PER_LINE * sizeof(char));
   char *category;

   while (fgets(line, MAX_CHARS_PER_LINE, fp))
   {
      strncpy(str_line, line, strlen(line));
      char *categories = strchr(str_line, '[');

      // Get recipe
      int length = categories - str_line - 1;
      char *recipe = malloc(length * sizeof(char));

      verifyStringAllocation(recipe);
      strncpy(recipe, str_line, length);

      char *ptr = strtok(categories, "[");

      while (ptr != NULL)
      {
         category = getStringUntilBracket(ptr);
         addRecipeToCategory(&category_head, category, recipe);
         ptr = strtok(NULL, "[");
      }

      if (strlen(recipe) > strlen(stats.longestRecipeName))
      {
         stats.longestRecipeName = recipe;
      }
      stats.nbLines++;
      addWord(&word_counter_head, line);
   }

   fclose(fp);

   free(str_line);

   // Write stats into file
   if (argc == 4 && (strcmp(argv[2], OPTION_S) == 0))
   {
      stats.nbCategories = getLength(&category_head);
      stats.categoryWithMostRecipes = getNodeWithMaxDataSize(category_head);

      saveStatsInFile(argv[3], stats, word_counter_head);
      deleteList(&category_head);

      return 0;
   }
   else if (argc == 2)
   {
      while (argc == 2)
      {
         char input[120];
         int nb_words = 0;

         readUserInput(input, &nb_words);

         if (nb_words == 1)
         {
            char *category_copie1 = input;
            struct Node *recipes;
            recipes = findRecipesFromCategory(category_head, category_copie1);
            if (recipes != NULL)
               printSubList(recipes->data);
         }
         else if (nb_words == 2)
         {
            char *recette = strchr(input, ' ') + 1;
            int length = strlen(input) - strlen(recette) - 1;
            char *category = malloc(length * sizeof(char));
            strncpy(category, input, length);

            struct Node *data = findRecipeByKeyWord(category_head, category, recette);

            if (data != NULL)
               printf("%s\n", data->name);

            free(category);
         }
      }
   }

   deleteList(&category_head);

   return 0;
}
