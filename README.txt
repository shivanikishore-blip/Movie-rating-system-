MOVIE RATING SYSTEM - FRONTEND + C BACKEND

Project structure
-----------------
frontend/
  index.html   - User interface
  style.css    - Page design
  script.js    - Sends the rating to the backend
backend/
  rate.c       - C CGI program; saves ratings and calculates average

REQUIREMENTS
------------
1. Apache web server with CGI enabled (XAMPP can be used on Windows).
2. GCC compiler (MinGW GCC on Windows, or GCC on Linux).

SETUP (XAMPP on Windows)
------------------------
1. Install and open XAMPP. Start Apache.
2. Copy the contents of the frontend folder into:
   C:\\xampp\\htdocs\\movie-rating\\
3. Create this folder if it does not exist:
   C:\\xampp\\cgi-bin\\
4. Compile backend/rate.c using MinGW GCC:
   gcc rate.c -o rate.cgi.exe
5. Copy rate.cgi.exe into C:\\xampp\\cgi-bin\\
6. Make sure Apache has CGI enabled. In the Apache configuration,
   enable the CGI module and a ScriptAlias for /cgi-bin/ if they
   are not already enabled. XAMPP commonly provides this configuration.
7. Open:
   http://localhost/movie-rating/

IMPORTANT
---------
The CGI executable must be allowed to run by Apache. The ratings.txt file
is created in the CGI program's working directory. Give Apache write
permission to that directory. If Apache cannot write there, change
DATA_FILE in rate.c to a writable absolute path and recompile.

LINUX QUICK SETUP
-----------------
1. Install Apache and GCC.
2. Enable CGI (for example, a2enmod cgi on Debian/Ubuntu) and restart Apache.
3. Compile:
   gcc rate.c -o rate.cgi
4. Copy rate.cgi into the configured CGI directory (often /usr/lib/cgi-bin/)
   and make it executable:
   chmod +x rate.cgi
5. Copy frontend files into the web document root, preserving the
   frontend files at the /movie-rating/ URL used by script.js.
6. Ensure the CGI working directory is writable for ratings.txt.

HOW IT WORKS
------------
1. The user selects a rating from 1 to 5.
2. JavaScript sends it to the C CGI backend.
3. C validates and stores the rating in ratings.txt.
4. C calculates the average of all stored ratings.
5. The frontend displays the average and total number of ratings.

NOTE
----
This is a simple academic mini-project. It stores ratings in a local text
file and is intended for a local classroom demonstration, not production use.
