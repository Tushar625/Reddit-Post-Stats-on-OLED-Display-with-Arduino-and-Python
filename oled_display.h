// this file provides an object for easy handling of oled display

#ifndef OLED_DISPLAY_HEADER
#define OLED_DISPLAY_HEADER

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

using namespace std;

#define I2C_ADDRESS_OLED 0X3C

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64

// display and ui class

class OLED_DISPLAY
{
    Adafruit_SH1106G display;

    public:
    
    OLED_DISPLAY() : display(SCREEN_WIDTH, SCREEN_HEIGHT)
    {}

    // call the following function from setup()

    void setup()
    {
        // initialize and set up our display

        delay(250); // wait for our display to power up

        display.begin(I2C_ADDRESS_OLED);

        display.setContrast(10);  // dim the display

        display.clearDisplay(); // cleanup the screen

        display.display();  // refresh the screen, so, it's nice and clean

        // setting text properties

        display.setTextSize(1);

        display.setTextColor(SH110X_WHITE);
    }

    /*
        this class is ued by the function below to display a '+' or '-' sign on the screen 
        to indicate if teh data has increased or decreased
    */

    class status
    {
        uint8_t count;  // for how many iteration we display the sign

        String str; // to store the sign string

        public:

        status() : count(0), str("")
        {}

        // ture means up, false means down

        void set(bool up)
        {
            count = 5;  // initializing iteration counter to count for 5 iterations

            // '+' sign for up, '-' sign for down

            str = up ? " +" : " -";
        }

        // get the sign, it also updates the iteration count silently

        const String& get()
        {
            if(count != 0)
            {
                count--;
            }
            else if(str.length() > 0)
            {
                str = "";   // empty the the string as counter has expired
            }

            return str;
        }
    };

    /*
        get some data about a reddit post to display in the screen

        score: no. of upvotes - no. of downvotes

        comments: no. of comments

        title: title of the post

        score_trends: -1 (score is decreasing) 0 (no change) 1 (increase)

        comments_trends: -1 (comments is decreasing) 0 (no change) 1 (increase)
    */

    void print_reddit_data(long score, long comments, String title, int8_t score_trends = 0, int8_t comments_trends = 0)
    {
        static status score_status, comments_status;

        uint8_t x, y;

        int16_t _x, _y;

        uint16_t w, h;

        // updating status according to score

        if(score_trends)
        {
            score_status.set(score_trends == 1);
        }
        
        if(comments_trends)
        {
            comments_status.set(comments_trends == 1);
        }

        // makes the score and comments strings and add '+' or '-' after to indicate the trends

        String score_str = "Score: " + String(score) + score_status.get();

        String comments_str = "Comments: " + String(comments) + comments_status.get();

        // cleaning the display

        display.clearDisplay();
        
        // placing score string

        display.getTextBounds(score_str, 0, 0, &_x, &_y, &w, &h);

        x = SCREEN_WIDTH / 2 - w / 2;

        y = SCREEN_HEIGHT / 2 - h - 2;

        display.setCursor(x, y);

        display.print(score_str);

        // placing comments string

        display.getTextBounds(comments_str, 0, 0, &_x, &_y, &w, &h);

        x = SCREEN_WIDTH / 2 - w / 2;

        y = SCREEN_HEIGHT / 2 + 2;

        display.setCursor(x, y);

        display.print(comments_str);

        // placing post title

        display.setCursor(0, 0);

        display.print(title);

        display.display();
    }
} OLED; // display and ui object

#endif // OLED_DISPLAY_HEADER