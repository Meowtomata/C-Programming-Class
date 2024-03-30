
#include <stdlib.h>  // Needed to get the NULL constant  
#include <stdio.h>   // Needed for printf function
#include <string.h>  // Needed to get strcmp function 
#include <stdbool.h> // Needed for bool data type
#include <math.h>

// Node of a linked list that stores (x, y) location of points.
// DO NOT MODIFY this struct!
typedef struct node
{
   double x;             // x-coordinate of this point in the tour 
   double y;             // y-coordinate of this point in the tour
   char* name;           // null terminated string storing the name of the tour location  
   struct node* next;    // Pointer to the next node in the linked list 
} Node;

// Stores information about a linked list.
// DO NOT MODIFY this struct!
typedef struct list
{
   Node* first;          // Pointer to the first node, NULL if empty linked list
   int size;             // Number of nodes in the linked list 
} List;

// Function prototypes. These allow functions to be implemented in any 
// order later in the file. DO NOT MODIFY!   
void printNode(const Node* node);
void printTour(const List* tour);
double distance(const Node* a, const Node* b);
double tourDistance(const List* tour);
void addNearestNeighbor(List* tour, double x, double y, const char* name);
void addSmallestIncrease(List* tour, double x, double y, const char* name);  
void freeTour(List* tour);

// Replace the body of all the functions in this file.
// Add a comment above each function describing in your own words what the function does.
// DO NOT MODIFY the function signatures!

void printNode(const Node* node)
{
   printf("%.4f %.4f \"%s\"\n", node->x, node->y, node->name);
}

void printTour(const List* tour)
{
   Node* currentNode = tour->first;

   printNode(currentNode);
   currentNode = currentNode->next;

   while (currentNode != tour->first)
   {
      printNode(currentNode);
      currentNode = currentNode->next;
   }
}

double distance(const Node* a, const Node* b)
{
   if (a && b)
      return sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2));
   
   return -1;
}

double tourDistance(const List* tour)
{
   Node* a = tour->first;
   Node* b = tour->first->next;
   double distanceValue = 0;

   // (first, next) + (next, first)
   while (b != NULL && a != NULL && b != tour->first)
   {

      distanceValue += distance(a,b);
      a = a->next;
      b = b->next;
   }
   
   distanceValue += distance(a, b);
   
   return distanceValue;
}

void addNearestNeighbor(List* tour, double x, double y, const char* name)
{
   char* nodeName = malloc((strlen(name) + 1)*sizeof(char));
   strcpy(nodeName, name);

   if (nodeName == NULL)
   {
      printf("What\n");
      return;
   }

   // MALLOC SAVED THIS HOLY FUCK
   Node* newNode = malloc(sizeof(Node));
   newNode->x = x;
   newNode->y = y;
   newNode->name = nodeName;
   newNode->next = NULL;


   tour->size++;
   // if the first Node is NULL, make the new Node first
   if (tour->first == NULL)
   {
      // set the newNode to start of tour
      tour->first = newNode;
      // make the linked list circular
      tour->first->next = tour->first;

      return;
   }
   
   
   Node* currentNode = tour->first;
   Node* smallestNode = currentNode;
   
   double smallestDistance = __DBL_MAX__;
   currentNode = currentNode->next;
  
   while (currentNode != tour->first)
   {
      if (distance(currentNode, newNode) < smallestDistance)
      {
         smallestDistance = distance(currentNode, newNode);
         smallestNode = currentNode;
      }
      currentNode = currentNode->next;
   }

   Node* nextNode = smallestNode->next;

   smallestNode->next = newNode;
   newNode->next = nextNode;
   
}

void addSmallestIncrease(List* tour, double x, double y, const char* name)
{
   printf("This ran6\n");
}

void freeTour(List* tour)
{
}

