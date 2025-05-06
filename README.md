# Reddit Post Monitor (Arduino + Python)

A small desktop companion that shows live stats of your Reddit post on an OLED screen, using an Arduino Pro Micro and a Python script.

![IMG_20250506_230831](https://github.com/user-attachments/assets/8c2c894d-d41e-4944-a10e-a3bdb4b23da3)

---

## ✨ What It Does

This project tracks a specific Reddit post and displays its stats in real time. It shows:

* A portion of the post title
* The current score (upvotes – downvotes) (with a **+** or **–** to indicate recent changes)
* Number of comments (also with a **+** or **–** change indicator)
* A **buzzer sound** when someone comments

---

## 🔧 How It Works

A Python script fetches Reddit post data once every second using the **PRAW** library (Reddit API wrapper). It sends the data to an **Arduino Pro Micro** through serial communication using the **pySerial** library.

The Arduino receives the data and displays it on a **1.3" OLED screen**. It also uses an **active buzzer** to play a short ping sound whenever there’s a new comment.

---

## ⚙️ Key Features

**Script**

* Runs inside a venv virtual environment
* A `.bat` file is included to activate the virtual environment and run the script (in background) easily
* Checks for USB device (port) availability before starting
* Runs an infinite loop, that fetchs and sends Reddit post data to the Arduino every second
* Breaks out of the loop and Auto-terminates if the Arduino is disconnected or internet connection is lost

**Sketch**

* Receives serial data from the python script and displays it
* Detect if the score or comment count is going up or down and indicates that with **+** (up) and **-** (down) sign
* Pings the buzzer if comment count is going up

---

## 🧰 What You Need

**Hardware:**

* Arduino Pro Micro
* 1.3" 128x64 I2C OLED Display (SH110X-based, Monochrome)
* Active buzzer

**Python Libraries:**

* `praw`
* `pyserial`

---

## 🚀 Getting Started

1. **Clone the Repo**

   ```cmd
   git clone https://github.com/Tushar625/reddit_display
   ```

2. **Upload Arduino Sketch**
   
   Move the downloaded folder containing this repository to the `Arduino` folder inside the `Documents` folder (Windows). Now, this project should appear in the **SKETCHBOOK** tab in Arduino IDE. Upload this into your Arduino.

3. **Set up the Python Environment**

   The Python Environment is created inside `python script to access reddit api` folder. Create a `venv` virtual environment inside it and install the dependencies. Open `Command Prompt` inside this folder and run,
   
   ```cmd
   python -m venv .venv
   .venv\Scripts\activate
   pip install -r requirements.txt
   ```

4. **Configure Reddit Access**

   Create Reddit API credentials

   https://youtu.be/0mGpBxuYmpU?si=fChEYfVl4QntOivs

   Add your Reddit post URL and Reddit API credentials (client ID, secret, etc.) in the text file accessed by the python script (check out the comments in this script for more details).

5. **Run the Script**
   
   Plug in the Arduino to a USB port, activate the virtual environment and run the script, you can also Double-click the `.bat` file to do the same, though it will run the script in background.

---