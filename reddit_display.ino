#include<limits.h>
#include"oled_display.h"
#include"buzzer.h"

// current data

long score = 0;

long comments = 0;

// previous data

long prev_score = 0;

long prev_comments = 0;

String title;

bool initialized = false;

void setup() {
    // put your setup code here, to run once:

    OLED.setup();

    buzzer_setup();

    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:

    // checking if any serial data is available

    if(Serial.available())
    {
        /*
            reading the serial data

            format of serial data: "{score},{comments},{title}\n
        */

        score = Serial.parseInt();   // reading integer

        comments = Serial.parseInt();   // reading integer

        Serial.read();  // extracting extra ',' after last integer

        title = Serial.readStringUntil('\n'); // reading a string till we find '\n'
        
        title.trim();   // getting rid of extra '\n' at the end

        if(initialized)
        {
            /*
                previous values are already initialized so we use them to determine
                the change in score and no. of comments
            */

            if(prev_comments < comments)
            {
                ping(); // ping when new comments are added
            }

            OLED.print_reddit_data(
                score, 
                comments,
                title.substring(0, 15) + "...",
                ((prev_score == score) ? 0 : ((prev_score < score) ? 1 : -1)),
                ((prev_comments == comments) ? 0 : ((prev_comments < comments) ? 1 : -1))
            );
        }
        else
        {
            /*
                previous values are not initialized yet as it's the first iteration
                so send 0 to indicate no change in score or no. of comments
            */

            OLED.print_reddit_data(score, comments, title.substring(0, 15) + "...");

            initialized = true; // previous values will be initialized soon
        }

        prev_score = score;
        
        prev_comments = comments;
    }

    delay(100);
}
