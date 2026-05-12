# Balatro-Like Poker Roguelike

A terminal-based (CLI) poker roguelike game developed in C++, heavily inspired by Balatro. The core experience revolves around building a scoring engine from limited random cards, where upgrades make ordinary poker hands explode into massive high scores.

## Project Overview

- **Language:** C++ (Pure Object-Oriented Programming)
  - No procedural globals or free functions for business logic.
  - All behavior encapsulated within classes.
  - Polymorphism via virtual methods; composition over inheritance for modifiers.
- **Runtime:** Command-Line Interface (CLI)
  - Text-based interaction (numbered menus, typed input).
  - No graphics libraries or GUI frameworks.

## Core Loop

1. Draw hand (max 8 cards).
2. Player selects up to 5 cards.
3. Evaluate poker hand type.
4. Calculate base chips and mult.
5. Create `ScoreContext`.
6. Apply Joker/modifier effects.
7. Compute final score (chips × mult).
8. Update round score and check against blind target.
9. Discard and redraw.
10. Gain reward on blind clear.
11. Upgrade build (Shop).
12. Face harder blind.

## Genre Invariants

To maintain the Balatro-like feel, the following rules are non-negotiable:
- Player makes discrete scoring decisions.
- Poker hands are evaluated by standard rules.
- Score comes from a readable `chips × mult` calculation.
- Random card draw creates uncertainty.
- Upgrades (Jokers/Planet Cards) modify future scoring potential.
- Runs are built through repeated risk/reward choices.

## Team Structure & Architecture

The project is split into two strict domains, managed by two programmers.

### Programmer A: System Programmer (Core Engine)
**Domain:** `src/system/`
- **Card & Deck System:** `Card`, `Deck`, `DrawService`
- **Evaluation System:** `PokerHandEvaluator`, Chain of Responsibility Checkers
- **Scoring System:** `HandScoreTable`, `ScoringRule`, immutable `PlayedHandResult`
- **Blind System:** Targets, win/loss conditions
- **Run System:** `GameManager`, CLI rendering, state machine

### Programmer B: Mechanic Programmer (Game Feel & Content)
**Domain:** `src/mechanic/`
- **Hand Selection:** Player input validation
- **Joker System:** Joker effects modifying `ScoreContext`
- **Reward System:** Shop, Planet Cards, economy

### Shared Interface Boundary
System and Mechanic domains interact *only* through specific interfaces:
- `ScoreContext`: Mutable state for Jokers to modify (chips/mult).
- `PlayedHandResult`: Immutable base score and hand type.
- `Joker`: Abstract base class implemented by Mechanic, executed by System.

## Architecture Data Flow

```text
Deck
  └─► DrawService
        └─► HandState
              └─► ChosenHand
                    └─► PokerHandEvaluator   [Chain of Responsibility]
                          └─► ScoringRule    [Data-Driven]
                                └─► PlayedHandResult  [immutable]
                                      └─► ScoreContext
                                            ▲
                                      JokerManager    [Observer]
                                            │
                                      FinalScore  (chips × mult)
                                            └─► BlindManager
                                                  └─► RoundState
                                                        └─► RewardManager
```
