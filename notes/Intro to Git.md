# Intro to Git

Git is a distributed version control system.  It records changes to the files it
tracks,  so you can always go back  to an older version.  Its distributed nature
makes it easy for  multiple people to collaborate  on a project,  even without a
centralized server.  And it supports multiple "braches" of history  for the same
files,  allowing you to keep a stable `master` branch  while working on multiple
features and bugfixes at the same time, each in their own branch.

Git is normally used to track changes to  source code,  and that's what we'll be
using it for in this class. All your assignments - even the lecture notes - will
be distributed via Git, so you'll want to be familiar with it.  If you're new to
Git, you may find these helpful:

- Getting Set Up with Git\
  https://help.github.com/en/github/getting-started-with-github/set-up-git
- The GitHub Git Cheatsheet\
  https://education.github.com/git-cheat-sheet-education.pdf
- Yet Another Git Cheatsheet\
  https://xavierholt.github.io/cheatsheets/git.html


## Repositories

A  **repository**  -  usually shortened to  **repo**  -  is a  collection of Git
objects.  On your computer,  a Git repo is simply a folder  with a `.git` folder
inside it. This `.git` folder contains the entire history of the repo; the other
files can be automatically modified to match any snapshot in the history.


## Commits

A **commit** is the basic unit of Git.  Each commit represents a snapshot of the
files in the repo. Each commit has one or more parent commits, and describes how
to transform the state described by its parents into a new state. The commits in
a repo are all linked together, forming a directed acyclic graph.

A regular commit  has one parent.  It describes a set of changes  that should be
applied on top of its parent commit to bring the repo to a new state.  A **merge
commit** has  multiple  parents,  and describes how to  merge  the states of its
parents into a single state.

All commits are uniquely identified by a hash of their data.


## Tags

Commit hashes aren't great names. They're hard to remember.  So Git lets you add
**tags** to give commits  human-friendly names.  For example, if you used commit
`944d758` to build version 2.3.1 of your program, you could use a tag to make it
easier to find:

```sh
git tag v2.3.1 944d758
```

Tags aren't used too much in practice - mostly just for tagging releases like in
this example.  But they're the basis for branches, which are used all the time.


## Branches

A **branch** is like a tag in that it's a name for a commit.  But branches don't
always refer to the same commit - they update to always point to the most recent
commit to that branch.

Git always  keeps track of your  current branch.  Any commits  you make have the
most recent commit to that branch as a parent, and then the branch is updated to
point to your new commit.

You'll typically have  one branch called  `master`  that only contains finished,
working code.  Every feature  you work on gets its own  "feature branch."  These
feature branches can contain code in progress. It doesn't even need to compile -
since it's on  a separate branch, it won't interfere with anything else.  Once a
feature is complete, it'll get merged into the `master` branch.


## Remotes

A  **remote**  is another copy of the same Git repo on a different machine.  Git
keeps  track of these  so it's easy to share  your changes.  You can  `git pull`
changes from a remote, and `git push` your local changes to a remote if you have
write access.

You'll typically have one remote that you keep in sync with your local work. The
convention  is to call it  `origin`.  If there's  another copy  of the same repo
that's more official  than yours - maybe your repo is a fork of a popular repo -
then you'll typically have a remote for it as well, called `upstream`.

In this class you'll have your GitHub repo as your `origin`,  and the class repo
as your `upstream`. This makes getting the lecture notes and assignments as easy
as running:

```sh
git pull upstream master
```


## Tracking

In addition to  keeping track of your  current local branch, Git will also track
associations between your local branches and remote branches.  Usually any local
branch will be associated with a branch of the same name at the `origin` remote.
This lets you sync changes with that branch simply by running:

```sh
git push # to upload your local commits, or
git pull # to download commits from your remote
```

It's also possible to interact with arbitrary remote branches:

```sh
git push remote-name branch-name
git pull remote-name branch-name
```

But this is a little dangerous,  as it makes it very easy to  create an unwanted
merge commit by typing the wrong remote or branch name, so you should prefer the
shorter versions whenever possible.
