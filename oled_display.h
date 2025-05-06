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

    // uint8_t x, y;

    // char str[6];

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

        display.clearDisplay();

        display.display();

        // calculating display position

        display.setTextSize(1);

        display.setTextColor(SH110X_WHITE);
    }

    // print given integer in the middle of the screen

    void print_reddit_data(int score, int comments, String title, bool is_score_up = false, bool is_comments_up = false, bool is_score_down = false, bool is_comments_down = false)
    {
        static uint8_t score_pt_count = 0, comments_pt_count = 0;

        static String score_pt = "", comments_pt = "";

        uint8_t x, y;

        int16_t _x, _y;

        uint16_t w, h;

        display.clearDisplay();

        if(is_score_up || is_score_down)
        {
            score_pt_count = 5;

            score_pt = is_score_up ? " +" : " -";
        }
        
        if(is_comments_up || is_comments_down)
        {
            comments_pt_count = 5;

            comments_pt = is_comments_up ? " +" : " -";
        }

        String score_str = "Score: " + String(score) + score_pt;

        String comments_str = "Comments: " + String(comments) + comments_pt;

        if(score_pt_count > 0)
        {
            score_pt_count--;
        }
        else if(score_pt.length() > 0)
        {
            score_pt = "";
        }

        if(comments_pt_count > 0)
        {
            comments_pt_count--;
        }
        else if(comments_pt.length() > 0)
        {
            comments_pt = "";
        }

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