#include<limits.h>
#include"oled_display.h"
#include"buzzer.h"

long score = 0;

long comments = 0;

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
            an app in the pc writes two bytes of serial data (temp) and a string
            describing the weather, which is read in the same order as they were
            written
        */

        /*
            format of serial data: "{score},{comments},{title}\n
        */

        score = Serial.parseInt();   // reading integer

        comments = Serial.parseInt();   // reading integer

        Serial.read();  // extracting extra ','

        title = Serial.readStringUntil('\n'); // reading a string
        
        title.trim();

        if(initialized && prev_comments < comments)
        {
            ping();
        }

        OLED.print_reddit_data(score, comments, title.substring(0, 15) + "...", initialized && prev_score < score, initialized && prev_comments < comments, initialized && prev_score > score, initialized && prev_comments > comments);

        prev_score = score;
        
        prev_comments = comments;

        initialized = true;
    }

    delay(100);
}
