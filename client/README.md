# Purpl.
A simple instant messaging client.

# v0.11:
As promised, I will be documenting my progress more thoroughly from now on. Here we go.

**November 20, 2017**
 - Unfortunately I've had a ton of coursework this semester, so I've only been able to work on Purpl. very sporadically.
 - I've been thinking about how I'll be implementing a GUI with the code I've already written. At this point, Purpl. is inherantly a console application, so i may need to rewrite some code to make it less console-dependant. 
 - I know that GUI implementation in C# is pretty straightforward (especailly with Visual Studio), and I know that there are ways to use my preexisting C++ code in C#, so I'm going to be using that as a starting point.
 - I'm thinking I can probably build a .dll file (or maybe a .lib file) from my code, and import that file into a C# program containing the GUI. We'll see how that works out.
 
**November 28, 2017**
 - This is turning out to be a bit more complicated than I thought. I can't for the life of me figure out a way to use my C++ code in C# without making so many changes to my code that I might as well start over from scratch, and without having my code looking like a complete mess.
 - I've been doing a lot of research on how to best approach this, and I'm starting to think I went about it all wrong, considering there are *many* simpler methods out there. The problem with those methods is that they all involve starting over from scratch. However, considering Purpl. is still in its very early stages, starting over wouldn't be that big of a setback.
 - Right now, I'm leaning towards using JavaScript and HTML5 with GitHub's Electron module, similar to how Discord was implemented. Right now, I have very little knowlege of JavaScript and HTML5, so I would need get more exposure to them before I decide whether or not I want to go this route.
 
**December 17, 2017**
 - Now that the semester is over, I have much more time to work on Purpl. Hopefully, progress shall be made much more swiftly from this point on.
 - I've been playing around with JavaScript, HTML5, and Electron, and I've decided that this is, in fact, the route I want to go. I will also be using Node.js for server-side code execution, as well as CSS for stylizing.
