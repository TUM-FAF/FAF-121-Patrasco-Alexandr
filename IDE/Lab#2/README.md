##Laboratory Work # 3 @ IDE##
This laboratory work had a purpose of making us acquainted with principles and mechanics of creating Graphical User Interfaces, as well as using Drag-and-Drop features of IDEs in order to perform this task.

We had to create an interface for Simulatron, an alien ship captured by earthlings and redesigned to capture aliens. I decided to execute alittle different task, I created a starship bridge, that would have basic functionality, i.e. Weapon control, Shields, Locking on target, Hyperjump and Cloaking.

In my application I used several types of WPF controls, such as:
1) Image (Pic of the Death Star)
2) ProgressBar (Chargers of various systems)
3) Button (Triggers for systems)
4) RadioButton (Group of weapons)
5) Label (Hat of the App)
6) Slider (Shields control)
###Tools used and points gained###
  - **Visual Studio**

  Mandatory Tasks:
  - Define 3 virtual tasks that you Simulatron is supposed to control
  - Create a GUI application with 5 standard controls (any child window control mentioned in book Windows Programming ed.5 is considered standard)

  Tasks With Points:
  - Add 3 non-standard controls (2pt)
  - Create a custom control (not existent in IDE) (2pt) (Gif usage)
  - Make controls to interact. At least 3 interactions (1pt) (Reset chargers, Charging chargers, play sound)
  - Create a _Reset_ button. On clicking this button all controls should go to their default state (1pt) (Reset Chargers)
  - Set a breakpoint in your application and check variables values at that moment of time (1pt)
  - _Mention your own tasks that you did and claim points for them (max of 5 pt in total)_(1) Used sound 2)Created design from a scratch 3)Used gifs )

###Functionality###

![The App](http://i.imgur.com/i2vjwTq.png)

Progress bars use timer to charge.
When the button "Add SWAG!" is pressed it plays a sound.
Fire button resets chargers of Weapons.
There's also .gif imagery implemented, for this I had to use external dependeny(WpfAnimatedGif), since by default WPF does not provide programmer with the possibility of using .gif. 