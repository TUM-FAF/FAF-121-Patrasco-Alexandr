#Laboratory nr.1#

In this laboratory work we had to work with CLIs(Vim), VCS(Git) and secure shell. Since I had almost no prior experience with Git and no experience at all with CLI, it was quite frightening for me to see task list at first, but after some googlin' it happened to be not that hard, moreover these tasks kept me feeling motivated.

##Executed Tasks##

### Mandatory Tasks:
  - Connect to a remote server via SSH

For this task, initially I used  putty, but afterwards I connected using GitBashby running `ssh username@IP` line.

  - Initialize a repository on server

For this one, first of all I had to do `mkdir AlexPatrasco` - creating a new folder and `cd AlexPatrasco` to get into that folder, then run `git init`, which initializes an empty repository in given folder.

- Create a file in repository folder, write in your name, save it and commit it

For this task, I've run
-`touch file.txt` create file.txt
-`vim file.txt` open it in vim
-`i` enter insert mode
-`ESC` exit from insert mode
-`:wq` save and exit file.txt
-`git add file.txt` track file.txt
-`git commit -m "message"` commit

### Tasks With Points:
  - Connect to server using public key (1 pt)
To get this task done, I had to generate a RSA key pair by running `ssh-keygen - t rsa` then in order to append my public key to `authorized_keys` I had to run `cat ~/.ssh/id_rsa.pub | ssh user@ip "cat - >> ~/.ssh/authorized_keys"`, which pipes contetnts of id_rsa.pub into authorized_keys on server.

  - Create 2 more branches with at least one unique committed file per branch (1 pt)

This was done by running `git branch <branch_name>`, and then `git checkout <branch_name>` to switch between branches. Files were created using command `touch` then saved and commited.

  - Set a branch to track a remote origin on which you are able to push (ex. github, bitbucket or a custom server) (1 pt)

 `git remote add origin git@github.com:AlexPatrasco/IDE-Labs.git` add a remote origin
 `git push -u origin master` pushing commits
  - Reset a branch to previous commit, reset a branch to some specific commit (1 pt)
  `git reset --hard HEAD^` reset to previous commit
  or run `git log` then copy id and use it instead of HEAD^, to reset to some specific commit
  - Restore a reset branch back to its previous state (1 pt)
Here I used `git reflog` and copied id of the coomit I wanted to restore then using it in `git reset --hard ID`
  - Create a VCS hook (1 pt)
First, I had to access `~/.git/hooks` then I did `touch post-commit`
and `vim post-commit` and adding
-`#!bin/sh`
-`echo "wow, much message, very commit" >&2`
-`exit 1`, save and quit and then in the same folder `chmod -x post-commit` to apply it. This hook will show a message after every commit.
  - Make your CLI text editor to highlight code (1 pt)
Since Vim has a built-in syntax highlighter it was just a matter of finding command, moreover it's turned on by default, but can be switched by using `:sy[ntax] on/off`.
  - Create a VCS alias (1 pt)
  I ran `git config --global alias.undo 'reset --soft HEAD^'`, which resets current branch to previous commit by running `git undo`.

  - Create your own server (ex. virtual machine) (2 pt)
For this task I had to use a virtual machine with Ubuntu.
In ubuntu i ran several commands:
-`sudo apt-get install openssh-server`
-`sudo service ssh start`
-`ifconfig`. 
The first one installs OpenSSH, the second is for starting the server and the third is for getting the ip.
Then on Windows I ran GitBash and typed in `ssh ubuntu_login@ip` and been able to connect to the server using Ubuntu login and password.

##Conclusion
By performing these tasks we've been able to widen our knowledge in using git and CLI which may come in handy, since CLIs provide much more flexibility then GUI. The tasks were basically not hard, yet challenging and requiring ability to seek and find.
