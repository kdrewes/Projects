# About
 
 This program is designed to implement a library search
 engine.  The user has the ability to select from four different
 searches:
 
 • Call number
 • Title
 • Subject
 • Other
 
 The search engine will traverse through the following media types:
 
 • Book
 • Periodical
 • Film
 • Video
 
 and retrieve the user's desired results through several files:
 
 • book.txt
 • film.txt
 • periodic.txt
 • video.txt

For further questions please view instructions.  Thank you.

# Structure

This program is constructed using inheritance.  Media is the base class, and Book, Film, Periodical and Video are the subclasses.  This program is a C++ console app that loads library records from text files and lets users search by call number, title, subject, or other fields. Matching results are displayed using polymorphic methods defined in each subclass.

Media (Parent class) — Holds fields shared by every item (call number, title, subject, notes) and defines virtual methods so each media type can search and display it's individual content

Book, Film, Periodical, Video (Child classes) - Extend Media with type-specific fields and execute those virtual functions for their own data

Parse — Reads the text files, instantiates the media objects, handles the menu and user input, and routes each search to the correct subclass.

# TechStack

C++ - Programing language

XCode - IDE

# How to run

Please import code on your IDE


# Output

Library records are print out categorized by book, film, periodical and video
