#include "scores.h"

#define MAX_CHAR 1000
#define TONS_OF_HIGH_SCORES 100000
#define NUM_SCORES_TO_DISPLAY 10

uint32_t num_scores = 0;

// Insertion sort function to sort all the scores
// @param scores - array of scores from the file to sort
// @return - returns a new array of scores (sorted)
score_t* scores_insertion_sort(score_t scores[]) 
{
    uint32_t j;

    for (uint32_t i = 1; i < num_scores; i++) 
    {
        j = i;

        while (j > 0 && scores[j].value > scores[j-1].value) 
        {
            score_t temp = scores[j];
            scores[j] = scores[j-1];
            scores[j - 1] = temp;
            j--;
        }
    }
    return scores;
}

// This function gets only the top ten scores to display on the screen
// @param top_ten - array of the top ten scores after the sort
void scores_get_top_10_scores(score_t top_ten[]) 
{
    score_t high_scores[TONS_OF_HIGH_SCORES];
    FILE *ptr_file;
    char buf[MAX_CHAR];

    ptr_file = fopen("../scores/high_scores.txt", "r");
    if (!ptr_file)
        return;
    
    while (fgets(buf, MAX_CHAR, ptr_file) != NULL)
    {
        score_t newScore = 
        {
            .name = {buf[GLOBALS_LETTER_0_SCORE], buf[GLOBALS_LETTER_1_SCORE], buf[GLOBALS_LETTER_2_SCORE]},
            .value_char = {buf[GLOBALS_VALUE_CHAR_0], buf[GLOBALS_VALUE_CHAR_1], buf[GLOBALS_VALUE_CHAR_2], buf[GLOBALS_VALUE_CHAR_3], buf[GLOBALS_VALUE_CHAR_4]}
        };

        if (!(newScore.name[GLOBALS_LETTER_0_SCORE] < 'A' || newScore.name[GLOBALS_LETTER_1_SCORE] < 'A' || newScore.name[GLOBALS_LETTER_2_SCORE] < 'A'))
        {
            printf("%s\n\r", buf);
            sscanf(newScore.value_char, "%d", &newScore.value);
            high_scores[num_scores] = newScore;
            num_scores++;
        }
    }

    fclose(ptr_file);
    scores_insertion_sort(high_scores);

    for (uint8_t i = 0; i < NUM_SCORES_TO_DISPLAY; i++) 
    {
        top_ten[i] = high_scores[i];
    }
}

// This function writes the scores to the text file
// @param new_score - the new score to append to the text file
void scores_write_new_score(score_t new_score) 
{   
    FILE *out = fopen("../scores/high_scores.txt", "a");
    fprintf(out, "%s %05d\n\r", new_score.name, new_score.value);
    fclose(out);
}