# FAQ

 * I want to join the team. What must I do?
 * How to contact the team?
 * How is Discord used?

## I want to join the team. What must I do?

Awesome!

To join the team, you will need:

 * To have a desktop or laptop computer
 * To have a GitHub account (free)
 * To have a Discord account (free)
 * Be able to speak English
 * Be able to type

Just contact one of the members (see 'How to contact the team?')!

Things you may wonder:

 * You do not need to know C++: the team will teach you
 * You will not need to be present every meeting. It is appreciated to let
   the team know you will be absent. You do not need to give a reason for
   your absence: we trust you do something useful/fun :-)
 * There is no 'homework': we work only when we can and want to

## Who is in the team?

Active team members have their own git branch (whatever that is),
so [https://github.com/tresinformal/game#game](https://github.com/tresinformal/game#game)
gives a nice overview of all team members.

## How to contact the team?

 * Send Richel (or any team member) a Discord Friend Request: `richelbilderbeek#9002`
 * Send Richel (or any team member) an email: `richel@richelbilderbeek.nl`
 * Post at the GitHub Issue [Become a tresinformal team member](https://github.com/tresinformal/game/issues/1)

## How is Discord used?

We develop our game, while chatting on Discord.

![](pics/discord.png)

To join, send Richel (or any team member) a Discord Friend Request: `richelbilderbeek#9002`.
He/she will add you to the `tresinformal` Discord server.

Our Discord server has mostly obvious rules that follow from the categories:

 * 4x 'Group Rooms': rooms for duos/triplets, open for questions
 * 2x 'Offices With An Open Door': single room, open for questions
 * 2x 'Offices With A Closed Door': single room, please do not disturb

One rule that needs to be written down, however, is that members 
are never allowed to silence another member, not even as a joke.

See this video for an introduction: [YouTube](https://youtu.be/zyn5VyNjz5I) [download (.OGG)](http://richelbilderbeek.nl/dutch_by_kids_students.ogv)

## I am a newbie developer. What must I do?

Welcome to the team! Here is a more-or-less-chronological (i.e. if you
get stuck, start working on the next one) list of what to do:

 * [Become a tresinformal team member](https://github.com/tresinformal/game/issues/1)
 * [Install Qt Creator and SFML](https://github.com/tresinformal/game/issues/16)
 * [Modify README.md on master branch](https://github.com/tresinformal/game/issues/19)
 * [Make a branch for yourself via the GitHub web interface](https://github.com/tresinformal/game/issues/47)
 * [Modify README.md on your local harddrive on your own branch](https://github.com/tresinformal/game/issues/48)
 * [Add your branch's badges to the README.md](https://github.com/tresinformal/game/issues/87)

When you feel comfortable with the workflow, you become a junior developer!

## I am a junior developer, what should I do?

Junior developers are those that feel comfortable enough with the workflow
to write their own tests. Next to programming, juniors will
occasionally teach newbies.

You will be practicing:

 * Team development workflow
 * git an GitHub
 * C++ and SFML entry level development

Start from an idea of a visible change in the game,
for example, 'The players should be able to do a little dance'.
Create an Issue for that and assign yourself to it
Work from big to small, in TDD fashion.

For a big Issue:

 * Postpone the hard work, create simpler and simpler tests, 
   until a test can be fixed by a small Issue.
 * Do push the #IFDEF-ed tests

For a small Issue:

 * Write a test that breaks the build
 * Make the test pass
 * Push to GitLab

Golden rules:

 * Whatever you work on, always be assigned to an Issue
 * Whatever code you develop, always be working to fix a test,
   unless you work on graphics
 * If all tests pass, we are -by definition- happy :)

## I am a medior developer, what should I do?

A medior developer 

 * writes tests and creates Issues for juniors and themselves
 * does code reviews
 * works on more complex issues, such as improving the architecture of
   the code or improving the continuous integration tools (whatever those are :-))
 * see the bigger picture of the code and the team.

You know what to do :+1:

