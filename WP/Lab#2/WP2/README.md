#Laboratory Work №2#

The purpose of this laboratory work was for us to learn how to use scrollbars, listboxes, system menus, hotkeys and dialog boxes.

##Features##
![App window](https://raw.github.com/TUM-FAF/FAF-121-Patrasco-Alexandr/master/WP/Lab%232/WP2/Screenshots/Screen1.png)
![About Box](https://raw.github.com/TUM-FAF/FAF-121-Patrasco-Alexandr/master/WP/Lab%232/WP2/Screenshots/AboutBox.png)

In this app I have created one text field, 2 horizontal scrollbars (upper to change intensity of the color of the text field, lower to change width of the window), one vertical scrollbar for adjusting heigth, a listbox with possibility of choosing a font and a system menu. The menu has two submenus, first (File) includes options Move (move window to a random position) and Quit(exit), the second one provides option About, which leads to a dialog box. Moreover, I included vertical and horizontal scrollbars for adjusting position of visible region of the app as well as I binded two hotkeys: ALT+C(maximize window & change color of background randomly) and CTRL+X(quit).

##Encountered issues##
* When the cursor was hovering over listbox and some other child windows it was changing back to default, thus I had to solve this using `WM_SETCURSOR`.

* When I was trying to use .rc file for system menu, I couldn't link it to the app by `MAKEINTRESOURCE`, in order to solve it I named the menu as I named the app class.

* I had difficulties with "switching on" scrollbars, since they require quite a lot lines of code and it is easy to get lost in them in case of an error.

##Conclusion##
By performing this laboratory work I got skills and knowledge in creating hotkeys, adding system menus, creating dialog boxes (and processing them) as well as using scrollbars. But there is still a lot to learn, since I didn't adjust the app in the way that would hide scrollbars if they're "not needed". And it was very interesting to discover new features and opportunities.
