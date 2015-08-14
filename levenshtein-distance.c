/* This sequential C program implements the Levenshtein distance which is 
a string metric for measuring the difference between two sequences. Informally,
 the Levenshtein distance between two words is the minimum number 
of single-character edits (i.e. insertions, deletions or substitutions) 
required to change one word into the other.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LevenshteinDistance(char *restrict s, char *restrict t);

#define min(a,b) (((a)<(b))?(a):(b))
#define minimum(a,b,c) ((min(a,b)<(min(a,c)))? \
			min(a,b)<min(b,c)?min(a,b):min(b,c):\
			(min(a,c))<min(b,c)?min(a,c):min(b,c))

int main()
{
    char *s = "Saturday";
    char *t = "Sunday";

    int cost = LevenshteinDistance(s,t);
    printf("The minimum number of operations required to change %s into %s is %d \n", s, t, cost);

    cost = LevenshteinDistance(t,s);
    printf("The minimum number of operations required to change %s into %s is %d \n", t, s, cost);

    cost = LevenshteinDistance("Sunday", "");
    printf("The minimum number of operations required to change %s into %s is %d \n", t, "", cost);

    cost = LevenshteinDistance(s, s);
    printf("The minimum number of operations required to change %s into %s is %d (should be zero) \n", s, s, cost);

    return 1;
}


int LevenshteinDistance(char *restrict s, char *restrict t)
{
    // degenerate cases
    if (strcmp(s, t) == 0) return 0;
    if (strlen(s) == 0) return strlen(t);
    if (strlen(t) == 0) return strlen(s);
    
    // create two work vectors of integer distances
    int *v0 = malloc(((strlen(t)+1) * sizeof(int)));
    int *v1 = malloc(((strlen(t)+1) * sizeof(int)));
    
    // initialize v0 (the previous row of distances)
    // the distance is just the number of characters to delete from t
    for (int i = 0; i < strlen(t)+1; i++)
        v0[i] = i;

    for (int i = 0; i <  strlen(s); i++)
    {
        // calculate v1 (current row distances) from the previous row v0
        //   edit distance is delete (i+1) chars from s to match empty t
        v1[0] = i + 1;

        // use formula to fill in the rest of the row
        for (int j = 0; j <  strlen(t); j++)
        {
            int cost = (s[i] == t[j]) ? 0 : 1;
            v1[j + 1] = minimum(v1[j] + 1, v0[j + 1] + 1, v0[j] + cost);
        }

        // copy v1 (current row) to v0 (previous row) for next iteration
        for (int j = 0; j <  strlen(t)+1; j++)
            v0[j] = v1[j];
    }
    int distance =  v1[strlen(t)];
    free(v0);
    free(v1);
    return distance;
}
