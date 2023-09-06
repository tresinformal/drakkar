# 20220802_tresinformal_evaluation

## Questions and answers

### What do you think the people of the team do well, and should keep doing?

 * It's always a pleasure to work with everyone in the team!
 * Help each other and do not prioritize making progress over helping
 * Yes, they are all kind and patient.

### What do you think the people of the team could do better?

 * It would be good practice to make sure your branch is ready to work 
   on (no uncommitted stuff, unresolved merged conflict etx.) 
   before joining the session. 
   We sometimes lose a lot of time to these issues instead of programming. 
 * Focus on merging to keep project cohesion
 * I know the better way to master something is to start doing it, 
   but I do think some clear and basic guides matter. 

### What do you think Claudio does well, and should keep doing?

 * I think he is really nice.
 * n/a

### What do you think Claudio does could do better?

 * n/a

### What do you think Richel does well, and should keep doing?

 * He is there to help and structure the work, he is very good at teaching
 * He likes encouraging people, I really like it.

## What do you think Richel could do better?

 * Do not talk about programming during the breaks

## What do you think Theo does well, and should keep doing?

 * He is really nice.
 * He has ideas and he pursues them

## What do you think Theo could do better?

 * [nothing]

## What do you think is good about the workflow of the team, and should be preserved?

 * Stick to the time, that's perfect.
 * Merging often

## How do you think the workflow of the team can be improved?

 * Perhaps vote on task force so that we can focus energy on few at a time

## What do you think is good about the monthly mob programming sessions?

 * I love that we can interrupt to ask questions, 
   and I feel the frequency of the sessions is ideal.
 * Very good
 * I don't know what is the monthly mob programming sessions, I can't tell.

## How do you think the monthly mob programming sessions can be improved?

 * They are very good
 * Ask members to provide Richel with ideas of issues / topics 
   to work on a bit ahead (1 hour before?) of the session? 
   Ofc Richel should always be free to decide what he will work on :)

## What do you think is good about the monthly C++ Core Guideline of the Month?

 * Everything
 * Straight to the point
 * Is it the 5 minutes by Richel before we start working. 
   If it is, then I think it's too short.

## How do you think the monthly C++ Core Guideline of the Month can be improved?

 * Maybe we could keep track of the guidelines that were 
   discussed in the past somewhere in a .md or a Discord channel? with links to the corresponding sections in the book.
 * Perhaps doing some live programming with a minimal example 
   (also easy to understand by newbies)
 * I think the time for it can be prolonged.

## What do you think is good about the monthly Project Update?

 * I like to keep in touch with part of the project 
   that I do not work on
 * Don't know what the monthly project update is.

### How do you think the monthly Project Update can be improved?

 * There should be some minimal preparation so that it can truly benefit team members

### What do you think is good, but not covered here?

 * Task forces

### How do you think can be improved, but is not covered by the other questions?

 * Have some kind of roadmap and focus/priority
 * Maybe it would be time to settle on a name for the game? 
   Also, we should start a pyramid scheme to get more people in the team

### Do you think we should start on a new game after the Summer holiday?

 * No, I would like to continue working on this game
 * No, I would like to continue working on this game
 * No, I would like to continue working on this game

### Do you intend to continue with tresinformal after the Summer holiday?

 * Yes
 * Yes
 * Yes

### What do you enjoy about this type of this evaluation?

 * Can do it at my own time
 * I enjoy that it's (only?) as long to fill as we want it to be, 
   and that there is room to answer extra questions or not answer some of them
 * Asking what can be improved. I don't have any complaints about it, 
   but it's good to see that the group is always preparing to be improved. :) 

### How would you have preferred to do such an evaluation?

 * preferred to do it face to face, one person at a time, less anonymous
 * this way is fine.

## Interpretation by Richel

Having only three survey results from a team of ten is a problem,
as it can be interpreted both positive ('everything is good already')
and negative ('it is not worth answering anyways'), where the goal
of the survey is to remove the need of such interpretation.
Next time, the survey will be under tresinformal time,
like we did last year.

One member would enjoy 'clear and basic guides' to 'master something'.
I am unsure what is meant here. It could be about gettig a
better `git` guide [again](https://github.com/tresinformal/game/issues/342).
I will add a ['How to do TDD'](https://github.com/tresinformal/game/issues/571) guide.

I think 'vote on task force so that we can focus energy on [a] few [tasks] at a time'
is interesting. I will try the following: (1) first person that wants to
lead a task force, gets it (2) next persons fill up the task force and
(3) if all task forces are full, add another. I like it 
because (1) it rewards people being first, and (2) as the same people
tend to be the first, that same early bird will focus energy on the
most important task at that time.  If this theory fails, I will vote.

However, having a roadmap seems like an even better idea.
Let's get some experience with making it!

Regarding the mob programming, I wonder why '[asking] members to provide Richel 
with ideas [...] to work on [before] the session [...]' is suggested,
as (1) mob programming is after the first break, so team members have one
hour to suggest topics, and (2) I got most suggestions indeed at the start
of a tresinformal meeting and (3) the mob programming is monthly,
hence already announced weeks ahead. Due to this, I feel this already OK. I can
imagine that first hour of tresinformal can be a distraction from suggesting
those ideas, e.g. when teaching a new member, but a direct message to me,
or an Issue on GitHub would both work. I hope to find out what this feedback
entailed exactly.

It is indeed time to settle on a name.
I suggest the deadline 10th of septemer, as that is exactly 3 years since the
first commit.

```
richel@N141CU:~/GitHubs/game$ git log --format="format:%ci" --name-only --diff-filter=A README.md
2019-09-10 09:03:28 +0200
README.md
```

I agree it would be great to get more members in. I assume we all do our best at that?
I will encourage the team. In Uppsala, we now have the OFOF rule, short 
for 'One Visit [by a new member], One Free [drink/beer for the recruiter]'.

The monthly events are appreciated.
The C++ Core Guideline of the Month is extended to 10 mins
and the discussed guidelines should be put online somewhere.

The monthly Project Update is appreciated and 
recommended to 'have some minimal preparation', 
so that it 'can truly benefit team members'.
I wish I had an idea what this benefit is.
The goal is to show the team other parts of the project they do not
work on, and this goals is reached for at least one team member (see this survey). 
From there on, I can only guess about the benefit.
My best guess is that the benefit would be to give an overview
of the project to see the bigger pictures (and thus, not getting lost).
Connecting the Project Update with a roadmap may fix that.

Actions

 * [T] Settle on a name of the game on september 10th
 * [T] Encourage the team to recruit members
 * [T] Fix the `git` guide, `https://github.com/tresinformal/game/issues/342`
 * [GD] Make a road map
 * [PU] Discuss the road map with the monthly project update
 * [CG] Keep track of the discussed C++ Core Guideline of the month
 * [R] The Core Guideline of the Month will be extended to 10 mins.
 * [R] Do next evaluation under tresinformal time
 * [R] Formalize: helping others goes first, then merging, then task force
 * [R] Formalize new workflow: task forces fill up until a new one is started
 * [R] 5 mins before end: let everyone push their work
 * [R] Add ['How to do TDD'](https://github.com/tresinformal/game/issues/571) guide
 * [R] Formalize OFOF rule in Uppsala
 * [R] Richel should not talk about programming during the breaks

Abbreviation|Full
---|--------------
R  |Richel
GD |Game Design team
PU |Project Update presenter
CG |C++ Core Guideline presenter
T  |Tresinformal
