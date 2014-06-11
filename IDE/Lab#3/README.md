##Laboratory Work 3##

###Tools Used and Tasks###
- Eclipse

Mandatory Tasks:
  - Study design guidlines for any mobile OS ([Android](https://developer.android.com/design/index.html), [iOS](https://developer.apple.com/library/ios/documentation/userexperience/conceptual/MobileHIG/index.html), [Windows Mobile](http://dev.windowsphone.com/en-us/design))
  - Create a mobile app and launch it on emulator/simulator. Your app should have at least 3 element (ex. button, textarea, statusbar...) and one action (ex. clicking on a button will trigger a popup)

Tasks With Points:
  
  - Install your application on a mobile phone. It should have somewhere your full name (on main screen, in settings...) (2pt)
  - Create 3 different views (ex. one with a list of some element, one with some settings and one with application description) (2pt)
  - Debug an application. At some point you'll have bugs (ex. null pointer exception). Set breakpoints and/or watchers. Find out buggy variables. (1pt)
  - Use a hardware device for testing and debugging (1pt)
  - Create a responsive layout (1pt)
  - _Mention your own tasks that you did and claim points for them (max of 5 pt in total)_(Added audio playback)

###Android App###

During this lab I created a todo list app with some extra features.
The application possesses possibilities to create todo lists, has a dialog box triggered by button click and provides playback of audio, if the user feels bored by lists.
![App itself](http://i.imgur.com/e6ZuxJT.png?1)
For these purposes I used AlertDialog, ListView, Button, EditText, MediaPlayer, ArrayAdapter classes.