// main function, DO NOT MODIFY!
int main(int argc, char** argv)
{
   if (argc < 2)
   {
      printf("Usage: TSP <command>\n");
      printf("  test0    - Test on empty list\n");
      printf("  test1    - Test on list with one node\n");
      printf("  test2    - Test on list with two nodes\n");
      printf("  nearest  - Create tour using nearest neighbor heuristic, reads from standard input\n");
      printf("  smallest - Create tour using smallest increase heuristic, reads from standard input\n");
      return 0;
   }

   const char* cmd = argv[1];

   // All commands start with an empty tour
   List tour;
   tour.first = NULL;
   tour.size = 0;

   if (strcmp(cmd, "test0") == 0)
   {
      printf("printTour\n"); 
      printTour(&tour);

      printf("tourDistance\n");
      printf("%.4f\n", tourDistance(&tour)); 

      printf("freeTour\n");
      freeTour(&tour);
      printf("tour: first %p, size %d\n", (void *) tour.first, tour.size);
   }
   else if (strcmp(cmd, "test1") == 0)
   {
         // Create a circular linked list with a single node
         Node* first = malloc(sizeof(Node));
         first->x = 1.1;
         first->y = 3.33333333;
         first->name = malloc(2);   
         first->name[0] = 'A';
         first->name[1] = '\0';
         first->next = first;

         tour.first = first;
         tour.size = 1;
         
         printf("printNode\n");
         printNode(tour.first);           
         
         printf("printTour\n");
         printTour(&tour);
         
         printf("tourDistance\n");
         printf("%.4f\n", tourDistance(&tour));
         
         printf("distance(first, first)\n");
         printf("%.4f\n", distance(tour.first, tour.first));
         
         printf("freeTour\n");
         freeTour(&tour);
         printf("tour: first %p, size %d\n", (void *) tour.first, tour.size);

         first = NULL;
   }
   else if (strcmp(cmd, "test2") == 0)
   {
      // Create a circular linked list with two nodes  
      Node* first = malloc(sizeof(Node));
      first->x = 2.2;
      first->y = 3.33333;
      first->name = malloc(2); 
      first->name[0] = 'A';
      first->name[1] = '\0';

      Node* second = malloc(sizeof(Node)); 
      second->x = 4.4;  
      second->y = 7.77777;
      second->name = malloc(2);
      second->name[0] = 'B';
      second->name[1] = '\0';

      first->next = second;   
      second->next = first;  

      tour.first = first;
      tour.size = 2;
      
      printf("printNode first\n");
      printNode(first);

      printf("printNode second\n");
      printNode(second);
      
      printf("printTour\n");
      printTour(&tour);
            
      printf("tourDistance\n");
      printf("%.4f\n", tourDistance(&tour));
      
      printf("distance(first, second)\n");
      printf("%.4f\n", distance(first, second));
      
      printf("freeTour\n");
      freeTour(&tour);
      printf("tour: first %p, size %d\n", (void *) tour.first, tour.size);

      first = NULL;
      second = NULL;   
   }
   else if ((strcmp(cmd, "nearest") == 0) || (strcmp(cmd, "smallest") == 0))
   {
      // Set a bool for use in the main read loop
      bool nearest = (strcmp(cmd, "nearest") == 0);

      // Variables for reading in the next point from standard input
      double x = 0.0;
      double y = 0.0;

      // We'll assume location names are never more than 99 characters
      char name[100];

      // Read in points until we run out of data
      while (scanf("%lf %lf %99s", &x, &y, name) == 3)
      {
         if (nearest)
         {
            addNearestNeighbor(&tour, x, y, name);  
         }
         else
         {
            addSmallestIncrease(&tour, x, y, name);     
         }
      }

      printf("%d\n", tour.size);
      printf("%.4f\n", tourDistance(&tour));
      printTour(&tour);
 
      freeTour(&tour);
   }
   else
   {
      printf("ERROR: unknown command '%s'\n", cmd);
      return 0;
   }
   printf("%s done\n", cmd);  

}
