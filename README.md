# game

Branch     |[GitHub Actions](https://github.com/tresinformal/game/actions)                                       |[![Codecov logo](man/figures/Codecov.png)](https://www.codecov.io)
-----------|-----------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------
`master`   |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=master)   |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=master)](https://codecov.io/github/tresinformal/game/branch/master)
`develop`  |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=develop)  |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=develop)](https://codecov.io/github/tresinformal/game/branch/develop)
`claudio`     |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=claudio)     |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=claudio)](https://codecov.io/github/tresinformal/game/branch/claudio)
`clem`     |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=clem)     |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=clem)](https://codecov.io/github/tresinformal/game/branch/clem)
`kristiina`|![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=kristiina)  |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=kristiina)](https://codecov.io/github/tresinformal/game/branch/kristiina)
`pavel`    |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=pavel)    |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=pavel)](https://codecov.io/github/tresinformal/game/branch/pavel)
`oliver`    |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=oliver)    |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=oliver)](https://codecov.io/github/tresinformal/game/branch/pavel)
`richel`   |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=richel)   |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=richel)](https://codecov.io/github/tresinformal/game/branch/richel)
`sebastian`|![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=sebastian)|[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=sebastian)](https://codecov.io/github/tresinformal/game/branch/sebastian)
`swom`     |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=stefano)  |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=stefano)](https://codecov.io/github/tresinformal/game/branch/stefano)
`theo`     |![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=theo)     |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=theo)](https://codecov.io/github/tresinformal/game/branch/theo)
`christiaan`|![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=christiaan)   |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=christiaan)](https://codecov.io/github/tresinformal/game/branch/christiaan)
`yang`|![check](https://github.com/tresinformal/game/workflows/check/badge.svg?branch=yang)   |[![codecov.io](https://codecov.io/github/tresinformal/game/coverage.svg?branch=yang)](https://codecov.io/github/tresinformal/game/branch/yang)

 * Branches are ordered `master`, `develop`, then topic branches alphabetically

A video game, developed informally and professionally.

## Meetings

 * Date: Weekly, every Wednesday
 * Time: 17:00-19:00
 * On Discord, see [FAQ](faq.md)

We follow this timetable:

What             | Time
-----------------|------
Doors open       | 17:00
Lesson starts    | 17:15
Break time!      | 18:00
Lesson continues | 18:15
End of lesson    | 19:00

## Code of Conduct

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

In case it is undesirable to email Richel,
contact [Stefano 'swom' Tiso](https://github.com/swom).

## Game: 2D PvP chasing game

A game where you are on a 2D surface with heterogeneous characteristics, as different terrains, resources etc. You start with a very small particle-like character, as you play you can gather resources scattered around and increase your size/mass, the more you grow the more your options increase(you can change shape, what matter composes you etc.), other players roam around as you do increasing size and having more options as they progress. The goal is to chase and eliminate the other players. It would be good to have multiple conditions(you have to be bigger, you need to be made of a certain material etc.) you need to satisfy to be able to eliminate the other players.e.

Ideas:

Issue                                                 |Idea
------------------------------------------------------|------------------------
[221](https://github.com/tresinformal/game/issues/221)|-1. Rock-Paper-Scissor dynamics
[219](https://github.com/tresinformal/game/issues/219)|0. Food
[208](https://github.com/tresinformal/game/issues/208)|1. Stun
[209](https://github.com/tresinformal/game/issues/209)|2. Poison
[210](https://github.com/tresinformal/game/issues/210)|3. Regenerating walls
[212](https://github.com/tresinformal/game/issues/212)|4. Heal
[222](https://github.com/tresinformal/game/issues/222)|5. Targeting system
[223](https://github.com/tresinformal/game/issues/223)|6. Minimap

## [Installation](install.md)

See [install.md](install.md).

## Links

https://agar.io/, this game could give a good idea of how we would like this game to work. The game we think about though should allow more variation in determining how you grow and/or change shape, as well as could require different conditions than just being bigger than the other player to eliminate it.

## Short-term schedule

Next meeting:

Timespan    |Activity
------------|--------------------------------------------------------------------------
17:00       |Door opens
..          |Do Issues
17:45-18:00 |Break
..          |Do Issues

 * Note that `xx` and the other variables can be in range `00` to and including `59`. 

## Long-term schedule

Date       |Activity
-----------|--------------------------------------------------------------------------
2021-02-17 |practice git branching
2021-02-17 |fixing tests
2021-04-28 |merge to develop by code reviewed Pull Request
.          |pair programming
.          |move to C++14
.          |add clang tidy

## [Frequently Asked Questions](faq.md)

See the [FAQ](faq.md).

## Screenshots

Most recent at the top.

![](pics/20210728.png)

![](pics/20210922.png)

![](pics/20210527.png)

![](pics/20210512.png)

![](pics/20200517.png)

![](pics/20200326.png)

![](pics/20200219.png)

![](pics/20200110.png)

![](pics/20191209.png)

![](pics/20191206.png)

![](pics/20191205.png)

![](pics/20191122.png)

![](pics/20191115.png)

![](pics/20191024.png) 

![](pics/20190929.png)
Hi
