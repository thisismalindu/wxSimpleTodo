# Simple To Do App Made with wxWidgets
## Intro
My First attempt at wxWidgets. Really seems like a nice library to work with!

The App is simple. You can type in the thing you want to do and click add to add it to the list and then use Edit, Remove and Remove All buttons to those tasks. The app looks for a notes.txt file in the user's documents folder and creates if it's not available. All to-do items will be saved in this file when you exit the app. And all items will be retrieved from it at launch.

![Simple To-Do in Action](https://i.imgur.com/6UNNQ5m.png)


## Compiling
This project was made with Visual Studio 2022.
To compile this project you need the [wxWidgets](https://www.wxwidgets.org/) library.
All the code is inside App.cpp. Although this is not good practice I tend to put everything in one file if the app is too small. (this one is just 150 lines of code)
This Project is configured with static linking.
My Visual Studio installation is messed up and even VS doesn't know where the C++ library is. So I had to change the include directories manually. So please check them in project properties if you get any error when compiling.

If you have wxWidgets configured already, just copy everything from App.cpp and compile your project. 
For the icon, you need the resources.rc file and icon.icon file.
