ECHO OFF

@REM this batch file just activates the virtual environment called ".vemv" and 
@REM runs the script in background

call .venv/scripts/activate.bat

start pyw reddit_scrapper.py